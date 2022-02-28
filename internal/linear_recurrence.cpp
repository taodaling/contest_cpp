#pragma once
#include "common.cpp"
#include "iter.cpp"
#include "polynomial.cpp"
namespace dalt {
//lr = {1, -c1, -c2, ...}
template <class Conv, class T, class I>
T KthTermOfLinearRecurrence(Vec<T> lr, Vec<T> prefix, I k) {
  static_assert(is_iter_v<I>);
  static_assert(is_convolution_v<Conv>);
  static_assert(is_same_v<T, typename Conv::Type>);
  static_assert(is_integral_v<typename I::Type>);
  using Poly = poly::Polynomial<Conv>;

  auto dfs = [&](auto &dfs, const Poly &P, const Poly &Q) -> T {
    if (!k.has_next()) {
      return P[0] / Q[0];
    }
    auto bit = k.next();
    Vec<T> neg_Q_data = Q.data;
    for (int i = 1; i < Size(neg_Q_data); i += 2) {
      neg_Q_data[i] = T(0) - neg_Q_data[i];
    }
    Poly neg_Q(Move(neg_Q_data));
    let AB = P * neg_Q;
    let QQ = Q * neg_Q;
    Vec<T> A;
    Vec<T> C;
    A.reserve((AB.rank() + 1 + 1) / 2);
    C.reserve((QQ.rank() + 1 + 1) / 2);
    for(int i = bit; i <= AB.rank(); i += 2) {
        A.push_back(AB[i]);
    }
    for(int i = 0; i <= QQ.rank(); i += 2) {
        C.push_back(QQ[i]);
    }
    return dfs(dfs, Poly(move(A)), Poly(move(C)));
  };
  let rank = Size(lr) - 1;
  Poly Q(Move(lr));
  Poly F(Move(prefix));
  Poly P = (Q * F).modular(rank);
  return dfs(dfs, P, Q);
}
} // namespace dalt
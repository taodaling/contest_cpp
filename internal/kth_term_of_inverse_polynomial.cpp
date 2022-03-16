#pragma once
#include "polynomial.cpp"
#include "function.cpp"
namespace dalt {
namespace poly {
// [x^k] P/Q 
// time complexity: O(M(Poly) n) where M(Poly) is the time taken to perform polynomial mutiplication
// consider from last bit to first bit
template <class Poly>
typename Poly::Type KthTermOfInversePolynomial(int n,
                                               const Indexer<int> &bit_indexer,
                                               const Poly &P, const Poly &Q) {
  static_assert(is_polynomial_v<Poly>);
  using T = typename Poly::Type;
  if (n == 0) { return P[0] / Q[0]; }
  auto bit = bit_indexer(n - 1);
  //assert(P.rank() <= 1 && Q.rank() <= 1);
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
  for (int i = bit; i <= AB.rank(); i += 2) {
    A.push_back(AB[i]);
  }
  for (int i = 0; i <= QQ.rank(); i += 2) {
    C.push_back(QQ[i]);
  }
  return KthTermOfInversePolynomial(n - 1, bit_indexer, Poly(Move(A)),
                                    Poly(Move(C)));
}
}  // namespace poly
}  // namespace dalt
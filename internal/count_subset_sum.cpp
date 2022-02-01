#pragma once
#include "iter.cpp"
#include "math.cpp"
#include "polynomial.cpp"
#include "function.cpp"
namespace dalt {
// reference: https://arxiv.org/pdf/1807.11597.pdf
// given |s| polynomial, F_i = c_i x^{s_i}+1
// Find F = F_1 * F_2 * ... * F_|S| % x^{n}
// - constraint: s[i] > 0
// - time: O(|s| + n\log n)
template <class Conv, class T = typename Conv::Type>
Vec<T> CountSetsetSum(const Vec<i32> &s, const Indexer<T> &c, i32 n) {
  static_assert(is_same_v<typename Conv::Type, T>);
  Vec<T> cnt(n);
  for (auto x : s) {
    if (x < n) {
      cnt[x] = cnt[x] + T(1);
    }
  }
  Vec<T> log(n);
  Vec<T> inv_buf(n);
  auto inv = InverseBatch(
      Range<i32>(0, n - 1).iter().map(ConstructorMapper<i32, T>()).to_vec());
  for (i32 i = 1; i < n; i++) {
    T prod = T(1);
    T x = c(i);
    for (i32 j = 1, ij; (ij = i * j) <= n; j++) {
      prod = prod * x;
      T inv_j = inv[j];
      T contrib = inv_j * cnt[i] * prod;
      if ((j & 1) == 0) {
        contrib = T(0) - contrib;
      }
      log[ij] = log[ij] + contrib;
    }
  }
  using Poly = poly::Polynomial<Conv>;
  Poly exp = Poly(log).exp(n);
  auto ans = Move(exp.data);
  ans.resize(n);
  return ans;
}
} // namespace dalt
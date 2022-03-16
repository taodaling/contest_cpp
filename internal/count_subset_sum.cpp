#pragma once
#include "function.cpp"
#include "iter.cpp"
#include "polynomial.cpp"
#include "mod_inverse.cpp"
namespace dalt {
namespace poly {
// reference: https://arxiv.org/pdf/1807.11597.pdf
// given |s| polynomial, F_i = x^{s_i}+1
// Find F = F_1 * F_2 * ... * F_|S| % x^{n}
// - constraint: s[i] > 0
// - time: O(|s| + n\log n)
template <class Conv, class T = typename Conv::Type>
Vec<T> CountSetsetSum(const Vec<i32> &s, i32 n) {
  static_assert(is_same_v<typename Conv::Type, T>);
  Vec<T> cnt(n);
  for (auto x : s) {
    if (x < n) {
      cnt[x] = cnt[x] + T(1);
    }
  }
  Vec<T> log(n);
  Vec<T> inv_buf(n);
  auto inv = math::InverseBatch(
      Range<i32>(0, n - 1).iter().map(ConstructorMapper<i32, T>()).to_vec());
  for (i32 i = 1; i < n; i++) {
    for (i32 j = 1, ij; (ij = i * j) <= n; j++) {
      T inv_j = inv[j];
      T contrib = inv_j * cnt[i];
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
}  // namespace conv
}  // namespace dalt
#pragma once
#include "common.cpp"
#include "pentagonal_number.cpp"
#include "polynomial.cpp"
namespace dalt {
namespace math {
// verified by: https://judge.yosupo.jp/problem/partition_function
// ret[j] = way of (a1,...,an) where \sum_i i*ai = j
// time complexity: O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>> PartitionNumber(
    int n) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  auto inv = Poly(PentagonalNumber<T>(n + 1)).inverse(n + 1);
  auto vec = Move(inv.data);
  vec.resize(n + 1);
  return vec;
}
}  // namespace math
}  // namespace dalt
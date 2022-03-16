#pragma once
#include "common.cpp"
#include "iter.cpp"
#include "kth_term_of_inverse_polynomial.cpp"
#include "polynomial.cpp"
namespace dalt {
namespace poly {
// lr = {1, -c1, -c2, ...}
// consider from last bit to first bit
template <class Poly, class T>
T KthTermOfLinearRecurrence(int n, const Indexer<int>& indexer, Vec<T> lr,
                            Vec<T> prefix) {
  static_assert(is_polynomial_v<Poly>);
  static_assert(is_same_v<T, typename Poly::Type>);
  let rank = Size(lr) - 1;
  Poly Q(Move(lr));
  Poly F(Move(prefix));
  Poly P = (Q * F).modular(rank);
  return KthTermOfInversePolynomial<Poly>(n, indexer, P, Q);
}
}  // namespace poly
}  // namespace dalt
#pragma once
#include "modint.cpp"
namespace dalt {
namespace math {
template <class T>
struct Combination {
  static_assert(is_modint_v<T>);
  using Modular = typename T::Modular;
  Vec<T> fact;
  Vec<T> inv_fact;
  Combination(int cap) {
    cap += 1;
    fact.resize(cap);
    inv_fact.resize(cap);
    fact[0] = T(1);
    for (int i = 1; i < cap; i++) {
      T v = T(i);
      if (v != T(0)) {
        fact[i] = fact[i - 1] * v;
      } else {
        fact[i] = fact[i];
      }
    }
    T inv = T(1) / fact.back();
    for (int i = cap - 1; i >= 0; i--) {
      T v = T(i);
      inv_fact[i] = inv;
      if (v != T(0)) {
        inv = inv * T(i);
      }
    }
  }
  T inverse(int x) { return inv_fact[x] * fact[x - 1]; }
  T combination(int a, int b) {
    if (a < b || b < 0) {
      return T(0);
    }
    return fact[a] * inv_fact[b] * inv_fact[a - b];
  }
  template <class E>
  T combination_lucas(E a, E b) {
    if (a < b || b < 0) {
      return T(0);
    }

    if (a < Modular::modulus) {
      return fact[a] * inv_fact[b] * inv_fact[a - b];
    } else {
      return combination(a % Modular::modulus, b % Modular::modulus) *
             combination_lucas(a / Modular::modulus, b / Modular::modulus);
    }
  }
};
}  // namespace math
}  // namespace dalt
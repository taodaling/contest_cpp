#pragma once
#include "modint.cpp"
namespace dalt {
template <class Modular> struct ModIntSum {
  static_assert(is_modular_v<Modular>);
  using Type = typename Modular::Type;
  static_assert(is_same_v<i32, Type>);

  void add(i64 x) {
    if (x >= 0) {
      if (sum + x < sum) {
        sum %= Modular::modulus;
      }
      sum += x;
    } else {
      if (sum + x > sum) {
        sum %= Modular::modulus;
      }
      sum += x;
    }
  }
  ModInt<Modular> get() {
    normalize();
    return ModInt<Modular>(sum);
  }

  ModIntSum() : sum(0) {}

private:
  i64 sum;
  void normalize() {
    if (sum < -Modular::modulus || sum >= Modular::modulus) {
      sum %= Modular::modulus;
    }
    if (sum < 0) {
      sum += Modular::modulus;
    }
  }
};
} // namespace dalt
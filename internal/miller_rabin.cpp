#pragma once
#include "common.cpp"
#include "math.cpp"
#include "modint.cpp"
namespace dalt {
// Check whether n is a prime s times, O(slog n)
template <class T> enable_if_t<is_integral_v<T>, bool> MillerRabin(T n, int s = 10) {
  using Modular = DynamicModular<T, -2>;
  using mi = ModInt<Modular>;
  Modular::Register(n);
  auto test = [&](auto &test, mi y, T exp, T n) -> bool {
    auto y2 = y * y;
    if (!(exp == n - 1 || test(test, y2, exp * 2, n))) {
      return false;
    }
    if (exp != n - 1 && y2.value != 1) {
      return true;
    }
    if (y.value != 1 && y.value != n - 1) {
      return false;
    }
    return true;
  };

  if (n <= 1) {
    return false;
  }
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }
  T m = n - 1;
  while (m % 2 == 0) {
    m /= 2;
  }
  for (int i = 0; i < s; i++) {
    T x = random_choice<T>(2, n - 1);
    if (!test(test, PowBinaryLift(mi(x), m), m, n)) {
      return false;
    }
  }
  return true;
}
} // namespace dalt
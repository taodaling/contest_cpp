#pragma once
#include "common.cpp"
#include "number.cpp"
#include "optional.cpp"
namespace dalt {
template <class T>
enable_if_t<is_integral_v<T>, Optional<T>> FirstTrue(
    T l, T r, const Checker<T> &checker) {
  if (!checker(r)) {
    return {};
  }
  while (l < r) {
    T m = DivFloor(l + r, 2);
    if (checker(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return l;
}
template <class T>
enable_if_t<is_integral_v<T>, Optional<T>> LastTrue(T l, T r,
                                                    const Checker<T> &checker) {
  if (!checker(l)) {
    return {};
  }
  while (l < r) {
    T m = DivCeil(l + r, 2);
    if (checker(m)) {
      l = m;
    } else {
      r = m - 1;
    }
  }
  return l;
}

template <class T>
enable_if_t<is_floating_point_v<T>, Optional<T>> FirstTrue(
    T l, T r, const Checker<T> &checker, Function<bool()> stopper) {
  if (!checker(r)) {
    return {};
  }
  while (!stopper()) {
    T m = (l + r) / 2;
    if (checker(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  return l;
}
template <class T>
enable_if_t<is_floating_point_v<T>, Optional<T>> FirstTrue(
    T l, T r, const Checker<T> &checker, i32 max_round) {
  return FirstTrue<T>(
      l, r, checker,[&]() { return max_round-- <= 0; });
}
}  // namespace dalt
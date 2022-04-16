#pragma once
#include "common.cpp"
#include "optional.cpp"
#include "number.cpp"
namespace dalt {
template <class T>
enable_if_t<is_integral_v<T>, Optional<T>> FirstTrue(T l, T r, const Checker<T> &checker) {
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
enable_if_t<is_floating_point_v<T>, Optional<T>> FirstTrue(T l, T r,
                                                     const Checker<T> &checker,
                                                     i32 max_round) {
  if (!checker(r)) {
    return {};
  }
  while (max_round > 0) {
    max_round -= 1;
    T m = (l + r) / 2;
    if (checker(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  return l;
}
} // namespace dalt
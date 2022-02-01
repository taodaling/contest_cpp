#pragma once
#include "../common.cpp"
#include "optional.cpp"
#include "prefer_div.cpp"
namespace dalt {
template <class T,
          class = typename std::enable_if<std::is_integral<T>::value>::Type>
Optional<T> FirstTrue(T l, T r, const Checker<T> &checker) {
  if (!checker(r)) {
    return {};
  }
  while (l < r) {
    T m = DivFloor(l, r);
    if (checker(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return l;
}
template <class T,
          class = typename std::enable_if<std::is_integral<T>::value>::Type>
Optional<T> LastTrue(T l, T r, const Checker<T> &checker) {
  if (!checker(l)) {
    return {};
  }
  while (l < r) {
    T m = DivCeil(l, r);
    if (checker(m)) {
      l = m;
    } else {
      r = m - 1;
    }
  }
  return l;
}
template <class T, class = typename std::enable_if<
                       std::is_floating_point<T>::value>::Type>
Optional<T> FirstTrue(T l, T r, const Checker<T> &checker, i32 max_round) {
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
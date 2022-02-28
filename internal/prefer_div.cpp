#pragma once
#include "common.cpp"

namespace dalt {
template <class T> std::enable_if_t<is_integral_v<T>, T> DivFloor(T a, T b) {
  Assert(b > 0);
  auto ans = a / b;
  if (ans * b > a) {
    ans = ans - 1;
  }
  return ans;
}
template <class T> std::enable_if_t<is_integral_v<T>, T> DivCeil(T a, T b) {
  Assert(b > 0);
  auto ans = a / b;
  if (ans * b < a) {
    ans = ans + 1;
  }
  return ans;
}
template <class T>
std::enable_if_t<is_floating_point_v<T>, T> DivFloor(T a, T b) {
  return a / b;
}
template <class T>
std::enable_if_t<is_floating_point_v<T>, T> DivCeil(T a, T b) {
  return a / b;
}
} // namespace dalt
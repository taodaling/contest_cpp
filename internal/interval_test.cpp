#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
bool InRange(T l, T r, T x) {
  return l <= x && x <= r;
}
template <class T>
bool InRangeRotate(T l, T r, T x) {
  if (l <= r) {
    return InRange(l, r, x);
  } else {
    return !InRange(r + 1, l - 1, x);
  }
}
}  // namespace dalt
#pragma once
#include "common.cpp"
#include "number.cpp"
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
    return !InRange(LargerValue(r), SmallerValue(l), x);
  }
}
}  // namespace dalt
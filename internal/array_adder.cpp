#pragma once
#include "alias.cpp"
template <class T, int S>
Array<T, S> operator+(const Array<T, S>& a, const Array<T, S>& b) {
  Array<T, S> res;
  for (int i = 0; i < S; i++) {
    res[i] = a[i] + b[i];
  }
  return res;
}
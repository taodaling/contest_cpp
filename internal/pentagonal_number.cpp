#pragma once
#include "common.cpp"
namespace dalt {
namespace math {
//O(n)
template <class T>
Vec<T> PentagonalNumber(int n) {
  Vec<T> data(n);
  if (n == 0) {
    return data;
  }
  T one = T(1);
  T neg = T(-1);
  data[0] = one;
  for (int k = 1; k * (3 * k + 1) / 2 < n; k++) {
    T val = k % 2 == 1 ? neg : one;
    data[k * (3 * k + 1) / 2] += val;
  }
  for (int k = 1; k * (3 * k - 1) / 2 < n; k++) {
    T val = k % 2 == 1 ? neg : one;
    data[k * (3 * k - 1) / 2] += val;
  }
  return data;
}
}  // namespace math
}  // namespace dalt
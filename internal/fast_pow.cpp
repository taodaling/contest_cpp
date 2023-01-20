#pragma once
namespace dalt {
namespace math {
template <class T>
struct FastPower2 {
  Vec<T> high;
  Vec<T> low;
  i32 mask;
  i32 shift;

  FastPower2(const T& x, int n, const T& one = T(1)) {
    mask = 1;
    shift = 0;
    // n / mask <= mask
    // n <= mask * mask
    while (mask * mask < n) {
      mask *= 2;
      shift++;
    }
    high.resize(mask);
    low.resize(mask);
    mask--;
    low[0] = one;
    for (int i = 1; i <= mask; i++) {
      low[i] = low[i - 1] * x;
    }
    T y = low.back() * x;
    high[0] = one;
    for (int i = 1; i <= mask; i++) {
      high[i] = high[i - 1] * y;
    }
  }
  T pow(int exp) const { return high[exp >> shift] * low[exp & mask]; }
};
}  // namespace math
}  // namespace dalt
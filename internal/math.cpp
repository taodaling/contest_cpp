#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
inline T& Chmin(T& a, const T& b) {
  if (a > b) {
    a = b;
  }
  return a;
}
template <class T>
inline T& Chmax(T& a, const T& b) {
  if (a < b) {
    a = b;
  }
  return a;
}
template <class T>
inline T& AddTo(T& a, const T& b) {
  a = a + b;
  return a;
}
template <class T>
inline T& MulTo(T& a, const T& b) {
  a = a * b;
  return a;
}
template <class T>
inline T& SubFrom(T& a, const T& b) {
  a = a - b;
  return a;
}
template <class T>
inline T& DivFrom(T& a, const T& b) {
  a = a / b;
  return a;
}
template <class T, class E>
constexpr enable_if_t<is_integral_v<E>, T> PowBinaryLift(T x, E n) {
  if (n == E(0)) {
    return T(1);
  }
  auto ans = PowBinaryLift(x, n >> 1);
  ans = ans * ans;
  if (n & 1) {
    ans = ans * x;
  }
  return ans;
}

template <class T>
inline T MulLimit(T a, T b, T max, T def) {
  if (a == T(0) || b == T(0)) {
    return T(0);
  }
  // a * b <= max
  // a <= max / b
  // a <= floor(max / b)
  if (a <= max / b) {
    return a * b;
  } else {
    return def;
  }
}
template <class T>
inline T MulLimit(T a, T b, T max) {
  return MulLimit(a, b, max, max);
}
template <class T>
inline T AddLimit(T a, T b, T max, T def) {
  if (a <= max - b) {
    return a + b;
  } else {
    return def;
  }
}
template <class T>
inline T AddLimit(T a, T b, T max) {
  return AddLimit(a, b, max, max);
}
i64 Round(f32 x) { return roundf(x); }
i64 Round(f64 x) { return round(x); }
i64 Round(f80 x) { return roundl(x); }
}  // namespace dalt
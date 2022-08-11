#pragma once
#include "common.cpp"
namespace dalt {
template <class T, class E>
T Modular(E val, T mod) {
  val = val % mod;
  if (val < 0) {
    val = val + mod;
  }
  return T(val);
}
template<class T>
inline T MulMod(T a, T b, T modulus) {
  i64 res = i64(a) * i64(b) % modulus;
  return T(res);
}
template<>
inline i64 MulMod<i64>(i64 a, i64 b, i64 modulus) {
  i64 k = roundl((f80)a / modulus * b);
  i64 res = (a * b - k * modulus) % modulus;
  if (res < 0) {
    res += modulus;
  }
  return res;
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> AddMod(T a, T b, T modulus) {
  T res = a + b;
  if (res >= modulus) {
    res -= modulus;
  }
  return res;
}
template <class T, class E>
inline enable_if_t<is_integral_v<T> && is_integral_v<E>, T> PowMod(T x, E exp,
                                                                   T modulus) {
   Assert(exp >= E(0));                                                          
  if (exp == E(0)) {
    return modulus == T(1) ? T(0) : T(1);
  }
  T ans = PowMod(x, exp >> 1, modulus);
  ans = MulMod(ans, ans, modulus);
  if (exp & T(1)) {
    ans = MulMod(ans, x, modulus);
  }
  return ans;
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> SubMod(T a, T b, T modulus) {
  T res = a - b;
  if (res < T(0)) {
    res += modulus;
  }
  return res;
}
}  // namespace dalt
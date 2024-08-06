#pragma once
#include "binary.cpp"
#include "common.cpp"
#include "poly.cpp"
namespace dalt {
namespace fwt {
// res[i] is how many superset of i occur in p
template <class T>
struct And {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a + b, b}; }
};
// p[i] is the number of superset of i, ret[i] is the occurrence number of
// number i
template <class T>
struct IAnd {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a - b, b}; }
};
// res[i] is how many subsets of i occur in p
template <class T>
struct Or {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a, b + a}; }
};
// p[i] is the number of subset of i, ret[i] is the occurrence number of number
// i
template <class T>
struct IOr {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a, b - a}; }
};
template <class T>
struct Xor {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a + b, a - b}; }
};
template <class T>
struct IXor {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) {
    return {(a + b) / T(2), (a - b) / T(2)};
  }
};
template <class T>
struct IXorFast {
  using Type = T;
  static T half;
  static void Register(T _half) { half = _half; }
  static Array<T, 2> conv(const T &a, const T &b) {
    return {(a + b) * half, (a - b) * half};
  }
};
template <class T>
T IXorFast<T>::half;

template <class Conv, class T = typename Conv::Type>
void BitwiseTransform(Vec<T> &data, int l, int r) {
  static_assert(is_same_v<typename Conv::Type, T>);
  if (l >= r) {
    return;
  }
  i32 m = (l + r) / 2;
  i32 step = r - m;
  BitwiseTransform<Conv>(data, l, m);
  BitwiseTransform<Conv>(data, m + 1, r);
  for (int i = l; i <= m; i++) {
    Array<T, 2> res = Conv::conv(data[i], data[i + step]);
    data[i] = res[0];
    data[i + step] = res[1];
  }
}

template <class Conv, class T = typename Conv::Type>
void BitwiseInverse(Vec<T> &data, int l, int r) {
  static_assert(is_same_v<typename Conv::Type, T>);
  if (l >= r) {
    return;
  }
  i32 m = (l + r) / 2;
  i32 step = r - m;
  for (int i = l; i <= m; i++) {
    Array<T, 2> res = Conv::conv(data[i], data[i + step]);
    data[i] = res[0];
    data[i + step] = res[1];
  }
  BitwiseInverse<Conv>(data, l, m);
  BitwiseInverse<Conv>(data, m + 1, r);
}


}  // namespace fwt
}  // namespace dalt
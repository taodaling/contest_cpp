#pragma once
#include "common.cpp"
#include "binary.cpp"
#include "poly.cpp"
namespace dalt {
namespace fwt {
// res[i] is how many superset of i occur in p
template <class T> struct And {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a + b, b}; }
};
// p[i] is the number of superset of i, ret[i] is the occurrence number of
// number i
template <class T> struct IAnd {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a - b, b}; }
};
// res[i] is how many subsets of i occur in p
template <class T> struct Or {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a, b + a}; }
};
// p[i] is the number of subset of i, ret[i] is the occurrence number of number
// i
template <class T> struct IOr {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a, b - a}; }
};
template <class T> struct Xor {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a + b, a - b}; }
};
template <class T> struct IXor {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) {
    return {(a + b) / T(2), (a - b) / T(2)};
  }
};
template <class T> struct IXorFast {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) {
    static const T div = T(1) / T(2);
    return {(a + b) * div, (a - b) * div};
  }
};
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

// ret[i] = \sum_{j \in i} a[j] * b[i ^ j]
// O(n(\log n)^2)
template <class T> Vec<T> SubsetConvolution(Vec<T> a, Vec<T> b) {
  Assert(Size(a) == Size(b));
  Assert(Size(a) == LowestOneBit(Size(a)));
  i32 n = Size(a);
  if (n == 0) {
    return Vec<T>();
  }
  i32 log = Log2Floor(n);
  Vec<Vec<T>> fwta = Vec<Vec<T>>(log + 1, Vec<T>(n));
  Vec<Vec<T>> fwtb = fwta;
  Vec<T> c(n);
  Vec<T> t(n);
  for (i32 i = 0; i < n; i++) {
    let bitcount = CountBit(i);
    fwta[bitcount][i] = a[i];
    fwtb[bitcount][i] = b[i];
  }
  for (i32 i = 0; i <= log; i++) {
    BitwiseTransform<Or<T>>(fwta[i], 0, Size(fwta[i]) - 1);
    BitwiseTransform<Or<T>>(fwtb[i], 0, Size(fwtb[i]) - 1);
  }
  for (i32 i = 0; i <= log; i++) {
    Fill(All(t), T(0));
    for (i32 j = 0; j <= i; j++) {
      let k = i - j;
      poly::DotMulPlus(fwta[j], fwtb[k], t);
    }
    BitwiseInverse<IOr<T>>(t, 0, Size(t) - 1);
    for (i32 j = 0; j < n; j++) {
      if (CountBit(j) == i) {
        c[j] = t[j];
      }
    }
  }
  return c;
}
} // namespace fwt
} // namespace dalt
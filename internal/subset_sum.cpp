#pragma once
#include "bitwise_convolution.cpp"
namespace dalt {
namespace fwt {

// ret[i] = \sum_{j \in i} a[j] * b[i ^ j]
// O(n(\log n)^2)
template <class T>
Vec<T> SubsetConvolution(const Vec<T>& a, const Vec<T>& b) {
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

// copied from https://www.cnblogs.com/birchtree/p/14531986.html
// O(n^2 * 2^n)
// 每个集合S有[xS]F种染色方案，[xS](expF)就是选取若干不相交集合无序地组成S并染色的方案数。
template <class T>
Vec<T> Exp(Vec<T> data, int n) {
  assert((1 << n) == Size(data));
  assert(data[0] == T(0));
  Vec<Vec<T>> F(n + 1, Vec<T>(1 << n));
  Vec<Vec<T>> G(n + 1, Vec<T>(1 << n));
  Vec<T> inv(n + 1);
  for (int i = 1; i <= n; i++) {
    inv[i] = T(1) / T(i);
  }
  for (int i = 0; i < 1 << n; i++) {
    F[CountBit(i)][i] = data[i];
  }
  for (int i = 0; i <= n; i++) {
    BitwiseTransform<Or<T>>(F[i], 0, Size(data) - 1);
  }
  G[0][0] = T(1);
  BitwiseTransform<Or<T>>(G[0], 0, Size(data) - 1);
  for (int s = 0; s < 1 << n; s++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        G[i + 1][s] += G[j][s] * F[i - j + 1][s] * T(i - j + 1);
      }
      G[i + 1][s] *= inv[i + 1];
    }
  }
  for (int i = 0; i <= n; i++) {
    BitwiseInverse<IOr<T>>(G[i], 0, Size(data) - 1);
  }
  for (int i = 0; i < 1 << n; i++) {
    data[i] = G[CountBit(i)][i];
  }
  return data;
}
// copied from https://www.cnblogs.com/birchtree/p/14531986.html
// O(n^2 * 2^n)
template <class T>
Vec<T> Ln(Vec<T> data, int n) {
  assert((1 << n) == Size(data));
  // assert(data[0] == T(1));
  Vec<Vec<T>> F(n + 1, Vec<T>(1 << n));
  Vec<Vec<T>> G(n + 1, Vec<T>(1 << n));
  Vec<T> inv(n + 1);
  for (int i = 1; i <= n; i++) {
    inv[i] = T(1) / T(i);
  }
  for (int i = 0; i < 1 << n; i++) {
    F[CountBit(i)][i] = data[i];
  }
  for (int i = 0; i <= n; i++) {
    BitwiseTransform<Or<T>>(F[i], 0, Size(data) - 1);
  }
  G[0][0] = T(1);
  BitwiseTransform<Or<T>>(G[0], 0, Size(data) - 1);
  for (int s = 0; s < 1 << n; s++) {
    for (int i = 0; i < n; i++) {
      for (int j = 1; j <= i; j++) {
        G[i + 1][s] += F[j][s] * G[i - j + 1][s] * T(i - j + 1);
      }
      G[i + 1][s] = F[i + 1][s] - G[i + 1][s] * inv[i + 1];
    }
  }
  for (int i = 0; i <= n; i++) {
    BitwiseInverse<IOr<T>>(G[i], 0, Size(data) - 1);
  }
  for (int i = 0; i < 1 << n; i++) {
    data[i] = G[CountBit(i)][i];
  }
  data[0] = T();
  return data;
}
}  // namespace fwt
}  // namespace dalt
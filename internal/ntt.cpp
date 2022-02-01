#pragma once
#include "../common.cpp"
#include "binary.cpp"
#include "bit_reverse.cpp"
#include "convolution.cpp"
#include "math.cpp"
#include "modint.cpp"
#include "poly.cpp"
namespace dalt {
namespace poly {
template <class M>
enable_if_t<is_modular_v<M>> NumberTheoryTransform(Vec<ModInt<M>> &p,
                                                   bool inv) {
  using mi = ModInt<M>;
  auto modulus = mi::modulus();
  mi g = mi(mi::primitive_root());
  i32 m = Log2Ceil(Size(p));
  i32 n = 1 << m;
  Assert(n == Size(p));
  auto shift = 32 - TrailingZeroNumber(n);
  for (int i = 1; i < n; i++) {
    auto j = ReverseBit(u32(i << shift));
    if (i < j) {
      Swap(p[i], p[j]);
    }
  }
  Vec<mi> ws(n / 2);
  Assert((modulus - 1) % n == 0);
  auto unit = PowBinaryLift(g, (modulus - 1) / n);
  if (Size(ws) >= 1) {
    ws[0] = 1;
  }
  for (int i = 1; i < Size(ws); i++) {
    ws[i] = ws[i - 1] * unit;
  }

  for (int d = 0; d < m; d++) {
    auto s = 1 << d;
    auto s2 = s << 1;
    auto right = n >> (1 + d);
    for (int i = 0; i < n; i += s2) {
      for (int j = 0; j < s; j++) {
        auto a = i + j;
        auto b = a + s;
        auto t = ws[j * right] * p[b];
        p[b] = p[a] - t;
        p[a] = p[a] + t;
      }
    }
  }

  if (inv) {
    auto inv_n = mi(1) / mi(n);
    auto i = 0;
    auto j = 0;
    while (i <= j) {
      auto a = p[j];
      p[j] = p[i] * inv_n;
      if (i != j) {
        p[i] = a * inv_n;
      }
      i += 1;
      j = n - i;
    }
  }
}
template <class M> struct NTTConv {
  static_assert(is_modular_v<M>);
  using mi = ModInt<M>;
  using Type = mi;
  using P = Vec<mi>;
  static P conv(P a, P b) {
    int n = Size(a) + Size(b);
    int conv_len = 1 << Log2Ceil(n);
    a.resize(conv_len);
    b.resize(conv_len);
    NumberTheoryTransform(a, false);
    NumberTheoryTransform(b, false);
    DotMulInplace(a, b);
    NumberTheoryTransform(a, true);
    return a;
  }
  static P conv2(P a) {
    int n = Size(a) + Size(a);
    int conv_len = 1 << Log2Ceil(n);
    a.resize(conv_len);
    NumberTheoryTransform(a, false);
    DotMulInplace(a, a);
    NumberTheoryTransform(a, true);
    return a;
  }
  static P inverse(P p, i32 n) {
    Extend(p, n);
    auto dfs = [&](auto &dfs, i32 m) {
      if (m == 1) {
        return P{mi(1) / mi(p[0])};
      }
      i32 prev_len = (m + 1) / 2;
      auto ans = dfs(dfs, prev_len);
      i32 n = (prev_len - 1) * 2 + m;
      auto proper_len = 1 << Log2Ceil(n);
      ans.resize(proper_len);
      P prefix;
      prefix.reserve(proper_len);
      prefix.insert(prefix.begin(), p.begin(), p.begin() + m);
      prefix.resize(proper_len);
      NumberTheoryTransform(prefix, false);
      NumberTheoryTransform(ans, false);
      for (int i = 0; i < proper_len; i++) {
        ans[i] = ans[i] * (mi(2) - prefix[i] * ans[i]);
      }
      NumberTheoryTransform(ans, true);
      ans.resize(m);
      return ans;
    };
    return dfs(dfs, n);
  }
};
template <class M> struct is_convolution<NTTConv<M>> {
  static const bool value = true;
};
} // namespace poly
} // namespace dalt
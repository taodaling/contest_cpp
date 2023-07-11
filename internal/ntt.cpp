#pragma once
#include "common.cpp"
#include "binary.cpp"
#include "bit_reverse.cpp"
#include "convolution.cpp"
#include "math.cpp"
#include "modint.cpp"
#include "poly.cpp"
#include "brute_force_conv.cpp"
namespace dalt {
namespace poly {
template <class Mi>
enable_if_t<is_modint_v<Mi>> NumberTheoryTransform(Vec<Mi> &p, bool inv) {
  auto modulus = Mi::modulus();
  Mi g = Mi(Mi::primitive_root());
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
  Vec<Mi> ws(n / 2);
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
    auto inv_n = Mi(1) / Mi(n);
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
template <class M>
struct NTTConv {
  static_assert(is_modint_v<M>);
  using mi = M;
  using Type = mi;
  using P = Vec<mi>;
  static P conv(const P &a, const P &b) {
    if (Size(a) <= 20 || Size(b) <= 20) {
      return BruteForceConv<Type>::conv(a, b);
    }
    if (&a == &b) {
      return conv2(a);
    }
    int n = Size(a) + Size(b);
    int conv_len = 1 << Log2Ceil(n);
    auto pa = CopyAndExtend(a, conv_len);
    auto pb = CopyAndExtend(b, conv_len);
    NumberTheoryTransform(pa, false);
    NumberTheoryTransform(pb, false);
    DotMulInplace(pa, pb);
    NumberTheoryTransform(pa, true);
    return pa;
  }
  static P conv2(const P &a) {
    int n = Size(a) + Size(a) - 1;
    int conv_len = 1 << Log2Ceil(n);
    auto pa = CopyAndExtend(a, conv_len);
    NumberTheoryTransform(pa, false);
    DotMulInplace(pa, pa);
    NumberTheoryTransform(pa, true);
    return pa;
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
template <class M>
struct is_convolution<NTTConv<M>> {
  static const bool value = true;
};
}  // namespace poly
}  // namespace dalt
#pragma once
#include "binary.cpp"
#include "bit_reverse.cpp"
#include "convolution.cpp"
#include "math.cpp"
#include "modint.cpp"
#include "poly.cpp"
namespace dalt {
namespace poly {
template <class F>
enable_if_t<is_floating_point_v<F>> fft(Vec<Complex<F>> &p, bool inv) {
  using cpx = Complex<F>;
  static Vec<Vec<cpx>> multi_levels(30);
  int m = Log2Ceil(Size(p));
  int n = 1 << m;
  Assert((1 << m) == Size(p));
  int shift = 32 - TrailingZeroNumber(n);
  for (int i = 1; i < n; i++) {
    int j = ReverseBit(i << shift);
    if (i < j) {
      Swap(p[i], p[j]);
    }
  }

  for (int d = 0; d < m; d++) {
    int s = 1 << d;
    int s2 = s << 1;
    auto &level = multi_levels[d];
    if (level.empty()) {
      // init
      level.resize(1 << d);
      for (int j = 0, s = 1 << d; j < s; j++) {
        level[j] =
            cpx(Cos(F(M_PI) / s * j), Sin(F(M_PI) / s * j));
      }
    }
    for (int i = 0; i < n; i += s2) {
      for (int j = 0; j < s; j++) {
        auto a = i + j;
        auto b = a + s;
        auto t = level[j] * p[b];
        p[b] = p[a] - t;
        p[a] = p[a] + t;
      }
    }
  }

  if (inv) {
    int i = 0;
    int j = 0;
    F tn = n;
    while (i <= j) {
      auto pj = p[j];
      p[j] = p[i] / tn;
      if (i != j) {
        p[i] = pj / tn;
      }
      i += 1;
      j = n - i;
    }
  }
}
template <class M, class F = f80>
struct FFTConv {
  static_assert(is_modint_v<M>);
  using cpx = Complex<F>;
  using mi = M;
  using Type = mi;
  static_assert(is_same_v<i32, typename M::Type>);

  static Vec<mi> conv(const Vec<mi> &a, const Vec<mi> &b) {
    if (&a == &b) {
      return conv2(a);
    }
    return conv(a, Size(a), b, Size(b));
  }
  static Vec<mi> conv(const Vec<mi> &a, int na, const Vec<mi> &b, int nb) {
    let rank_a = na - 1;
    let rank_b = nb - 1;

    i32 step = 15;
    i32 mask = (1 << step) - 1;
    let n = 1 << Log2Ceil(rank_a + rank_b + 1);
    Vec<cpx> a_cpx(n);
    Vec<cpx> b_cpx(n);
    for (int i = 0; i < na; i++) {
      let x = a[i].value;
      a_cpx[i] = cpx(x & mask, x >> step);
    }
    for (int i = 0; i < nb; i++) {
      let x = b[i].value;
      b_cpx[i] = cpx(x & mask, x >> step);
    }
    fft(a_cpx, false);
    fft(b_cpx, false);

    i32 i = 0;
    i32 j = 0;
    while (i <= j) {
      let ari = a_cpx[i].real();
      let aii = a_cpx[i].imag();
      let bri = b_cpx[i].real();
      let bii = b_cpx[i].imag();
      let arj = a_cpx[j].real();
      let aij = a_cpx[j].imag();
      let brj = b_cpx[j].real();
      let bij = b_cpx[j].imag();

      let a1r = (ari + arj) / 2;
      let a1i = (aii - aij) / 2;
      let a2r = (aii + aij) / 2;
      let a2i = (arj - ari) / 2;

      let b1r = (bri + brj) / 2;
      let b1i = (bii - bij) / 2;
      let b2r = (bii + bij) / 2;
      let b2i = (brj - bri) / 2;

      a_cpx[i] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                     a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
      b_cpx[i] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                     a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);

      if (i != j) {
        let a1r = (arj + ari) / 2;
        let a1i = (aij - aii) / 2;
        let a2r = (aij + aii) / 2;
        let a2i = (ari - arj) / 2;

        let b1r = (brj + bri) / 2;
        let b1i = (bij - bii) / 2;
        let b2r = (bij + bii) / 2;
        let b2i = (bri - brj) / 2;

        a_cpx[j] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                       a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
        b_cpx[j] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                       a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);
      }

      i += 1;
      j = n - i;
    }

    fft(a_cpx, true);
    fft(b_cpx, true);

    i64 modulus = M::modulus;
    Vec<mi> ans(n);
    for (int i = 0; i < n; i++) {
      i64 aa = Round(a_cpx[i].real());
      i64 bb = Round(b_cpx[i].real());
      i64 cc = Round(a_cpx[i].imag());
      ans[i] = (aa + (bb % modulus << 15) + (cc % modulus << 30)) % modulus;
    }
    return ans;
  }
  static Vec<mi> conv2(const Vec<mi> &p) {
    let rank_a = na - 1;
    let rank_b = nb - 1;

    i32 step = 15;
    i32 mask = (1 << step) - 1;
    let n = 1 << Log2Ceil(rank_a + rank_b + 1);
    Vec<cpx> a_cpx(n);
    for (int i = 0; i < na; i++) {
      let x = a[i].value;
      a_cpx[i] = cpx(x & mask, x >> step);
    }
    fft(a_cpx, false);
    auto b = a_cpx;
    i32 i = 0;
    i32 j = 0;
    while (i <= j) {
      let ari = a_cpx[i].real();
      let aii = a_cpx[i].imag();
      let bri = b_cpx[i].real();
      let bii = b_cpx[i].imag();
      let arj = a_cpx[j].real();
      let aij = a_cpx[j].imag();
      let brj = b_cpx[j].real();
      let bij = b_cpx[j].imag();

      let a1r = (ari + arj) / 2;
      let a1i = (aii - aij) / 2;
      let a2r = (aii + aij) / 2;
      let a2i = (arj - ari) / 2;

      let b1r = (bri + brj) / 2;
      let b1i = (bii - bij) / 2;
      let b2r = (bii + bij) / 2;
      let b2i = (brj - bri) / 2;

      a_cpx[i] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                     a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
      b_cpx[i] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                     a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);

      if (i != j) {
        let a1r = (arj + ari) / 2;
        let a1i = (aij - aii) / 2;
        let a2r = (aij + aii) / 2;
        let a2i = (ari - arj) / 2;

        let b1r = (brj + bri) / 2;
        let b1i = (bij - bii) / 2;
        let b2r = (bij + bii) / 2;
        let b2i = (bri - brj) / 2;

        a_cpx[j] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                       a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
        b_cpx[j] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                       a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);
      }

      i += 1;
      j = n - i;
    }

    fft(a_cpx, true);
    fft(b_cpx, true);

    i64 modulus = M::modulus;
    Vec<mi> ans(n);
    for (int i = 0; i < n; i++) {
      i64 aa = Round(a_cpx[i].real());
      i64 bb = Round(b_cpx[i].real());
      i64 cc = Round(a_cpx[i].imag());
      ans[i] = (aa + (bb % modulus << 15) + (cc % modulus << 30)) % modulus;
    }
    return ans;
  }
  static Vec<mi> inverse(Vec<mi> p, i32 n) {
    Extend(p, n);
    auto dfs = [&](auto &dfs, i32 m) -> Vec<mi> {
      if (m == 1) {
        return Vec<mi>{mi(1) / p[0]};
      }
      i32 prev_mod = (m + 1) / 2;
      auto C = dfs(dfs, prev_mod);
      auto AC = conv(p, m, C, prev_mod);
      AC.resize(m);
      for (int i = 0; i < m; i++) {
        AC[i] = mi(0) - AC[i];
      }
      AC[0] = AC[0] + mi(2);
      auto res = conv(C, AC);
      res.resize(m);
      return res;
    };
    auto ans = dfs(dfs, n);
    ans.resize(n);
    return ans;
  }
};
template <class F, class M>
struct is_convolution<FFTConv<F, M>> {
  static const bool value = true;
};
}  // namespace poly
}  // namespace dalt
#pragma once
#include "combination.cpp"
#include "euler_sieve.cpp"
#include "polynomial.cpp"
namespace dalt {
namespace math {

template <class T>
struct FirstKindStirlingNumberResult {
  Vec<T> data;
  int n;
  // c(n, i) = ways to split n elements into k loops
  T get_unsign(int i) const { return data[i]; }
  T get_sign(int i) const {
    if ((n - i) & 1) {
      return -data[i];
    }
    return data[i];
  }
};
// according to - https://codeforces.com/blog/entry/117906
// O(nln n)
template <class C>
FirstKindStirlingNumberResult<typename C::Type> FirstKindStirlingNumberFixedK(
    int N, int K) {
  static_assert(poly::is_convolution_v<C>);
  Assert(K <= N);
  using Mi = typename C::Type;
  using Poly = poly::Polynomial<C>;
  Poly poly = Vec<Mi>{1, 1};
  var log = poly.ln(N + 1).powmod_fast(K, K, K, N + 1);
  // var log = poly.ln(N + 1).powmod_binary_lift(K, N + 1);
  Combination<Mi> comb(N + 1);
  Vec<Mi> S(N + 1);
  for (int i = 0; i <= N; i++) {
    S[i] = log[i] * comb.inv_fact[K] * comb.fact[i];
    if ((i - K) & 1) {
      S[i] = -S[i];
    }
  }
  return FirstKindStirlingNumberResult<Mi>{
      .data = Move(S),
      .n = K,
  };
}

// O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>,
            FirstKindStirlingNumberResult<typename C::Type>>
FirstKindStirlingNumber(int n) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  Combination<T> comb(n + 1);
  auto dfs = [&](auto &dfs, int n) -> Poly {
    if (n == 0) {
      return Poly(T(1));
    }
    if (n & 1) {
      Vec<T> ans = dfs(dfs, n - 1).data;
      ans.resize(n + 1);
      for (int i = n; i >= 0; i--) {
        ans[i] *= T(n - 1);
        if (i >= 1) {
          ans[i] += ans[i - 1];
        }
      }
      return Poly(Move(ans));
    } else {
      int half = n / 2;
      auto ans = dfs(dfs, half);
      Vec<T> A(half + 1);
      Vec<T> B(half + 1);
      T ni = T(1);
      for (int i = 0; i <= half; i++) {
        A[i] = ans[i] * comb.fact[i];
        B[i] = ni * comb.inv_fact[i];
        ni *= T(half);
      }
      auto delta = Poly(Move(A)).delta_convolution(Poly(Move(B)));
      for (int i = 0; i <= delta.rank() && i <= half; i++) {
        delta.data[i] *= comb.inv_fact[i];
      }
      // Debug(n);
      // Debug((delta * ans).to_vec());
      return delta * ans;
    }
  };
  auto ans = dfs(dfs, n).data;
  ans.resize(n + 1);
  return FirstKindStirlingNumberResult<T>{
      .data = Move(ans),
      .n = n,
  };
}
// ret[i] = ways to split n number into i non-empty subset
// time complexity: O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>>
SecondKindStirlingNumber(int n) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  Combination<T> comb(n);
  Vec<T> a(n + 1);
  Vec<T> b(n + 1);
  auto pow = EulerSieve::powmod<T>(n + 1, n);
  for (int i = 0; i <= n; i++) {
    a[i] = comb.inv_fact[i];
    if (i & 1) {
      a[i] = -a[i];
    }
    b[i] = comb.inv_fact[i] * pow[i];
  }
  auto c = (Poly(Move(a)) * Poly(Move(b))).data;
  c.resize(n + 1);
  return c;
}

// ret[i] = ways to split i number into K non-empty subset
// time complexity: O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>>
SecondKindStirlingNumberFixedK(int N, int K) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  Combination<T> comb(N + 1);
  Poly p = Vec<T>{0, 1};
  var exp = (p.exp(N + 1) - Poly(Vec<T>{1})).powmod_fast(K, K, K, N + 1);
  Vec<T> ans(N + 1);
  for (int i = 0; i <= N; i++) {
    ans[i] = exp[i] * comb.inv_fact[K] * comb.fact[i];
  }
  return ans;
}
}  // namespace math
}  // namespace dalt
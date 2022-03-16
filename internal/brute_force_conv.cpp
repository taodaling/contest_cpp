#pragma once
#include "common.cpp"
#include "convolution.cpp"
#include "uint128.cpp"
#include "modint.cpp"
namespace dalt {
namespace poly {
template <class T>
struct BruteForceConv {
  using Type = T;

  template <class Arg = T>
  static enable_if_t<is_same_v<Arg, T> &&
                         !(is_modint_v<T> && is_same_v<typename T::Type, i32>),
                     Vec<T>>
  conv(const Vec<T> &a, const Vec<T> &b) {
    int rank = Size(a) + Size(b) - 2; 
    Vec<T> c(rank + 1);
    for (int i = 0; i < Size(a); i++) {
      for (int j = 0; j < Size(b); j++) {
        c[i + j] += a[i] * b[j];
      }
    }
    return c;
  }
  template <class Arg = T>
  static enable_if_t<is_same_v<Arg, T> && is_modint_v<T> &&
                         is_same_v<typename T::Type, i32>,
                     Vec<T>>
  conv(const Vec<T> &a, const Vec<T> &b) {
    int rank = Size(a) + Size(b) - 2;
    Vec<u128> data(rank + 1);
    for(int i = 0; i < Size(a); i++) {
      for(int j = 0; j < Size(b); j++) {
        data[i + j] += u64(a[i].value) * b[j].value;
      }
    }
    Vec<T> ans(rank + 1);
    i32 modulus = T::modulus();
    for(int i = 0; i <= rank; i++) {
      ans[i] = data[i].modular(modulus);
    } 
    return ans;
  }

  static Vec<T> conv2(const Vec<T> &a) { return conv(a, a); }
  static Vec<T> inverse(Vec<T> p, i32 n) {
    Extend(p, n);
    auto dfs = [&](auto &dfs, i32 m) -> Vec<T> {
      if (m == 1) {
        return Vec<T>{T(1) / p[0]};
      }
      i32 prev_mod = (m + 1) / 2;
      auto C = dfs(dfs, prev_mod);
      auto AC = conv(p, m, C, prev_mod);
      AC.resize(m);
      for (int i = 0; i < m; i++) {
        AC[i] = T(0) - AC[i];
      }
      AC[0] = AC[0] + T(2);
      auto res = conv(C, AC);
      res.resize(m);
      return res;
    };
    auto ans = dfs(dfs, n);
    ans.resize(n);
    return ans;
  }
  static Array<Vec<T>, 2> div_and_rem(Vec<T> a, Vec<T> b) {
    Reverse(All(b));
    auto inv_first = T(1) / b[0];
    i32 n = Size(a);
    i32 m = Size(b);
    if (n < m) {
      return {Vec<T>{T(0)}, Vec<T>{Move(a)}};
    }
    Vec<T> divisor(n - m + 1);
    for (int i = n - 1; i >= m - 1; i++) {
      if (a[i] == T(0)) {
        continue;
      }
      T factor = a[i] * inv_first;
      divisor[i - (m - 1)] = factor;
      for (int j = 0; j < m; j++) {
        a[i - j] = a[i - j] - b[j] * factor;
      }
    }
    return Array<Vec<T>, 2>{Move(divisor), Move(a)};
  }
};
template<class T>
struct is_convolution<BruteForceConv<T>> {
  static const bool value = true;
};
}  // namespace poly
}  // namespace dalt
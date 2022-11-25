#pragma once
#include "combination.cpp"
namespace dalt {
namespace math {
// let ps(j) = \sum_{j\leq i} C(H, i)
// find ps(j) in O(\log_{mod} H)
// precalculation takes O(mod * \log_{mod} H) time & space complexity
template <class T>
struct PrefixSumOfLucas {
  static_assert(is_modint_v<T>);
  Combination<T> comb;
  Vec<Vec<T>> ps;
  Vec<i64> H_split;
  Vec<i64> split;
  i64 mod;
  i64 H;
  PrefixSumOfLucas(i64 _H) : comb(T::modulus() - 1), H(_H) {
    mod = T::modulus();
    while (mod != 1 && _H > 0) {
      ps.push_back(Vec<T>(mod));
      H_split.push_back(_H % mod);
      _H /= mod;
    }
    split.resize(Size(ps));
    for (int i = 0; i < Size(ps); i++) {
      if (i == 0) {
        Fill(All(ps[i]), T(1));
      } else {
        Fill(All(ps[i]), ps[i - 1].back());
      }
      for (int j = 0; j < mod; j++) {
        ps[i][j] *= comb.combination(H_split[i], j);
      }
      for (int j = 1; j < mod; j++) {
        ps[i][j] += ps[i][j - 1];
      }
    }
  }
  // return \sum_{i\leq B} C(H, i) in O(\log_{mod} H)
  T query(i64 B) {
    B = Min(B, H);
    if(B < 0 || mod == 1) {
      return T();
    }
    T ans;
    for (int i = 0; i < Size(split); i++) {
      i64 high = B / mod;
      i64 low = B - mod * high;
      B = high;
      split[i] = low;
    }
    T factor = T(1);
    for (int i = Size(split) - 1; i >= 0; i--) {
      if (split[i] > 0) {
        ans += ps[i][split[i] - 1] * factor;
      }
      factor *= comb.combination(H_split[i], split[i]);
    }
    ans += factor;
    return ans;
  }
  T query(i64 L, i64 R) {
    if(R < L) {
      return T();
    }
    return query(R) - query(L - 1);
  }
};
}  // namespace math
}  // namespace dalt
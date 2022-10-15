#pragma once
#include "common.cpp"
#include "limit_value.cpp"
#include "modular.cpp"
#include "totient.cpp"
namespace dalt {
namespace math {
//(\log mod)^2

template <class E>
struct PowerChain {
  static_assert(is_integral_v<E>);
  Vec<E> data;
  Vec<int> next;
  PowerChain(Vec<E> _data) : data(Move(_data)) {
    int n = Size(data);
    next.resize(n);
    int last = n;
    for (int i = n - 1; i >= 0; i--) {
      if (data[i] != E(0)) {
        last = i;
      }
      next[i] = last;
    }
  }
  template <class T>
  T query(int l, int r, T mod) const {
    static_assert(is_integral_v<T>);
    using Lv = LimitValue<T>;
    auto dfs = [&](auto& dfs, int index, T mod) -> Pair<T, Lv> {
      if (mod == T(1)) {
        int to = index;
        while (to + 1 <= r && to - index + 1 <= 5 && data[to] >= E(2)) {
          to++;
        }
        Lv estimate = Lv::from(1);
        if (data[to] == E(0)) {
          // hard case
          int zero = Min(r + 1, next[to]) - to;
          to--;
          if (zero % 2 == 1) {
            estimate = Lv::from(0);
          }
        }

        for (int i = to; i >= index; i--) {
          estimate = Lv::from(data[i]).pow(estimate.value);
        }
        return MakePair(T(0), estimate);
      }

      E val = data[index];
      T mod_val = Modular(val, mod);
      if (index == r) {
        return MakePair(mod_val, Lv::from(val));
      }
      T totient = TotientEval<T, true>(mod);
      auto res = dfs(dfs, index + 1, totient);
      T exp = res.second.value >= totient ? (totient + res.first) : (res.first);
      T ans = PowMod<T, E>(mod_val, exp, mod);
      auto lv_ans = Lv::from(val).pow(res.second.value);
      Debug(index);
      Debug(lv_ans);
      return MakePair(ans, lv_ans);
    };
    return dfs(dfs, l, mod).first;
  }
};
}  // namespace math
}  // namespace dalt
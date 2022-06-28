#pragma once
#include "big_multiplicative_function.cpp"
#include "hashmap.cpp"
#include "modint.cpp"
namespace dalt {
namespace math {
template <class T>
struct CoprimeModLog {
  static_assert(is_modint_v<T>);
  hash::HashMap<T, int> map;
  int m;
  T inv_m;
  int phi;
  CoprimeModLog(T x) {
    phi = EulerFunctionEval(T::modular());
    m = std::ceil(std::sqrt(T::modular()));
    map = hash::HashMap<T, T>(m);
    T inv_x = T(1) / x;
    inv_m = inv_x.pow(m);
    T prod = T(1);
    for (int i = 0; i < m; i++) {
      map[prod] = i;
      prod = prod * x;
    }
  }
  Optional<int> log(T y, decltype(T::Type) atleast = 0) {
    T start = y;
    auto modular = T::modular();
    for (decltype(modular) i = 0; i * m < modular; start *= inv_m, i++) {
      auto iter = map.find(start);
      if (iter != map.end()) {
        auto ans = (iter->second + i * m) % phi;
        if (ans >= atleast) {
          return ans;
        }
      }
    }
    return {};
  }
};
}  // namespace math
}  // namespace dalt
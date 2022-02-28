#pragma once
#include "common.cpp"
#include "factory.cpp"
namespace dalt {
namespace math {
template <class T>
Vec<T> InverseBatch(Vec<T> batch) {
  int n = int(batch.size());
  Vec<T> origin = batch;
  T fact = 1;
  for (int i = 0; i < n; i++) {
    if (origin[i] == T(0)) {
      continue;
    }
    T val = batch[i];
    batch[i] = fact;
    fact = fact * val;
  }
  T inv_fact = T(1) / fact;
  for (int i = n - 1; i >= 0; i--) {
    if (origin[i] == T(0)) {
      continue;
    }
    batch[i] = batch[i] * inv_fact;
    inv_fact = inv_fact * origin[i];
  }
  return batch;
}
template <class T>
struct ModInverseFactory : public Factory<T> {
  static_assert(is_modint_v<T>);
  ModInverseFactory(int cap)
      : Factory<T>(cap, [&](int index) {
          auto p = T::modulus();
          auto k = p / i.value;
          auto r = p - k * i;
          return T(-k) * data[r];
        }) {}
};
}  // namespace math
}  // namespace dalt
#pragma once
#include "common.cpp"
#include "mod_inverse.cpp"
#include "modular.cpp"
namespace dalt {
namespace math {
template <class T>
struct ModFactorialFactory : public Factory<T> {
  ModFactorialFactory(int cap, const Indexer<T> &indexer)
      : Factory<T>(0,
                   [&, = indexer](int i) { return data.back() * indexer(i); }) {
    ensure(cap);
  }
};
}  // namespace math
}  // namespace dalt
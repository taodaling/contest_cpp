#pragma once
#include "hashmap.cpp"
#include "modint.cpp"
namespace dalt {
namespace hash {
template <class T>
struct MultiHashBase {
  using Modular = MOD_BIG;
  using Mi = ModInt<Modular>;
  static HashMap<T, Mi> mem;
  static Mi get(T key) {
    Mi ans = mem[key];
    if (ans == Mi(0)) {
      ans = mem[key] = random();
    }
    return ans;
  }
  static Mi random() { return Mi(random_choice<i64>(1, Modular::modulus - 1)); }
};
template <class T>
HashMap<T, typename MultiHashBase<T>::Mi> MultiHashBase<T>::mem;
}  // namespace hash
}  // namespace dalt
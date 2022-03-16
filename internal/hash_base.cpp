#pragma once
#include "modint.cpp"
namespace dalt {
namespace hash {
struct HashBase {
  using Modular = MOD_BIG;
  using Mi = ModInt<Modular>;
  static Mi x;
  static Mi inv_x;
  static Vec<Mi> xp;
  static Vec<Mi> inv_xp;

  static CONSTRUCT(_init) { HashBase::init(); }
  static void init() {
    int cap = 1e6 + 10;
    x = Mi(random_choice<i64>(1, Modular::modulus - 1));
    inv_x = Mi(1) / x;
    xp.clear();
    inv_xp.clear();
    xp.reserve(cap);
    inv_xp.reserve(cap);
    xp.push_back(Mi(1));
    inv_xp.push_back(Mi(1));
  }
  static void ensure(i32 n) {
    if(xp.empty()) {
      init();
    }
    Assert(x != Mi(0));
    while (Size(xp) < n) {
      xp.push_back(xp.back() * x);
      inv_xp.push_back(inv_xp.back() * inv_x);
    }
  }

  static Mi pow(i32 n) {
    Assert(x != Mi(0));
    ensure(Abs(n) + 1);
    if (n >= 0) {
      return xp[n];
    } else {
      return inv_xp[-n];
    }
  }

  static Mi verbose(Mi hash, i32 size) {
    Assert(x != Mi(0));
    ensure(size + 1);
    return hash + xp[size];
  }
};
decltype(HashBase::x) HashBase::x;
decltype(HashBase::inv_x) HashBase::inv_x;
decltype(HashBase::xp) HashBase::xp;
decltype(HashBase::inv_xp) HashBase::inv_xp;
}  // namespace hash
}  // namespace dalt
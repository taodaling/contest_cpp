#pragma once
#include "../common.cpp"
#include "gcd.cpp"
#include "modular.cpp"
#pragma once

namespace dalt {
namespace modint {
// using Type = T;
// static T modulus;
// static T primitive_root;
MakeAnnotation(modular) MakeAnnotation(modint);
#define MOD MODULAR::modulus
#define SELF ModInt<MODULAR>
#define TEMPLATE_ARGS template <class MODULAR>
TEMPLATE_ARGS struct ModInt {
  using Modular = MODULAR;
  using Type = typename MODULAR::Type;
  static_assert(is_modular_v<MODULAR>);
  static_assert(is_integral_v<Type>);
  Type value;
  using Self = SELF;
  ModInt() : value(0) {}
  ModInt(const Type &v) {
    value = v;
    if (value < 0 || value >= MOD) {
      value %= MOD;
      if (value < 0) {
        value += MOD;
      }
    }
    value = v;
  }
  static Type modulus() { return MOD; }
  static Type primitive_root() { return Modular::primitive_root; }
  template <class F, class = typename enable_if<is_integral<F>::value>::Type>
  Self of(F v) {
    v %= MOD;
    if (v < 0) {
      v += MOD;
    }
    return Self(v);
  }
  Optional<Self> possible_inv() const {
    auto raw_optional_inv = PossibleModInverse(value, MOD);
    if (raw_optional_inv.is_some()) {
      return Self(raw_optional_inv.value());
    } else {
      return {};
    }
  }
};
TEMPLATE_ARGS inline SELF operator+(const SELF &a, const SELF &b) {
  auto res = a.value + b.value;
  if (res >= MOD) {
    res -= MOD;
  }
  return SELF(res);
}
TEMPLATE_ARGS inline SELF operator-(const SELF &a, const SELF &b) {
  auto res = a.value - b.value;
  if (res < 0) {
    res += MOD;
  }
  return SELF(res);
}
TEMPLATE_ARGS inline SELF operator*(const SELF &a, const SELF &b) {
  return SELF(MulMod(a.value, b.value, MOD));
}
TEMPLATE_ARGS inline SELF operator/(const SELF &a, const SELF &b) {
  auto inv = SELF(b.possible_inv().value());
  return a * inv;
}
TEMPLATE_ARGS inline bool operator==(const SELF &a, const SELF &b) {
  return a.value == b.value;
}
TEMPLATE_ARGS inline bool operator!=(const SELF &a, const SELF &b) {
  return !(a.value == b.value);
}
TEMPLATE_ARGS inline IStream &operator>>(IStream &is, SELF &x) {
  typename SELF::Type val;
  is >> val;
  x = SELF(val);
  return is;
}
TEMPLATE_ARGS inline OStream &operator<<(OStream &os, const SELF &x) {
  os << x.value;
  return os;
}
TEMPLATE_ARGS struct is_modint<ModInt<MODULAR>> {
  static const bool value = true;
};
#undef TEMPLATE_TYPE
#undef MOD

template <class T, i64 M, i64 PR> struct StaticModular {
  static_assert(is_integral_v<T>);
  const static T modulus;
  const static T primitive_root;
  using Type = T;
};
template <class T, i64 M, i64 PR> struct is_modular<StaticModular<T, M, PR>> {
  static const bool value = true;
};
template <class T, i64 M, i64 PR> const T StaticModular<T, M, PR>::modulus = M;
template <class T, i64 M, i64 PR>
const T StaticModular<T, M, PR>::primitive_root = PR;
using MOD998244353 = StaticModular<i32, 998244353, 3>;
using MOD1000000007 = StaticModular<i32, 1000000007, 5>;
using MOD1000000009 = StaticModular<i32, 1000000009, 13>;
using MOD_BIG = StaticModular<i64, 2305843009213693951, -1>;
// last used: -2
template <class T = i32, int id = 0> struct DynamicModular {
  static_assert(is_integral_v<T>);
  static T modulus;
  static T primitive_root;
  static void cinit(T _modulus, T _primitive_root = T()) {
    modulus = _modulus;
    primitive_root = _primitive_root;
  }
  using Type = T;
};
template <class T, int id> T DynamicModular<T, id>::modulus = T();
template <class T, int id> T DynamicModular<T, id>::primitive_root = T();
template <class T, int id> struct is_modular<DynamicModular<T, id>> {
  static const bool value = true;
};

} // namespace modint
using namespace modint;
using ModInt998244353 = ModInt<MOD998244353>;
using ModInt1000000007 = ModInt<MOD1000000007>;
using ModInt1000000009 = ModInt<MOD1000000009>;
} // namespace dalt
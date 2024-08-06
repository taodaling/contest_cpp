#pragma once
#include "common.cpp"
#include "gcd.cpp"
#include "modular.cpp"
#include "math.cpp"
#pragma once
namespace dalt {

// using Type = T;
// static T modulus;
// static T primitive_root;
MakeAnnotation(modular);

template <class T, i64 M, i64 PR = -1, i64 PHI = M - 1>
struct StaticModular {
  static_assert(is_integral_v<T>);
  const static T modulus = M;
  const static T primitive_root = PR;
  const static T phi = PHI;
  using Type = T;
};
template <class T, i64 M, i64 PR, i64 PHI>
struct is_modular<StaticModular<T, M, PR, PHI>> {
  static const bool value = true;
};
using MOD998244353 = StaticModular<i32, 998244353, 3>;
using MOD1004535809 = StaticModular<i32, 1004535809, 3>;
using MOD1000000007 = StaticModular<i32, 1000000007, 5>;
using MOD1000000009 = StaticModular<i32, 1000000009, 13>;
using MOD_BIG = StaticModular<i64, 2305843009213693951, -1>;
// last used: -2
template <class T = i32, i64 CID = 0, i64 ID = 0>
struct DynamicModular {
  static_assert(is_integral_v<T>);
  static T modulus;
  static T primitive_root;
  static T phi;
  static void Register(T _modulus, T _primitive_root = T(), T _phi = T()) {
    modulus = _modulus;
    primitive_root = _primitive_root;
    phi = _phi;
  }

  using Type = T;
};
template <class T, i64 CID, i64 ID>
T DynamicModular<T, CID, ID>::modulus = T();
template <class T, i64 CID, i64 ID>
T DynamicModular<T, CID, ID>::primitive_root = T();
template <class T, i64 CID, i64 ID>
T DynamicModular<T, CID, ID>::phi = T();
template <class T, i64 CID, i64 ID>
struct is_modular<DynamicModular<T, CID, ID>> {
  static const bool value = true;
};

MakeAnnotation(modint);
MakeAnnotation(modint_32);
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
    Assert(value >= 0);
  }
  static Self nil() {
    Self res;
    res.value = -1;
    return res;
  }
  bool is_nil() {
    return value == -1;
  }
  explicit operator Type() const { return value; }
  static Type modulus() { return MOD; }
  static Type primitive_root() { return Modular::primitive_root; }
  Self operator-() const { return Self(0) - *this; }
  template <class F>
  static enable_if_t<is_integral_v<F>, Self> of(F v) {
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
  Self operator+(const Self &rhs) const {
    auto res = value + rhs.value;
    if (res >= MOD) {
      res -= MOD;
    }
    return res;
  }
  Self operator-(const Self &rhs) const {
    auto res = value - rhs.value;
    if (res < Type(0)) {
      res += MOD;
    }
    return res;
  }
  Self operator/(const SELF &rhs) const {
    auto inv = Self(rhs.possible_inv().value());
    return (*this) * inv;
  }
  bool operator==(const Self &b) const { return value == b.value; }
  bool operator!=(const Self &b) const { return value != b.value; }
  bool operator<(const Self &b) const { return value < b.value; }
  ImplDefaultComparision(Self);
  ImplArithmeticAssignOperation(Self);
  template <class E>
  enable_if_t<is_integral_v<E>, Self> pow(E n) {
    return PowBinaryLift(*this, n);
  }
  friend inline IStream &operator>>(IStream &is, Self &x) {
    Type val;
    is >> val;
    x = Self::of(val);
    return is;
  }
  friend inline OStream &operator<<(OStream &os, const Self &x) {
    os << x.value;
    return os;
  }
};
TEMPLATE_ARGS inline enable_if_t<!is_same_v<MODULAR, MOD_BIG>, SELF> operator*(
    const SELF &a, const SELF &b) {
  return SELF(MulMod(a.value, b.value, MOD));
}
TEMPLATE_ARGS inline enable_if_t<is_same_v<MODULAR, MOD_BIG>, SELF> operator*(
    const SELF &x, const SELF &y) {
  static u64 mask = (u64(1) << 32) - 1;
  static u64 mod = MOD_BIG::modulus;
  u64 a = x.value;
  u64 b = y.value;
  u64 l1 = a & mask;
  u64 h1 = (a >> 32) & mask;
  u64 l2 = b & mask;
  u64 h2 = (b >> 32) & mask;
  u64 l = l1 * l2;
  u64 m = l1 * h2 + l2 * h1;
  u64 h = h1 * h2;
  u64 ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
  ret = (ret & mod) + (ret >> 61);
  ret = (ret & mod) + (ret >> 61);
  return SELF(ret - 1);
}

TEMPLATE_ARGS struct is_modint<ModInt<MODULAR>> {
  static const bool value = true;
};
TEMPLATE_ARGS struct is_modint_32<ModInt<MODULAR>> {
  static const bool value = is_same_v<typename MODULAR::Type, i32>;
};
#undef TEMPLATE_TYPE
#undef MOD
using ModInt998244353 = ModInt<MOD998244353>;
using ModInt1000000007 = ModInt<MOD1000000007>;
using ModInt1000000009 = ModInt<MOD1000000009>;
using ModInt1004535809 = ModInt<MOD1004535809>;
}  // namespace dalt
#pragma once
#include "common.cpp"
#include "gcd.cpp"
#include "modint.cpp"
namespace dalt {
namespace math {
#define CID -202202141300
template <class T>
struct CRT {
  static_assert(is_integral_v<T>);
  T r, m;
  bool valid;
  CRT() {
    r = T(0);
    m = T(1);
    valid = true;
  }
  bool add(T _r, T _m) {
    if (!valid) {
      return false;
    }
    T m1 = m;
    T x1 = r;
    T m2 = _m;
    T x2 = _r % _m;
    auto gcd_res = ExtGcd(m1, m2);
    T g = gcd_res[2];
    T a = gcd_res[0];
    if ((x2 - x1) % g != 0) {
      return valid = false;
    }
    using MOD = modint::DynamicModular<T, CID>;
    using Mi = modint::ModInt<MOD>;
    m = m1 / g * m2;
    MOD::Register(m, -1);
    r = (Mi(a) * Mi((x2 - x1) / g) * Mi(m1) + Mi(x1)).value;
    return true;
  }
};
template <class T>
OStream& operator<<(OStream& os, const CRT<T>& crt) {
  os << "CRT{ ? % " << crt.m << " = " << crt.r << "}";
}
#undef CID
}  // namespace math
}  // namespace dalt
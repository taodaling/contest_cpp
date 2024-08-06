#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct Affine {
  using Self = Affine;
  T a, b;
  Affine(T _a, T _b) : a(_a), b(_b) {}
  Affine(T _b = T(0)) : Affine(0, _b) {}
  friend Self operator+(const Self& lhs, const Self& rhs) {
    return Self(lhs.a + rhs.a, lhs.b + rhs.b);
  }
  friend Self operator-(const Self& lhs, const Self& rhs) {
    return Self(lhs.a - rhs.a, lhs.b - rhs.b);
  }
  static Self compose(const Self& lhs, const Self& rhs) {
    return Self(lhs.a * rhs.a, lhs.a * rhs.b + lhs.b);
  }
  friend Self operator*(const Self& lhs, const T& rhs) {
    return Self(lhs.a * rhs, lhs.b * rhs);
  }
  friend Self operator*(const T& lhs, const Self& rhs) { return rhs * lhs; }
  friend Self operator/(const Self& lhs, const T& rhs) {
    return Self(lhs.a / rhs, lhs.b / rhs);
  }
  T operator()(T x) const { return a * x + b; }
  static Self MulIdentity() { return Self(T(1), T(0)); }
  static Self add_identity() { return Self(T(0), T(0)); }
};
template<class T>
OStream& operator<<(OStream& os, const_ref(Affine<T>) a){
  os << a.a << "x + "<< a.b;
  return os;
}
}  // namespace dalt
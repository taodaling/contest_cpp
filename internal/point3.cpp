#pragma once
#include "common.cpp"
#include "near_value.cpp"
namespace dalt {
namespace geo3 {
template <class T>
struct Point3 {
  static_assert(is_near_value_v<T>);
  using Self = Point3<T>;
  using Type = T;
  using TType = typename T::Type;
  using FType = typename T::FType;
  using p3 = Self;
  T x, y, z;
  // Basic vector operations
  p3 operator+(p3 p) const { return {x + p.x, y + p.y, z + p.z}; }
  p3 operator-(p3 p) const { return {x - p.x, y - p.y, z - p.z}; }
  p3 operator*(T d) const { return {x * d, y * d, z * d}; }
  IsBool(is_floating_point_v<TType>, p3)
  operator/(T d) const {
    return {x / d, y / d, z / d};
  }  // only for floating-point
     // Some comparators
  bool operator==(p3 p) const { return tie(x, y, z) == tie(p.x, p.y, p.z); }
  bool operator!=(p3 p) const { return !operator==(p); }
  T operator|(p3 w) const {
    var &v = *this;
    return v.x * w.x + v.y * w.y + v.z * w.z;
  }
  static p3 zero() {
    return {T(0), T(0), T(0)};
  }
  T sq() const { return (*this) | (*this); }
  FType abs() const { return sq().sqrt(); }
  IsBool(is_floating_point_v<T>, p3) unit() const { return (*this) / abs(); }
  static FType angle(p3 v, p3 w) {
    var cosTheta = (v | w) / abs(v) / abs(w);
    return Max(FType(-1.0), Min(FType(1.0), cosTheta)).acos();
  }
  p3 operator*(p3 w) const {
    var &v = *this;
    return {v.y * w.z - v.z * w.y, v.z * w.x - v.x * w.z,
            v.x * w.y - v.y * w.x};
  }
  //postive if PS is upper plane(PQ, PR)
  //0 if PS on plane
  //negative if PS is under plane(PQ, PR)
  static int orient(p3 Q, p3 R, p3 S, p3 P) {
    return ((Q - P) * (R - P) | (S - P)).sign();
  }
  static int orient(p3 Q, p3 R, p3 S) {
    return (Q * R | S).sign();
  }
  //given normal perpendicular to plane N
  //return orient of p'q' and p'r' where x' means the projection of x on plane N 
  static int orientByNormal(p3 p, p3 q, p3 r, p3 n) { return ((q - p) * (r - p) | n).sign(); }
  static FType smallAngle(const_ref(p3) v, const_ref(p3) w) {
    return (Min((v | w).abs() / v.abs() / w.abs(), FType(1.0))).acos();
  }
  friend OStream& operator<<(OStream& os, const_ref(p3) p) {
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
  }
};
}  // namespace geo3
}  // namespace dalt
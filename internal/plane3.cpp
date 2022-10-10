#pragma once
#include "point3.cpp"
namespace dalt {
namespace geo3 {
template <class T>
struct Plane3 {
  static_assert(is_near_value_v<T>);
  using Self = Plane3<T>;
  using Type = T;
  using TType = typename T::Type;
  using FType = typename T::FType;
  using p3 = Point3<T>;
  using plane = Self;
  p3 n;
  T d;
  // From normal n and offset d
  Plane3(p3 n, T d) : n(n), d(d) {}
  // From normal n and point P
  Plane3(p3 n, p3 p) : n(n), d(n | p) {}
  // From three non-collinear points P,Q,R
  Plane3(p3 p, p3 q, p3 r) : Plane3((q - p) * (r - p), p) {}
  // Will be defined later:
  // - these work with T = int
  T side(p3 p) const { return (n | p) - d; }
  FType dist(p3 p) const { return side(p).abs() / n.abs(); }
  plane translate(p3 t) const { return {n, d + (n | t)}; }
  // - these require T = double
  plane shiftUp(FType dist) const { return {n, d + dist * n.abs()}; }
  IsBool(is_floating_point_v<TType>, p3) proj(p3 p) const {
    return p - n * p.side() / n.sq();
  }
  IsBool(is_floating_point_v<TType>, p3) refl(p3 p) const {
    return p - n * 2 * p.side() / n.sq();
  }
  static FType angle(const_ref(plane) p1, const_ref(plane) p2) {
    return p3::smallAngle(p1.n, p2.n);
  }
  static bool isParallel(const_ref(plane) p1, const_ref(plane) p2) {
    return p1.n * p2.n == p3::zero();
  }
  static bool isPerpendicular(const_ref(plane) p1, const_ref(plane) p2) {
    return (p1.n | p2.n) == T(0);
  }
};
}  // namespace geo3
}  // namespace dalt
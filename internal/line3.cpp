#pragma once
#include "point3.cpp"
#include "plane3.cpp"
namespace dalt {
namespace geo3 {
template <class T>
struct Line3 {
  static_assert(is_near_value_v<T>);
  using Self = Line3<T>;
  using Type = T;
  using TType = typename T::Type;
  using FType = typename T::FType;
  using p3 = Point3<T>;
  using plane = Plane3<T>;
  using line3d = Self;
  p3 d, o;
  // From two points P, Q
  Line3(const_ref(p3) p, const_ref(p3) q) : d(q - p), o(p) {}
  // From two planes p1, p2 (requires T = double)
  Line3(const_ref(plane) p1, const_ref(plane) p2) {
    d = p1.n * p2.n;
    o = (p2.n * p1.d - p1.n * p2.d) * d / d.sq();
  }
  // Will be defined later:
  // - these work with T = int
  FType sqDist(const_ref(p3) p) const { return (d * (p - o)).sq() / d.sq(); }
  FType dist(const_ref(p3) p) const { return std::sqrt(sqDist(p)); }
  bool cmpProj(const_ref(p3) p, const_ref(p3) q) const { return (d | p) < (d | q); }
  // - these require T = double
  IsBool(is_floating_point_v<TType>, p3)
  proj(const_ref(p3) p) const { return o + d * (d | (p - o)) / sq(d); }
  p3 refl(const_ref(p3) p) const { return proj(p) * 2 - p; }
  //intersection with plane
  IsBool(is_floating_point_v<TType>, p3)
  inter(const_ref(plane) p) const {
    return o - d * p.side(o) / (d | p.n);
  }
  static FType dist(const line3d& l1, const line3d& l2) {
    p3 n = l1.d * l2.d;
    if (n == p3 {0, 0, 0})  // parallel
      return l1.dist(l2.o);
    return ((l2.o - l1.o) | n).abs() / n.abs();
  }
  IsBoolStatic(is_floating_point_v<TType>, p3)
  closestOnL1(const line3d& l1, const line3d& l2) {
    p3 n2 = l2.d * (l1.d * l2.d);
    return l1.o + l1.d * ((l2.o - l1.o) | n2) / (l1.d | n2);
  }
  static FType angle(const_ref(line3d) l1, const_ref(line3d) l2) { return p3::smallAngle(l1.d, l2.d); }
  static bool isParallel(const_ref(line3d) l1, const_ref(line3d) l2) {
    return l1.d * l2.d == p3::zero();
  }
  static bool isPerpendicular(const_ref(line3d) l1, const_ref(line3d) l2) {
    return (l1.d | l2.d) == T(0);
  }

  static FType angle(const_ref(plane) p, const_ref(line3d) l) { return M_PI / 2 - smallAngle(p.n, l.d); }
  static bool isParallel(const_ref(plane) p, const_ref(line3d) l) {
    return (p.n | l.d) == T(0);
  }
  static bool isPerpendicular(const_ref(plane) p, const_ref(line3d) l) {
    return p.n * l.d == p3::zero();
  }
  static line3d perpThrough(plane p, p3 o) { return line3d(o, o + p.n); }
  static plane perpThrough(line3d l, p3 o) { return plane(l.d, o); }
};
}  // namespace geo3
}  // namespace dalt
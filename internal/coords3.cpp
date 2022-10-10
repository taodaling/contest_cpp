#pragma once
#include "point3.cpp"
namespace dalt {
namespace geo3 {
template <class T>
struct Coords3 {
  static_assert(is_near_value_v<T>);
  using Self = Plane3<T>;
  using Type = T;
  using FType = typename T::FType;
  using p3 = Point3<T>;
  p3 o, dx, dy, dz;
  Coords3(p3 p, p3 q, p3 r) : o(p) {
    dx = (q - p).unit();
    dz = (dx * (r - p)).unit();
    dy = dz * dx;
  }
  Coords3(p3 p, p3 q, p3 r, p3 s) : o(p), dx(q - p), dy(r - p), dz(s - p) {}
  pt pos2d(p3 p) const { return {(p - o) | dx, (p - o) | dy}; }
  p3 pos3d(p3 p) const { return {(p - o) | dx, (p - o) | dy, (p - o) | dz}; }
};
}  // namespace geo3
}  // namespace dalt
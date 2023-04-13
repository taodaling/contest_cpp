#pragma once
#include "gcd.cpp"
#include "near_value.cpp"
#include "optional.cpp"
namespace dalt {
namespace geo2 {
template <class T>
struct Point {
  static_assert(is_near_value_v<T>);
  using Self = Point<T>;
  using Type = T;
  using FType = typename T::FType;
  T x;
  T y;
  Point(T _x = T(0), T _y = T(0)) : x(_x), y(_y) {}
  Self operator+(const Self& rhs) const { return {x + rhs.x, y + rhs.y}; }
  Self operator-(const Self& rhs) const { return {x - rhs.x, y - rhs.y}; }
  T cross_product(const Self& rhs) { return x * rhs.y - y * rhs.x; }
  Self operator*(const Self& rhs) const {
    return {x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x};
  }
  Self operator/(const Self& rhs) const {
    return *this * rhs.conj() / rhs.square();
  }
  Self operator*(const T& rhs) const { return {x * rhs, y * rhs}; }
  Self operator/(const T& rhs) const { return {x / rhs, y / rhs}; }
  bool operator<(const Self& rhs) const {
    return MakePair(x, y) < MakePair(rhs.x, rhs.y);
  }
  ImplDefaultComparision(Self);
  bool operator==(const Self& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Self& rhs) const { return !(*this == rhs); }
  T square() const { return Self::dot(*this, *this); }
  FType abs() const{ return square().sqrt(); }
  static T dist2(const Self& lhs, const Self& rhs) {
    return (lhs - rhs).square();
  }
  static FType dist(const Self& lhs, const Self& rhs) {
    return (lhs - rhs).abs();
  }
  Self operator-() const { return {-x, -y}; }

  //(-pi,pi]
  FType atan2() const {
    return T::atan2(y, x);
  }
  static int half(T x, T y) {
    return y > T(0) || y == T(0) && x < T(0) ? 1 : 0;
  }
  int half() const { return half(x, y); }
  Self norm(T d = T(1)) const { return *this * d / abs(); }
  Self conj() const { return {x, -y}; }
  //count-clockwise rotate pi/2
  Self perpendicular() const { return {-y, x}; }
  static Self rotate(const Self& pt, FType cos, FType sin,
                     const Self& center = Self()) {
    auto a = pt - center;
    return {a.x * cos - a.y * sin, a.x * sin + a.y * cos};
  }
  static Self rotate(const Self& a, FType angle, const Self& center = Self()) {
    return rotate(a, Cos(angle), Sin(angle), center);
  }
  static T dot(const Self& lhs, const Self& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  static T cross(const Self& lhs, const Self& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
  static T cross(const Self& base, const Self& lhs, const Self& rhs) {
    return cross(lhs - base, rhs - base);
  }
  static bool is_perpendicular(const Self& lhs, const Self& rhs) {
    return dot(lhs, rhs) == T(0);
  }
  static bool is_parallel(const Self& lhs, const Self& rhs) {
    return lhs.cross_product(rhs) == T(0);
  }
  // ret \in [0, pi)
  static FType angle(const Self& lhs, const Self& rhs) {
    return Acos(Clamp<FType>(dot(lhs, rhs).value / lhs.abs() / rhs.abs(),
                             FType(-1), FType(1)));
  }

  static int orient(const Self& b, const Self& c) { return cross(b, c).sign(); }
  //获取c处于ab的方向，-1表示順時針方向，1表示逆時針，0表示在綫上
  static int orient(const Self& a, const Self& b, const Self& c) {
    return orient(b - a, c - a);
  }
  static bool in_angle(const Self& b, const Self& c, const Self& p,
                       const Self& center = Self()) {
    if (orient(b, c, center) < 0) {
      Swap(b, c);
    }
    return orient(b, p, center) >= 0 && orient(c, p, center) <= 0;
  }
  static FType oriented_angle(const Self& a, const Self& b,
                              const Self& center = Self()) {
    FType angle = Self::angle(a - center, b - center);
    if (orient(a, b, center) >= 0) {
      return angle;
    } else {
      return 2 * M_PI - angle;
    }
  }
  Self linear_transform(const Self& p, const Self& fp, const Self& q,
                        const Self& fq) const {
    return fp + (*this - p) * ((fq - fp) / (q - p));
  }
  //判断c是否落在以a与b为直径两端的圆中（包含边界）
  static bool in_disk(const Self& a, const Self& b, const Self& c) {
    return dot(a - c, b - c).sign() <= 0;
  }
  //判断c是否在a到b的线段上
  static bool on_segment(const Self& a, const Self& b, const Self& c) {
    return orient(a, b, c) == 0 && in_disk(a, b, c);
  }
  //获取线段a->b与线段c->d的交点
  static Optional<Self> proper_intersect(const Self& a, const Self& b,
                                         const Self& c, const Self& d) {
    T oa = cross(d - c, a - c);
    T ob = cross(d - c, b - c);
    T oc = cross(b - a, c - a);
    T od = cross(b - a, d - a);
    if (oa * ob < T(0) && oc * od < T(0)) {
      return (a * (ob / (ob - oa))) + (b * (-oa / (ob - oa)));
    }
    return {};
  }
  static Optional<Self> intersect(const Self& a, const Self& b, const Self& c,
                                  const Self& d) {
    auto pt = proper_intersect(a, b, c, d);
    if (pt.is_none() && on_segment(a, b, c)) {
      pt = c;
    }
    if (pt.is_none() && on_segment(a, b, d)) {
      pt = d;
    }
    if (pt.is_none() && on_segment(c, d, a)) {
      pt = a;
    }
    if (pt.is_none() && on_segment(c, d, b)) {
      pt = b;
    }
    return pt;
  }
  static int above(const Self& a, const Self& b) { return b.y >= a.y ? 1 : 0; }
  static bool cross_ray(const Self& a, const Self& p, const Self& q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
  }
  static Self mirror(const Self& symmetric_center, const Self& a) {
    return {symmetric_center.x * 2 - a.x, symmetric_center.y * 2 - a.y};
  }
  static FType distanceToLine(const Self& a, const Self& b, const Self& c) {
    FType len = dist(a, b);
    if (len == 0) {
      return dist(a, c);
    }
    FType area2 = FType(Abs(cross(a - c, b - c)));
    return area2 / len;
  }
  template <class Arg = Type>
  static enable_if_t<is_same_v<Arg, Type> && is_integral_v<typename Type::Type>,
                     Type>
  lattice_point_number_on_segment(const Self& a, const Self& b) {
    T dx = (a.x - b.x).abs();
    T dy = (a.y - b.y).abs();
    auto gcd = Gcd(dx.value, dy.value);
    return Type(gcd + 1);
  }
};
template <class T>
struct SortByPolarAngleAround {
  using Pt = Point<T>;
  Pt center;
  SortByPolarAngleAround(Pt _center = Pt()) : center(_center) {}
  bool operator()(const Pt& a, const Pt& b) const { return compare(a, b) < 0; }
  int compare(const Pt& a, const Pt& b) const {
    int a_half = (a - center).half();
    int b_half = (b - center).half();
    if (a_half != b_half) {
      return a_half - b_half;
    }
    return Pt::orient(center, b, a);
  }
};
template <class T>
OStream& operator<<(OStream& os, const Point<T>& pt) {
  os << MakeTuple(pt.x, pt.y);
  return os;
}

}  // namespace geo2
}  // namespace dalt
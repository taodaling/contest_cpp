#pragma once
#include "point2.cpp"
namespace dalt {
namespace geo2 {
template <class T>
struct Polygon {
  using Type = Point<T>;
  using Pt = Type;
  Vec<Pt> data;
  Polygon(Vec<Pt> _data) : data(Move(_data)) {}

  int size() const { return data.size(); }
  Pt& operator[](int index) { return data[index]; }
  const Pt& operator[](int index) const { return data[index]; }
  bool is_convex() const {
    bool has_pos = false;
    bool has_neg = false;
    for (int i = 0, n = Size(data); i < n; i++) {
      int o = Pt::orient(data[(i + 1) % n], data[(i + 2) % n], data[i]);
      if (o > 0) {
        has_pos = true;
      }
      if (o < 0) {
        has_neg = true;
      }
    }
    return !(has_pos && has_neg);
  }
  //判断某个顶点是否落在矩形内，1表示矩形内，2表示矩形边缘，0表示矩形外
  int in_polygon(const Pt& pt) const {
    int cross = 0;
    for (int i = 0, n = Size(data); i < n; i++) {
      auto& cur = data[i];
      auto& next = data[(i + 1) % n];
      if (Pt::on_segment(cur, next, pt)) {
        return 2;
      }
      if (Pt::cross_ray(pt, cur, next)) {
        cross++;
      }
    }
    return cross & 1;
  }
  T area_2() const {
    T sum = 0;
    for (int i = 0, n = Size(data); i < n; i++) {
      sum = sum + Pt::cross(data[i], data[(i + 1) % n]);
    }
    return sum.abs();
  }
  T area() const { return area_2() / T(2); }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<typename T::Type>, T>
  lattice_point_number_on_boundary() const {
    T sum = T(0);
    for (int i = 0, n = Size(data); i < n; i++) {
      auto& cur = data[i];
      auto& next = data[(i + 1) % n];
      sum = sum + Pt::lattice_point_number_on_segment(cur, next);
    }
    sum = sum - T(Size(data));
    return sum;
  }
  // pick theorem
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<typename T::Type>, T>
  lattice_point_number_inside() const {
    return (area_2() + T(2) - lattice_point_number_on_boundary()) / T(2);
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<typename T::Type>, T>
  lattice_point_number_inside_or_on_boundary() const {
    return (area_2() + T(2) + lattice_point_number_on_boundary()) / T(2);
  }
};
}  // namespace geo2
}  // namespace dalt
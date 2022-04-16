#pragma once
#include "line2.cpp"
namespace dalt {
namespace geo2 {
template <class T>
struct Circle {
  static_assert(is_near_value_v<T>);
  using Pt = Point<T>;
  using Ln = Line<T>;
  using Self = Circle<T>;
  Pt center;
  T r;
  Circle(Pt _pt, T _r) : center(_pt), r(_r) {}
  bool contain(Pt pt, bool include_boarder = true) const {
    if (include_boarder) {
      return Pt::dist2(center, pt) <= r * r;
    } else {
      return Pt::dist2(center, pt) < r * r;
    }
  }
  Vec<Pt> intersect(Ln line) const {
    Pt proj = line.projection(center);
    if (!contain(proj)) {
      return {};
    }
    T h = (r * r - Pt::dist2(proj, center)).sqrt();
    if (h == T(0)) {
      return {proj};
    } else {
      Pt vec = line.vec.norm(h);
      return {proj + vec, proj - vec};
    }
  }
  Vec<T> intersect(const Self& c1, const Self& c2) {
    Pt d = c2.center - c1.center;
    T d2 = d.square();
    if (d2 == T(0)) {
      return {T(0)};
    }
    T pd = (d2 + c1.r * c1.r - c2.r * c2.r) / T(2);
    T h2 = c1.r * c1.r - pd * pd / d2;
    if (h2 >= T(0)) {
      Pt p = c1.center + d * (pd / d2);
      if (h2 == T(0)) {
        return {p};
      }
      Pt h = d.perpendicular() * (h2 / d2).sqrt();
      return {p - h, p + h};
    }
    return {};
  }
  static T det(T a11, T a12, T a21, T a22, T a31, T a32) {
    return a11 * a22 - a21 * a12 - a11 * a32 + a31 * a12 + a21 * a32 -
           a31 * a22;
  }
  static Self from_diameter(Pt a, Pt b) {
    return Circle((a + b) / T(2), (a - b).abs());
  }
  static Self outer_circle_of_triangle(Pt A, Pt B, Pt C) {
    T a = Pt::dist(B, C);
    T b = Pt::dist(A, C);
    T c = Pt::dist(A, B);
    T area = Pt::cross(A, B, C).abs() / T(2);
    T r = a * b * c / T(4) / area;
    T bot = det(A.x, A.y, B.x, B.y, C.x, C.y) * T(2);
    T x = det(A.square(), A.y, B.square(), B.y, C.square(), C.y) / bot;
    T y = det(A.x, A.square(), B.x, B.square(), C.x, C.square()) / bot;
    return Self(Pt(x, y), r);
  }
  static Self inner_circle_of_triangle(Pt A, Pt B, Pt C) {
    T a = T::dist(B, C);
    T b = T::dist(A, C);
    T c = T::dist(A, B);
    T area = Pt::cross(A, B, C).abs() / T(2);
    T r = area * T(2) / (a + b + c);
    T x = (a * A.x + b * B.x + c * C.x) / (a + b + c);
    T y = (a * A.y + b * B.y + c * C.y) / (a + b + c);
    return Self(Pt(x, y), r);
  }
  Pt point_on_boarder(T radian) const {
    T x = radian.cos();
    T y = radian.sin();
    return center + Pt(x, y) * r;
  }
  static Self min_circle_cover(Vec<T> pts) {
    Shuffle(All(pts));
    Self circle(Pt(), T(0));
    for (int i = 0; i < Size(pts); i++) {
      if (circle.contain(pts[i])) {
        continue;
      }
      circle = Self(pts[i], 0);
      for (int j = 0; j < i; j++) {
        if (circle.contain(pts[j])) {
          continue;
        }
        circle = from_diameter(pts[i], pts[j]);
        for (int k = 0; k < j; k++) {
          if (circle.contain(pts[k])) {
            continue;
          }
          circle = outer_circle_of_triangle(pts[i], pts[j], pts[k]);
        }
      }
    }
    return circle;
  }
  static Vec<Pt> tangent(Self c1, Self c2, bool inner) {
    Pt o1 = c1.center;
    T r1 = c1.r;
    Pt o2 = c2.center;
    T r2 = c2.r;
    if (inner) {
      r2 = -r2;
    }
    Pt d = o2 - o1;
    T dr = r1 - r2, d2 = d.square(), h2 = d2 - dr * dr;
    if (d2 == T(0) || h2 < T(0)) {
      Assert(h2 != T(0));
      return 0;
    }
    T sqrtH2 = h2.sqrt();
    Vec<T> ans;
    ans.reserve(4);
    for (int sign = -1; sign <= 1; sign += 2) {
      Pt v = d * (dr / d2) + d.perpendicular() * (sqrtH2 * sign / d2);
      ans.push_back(o1 + v * r1);
      ans.push_back(o2 + v * r2);
    }
    return ans;
  }
};
}  // namespace geo2
}  // namespace dalt
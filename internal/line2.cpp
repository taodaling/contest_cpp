#pragma once
#include "point2.cpp"
namespace dalt {
namespace geo2 {
template <class T>
struct Line {
  static_assert(is_near_value_v<T>);
  using Self = Line<T>;
  using Pt = Point<T>;

 private:
  T side0(const Pt& pt) const {
    Debug(Pt::cross(vec, pt) - c);
    return Pt::cross(vec, pt) - c;
  }

public:

 Pt vec;
 T c;

 Line(const Pt& _vec = Pt(), T _c = T()) : vec(_vec), c(_c) {}
 Pt any() const {
   T a = -vec.y;
   T b = vec.x;
   if (a.sign() != 0) {
     return Pt(c / a, T(0));
   } else {
     return Pt(T(0), c / b);
   }
  }
  //ax + by = c
  static Pt from_formula(T a, T b, T c) {
    return Self(Pt(b, -a), c);
  }
  static Self from_ends(const Pt& a, const Pt& b) {
    Pt vec = b - a;
    return Self(vec, Pt::cross(vec, a));
  }
  //如果pt在逆时针方向，返回1，顺时针方向返回-1，否则返回0
  int side(const Pt& pt) const {
     auto ans = side0(pt);
     return ans.sign();
  }
  T dist(const Pt& pt) const { return side0(pt).abs() / vec.abs(); }
  T square_dist(const Pt& pt) const { return Pow2(side0(pt)) / vec.square(); }
  Self perpendicular_through(const Pt& pt) const {
    return Self(pt, pt + vec.perpendicular());
  }
  //判断一条平行的直线处于当前的上方还是下方，上方为1，下方为-1，重合为0
  int side(const Self& line) const {
    return side(line.any());
  }
  Comparator<Pt> sort_point_on_line() const {
    return [=](const Pt& a, const Pt& b) {
      return Pt::dot(a, vec) < Pt::dot(b, vec); 
    };
  }
  Self translate(Pt pt) const {
    return Self(vec, c + Pt::cross(vec, pt));
  }
  friend Self operator+(const Self& line, const Pt& pt) {
    return line.translate(pt);
  }
  Self shift_left(T dist) const {
    return Self(vec, c + dist * vec.abs());
  }
  static Optional<Pt> intersect(const Self& a, const Self& b) {
    T d = Pt::cross(a.vec, b.vec);
    if(d.sign() == 0) {
      return {};
    }
    return (b.vec * a.c - a.vec * b.c) / d;
  }
  Pt projection(const_ref(Pt) pt) const {
    T factor = side0(pt) / vec.square();
    return Pt(pt.x - (-vec.y * factor), pt.y - vec.x * factor);
  }
  Pt reflect(const_ref(Pt) pt) const {
    return pt - vec.perpendicular() * (2 * side0(pt) / vec.square);
  } 
  Comparator<Pt> sort_point_along_line() const {
    return [=] (const Pt& a, const Pt& b) {
      return Pt::dot(vec, a) < Pt::dot(vec, b);
    };
  }
  friend OStream& operator<<(OStream& os, const Self& line) {
    os << -line.vec.y << "x + " << line.vec.x << "y = " << line.c;
    return os;
  }
};

}  // namespace geo2
}  // namespace dalt
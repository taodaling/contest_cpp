#pragma once
#include "common.cpp"
#include "nil.cpp"
#include "prefer_div.cpp"
namespace dalt {
template <class T, class I = Nil>
struct CHTLine {
  using Self = CHTLine;
  Nil id;
  T a;
  T b;
  mutable T l;
  mutable T r;
  T apply(T x) const { return a * x + b; }
  bool empty() const { return l >= r; }
  bool operator==(const Self &rhs) const { return l == rhs.l && r == rhs.r; }
  bool operator!=(const Self &rhs) const { return !(*this == rhs); }
};
template <class T, class I>
OStream &operator<<(OStream &os, const CHTLine<T, I> &line) {
  os << line.a << "x + " << line.b;
  return os;
}
template <class T, class I = Nil>
struct ConvexHullTrick {
  static_assert(is_floating_point_v<T> || is_integral_v<T>,
                "only integer and float are supported");

  using L = CHTLine<T, I>;
  struct SortLineByA {
    bool operator()(const L &a, const L &b) const { return a.a < b.a; }
  };
  struct SortLineByLeft {
    bool operator()(const L &a, const L &b) const { return a.l < b.l; }
  };
  using Self = ConvexHullTrick<T, I>;
  using SA = TreeSet<L, SortLineByA>;
  using SL = TreeSet<L, SortLineByLeft>;
  SA sort_by_a;
  SL sort_by_l;
  T constant;

 private:
  const static T INF = std::numeric_limits<T>::max() / 2;
  T intersect(const L &x, const L &y) {
    Assert(y.a > x.a);
    return DivCeil(x.b - y.b, y.a - x.a);
  }
  void add(L line) {
    sort_by_a.insert(line);
    sort_by_l.insert(line);
  }
  Vec<L> to_vec_l() { return Vec<L>(sort_by_l.begin(), sort_by_l.end()); }

 public:
  // call this method for id only
  const L &best_line(T x) const {
    L q;
    q.l = x;
    auto iter = sort_by_l.lower_bound(q);
    if (iter == sort_by_l.end() || iter->l > x) {
      iter--;
    }
    return *iter;
  }
  // max_i Line[i](x)
  T query(T x) const { return best_line(x).apply(x) + constant; }
  void global_add(T x) { constant = constant + x; }
  void insert(T a, T b, I id = I()) {
    b = b - constant;
    L line{
        .id = id,
        .a = a,
        .b = b,
    };

    auto ceil_a = sort_by_a.lower_bound(line);
    auto ceil_l = ceil_a == sort_by_a.end() ? sort_by_l.end()
                                            : sort_by_l.lower_bound(*ceil_a);
    if (ceil_a != sort_by_a.end() && ceil_a->a == line.a) {
      if (ceil_a->b >= line.b) {
        return;
      }
      ceil_a = sort_by_a.erase(ceil_a);
      ceil_l = sort_by_l.erase(ceil_l);
    }
    while (true) {
      if (ceil_a == sort_by_a.end()) {
        line.r = INF;
        break;
      }
      T r = intersect(line, *ceil_a);
      if (r >= ceil_a->r) {
        ceil_a = sort_by_a.erase(ceil_a);
        ceil_l = sort_by_l.erase(ceil_l);
        continue;
      }
      ceil_l->l = ceil_a->l = Max(ceil_a->l, r);
      line.r = r;
      break;
    }
    while (true) {
      if (ceil_a == sort_by_a.begin()) {
        line.l = -INF;
        break;
      }
      ceil_a--;
      ceil_l--;
      T r = intersect(*ceil_a, line);
      if (r <= ceil_a->l) {
        ceil_a = sort_by_a.erase(ceil_a);
        ceil_l = sort_by_l.erase(ceil_l);
        continue;
      }
      ceil_a->r = ceil_l->r = Min(ceil_a->r, r);
      line.l = r;
      break;
    }

    if (!line.empty()) {
      add(line);
    }

    Assert(to_vec() == to_vec_l());
  }
  Vec<L> to_vec() const {
    auto ans = Vec<L>(sort_by_a.begin(), sort_by_a.end());
    for (auto& l : ans) {
      l.b = l.b + constant;
    }
    return ans;
  }
};

}  // namespace dalt
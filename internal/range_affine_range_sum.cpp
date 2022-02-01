#pragma once
#include "../common.cpp"
#include "segtree.cpp"
namespace dalt {
template <class T> struct RangeAffineRangeSum {
private:
  using A = Array<T, 2>;
  SegTree<A, A> *st;

public:
  using Self = RangeAffineRangeSum<T>;
  RangeAffineRangeSum(int n, const Indexer<T> &indexer) {
    st = new SegTree<A, A>(
        n, A{0, 0}, A{1, 0},
        [&](auto a, auto b) {
          return A{a[0] + b[0], a[1] + b[1]};
        },
        [&](auto a, auto b) {
          return A{a[0] * b[0], b[0] * a[1] + b[1]};
        },
        [&](auto a, auto b) {
          return A{a[0] * b[0] + a[1] * b[1], a[1]};
        },
        [&](auto i) {
          return A{indexer(i), 1};
        });
  }
  T query(int L, int R) { return st->query(L, R)[0]; }
  void update(int L, int R, T a, T b) { return st->update(L, R, {a, b}); }
  Vec<T> to_vec() {
    auto Array_vec = st->to_vec();
    Vec<T> res;
    res.reserve(Array_vec.size());
    for (auto x : Array_vec) {
      res.push(x[0]);
    }
    return res;
  }

#ifdef DROP
  ~RangeAffineRangeSum() { delete st; }
#endif
};
} // namespace dalt
#pragma once
#include "common.cpp"
#include "segtree.cpp"
namespace dalt {
namespace sbt {
#define CID -202202131600
template <class T>
struct RangeAffineRangeSum {
 private:
  using A = Array<T, 2>;
  using ST = SegTree<A, A, NoTag, CID>;
  ST st;
  static bool initialized;

 public:
  static CONSTRUCT(_init) {
    init();
  }
  static void init() {
    initialized = true;
    ST::Register(
        A{0, 0}, A{1, 0},
        [&](auto a, auto b) {
          return A{a[0] + b[0], a[1] + b[1]};
        },
        [&](auto a, auto b) {
          return A{a[0] * b[0] + a[1] * b[1], a[1]};
        },
        [&](auto a, auto b) {
          return A{a[0] * b[0], b[0] * a[1] + b[1]};
        });
  }
  using Self = RangeAffineRangeSum<T>;
  RangeAffineRangeSum(int n, const Indexer<T> &indexer)
      : st(n, [&](auto i) -> A {
          return A{indexer(i), 1};
        }) {}
  T query(int L, int R) { return st.query_const(L, R)[0]; }
  void update(int L, int R, T a, T b) { return st.update(L, R, {a, b}); }
  Vec<T> to_vec() {
    auto data = st.to_vec();
    Vec<T> res;
    res.reserve(data.size());
    for (auto x : data) {
      res.push_back(x[0]);
    }
    return res;
  }
};
template <class T>
bool RangeAffineRangeSum<T>::initialized = false;
#undef CID
}  // namespace sbt
}  // namespace dalt
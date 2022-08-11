#pragma once
#include "common.cpp"
#include "segtree.cpp"
namespace dalt {
namespace sbt {
template <class T>
struct RangeAffineRangeSum {
  using Self = RangeAffineRangeSum<T>;
 private:
  using A = Array<T, 2>;
  using ST = SegTree<SelfBalanceTreeRegistry<A, A, 0, Self>, A, A, false, false, 0>;
  ST st;

  struct InitJob {
    InitJob() {
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
  };
  static InitJob init_job;

 public:
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
typename RangeAffineRangeSum<T>::InitJob RangeAffineRangeSum<T>::init_job;
}  // namespace sbt
}  // namespace dalt
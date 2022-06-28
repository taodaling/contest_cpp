#pragma once
#include "common.cpp"
#include "function.cpp"
#include "segtree.cpp"
namespace dalt {
namespace misc {
#define CID -202202131300
template <class T, class C = Less<T>>
struct StaticRectQuery {
  using PST = sbt::SegTree<i32, i32, true, false, 0, CID>;
  using Self = StaticRectQuery<T>;
  using Node = typename PST::Node;

 private:
  Vec<PST> psts;
  Vec<T> sorted_input;
  C comp;
  struct InitJob {
    InitJob() {
      PST::Register(
          0, 0, [](auto a, auto b) { return a + b; },
          [](auto a, auto b) { return a + b; },
          [](auto a, auto b) { return a + b; });
    }
  };
  static InitJob _init_job;

 public:


  StaticRectQuery(int n, const Indexer<T> &indexer, C _comp = C())
      : comp(_comp) {
    sorted_input = ExpandIndexer(n, indexer);
    Sort(All(sorted_input), comp);
    MakeUnique(sorted_input);
    psts.reserve(n + 1);
    psts.push_back(PST::MakePersistentTree(Size(sorted_input)));
    // debug(psts.back().to_vec());
    for (int i = 0; i < n; i++) {
      int val = LowerBound(All(sorted_input), indexer(i), comp) -
                sorted_input.begin();
      psts.push_back(psts.back().clone());
      psts.back().update(val, val, 1);
      // debug(psts.back().to_vec());
    }
  }

  int count_rect_point(int L, int R, T below, T top) {
    int below_value =
        LowerBound(All(sorted_input), below, comp) - sorted_input.begin();
    int top_value =
        (UpperBound(All(sorted_input), top, comp) - sorted_input.begin()) - 1;
    int plus = psts[R + 1].query_const(below_value, top_value);
    int sub = psts[L].query_const(below_value, top_value);
    return plus - sub;
  }
  Optional<T> kth_lowest_point(int L, int R, int k) {
    auto dfs = [&](auto &dfs, Node *a, Node *b, int l, int r,
                   int k) -> Optional<i32> {
      if (l == r) {
        if (k <= b->sum - a->sum) {
          return l;
        } else {
          return {};
        }
      }
      int m = (l + r) / 2;
      int left_cnt = b->left->sum - a->left->sum;
      if (left_cnt >= k) {
        return dfs(dfs, a->left, b->left, l, m, k);
      } else {
        return dfs(dfs, a->right, b->right, m + 1, r, k - left_cnt);
      }
    };
    // debug(psts[L].to_vec());
    // debug(psts[R + 1].to_vec());
    Optional<i32> offset =
        dfs(dfs, psts[L].tree, psts[R + 1].tree, 0, Size(sorted_input) - 1, k);
    return offset.map<T>([&](int i) { return sorted_input[i]; });
    // return res;
  }
};
#undef CID
template <class T, class C>
typename StaticRectQuery<T, C>::InitJob StaticRectQuery<T, C>::_init_job;
}  // namespace dalt
}
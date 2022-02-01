#include "../common.cpp"
#include "function.cpp"
#include "persistent_segtree.cpp"
namespace dalt {
namespace static_rect_query {
template <class T> struct StaticRectQuery {
  using PST = PersistentSegTree<i32, i32>;
  using Self = StaticRectQuery<T>;
  using Node = typename PST::Node;

private:
  Vec<PST> psts;
  Vec<T> sorted_input;
  Comparator<T> comp;

public:
  StaticRectQuery(int n, const Indexer<T> &indexer,
                  Comparator<T> _comp = less<T>())
      : comp(_comp) {
    sorted_input = ExpandIndexer(n, indexer);
    sort(All(sorted_input), comp);
    MakeUnique(sorted_input);
    psts.reserve(n + 1);
    auto simple_adder = [](auto a, auto b) { return a + b; };
    psts.push_back(PST(Size(sorted_input), 0, 0, simple_adder, simple_adder,
                       simple_adder));
    // debug(psts.back().to_vec());
    for (int i = 0; i < n; i++) {
      int val = LowerBound(All(sorted_input), indexer(i), comp) -
                sorted_input.begin();
      psts.push_back(psts.back().update(val, val, 1));
      // debug(psts.back().to_vec());
    }
  }

  int count_rect_point(int L, int R, T below, T top) {
    int below_value =
        LowerBound(All(sorted_input), below, comp) - sorted_input.begin();
    int top_value =
        (UpperBound(All(sorted_input), top, comp) - sorted_input.begin()) - 1;
    int plus = psts[R + 1].query(below_value, top_value);
    int sub = psts[L].query(below_value, top_value);
    return plus - sub;
  }
  Optional<T> kth_lowest_point(int L, int R, int k) {
    auto dfs = [&](auto &rec, Node *a, Node *b, int l, int r,
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
        return rec(rec, a->left, b->left, l, m, k);
      } else {
        return rec(rec, a->right, b->right, m + 1, r, k - left_cnt);
      }
    };
    // debug(psts[L].to_vec());
    // debug(psts[R + 1].to_vec());
    auto offset = dfs(dfs, psts[L].get_root(), psts[R + 1].get_root(), 0,
                      Size(sorted_input) - 1, k);
    TreeMapper<i32, T> TreeMapper = [&](auto i) { return sorted_input[i]; };
    return offset.TreeMap(TreeMapper);
  }
};
} // namespace static_rect_query
using static_rect_query::StaticRectQuery;
} // namespace dalt
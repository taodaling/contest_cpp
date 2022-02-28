#pragma once
#include "graph.cpp"
#include "multi_hash_base.cpp"
#include "collection.cpp"
namespace dalt {
namespace hash {
// ret[i] = the hash value of the whole tree if we regard i-th node as the root
// of the tree
//- time: O(n)
//- space: O(n)
template <class E>
Vec<i64> HashTreeAllRoot(const graph::Graph<E>& g) {
  static_assert(is_base_of_v<graph::BiBaseEdge, E>);
  using Mi = ModInt<MOD_BIG>;
  int n = Size(g);
  Vec<Mi> subtree_hash(n);
  auto down_up = [&](auto& down_up, i32 root, i32 rev) -> void {
    i32 m = Size(g[root]);
    Mi sum = Mi(0);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        continue;
      }
      auto& e = g[root][i];
      down_up(down_up, e.to, e.rev);
      sum = sum + subtree_hash[e.to];
    }
    subtree_hash[root] = MultiHashBase<Mi>::get(sum);
  };
  down_up(down_up, 0, -1);
  auto up_down = [&](auto& up_down, i32 root, i32 rev, Mi fa_hash) -> void {
    i32 m = Size(g[root]);
    Mi sum = Mi(0);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        sum = sum + fa_hash;
        continue;
      }
      auto& e = g[root][i];
      sum = sum + subtree_hash[e.to];
    }
    subtree_hash[root] = MultiHashBase<Mi>::get(sum);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        continue;
      }
      auto& e = g[root][i];
      auto truncated = MultiHashBase<Mi>::get(sum - subtree_hash[e.to]);
      up_down(up_down, e.to, e.rev, truncated);
    }
  };
  up_down(up_down, 0, -1, Mi(0));
  Vec<i64> ans = Cast<i64>(subtree_hash);
  return ans;
}

}  // namespace hash
}  // namespace dalt
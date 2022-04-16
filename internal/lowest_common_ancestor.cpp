#pragma once
#include "binary.cpp"
#include "graph.cpp"
namespace dalt {
namespace graph {
// credited to:
// https://github.com/indy256/codelibrary/blob/master/java/graphs/lca/LcaSchieberVishkin.java
template <class E>
struct LowestCommonAncestorBySchieberVishkin {
  static_assert(is_base_of_v<BiBaseEdge, E>);

 private:
  Vec<int> parent;
  Vec<int> pre_order;
  Vec<int> i;
  Vec<int> head;
  Vec<int> a;
  int time;
  const Graph<E> &tree;

  void dfs1(int u, int p) {
    parent[u] = p;
    i[u] = pre_order[u] = time++;
    for (auto &e : tree[u]) {
      int v = e.to;
      if (v == p) continue;
      dfs1(v, u);
      if (LowestOneBit(i[u]) < LowestOneBit(i[v])) {
        i[u] = i[v];
      }
    }
    head[i[u]] = u;
  }

  void dfs2(int u, int p, int up) {
    a[u] = up | LowestOneBit(i[u]);
    for (auto &e : tree[u]) {
      int v = e.to;
      if (v == p) continue;
      dfs2(v, u, a[u]);
    }
  }
  int enter_into_strip(int x, int hz) {
    if (LowestOneBit(i[x]) == hz) return x;
    int hw = 1 << Log2Floor(u32(a[x] & (hz - 1)));
    return parent[head[i[x] & -hw | hw]];
  }

 public:
  LowestCommonAncestorBySchieberVishkin(const Graph<E> &_tree,
                                        const Checker<int> &is_root)
      : tree(_tree) {
    int n = Size(tree);
    pre_order = Vec<int>(n);
    i = Vec<int>(n);
    head = Vec<int>(n);
    a = Vec<int>(n);
    parent = Vec<int>(n);
    time = 0;
    for (int i = 0; i < n; i++) {
      if (is_root(i)) {
        dfs1(i, -1);
        dfs2(i, -1, 0);
      }
    }
  }

  int lca(int x, int y) {
    int hb =
        i[x] == i[y] ? LowestOneBit(i[x]) : (1 << Log2Floor(u32(i[x] ^ i[y])));
    int hz = LowestOneBit(a[x] & a[y] & -hb);
    int ex = enter_into_strip(x, hz);
    int ey = enter_into_strip(y, hz);
    return pre_order[ex] < pre_order[ey] ? ex : ey;
  }
};
}  // namespace graph
}  // namespace dalt
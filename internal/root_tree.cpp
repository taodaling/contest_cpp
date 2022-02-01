#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
Vec<i32> DepthOnTree(const Vec<i32> &fa) {
  int n = Size(fa);
  Vec<i32> depth(n, -1);
  auto dfs = [&](auto &dfs, auto root) -> i32 {
    if (root == -1) {
      return -1;
    }
    if (depth[root] == -1) {
      depth[root] = dfs(dfs, fa[root]) + 1;
    }
    return depth[root];
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  return depth;
}
template <class E>
IsBiGraph(E, Vec<i32>)
    DepthOnTree(const Graph<E> &g, const Checker<int> &is_root) {
  int n = Size(g);
  Vec<i32> depth(n);
  auto dfs = [&](auto &dfs, int root, int rev) -> void {
    int n = Size(g[root]);
    for (int i = 0; i < n; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      depth[e.to] = depth[root] + 1;
      dfs(dfs, e.to, e.rev);
    }
  };
  for (int i = 0; i < n; i++) {
    if (is_root(i)) {
      dfs(dfs, i, -1);
    }
  }
  return depth;
}
template <class T, class E>
enable_if_t<is_base_of_v<BiBaseEdge, E> && is_base_of_v<WithWeight<T>, E>,
            Vec<T>>
DepthOnTreeWeight(const Graph<E> &g, const Checker<int> &is_root) {
  int n = Size(g);
  Vec<T> depth(n);
  auto dfs = [&](auto &dfs, int root, int rev) -> void {
    int n = Size(g[root]);
    for (int i = 0; i < n; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      depth[e.to] = depth[root] + e.weight;
      dfs(dfs, e.to, e.rev);
    }
  };
  for (int i = 0; i < n; i++) {
    if (is_root(i)) {
      dfs(dfs, i, -1);
    }
  }
  return depth;
}
template <class E>
IsBiGraph(E, Vec<i32>)
    FatherOnTree(const Graph<E> &g, const Checker<i32> &is_root) {
  int n = Size(g);
  Vec<i32> father(n, -1);
  auto dfs = [&](auto &dfs, int root, int rev) -> void {
    int n = Size(g[root]);
    for (int i = 0; i < n; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      father[e.to] = root;
      dfs(dfs, e.to, e.rev);
    }
  };
  for (int i = 0; i < n; i++) {
    if (is_root(i)) {
      dfs(dfs, i, -1);
    }
  }
  return father;
}
} // namespace graph
} // namespace dalt
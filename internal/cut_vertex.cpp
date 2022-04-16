#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Tuple<Vec<bool> COMMA Vec<bool> COMMA Vec<int>>)
    CutVertex(const Graph<E> &g) {
  int n = Size(g);
  Vec<int> depth(n);
  Vec<int> parent(n);
  Vec<bool> visit(n);
  auto dfs_tree = [&](auto &dfs, int root, int p) -> void {
    if (visit[root]) {
      return;
    }
    visit[root] = true;
    parent[root] = p;
    depth[root] = p == -1 ? 0 : depth[p] + 1;
    for (auto &e : g[root]) {
      dfs(dfs, e.to, root);
    }
  };
  for (int i = 0; i < n; i++) {
    dfs_tree(dfs_tree, i, -1);
  }
  visit = Vec<bool>(n);
  Vec<bool> cut(n);
  Vec<bool> be_cut(n);
  auto dfs_cut = [&](auto &dfs, int root) -> int {
    visit[root] = true;
    int min = depth[root];
    for (auto &e : g[root]) {
      if (parent[e.to] == root && !visit[e.to]) {
        int sub = dfs(dfs, e.to);
        if (sub >= depth[root]) {
          cut[root] = true;
          be_cut[e.to] = true;
        }
        min = Min(sub, min);
      } else {
        min = Min(depth[e.to], min);
      }
    }
    return min;
  };

  for (int i = 0; i < n; i++) {
    if (parent[i] != -1) {
      continue;
    }
    dfs_cut(dfs_cut, i);
    cut[i] = false;
    int last_child = -1;
    for (auto &e : g[i]) {
      if (parent[e.to] == i) {
        if (last_child == -1 || last_child == e.to) {
          last_child = e.to;
        } else {
          cut[i] = true;
        }
      }
    }
  }

  return {cut, be_cut, parent};
}

}  // namespace graph
}  // namespace dalt
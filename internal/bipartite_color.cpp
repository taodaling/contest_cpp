#pragma once
#include "graph.cpp"
#include "optional.cpp"
namespace dalt {
namespace graph {
template <class E>
IsBiGraph(E, Optional<Vec<bool>>) BipartiteColor(const Graph<E> &g) {
  int n = Size(g);
  Vec<bool> visited(n);
  Vec<bool> color(n);
  bool valid = true;
  auto dfs = [&](auto &dfs, int root, bool c) {
    if (visited[root]) {
      if (color[root] != c) {
        valid = false;
      }
      return;
    }
    visited[root] = true;
    for (auto &e : g[root]) {
      dfs(dfs, e.to, !c);
    }
  };
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(dfs, i, true);
    }
  }
  if (valid) {
    return color;
  }
  return {};
}
}  // namespace graph
}  // namespace dalt
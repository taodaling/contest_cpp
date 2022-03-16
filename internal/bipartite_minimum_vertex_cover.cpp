#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
// O(V+E)
template <class E>
IsBiGraph(E, Vec<bool>)
    BipartiteMinimumVertexCover(const Graph<E>& g, const Vec<int>& mates,
                                const Vec<bool>& bipartite_color) {
  int n = Size(g);
  Vec<bool> visited(n);
  auto dfs = [&](auto& dfs, int root) {
    if (visited[root]) {
      return;
    }
    visited[root] = true;
    for (auto& e : g[root]) {
      if (mates[e.to] == -1 || visited[e.to]) {
        continue;
      }
      visited[e.to] = true;
      dfs(dfs, mates[e.to]);
    }
  };
  for (int i = 0; i < n; i++) {
    if (bipartite_color[i] && mates[i] == -1) {
      dfs(dfs, i);
    }
  }
  Vec<bool> ans(n);
  for (int i = 0; i < n; i++) {
    if (bipartite_color[i]) {
      ans[i] = !visited[i];
    } else {
      ans[i] = visited[i];
    }
  }
  return ans;
}
}  // namespace graph
}  // namespace dalt
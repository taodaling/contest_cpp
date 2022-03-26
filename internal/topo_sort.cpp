#include "graph.cpp"

namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Vec<int>) TopoSort(const Graph<E> &g) {
  int n = Size(g);
  Vec<bool> visited(n);
  Vec<int> res;
  res.reserve(n);
  auto dfs = [&](auto &dfs, int root) {
    if (visited[root]) {
      return;
    }
    visited[root] = true;
    for (auto &e : g[root]) {
      dfs(dfs, e.to);
    }
    res.push_back(root);
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  return res;
}
} // namespace graph
} // namespace dalt
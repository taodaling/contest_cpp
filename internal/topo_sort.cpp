#include "graph.cpp"
#include "optional.cpp"
namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Optional<Vec<int>>) TopoSort(const Graph<E> &g) {
  int n = Size(g);
  Vec<bool> visited(n);
  Vec<bool> instk(n);
  bool ok = true;
  Vec<int> res;
  res.reserve(n);
  auto dfs = [&](auto &dfs, int root) {
    if (visited[root]) {
      if(instk[root]) {
        ok = false;
      }
      return;
    }
    visited[root] = true;
    instk[root] = true;
    for (auto &e : g[root]) {
      dfs(dfs, e.to);
    }
    res.push_back(root);
    instk[root] = false;
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  if(!ok) {
    return {};
  }
  return res;
}
} // namespace graph
} // namespace dalt
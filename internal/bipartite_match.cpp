#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
// super fast, worst O(nm)
template <class E>
IsBiGraph(E, Vec<int>)
    BipartiteMatch(const Graph<E> &g, bool in_order = false,
                   Vec<int> _mate = Vec<int>(), int consider_prefix = -1) {
  int n = Size(g);
  if (consider_prefix == -1) {
    consider_prefix = n;
  }
  Vec<int> mate = Move(_mate);
  mate.resize(n, -1);
  Vec<int> visit(n, 0);
  int time = 0;
  auto dfs = [&](auto &dfs, int root) -> bool {
    if (visit[root] == time) {
      return false;
    }
    visit[root] = time;
    for (auto &e : g[root]) {
      if (mate[e.to] == -1) {
        mate[root] = e.to;
        mate[e.to] = root;
        return true;
      }
      visit[e.to] = time;
      if (dfs(dfs, mate[e.to])) {
        mate[root] = e.to;
        mate[e.to] = root;
        return true;
      }
    }
    return false;
  };
  while (true) {
    bool find = false;
    time++;
    for (int i = 0; i < consider_prefix; i++) {
      if (mate[i] == -1 && dfs(dfs, i)) {
        find = true;
        if (in_order) {
          time++;
        }
      }
    }
    if (!find || in_order) {
      break;
    }
  }
  return mate;
}
}  // namespace graph
}  // namespace dalt
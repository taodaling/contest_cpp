#include "graph.cpp"
namespace dalt {
namespace graph {
// super fast, worst O(nm)
template <class E> IsDiGraph(E, Vec<int>) BipartiteMatch(const Graph<E> &g) {
  int n = Size(g);
  Vec<int> mate(n, -1);
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
    for (int i = 0; i < n; i++) {
      if (mate[i] == -1 && dfs(dfs, i)) {
        find = true;
      }
    }
    if (!find) {
      break;
    }
  }
  return mate;
}
} // namespace graph
} // namespace dalt
#include "graph.cpp"
#include "optional.cpp"
namespace dalt {
namespace graph {
template <class E>
enable_if_t<is_base_of_v<WithTo, E>, Optional<Deque<int>>>
CycleDetect(const Graph<E> &g) {
  int n = Size(g);
  Deque<int> dq;
  Vec<bool> visited(n);
  Vec<bool> instk(n);
  auto dfs = [&](auto &dfs, int root) -> bool {
    if (visited[root]) {
      if (instk[root]) {
        int front;
        while ((front = dq.front()) != root) {
          instk[front] = false;
          dq.pop_front();
        }
        return true;
      }
      return false;
    }
    visited[root] = instk[root] = true;
    dq.push_back(root);
    for (auto &e : g[root]) {
      if (dfs(dfs, e.to)) {
        return true;
      }
    }
    instk[root] = false;
    assert(dq.back() == root);
    dq.pop_back();
    return false;
  };
  for (int i = 0; i < n; i++) {
    if (dfs(dfs, i)) {
      return dq;
    }
    assert(dq.empty());
  }
  return {};
}

} // namespace graph
} // namespace dalt

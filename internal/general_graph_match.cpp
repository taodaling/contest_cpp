#include "graph.cpp"
namespace dalt {
namespace graph {
// credited to: https://judge.yosupo.jp/submission/61234
template <class E>
IsBiGraph(E, Vec<i32>) GeneralGraphMatchByBlossom(const Graph<E> &graph) {
  int n = Size(graph), timer = -1;
  Vec<i32> mate(n, -1), label(n), parent(n), orig(n), aux(n, -1), q;
  auto lca = [&](int x, int y) {
    for (timer++;; Swap(x, y)) {
      if (x == -1)
        continue;
      if (aux[x] == timer)
        return x;
      aux[x] = timer;
      x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
    }
  };
  auto blossom = [&](int v, int w, int a) {
    while (orig[v] != a) {
      parent[v] = w;
      w = mate[v];
      if (label[w] == 1)
        label[w] = 0, q.push_back(w);
      orig[v] = orig[w] = a;
      v = parent[w];
    }
  };
  auto augment = [&](int v) {
    while (v != -1) {
      int pv = parent[v], nv = mate[pv];
      mate[v] = pv;
      mate[pv] = v;
      v = nv;
    }
  };
  auto bfs = [&](int root) {
    Fill(All(label), -1);
    std::iota(All(orig), 0);
    q.clear();
    label[root] = 0;
    q.push_back(root);
    for (int i = 0; i < (int)q.size(); ++i) {
      int v = q[i];
      for (auto &e : graph[v]) {
        int x = e.to;
        if (label[x] == -1) {
          label[x] = 1;
          parent[x] = v;
          if (mate[x] == -1)
            return augment(x), 1;
          label[mate[x]] = 0;
          q.push_back(mate[x]);
        } else if (label[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return 0;
  };
  // Time halves if you start with (any) maximal matching.
  for (int i = 0; i < n; i++)
    if (mate[i] == -1)
      bfs(i);
  return mate;
}
} // namespace graph
} // namespace dalt
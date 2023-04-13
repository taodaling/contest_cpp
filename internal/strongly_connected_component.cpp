#pragma once
#include "graph.cpp"

namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Vec<int>) 
StronglyConnectedComponentDi(const Graph<E> &g) {
  int n = Size(g);
  Deque<int> dq;
  Vec<int> dfn(n);
  Vec<int> low(n);
  Vec<int> repr(n);
  Vec<bool> instk(n);
  int time = 0;
  auto dfs = [&](auto &dfs, int root) {
    if (dfn[root] != 0) {
      return;
    }
    dfn[root] = low[root] = ++time;
    instk[root] = true;
    dq.push_back(root);
    for (auto &e : g[root]) {
      dfs(dfs, e.to);
      if (instk[e.to]) {
        low[root] = Min(low[root], low[e.to]);
      }
    }
    if (dfn[root] == low[root]) {
      while (true) {
        int tail = dq.back();
        dq.pop_back();
        repr[tail] = root;
        instk[tail] = false;
        if (tail == root) {
          break;
        }
      }
    }
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  return repr;
}

template <class E>
enable_if_t<is_base_of_v<WithTo, E> && is_base_of_v<WithRev, E>, Vec<int>>
StronglyConnectedComponentBi(const Graph<E> &g) {
  int n = Size(g);
  Deque<int> dq;
  Vec<int> dfn(n);
  Vec<int> low(n);
  Vec<int> repr(n);
  Vec<bool> instk(n);
  int time = 0;
  auto dfs = [&](auto &dfs, int root, int rev) {
    if (dfn[root] != 0) {
      return;
    }
    dfn[root] = low[root] = ++time;
    instk[root] = true;
    dq.push_back(root);
    int m = Size(g[root]);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      dfs(dfs, e.to, e.rev);
      if (instk[e.to]) {
        low[root] = Min(low[root], low[e.to]);
      }
    }
    if (dfn[root] == low[root]) {
      while (true) {
        int tail = dq.back();
        dq.pop_back();
        repr[tail] = root;
        instk[tail] = false;
        if (root == tail) {
          break;
        }
      }
    }
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i, -1);
  }
  return repr;
}
} // namespace graph
} // namespace dalt
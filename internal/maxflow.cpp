#pragma once
#include "flow.cpp"

namespace dalt {
namespace graph {

template <class T, class E>
IsFlow(E, Tuple<Vec<int> COMMA Vec<int>>)
AugmentPathBfs(const Graph<E> &g, int t, int inf) {
  int n = Size(g);
  Vec<int> dist(n, inf);
  Vec<int> prev(n, -1);
  Deque<int> dq;
  dq.push_back(t);
  dist[t] = 0;
  while (!dq.empty()) {
    int head = dq.front();
    dq.pop_front();
    for (auto &e : g[head]) {
      if (e.flow == 0) {
        continue;
      }
      if (dist[e.to] > dist[head] + 1) {
        dist[e.to] = dist[head] + 1;
        prev[e.to] = head;
        dq.push_back(e.to);
      }
    }
  }
  return Tuple<Vec<int>, Vec<int>>(dist, prev);
}
template <class E>
IsFlow(E, typename E::flow_type)
    MaxFlowDinic(Graph<E> &g, int s, int t, typename E::flow_type send) {
  using T = typename E::flow_type;
  T remain = send;
  int n = Size(g);
  Vec<int> iters(n);
  Vec<int> dist;
  auto dfs = [&](auto &dfs, int root, T flow) {
    if (root == t) {
      return flow;
    }
    T snapshot = flow;
    while (iters[root] >= 0 && flow != 0) {
      auto &e = g[root][iters[root]];
      auto &rev_e = g[e.to][e.rev];
      if (dist[e.to] + 1 == dist[root] && rev_e.flow > 0) {
        T sent = dfs(dfs, e.to, Min(rev_e.flow, flow));
        if (sent != 0) {
          flow -= sent;
          PushFlow(g, e, sent);
          continue;
        }
      }
      iters[root]--;
    }
    return snapshot - flow;
  };
  int inf = (int)1e9;
  while (remain > 0) {
    dist = std::get<0>(AugmentPathBfs<T, E>(g, t, inf));
    if (dist[s] == inf) {
      break;
    }
    for (int i = 0; i < n; i++) {
      iters[i] = Size(g[i]) - 1;
    }
    remain -= dfs(dfs, s, remain);
  }
  return send - remain;
}
} // namespace graph
} // namespace dalt
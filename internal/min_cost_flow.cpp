#pragma once
#include "cost_flow.cpp"
namespace dalt {
namespace graph {
template <class E>
IsCostFlow(E, Tuple<Vec<typename E::flow_type> COMMA Vec<int>>)
    AugmentPathSpfa(Graph<E> &g, int s, typename E::flow_type inf) {
  Timer timer("AugmentPathSpfa");
  using T = typename E::flow_type;
  int n = Size(g);
  Deque<int> dq;
  Vec<T> dist(n, inf);
  Vec<int> prev(n, -1);
  Vec<bool> inq(n, false);
  dist[s] = 0;
  dq.push_back(s);
  inq[s] = true;
  i64 threshold = i64(n) * n;
  while (!dq.empty()) {
    int root = dq.front();
    dq.pop_front();
    inq[root] = false;
    Assert(threshold-- >= 0);
    for (auto &e : g[root]) {
      if (g[e.to][e.rev].flow == 0 || dist[e.to] <= dist[root] + e.cost) {
        continue;
      }
      dist[e.to] = dist[root] + e.cost;
      prev[e.to] = root;
      if (!inq[e.to]) {
        inq[e.to] = true;
        dq.push_back(e.to);
      }
    }
  }
  return {dist, prev};
}
//return {flow, cost}
template <class E>
IsCostFlow(E, Array<typename E::flow_type COMMA 2>) MinCostFlowDijkstra(
    Graph<E> &g, int s, int t, typename E::flow_type send, bool use_pq = true,
    const Function<bool(typename E::flow_type, typename E::flow_type)>
        &call_back = [](auto x, auto y) { return true; },
    Vec<typename E::flow_type> last_dist = Vec<typename E::flow_type>()) {
  using T = typename E::flow_type;
  int n = Size(g);
  T inf = std::numeric_limits<T>::max() / 2;
  if(last_dist.empty()) {
    last_dist = std::get<0>(AugmentPathSpfa(g, s, inf));
  }
  Vec<E *> prev(n, NULL);
  Vec<T> cur_dist(n, inf);
  auto fix_dist = [&]() {
    for (int i = 0; i < n; i++) {
      last_dist[i] = Min(cur_dist[i] + last_dist[i], inf);
    }
  };
  Function<void()> elogv = [&]() {
    TreeSet<int, Comparator<i32>> set([&](auto a, auto b) {
      return Tuple<T, i32>(cur_dist[a], a) < Tuple<T, i32>(cur_dist[b], b);
    });
    Fill(All(cur_dist), inf);
    Fill(All(prev), (E *)NULL);
    cur_dist[s] = 0;
    set.insert(s);
    while (!set.empty()) {
      auto top = set.begin();
      i32 root = *top;
      Debug(root);
      set.erase(top);
      for (auto &e : g[root]) {
        if (g[e.to][e.rev].flow == 0) {
          continue;
        }
        T dist = cur_dist[root] + e.cost - last_dist[e.to] + last_dist[root];
        Assert(dist >= cur_dist[root]);
        if (dist < cur_dist[e.to]) {
          set.erase(e.to);
          cur_dist[e.to] = dist;
          prev[e.to] = &g[e.to][e.rev];
          set.insert(e.to);
        }
      }
    }
  };
  Function<void()> v2 = [&]() {
    Vec<bool> visited(n, false);
    Fill(All(cur_dist), inf);
    Fill(All(prev), (E *)NULL);
    cur_dist[s] = 0;
    for (int round = 0; round < n; round++) {
      int root = -1;
      for (int i = 0; i < n; i++) {
        if (!visited[i] && (root == -1 || cur_dist[root] > cur_dist[i])) {
          root = i;
        }
      }
      if (cur_dist[root] >= inf) {
        break;
      }
      visited[root] = true;
      for (auto &e : g[root]) {
        if (g[e.to][e.rev].flow == 0) {
          continue;
        }
        T dist = cur_dist[root] + e.cost - last_dist[e.to] + last_dist[root];
        if (dist < cur_dist[e.to]) {
          cur_dist[e.to] = dist;
          prev[e.to] = &g[e.to][e.rev];
        }
      }
    }
  };

  auto &algo = use_pq ? elogv : v2;

  T remain = send;
  T cost = 0;
  while (remain > 0) {
    Timer one_batch_push_flow("push flow");
    algo();
    fix_dist();
    if (prev[t] == NULL) {
      break;
    }
    T max = remain;
    T sum = 0;
    for (int trace = t; trace != s; trace = prev[trace]->to) {
      max = Min(max, prev[trace]->flow);
      sum -= prev[trace]->cost;
    }
    if (!call_back(max, sum)) {
      break;
    }
    for (int trace = t; trace != s; trace = prev[trace]->to) {
      PushFlow(g, *prev[trace], -max);
    }
    Assert(max > 0);
    cost += sum * max;
    remain -= max;
  }

  return {send - remain, cost};
}
}  // namespace graph
}  // namespace dalt
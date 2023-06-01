#include "flow.cpp"
#include "maxflow.cpp"
namespace dalt {
namespace graph {
template <class T>
struct BoundFlowEdge : FlowBaseEdge<T> {
  T bound;
};
#define IsBoundFlow(E, ret) \
  enable_if_t<is_base_of_v<BoundFlowEdge<typename E::flow_type>, E>, ret>

template <class E>
IsBoundFlow(E, bool) FeasibleFlow(
    Graph<E> &g,
    E::flow_type inf = numeric_limits<typename E::flow_type>::max() / 2) {
  int n = Size(g);
  g.resize(n + 2);
  int src = n;
  int dst = n + 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < Size(g[i]); j++) {
      var &fe = g[i][j];
      if (fe.to == src || fe.to == dst || !fe.real) {
        continue;
      }
      if (fe.bound > 0) {
        AddFlowEdge(g, src, e.to, e.bound);
        AddFlowEdge(g, i, dst, e.bound);
      }
    }
  }
  MaxFlowDinic(g, src, dst, inf);
  bool ans = true;
  for (var &e : g[src]) {
    ans = ans && g[e.to][e.rev].flow == 0;
  }
  for (var &e : g[dst]) {
    ans = ans && e.flow == 0;
  }
  for (int i = 0; i < n; i++) {
    while (Size(g[i]) > 0) {
      var &back = g[i].back();
      if (back.to == src || back.to == dst) {
        g[i].pop_back();
      } else {
        break;
      }
    }
  }
  g.resize(n);
  return ans;
}

template <class E>
IsBoundFlow(E, bool) FeasibleFlow(
    Graph<E> &g, int s, int t,
    E::flow_type inf = numeric_limits<typename E::flow_type>::max() / 2) {
  using T = typename E::flow_type;
  AddFlowEdge(g, t, s, inf, 0);
  bool ans = FeasibleFlow(g, inf);
  g[s].pop_back();
  g[t].pop_back();
  return ans;
}

}  // namespace graph
}  // namespace dalt
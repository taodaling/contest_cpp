#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
MakeTemplateAttribute(WithFlow, flow);
MakeAttribute(WithReal, bool, real);
template <class T>
struct FlowBaseEdge : WithTo, WithRev, WithFlow<T>, WithReal {};

#define IsFlow(T, E, ret) enable_if_t<is_base_of_v<FlowBaseEdge<T>, E>, ret>
template <class T, class E>
IsFlow(T, E, void) PushFlow(Graph<E> &g, E &e, T flow) {
  e.flow += flow;
  g[e.to][e.rev].flow -= flow;
}

template <class T, class E>
IsFlow(T, E, void) AddFlowEdge(Graph<E> &g, int s, int t, T flow) {
  if (s == t) {
    return;
  }
  AddBiEdge<E>(g, s, t);
  g[s].back().flow = 0;
  g[s].back().real = true;
  g[t].back().flow = flow;
  g[t].back().real = false;
}
} // namespace graph
} // namespace dalt
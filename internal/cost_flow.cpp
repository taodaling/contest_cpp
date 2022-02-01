#pragma once
#include "flow.cpp"
namespace dalt {
namespace graph {
MakeTemplateAttribute(WithCost, cost);
template <class T>
struct CostFlowBaseEdge : public FlowBaseEdge<T>, public WithCost<T> {};
#define IsCostFlow(T, E, ret)                                                  \
  enable_if_t<is_base_of_v<CostFlowBaseEdge<T>, E>, ret>
template <class T, class E>
IsCostFlow(T, E, void)
    AddCostFlowEdge(Graph<E> &g, int s, int t, T flow, T cost) {
  if(s == t) {
      return;
  }
  AddFlowEdge<T, E>(g, s, t, flow);
  g[s].back().cost = cost;
  g[t].back().cost = -cost;
}

} // namespace graph
} // namespace dalt
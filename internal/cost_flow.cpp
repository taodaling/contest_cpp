#pragma once
#include "flow.cpp"
namespace dalt {
namespace graph {
MakeTemplateAttribute(WithCost, cost);
template <class T>
struct CostFlowBaseEdge : public FlowBaseEdge<T>, public WithCost<T> {};
#define IsCostFlow(E, ret)                                                  \
  enable_if_t<is_base_of_v<CostFlowBaseEdge<typename E::flow_type>, E>, ret>
template <class E>
IsCostFlow(E, void)
    AddCostFlowEdge(Graph<E> &g, int s, int t, typename E::flow_type flow,
                    typename E::cost_type cost) {
  if(s == t) {
      return;
  }
  AddFlowEdge<E>(g, s, t, flow);
  g[s].back().cost = cost;
  g[t].back().cost = -cost;
}
template <class E>
IsFlow(E, String) CostFlowToString(const Graph<E> &g) {
  Func<String(const E &e)> tostring = [&](const E &e) -> String {
    return "->" + ToString(e.to) + ", flow = " + ToString(e.flow) + "/" +
           ToString(e.flow + g[e.to][e.rev].flow) +
           ", cost = " + ToString(e.cost);
  };
  return FlowToStringTemplate(g, tostring);
}
} // namespace graph
} // namespace dalt
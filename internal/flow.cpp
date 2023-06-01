#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
MakeTemplateAttribute(WithFlow, flow);
MakeAttribute(WithReal, bool, real);
template <class T>
struct FlowBaseEdge : BiBaseEdge, WithFlow<T>, WithReal {};

#define IsFlow(E, ret) \
  enable_if_t<is_base_of_v<FlowBaseEdge<typename E::flow_type>, E>, ret>
template <class E>
IsFlow(E, String)
    FlowToStringTemplate(const Graph<E> &g, Func<String(const E &e)> tostring) {
  String out = "\n";
  for (int i = 0; i < Size(g); i++) {
    out += ToString(i) + ": {\n";
    for (var &e : g[i]) {
      if (e.real) {
        out += tostring(e) + "\n";
      }
    }
    out += "}\n";
  }
  return out;
}
template <class E>
IsFlow(E, String) FlowToString(const Graph<E> &g) {
  Func<String(const E &e)> tostring = [&](const E &e) -> String {
    return "->" + ToString(e.to) + ", flow = " + ToString(e.flow) + "/" +
           ToString(e.flow + g[e.to][e.rev].flow);
  };
  return FlowToStringTemplate(g, tostring);
}

template <class E>
IsFlow(E, void) PushFlow(Graph<E> &g, E &e, typename E::flow_type flow) {
  e.flow += flow;
  g[e.to][e.rev].flow -= flow;
}

template <class E>
IsFlow(E, void)
    AddFlowEdge(Graph<E> &g, int s, int t, typename E::flow_type flow) {
  if (s == t) {
    return;
  }
  AddBiEdge<E>(g, s, t);
  g[s].back().flow = 0;
  g[s].back().real = true;
  g[t].back().flow = flow;
  g[t].back().real = false;
}
}  // namespace graph
}  // namespace dalt
#pragma once
#include "common.cpp"

namespace dalt {
namespace graph {
template <class E>
using Graph = Vec<Vec<E>>;
MakeAttribute(WithId, i32, id);
MakeAttribute(WithTo, i32, to);
MakeAttribute(WithRev, i32, rev);
MakeTemplateAttribute(WithWeight, weight);

struct DiBaseEdge: public WithTo {};
struct BiBaseEdge: public DiBaseEdge, public WithRev {};

#define IsDiGraph(E, ret) enable_if_t<is_base_of_v<DiBaseEdge, E>, ret>
#define IsBiGraph(E, ret) enable_if_t<is_base_of_v<BiBaseEdge, E>, ret>

template <class E> IsBiGraph(E, void) AddBiEdge(Graph<E> &g, int s, int t) {
  E pos, neg;
  pos.to = t;
  neg.to = s;
  pos.rev = Size(g[t]);
  neg.rev = Size(g[s]);
  g[s].push_back(pos);
  g[t].push_back(neg);
}
} // namespace graph
} // namespace dalt
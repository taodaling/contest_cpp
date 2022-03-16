#pragma once
#include "bipartite_match.cpp"
#include "bipartite_minimum_vertex_cover.cpp"
#include "common.cpp"
#include "graph.cpp"
#include "maximum_independent_set.cpp"
namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Vec<bool>) LongestAntiChain(const Graph<E>& g) {
  int n = Size(g);
  Graph<BiBaseEdge> bg(n * 2);
  Vec<bool> visit(n);
  for (int i = 0; i < n; i++) {
    Deque<int> dq;
    Fill(All(visit), false);
    visit[i] = true;
    dq.push_back(i);
    while (!dq.empty()) {
      int head = dq.front();
      dq.pop_front();
      for (auto& e : g[head]) {
        if (!visit[e.to]) {
          visit[e.to] = true;
          dq.push_back(e.to);
        }
      }
    }
    for (int j = 0; j < n; j++) {
      if (j != i && visit[j]) {
        AddBiEdge(bg, i, j + n);
      }
    }
  }

  auto mates = BipartiteMatch(bg);
  Vec<bool> color(n * 2);
  for (int i = 0; i < n; i++) {
    color[i] = true;
  }

  Vec<bool> min_vertex_cover = BipartiteMinimumVertexCover(bg, mates, color);
  Vec<bool> max_independent_set =
      MaximumIndependentSetFromMinimumVertexCover(Move(min_vertex_cover));
  Vec<bool> longest_antichain(n);
  for (int i = 0; i < n; i++) {
    if (max_independent_set[i] && max_independent_set[i + n]) {
      longest_antichain[i] = true;
    }
  }
  return longest_antichain;
}
}  // namespace graph
}  // namespace dalt
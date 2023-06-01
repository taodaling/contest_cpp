#pragma once
#include "common.cpp"
using namespace dalt;
#include "bound_flow.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  using namespace graph;
  using E = BoundFlowEdge<i32>;
  Graph<E> g(N + 1);
  Vec<Pair<int, int>> ids;
  for (int i = 0; i < M; i++) {
    int s, t, l, u;
    in >> s >> t >> l >> u;
    AddFlowEdge(g, s, t, u);
    g[s].back().bound = l;
    ids.push_back({s, Size(g[s]) - 1});
  }
  bool ans = FeasibleFlow(g);
  if (ans) {
    out << "YES";
  } else {
    out << "NO";
  }
  out << '\n';
  for (var id : ids) {
    out << g[id.first][id.second].flow << '\n';
  }
}

void SolveMulti(IStream &in, OStream &out) {
  // std::ifstream input("in");
  int num_of_input = 1;
  // in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    // SolveOne(i + 1, input, out);
    SolveOne(i + 1, in, out);
  }
}
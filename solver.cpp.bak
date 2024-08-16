#pragma once
#include "common.cpp"
using namespace dalt;
#include "cost_flow.cpp"
#include "min_cost_flow.cpp"
using namespace graph;
void SolveOne(int test_id, IStream &in, OStream &out) {
  using E = CostFlowBaseEdge<i64>;
  int N, M, K;
  in >> N >> M >> K;
  Graph<E> g(N);
  for (int i = 0; i < M; i++) {
    int a, b, r, c;
    in >> a >> b >> r >> c;
    a--;
    b--;
    AddCostFlowEdge(g, a, b, r, c);
    // AddCostFlowEdge(g, b, a, r, c);
  }
  if (N == 1) {
    out << 0;
    return;
  }
  var ans = MinCostFlowDijkstra<E>(g, 0, N - 1, K);
  if (ans[0] < K) {
    out << -1;
  } else {
    out << ans[1];
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
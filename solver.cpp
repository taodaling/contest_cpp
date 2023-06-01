#pragma once
#include "common.cpp"
using namespace dalt;
#include "bound_flow.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  using namespace graph;
  using E = BoundFlowEdge<i32>;
  Graph
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
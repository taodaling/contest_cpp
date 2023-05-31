#pragma once
#include "common.cpp"
using namespace dalt;
#include "prefixsum.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M, Q;
  in >> N >> M >> Q;
  MDVec<i64, 2> A = MDVec<i64, 2>::Make(N, M);
  in >> A;
  PrefixSum<i64, 2> ps(A);
  for (int i = 0; i < Q; i++) {
    int x1, y1, x2, y2;
    in >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    x2--;
    y2--;
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
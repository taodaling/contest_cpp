#pragma once
#include "all"
using namespace dalt;
using MOD = DynamicModular<int>;
using Mi = ModInt<MOD>;
using real = double;
void SolveOne(int test_id, IStream &in, OStream &out) {
  
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
#pragma once
#include "common.cpp"
using namespace dalt;
#include "euclid_like_function.cpp"
void SolveOne(IStream &in, OStream &out) {
  i64 N, M, A, B;
  in >> N >> M >> A >> B;
  auto sum = math::EuclidLikeFloorAffineSum1(N - 1, A, B, M);
  out << sum << '\n'; 
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    SolveOne(in, out);
  }
}
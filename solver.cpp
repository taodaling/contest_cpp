#pragma once
#include "common.cpp"
using namespace dalt;
#include "math.cpp"
#include "xor_subset_convolution.cpp"
using Mi = ModInt1000000007;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int K, N, M;
  in >> K >> N >> M;
  Vec<Mi> cnts(1 << M);
  for(int i = 0; i < N; i++) {
    int x;
    in >> x;
    cnts[x] += 1;
  }
  var ans = XorSubsetConvolutionLastTier(Move(cnts), K);
  // for(int i = 0; i <= K; i++) {
  //   Debug(i);
  //   Debug(ans[i]);
  // }
  for(int i = 0; i < 1 << M; i++) {
    out << ans[i] << ' ';
  }
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}
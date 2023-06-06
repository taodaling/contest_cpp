#pragma once
#include "common.cpp"
using namespace dalt;
#include "modint.cpp"
#include "combination.cpp"
#include "ntt.cpp"
#include "polynomial.cpp"
using Mi = ModInt998244353;
using namespace poly;
using Conv = NTTConv<Mi>;
using Poly = Polynomial<Conv>;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, K;
  in >> N >> K;
  Vec<int> S(K);
  in >> S;
  S -= 1;
  Vec<Mi> poly(N - 1);
  math::Combination<Mi> comb(N);
  for(int i : S) {
    poly[i] = comb.inv_fact[i];
  }
  Poly p = Poly(Move(poly));
  Debug(p.to_vec());

  var p_pow = p.powmod_binary_lift(N, N - 1);
  Debug(p_pow.to_vec());
  var ans = p_pow[N - 2] * comb.fact[N - 2];
  out << ans;
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
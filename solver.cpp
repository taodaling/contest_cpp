#pragma once
#include "common.cpp"
using namespace dalt;
#include "modint.cpp"
#include "matrix.cpp"

void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  i64 S;
  in >> N >> S;
  Vec<i64> A(N);
  in >> A;
  using Mi = ModInt998244353;
  using Mat = math::Matrix<Mi>;
  Mat trans(2, Vec<Mi> {
    1, 1,
    1, 0
  });
  Mat skip(2, Vec<Mi> {
    0, 1,
    1, 0
  });
  Mat must(2, Vec<Mi> {
    1, 0,
    0, 0
  });
  Mat first = Mat(1, Vec<Mi> {
    1,
    0
  });
  i64 last = 0;
  for(var a : A) {
    //last to a
    first = skip * trans.pow(a - last - 1) * first;
    last = a;
  }
  if(S == last) {
    out << 0;
    return;
  }
  first = must * trans.pow(S - last - 1) * first;
  var ans = first[0][0] + first[1][0];
  out << ans << '\n';
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
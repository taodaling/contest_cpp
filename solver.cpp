#pragma once
#include "common.cpp"
using namespace dalt;
#include "generic_log.cpp"
#include "modint.cpp"
using Mod = DynamicModular<i64>;
using Mi = ModInt<Mod>;

void SolveOne(int test_id, IStream &in, OStream &out) {
  i64 a, n, p;
  in >> a >> n >> p;
  Mod::Register(p);
  Mi a_val = a;
  Mi n_val = n;
  if(a == 0) {
    if(n == 0) {
      out << 1;
    } else {
      out << "DNE";
    }
    return;
  }
  math::CoprimeModLog<Mi> loger(a);
  var ans = loger.log(n);
  if(ans.is_none()) {
    out << "DNE";
  } else {
    out << ans.value();
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
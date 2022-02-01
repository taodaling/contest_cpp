#pragma once
#include "common.cpp"
using namespace dalt;
#include "F:\sourcecode\cppcp\internal\gravity_largrange_interpolation.cpp"
#include "modint.cpp"
void SolveOne(IStream &in, OStream &out) {
  i32 n;
  in >> n;
  using namespace poly;
  using Modular = MOD998244353;
  using Mi = ModInt<Modular>;
  GravityLargrangeInterpolation<Mi> glip(n);
  for(int i = 0; i < n; i++) {
    i32 t;
    in >> t;
    if(t == 1) {
      Mi x, y;
      in >> x >> y;
      glip.add(x, y);
    } else {
      Mi k;
      in >> k;
      Mi ans = glip.estimate_point(k);
      out << ans << '\n';  
    } 
  }
}

void SolveMulti(IStream &in, OStream &out) {
  int num_of_input = 1;
  for (int i = 0; i < num_of_input; i++) {
    SolveOne(in, out);
  }
}
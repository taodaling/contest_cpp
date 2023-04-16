#pragma once
#include "all"
using namespace dalt;
using real = double;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;
  using namespace geo2;
  using Nv = NearValue<real>;
  using Pt = Point<Nv>;
  Vec<Pt> pts(N);
  Trace(input);
  for(int i = 0; i < N; i++) {
    in >> pts[i].x >> pts[i].y;
  }
  Trace(convex hull);
  ConvexHull<Nv> ch(Polygon<Nv>(pts), false);
  Trace(convex hull done);
  var index = [&](int i) -> Pt& {
    return ch[Modular(i, Size(ch))];
  };
  int M = Size(ch);
  Debug(M);
  Vec<Vec<Nv>> area(M, Vec<Nv>(M));
  out << std::setprecision(3);
  if(M <= 2) {
    out << real(0);
    return;
  }
  Debug(ch.to_vec());
  for(int i = 0; i < Size(ch); i++) {
    var &pt = index(i);
    int next = i;
    for(int j = i + 1; j < i + Size(ch) - 1; j++) {
      //go up
      while(Pt::cross(index(j) - pt, index(next + 1) - index(next)) >= Nv(0)) {
        next++;
      }
      //DebugFmtln("(%d, %d) => %d", i, j, next);
      area[i][j % M] = Polygon<Nv>(Vec<Pt> {pt, index(j), index(next)}).area();
    }
  }
  Nv best = Nv(0);
  for(int i = 0; i < M; i++) {
    for(int j = 0; j < M; j++) {
      Chmax(best, area[i][j] + area[j][i]);
    }
  }
  out << best;
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
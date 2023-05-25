#pragma once
#include "common.cpp"
using namespace dalt;
#include "convexhull.cpp"
using namespace geo2;
using Nv = NearValue<double>;
using Pt = Point<Nv>;
using Ln = Line<Nv>;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;
  Vec<Pt> pts(N);
  for (int i = 0; i < N; i++) {
    int a, b, c;
    in >> a >> b >> c;
    pts[i].x = double(a) / c;
    pts[i].y = double(b) / c;
  }
  Debug(pts);
  ConvexHull<Nv> ch(pts);
  var profit = [&](Pt &pt) { return Min(Nv(1) / pt.x, Nv(1) / pt.y); };
  Debug(ch.to_vec());
  Nv dist = 0;
  for (int i = 0; i < Size(ch); i++) {
    var pt = ch[i];
    Chmax(dist, profit(pt));
  }
  for (int i = 0; i < Size(ch); i++) {
    var a = ch[i];
    var b = ch[(i + 1) % Size(ch)];
    if (Pt::in_angle(a, b, Pt(1, 1))) {
      var pt =
          Ln::intersect(Ln::from_ends(a, b), Ln::from_ends(Pt(0, 0), Pt(1, 1)));
      Chmax(dist, profit(*pt));
    }
  }
  out << dist;
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
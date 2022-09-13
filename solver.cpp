#pragma once
#include "common.cpp"
using namespace dalt;
#include "line3.cpp"
using namespace geo3;
using Nv = NearValue<f80, 6>;
using Pt = Point3<Nv>;
using Ln = Line3<Nv>;
void SolveOne(int test_id, IStream &in, OStream &out) {
  Pt a, b, c, d;
#define READ_PT(t) in >> t.x >> t.y >> t.z
  READ_PT(a);
  READ_PT(b);
  READ_PT(d);
  READ_PT(c);
  Ln l1(a, b);
  Ln l2(d, c);
  if (Ln::isPerpendicular(l1, l2)) {
    var np = Ln::closestOnL1(l1, l2);
    var np2 = Ln::closestOnL1(l2, l1);
    Debug(np);
    Debug(np2);
    Debug((a - np).abs() - ((a - b).abs() + (b - np).abs()));
    Debug((c - np2).abs() - ((c - d).abs() + (d - np2).abs()));
    if (l2.dist(np) == 0 && (a - np).abs() == (a - b).abs() + (b - np).abs() &&
        (c - np2).abs() == (c - d).abs() + (d - np2).abs()) {
      out << "Valid";
      return;
    }
  }
  out << "Invalid";
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
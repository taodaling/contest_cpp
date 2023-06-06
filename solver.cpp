#pragma once
#include "common.cpp"
using namespace dalt;

void SolveOne(int test_id, IStream &in, OStream &out) {
  using Pt = Array<int, 2>;
  Pt s, t;
  in >> s[0] >> s[1] >> t[0] >> t[1];
  int a, b, c, d;
  in >> a >> b >> c >> d;

  Vec<Pt> seq;
  Pt cur = s;
  var update = [&](int x, int y) {
    Assert(Size(seq) < 1e6);
    Assert(x >= a && x <= b);
    Assert(y >= c && y <= d);
    seq.push_back(Pt{x, y});
    // x1 + x0 = 2 * x
    cur[0] = 2 * x - cur[0];
    cur[1] = 2 * y - cur[1];
    DebugFmtln(" -> (%d, %d) = (%d, %d)", x, y, cur[0], cur[1]);
  };

  if (a == b && cur[0] != t[0]) {
    update(a, c);
  }
  if (c == d && cur[1] != t[1]) {
    update(a, c);
  }
  if (a == b && cur[0] != t[0] || c == d && cur[1] != t[1] ||
      (t[0] - cur[0]) & 1 || (t[1] - cur[1]) & 1) {
    out << "No";
    return;
  }
  while (cur != t) {
    if (cur[0] < t[0]) {
      // add 2
      update(a, c);
      update(a + 1, c);
    } else if (cur[0] > t[0]) {
      update(a + 1, c);
      update(a, c);
    } else if (cur[1] < t[1]) {
      update(a, c);
      update(a, c + 1);
    } else {
      update(a, c + 1);
      update(a, c);
    }
  }

  out << "Yes\n";
  for (var op : seq) {
    out << op[0] << " " << op[1] << "\n";
  }
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
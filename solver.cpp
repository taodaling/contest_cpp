#pragma once
#include "common.cpp"
using namespace dalt;
#include "fenwick_tree.cpp"
#include "operand.cpp"
#include "math.cpp"

  struct Pt {
    i64 x;
    i64 y;
    i64 z;
    i64 a;
    i64 max_sum;
  };

  DebugRun(
    OStream& operator<<(OStream& os, const Pt &pt) {
      return os << MakeTuple(pt.x, pt.y, pt.z, pt.a);
    }
  )
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;

  Vec<Pt> pts(N + 1);
  i64 inf = 1e18;
  for(int i = 0; i < N; i++) {
    i64 t, x, y, a;
    in >> t >> x >> y >> a;
    pts[i].x = t - x - y;
    pts[i].y = t + x - y;
    pts[i].z = y;
    pts[i].a = a;
    pts[i].max_sum = -inf;
  }
  Vec<i64> ys(N + 1);
  for(var &pt : pts) {
    ys.push_back(pt.y);
  }
  MakeUniqueAndSort(ys);
  for(var &pt : pts) {
    pt.y = LowerBound(All(ys), pt.y) - ys.begin();
  }
  Debug(pts);
  Sort(All(pts), [&](var &a, var &b) {
    return MakeTuple(a.z, a.y, a.x) < MakeTuple(b.z, b.y, b.x);
  });

  using Op = Operand<i64>;
  Op::add_op = [&](var &a, var &b) {
    return Max(a, b);
  };
  Op::default_val = -inf;

  FenwickTree<Op> fwt(N + 1);
  var dac = [&](var &dac, int l, int r) {
    if(l == r) {
      return;
    }
    int m = (l + r) / 2;
    Sort(pts.begin() + l, pts.begin() + r + 1, [&](var &a, var &b) {
      return MakeTuple(a.z, a.y, a.x) < MakeTuple(b.z, b.y, b.x);
    });
    dac(dac, l, m);
    Sort(pts.begin() + l, pts.begin() + m + 1, [&](var &a, var &b) {
      return MakeTuple(a.x, a.y) < MakeTuple(b.x, b.y);
    });
    Sort(pts.begin() + m + 1, pts.begin() + r + 1, [&](var &a, var &b) {
      return MakeTuple(a.x, a.y) < MakeTuple(b.x, b.y);
    });

    int i = l;
    int j = m + 1;
    while(i <= m || j <= r) {
      if(j > r || i <= m && MakeTuple(pts[i].x, pts[i].y) <= MakeTuple(pts[j].x, pts[j].y)) {
        fwt.update(pts[i].y, pts[i].max_sum);
        i++;
      } else {
        Chmax(pts[j].max_sum, pts[j].a + fwt.query(pts[j].y).value);
        j++;
      }
    }
    for(int i = l; i <= m; i++) {
      fwt.recover(pts[i].y);
    }

    dac(dac, m + 1, r);
  };

  dac(dac, 0, N);
  i64 best = -inf;
  for(var &pt : pts) {
    Chmax(best, pt.max_sum);
  }
  out << best << '\n';
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
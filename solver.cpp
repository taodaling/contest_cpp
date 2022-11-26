#pragma once
#include "common.cpp"
using namespace dalt;
#include "segtree.cpp"
#include "function.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  Vec<i64> A(N);
  in >> A;
  using namespace sbt;
  using A2 = Array<i64, 2>;
  using SBT = SelfBalanceTreeRegistry<i64, i64>;
  using ST = SegTree<SBT, true>;
  ST::Register(
      0, 0,
      [&](i64 a, i64 b) {
        return Min(a, b);
      },
      [&](i64 a, i64 x) {
        return a + x;
      },
      [&](i64 a, i64 b) { return a + b; });
  i64 inf = 1e18;
  i64 Size = inf + 10;
  var root = ST::MakePersistentTree(Size);
  TreeMap<i64, Vec<i64>> disable;
  TreeMap<i64, i64> cache;
  Vec<i64> events;
  events.insert(events.end(), All(A));
  for(int i = 0; i < M; i++) {
    i64 x, y;
    in >> x >> y;
    disable[x].push_back(x - y);
    events.push_back(x);
    events.push_back(x - y);
  }
  MakeUniqueAndSort(events);
  var update = [&](i64 l, i64 r, i64 val) {
    if(val == 0 || l > r) {
      return;
    }
    DebugFmtln("update(%lld, %lld, %lld)", l, r, val);
    root.update(l, r, val);
  };
  var mex = [&](const ST& root) {
    var ans = root.first_true_const(0, Size - 1, [&](var x) {
      return x == 0;
    }, 1).value();
    return std::get<0>(ans);
  };
  i64 last = -1;
  for(var e : events) {
    Debug(e);
    Line(previous handle);
    if(e - 2 - last >= 0) {
      i64 L = mex(root);
      update(L, L + e - 2 - last, 1);
    }
    Line(point handle);
    last = e;
    var new_root = root.clone();
    for(var item : disable[e]) {
      i64 sg = cache[item];
      new_root.update(sg, sg, -1);
    }
    i64 next_val = mex(new_root);
    DebugFmtln("sg(%lld) = %lld", e, next_val);
    update(next_val, next_val, 1);
    cache[e] = next_val;
  }
  i64 ans = 0;
  for(i64 a : A) {
    ans ^= cache[a];
  }
  out << (ans != 0 ? "Takahashi" : "Aoki");
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
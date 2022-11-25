#pragma once
#include "common.cpp"
using namespace dalt;
#include "treap.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  Vec<i64> A(N);
  in >> A;
  TreeMap<i64, Vec<i64>> disallow;
  TreeMap<i64, i64> sg_cache;
  Vec<i64> pending;
  pending.insert(pending.end(), All(A));
  for(int i = 0; i < M; i++) {
    i64 x, y;
    in >> x >> y;
    y = x - y;
    disallow[x].push_back(y);
    pending.push_back(x);
    pending.push_back(y);
  }
  MakeUniqueAndSort(pending);
  using namespace sbt;
  using SBT = SelfBalanceTreeRegistry<i64, Nil>;
  using Tp = Treap<SBT>;
  Tp::Register(0, Nil(), 
  NaturalAdder<i64>(), 
  ReturnLeftAdder<i64, Nil>(), 
  ReturnLeftAdder<Nil>());
  Tp *root = Tp::NIL;
  
  i64 mex = 0;
  var update_pt = [&](i64 x, i64 val) {
    var p0 = root->split_by_id(x);
    var p1 = p0[0]->split_by_id(x - 1);
    if(p1[1] == Tp::NIL) {
      p1[1] = new Tp(x);
    }
    p1[1]->sum += val;
    p1[1]->weight += val;
    p0[0] = Tp::merge(p1[0], p1[1]);
    root = Tp::merge(p0[0], p0[1]);
    mex = Max(mex, x);
  };
  var update_range = [&](i64 l, i64 r, i64 val) {
    update_pt(l, val);
    update_pt(r + 1, -val);
  };
  var query = [&](i64 x) {
    var p0 = root->split_by_id(x);
    i64 ans = p0[0]->sum;
    root = Tp::merge(p0[0], p0[1]);
    return ans;
  };
  i64 mex = 0;
  i64 last = 0;
  for(var item : pending) {
    if(last < item) {
      //last=>item-1
      update_range(mex, item - last + mex - 1, 1);
    }
    last = item + 1;
    if(last )
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
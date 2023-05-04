#pragma once
#include "common.cpp"
using namespace dalt;
#include "segtree.cpp"
#include "modint.cpp"
#include "range_affine_range_sum.cpp"

using Mi = ModInt998244353;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M, Q;
  in >> N >> M >> Q;
  struct Limit {
    int l;
    int r;
    int x;
  };
  Vec<Limit> Ls(Q);
  for(int i = 0; i < Q; i++) {
    in >> Ls[i].l >> Ls[i].r >> Ls[i].x;
  }

  using SBT = sbt::SelfBalanceTreeRegistry<int, int>;
  using ST = sbt::SegTree<SBT>;
  var inf = Mi::modulus() - 1;
  var MinOp = [&](int a, int b) {return Min(a, b);};
  Trace(gen limits);
  ST::Register(inf, inf, MinOp, MinOp, MinOp);
  ST st(N + 1);
  for(var& op : Ls) {
    st.update(op.l, op.r, op.x);
  }
  var limits = st.to_vec();
  TreeMap<int, Vec<int>> group_by_limits;
  TreeMap<int, Vec<Limit>> group_by_x;
  for(int i = 1; i <= N; i++) {
    group_by_limits[limits[i]].push_back(i);
  }
  for(var &op : Ls) {
    group_by_x[op.x].push_back(op);
  }
  Trace(solve by tier);
  
  sbt::RangeAffineRangeSum<Mi> rars(N + 1);
  Trace(next);
  Mi ans = 1;
  for(var& pair : group_by_limits) {
    var ls = group_by_x[pair.first];
    var& indices = pair.second;
    var ls_iter = ls.begin();
    var is_iter = indices.begin();
    rars.update(0, N, 0, 0);
    rars.update(0, 0, 0, 1);
    while(ls_iter != ls.end() || is_iter != indices.end()) {
      if(is_iter != indices.end() && (ls_iter == ls.end() || *is_iter <= ls_iter->r)) {
        var index = *is_iter;
        ++is_iter;
        var total = rars.query(0, N);
        rars.update(index, index, 0, total);
        rars.update(0, index - 1, limits[index] - 1, 0);    
      } else {
        var &item = *ls_iter;
        ++ls_iter;
        rars.update(0, item.l - 1, 0, 0);
      }
    }
    var local_contrib = rars.query(0, N);
    ans *= local_contrib;
    group_by_x.erase(pair.first);
  }
  if(Size(group_by_x) > 0) {
    ans = 0;
  }
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
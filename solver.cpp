#pragma once
#include "common.cpp"
using namespace dalt;
#include "combination.cpp"
#include "dsu.cpp"
#include "interval_map.cpp"
#include "modint.cpp"
#include "segtree.cpp"
using Mi = ModInt998244353;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, K;
  in >> N >> K;
  K++;
  Vec<Pair<int, int>> ints(K);
  for (int i = 0; i < K - 1; i++) {
    in >> ints[i].first >> ints[i].second;
    ints[i].first--;
    ints[i].second--;
  }
  ints.back().first = 0;
  ints.back().second = N - 1;
  Sort(All(ints));
  Debug(ints);
  // not equal l and r
  bool ok = true;
  for (var &x : ints) {
    if ((x.second - x.first + 1) % 2 != 0) {
      ok = false;
    }
    var iter = LowerBound(All(ints), MakePair(x.second, -1));
    if (iter != ints.end() && iter->first == x.second) {
      ok = false;
    }
  }
  if (!ok) {
    out << "0\n";
    return;
  }
  MinHeap<Pair<int, int>> heap;
  DSU<> dsu(K);
  using SBT = sbt::SelfBalanceTreeRegistry<int, int>;
  using ST = sbt::SegTree<SBT>;

  ST::Register(
      -1, -1,
      [&](var a, var b) {
        if (a >= 0 && b >= 0) {
          dsu.merge(a, b);
        }
        return Max(a, b);
      },
      [&](var a, var b) {
        if (a >= 0 && b >= 0) {
          dsu.merge(a, b);
        }
        return b;
      },
      [&](var a, var b) { return b; });

  ST st(N);
  for (int i = 0; i < K; i++) {
    int l = ints[i].first;
    int r = ints[i].second;
    while (!heap.empty() && heap.top().first < l) {
      var top = heap.top();
      heap.pop();
      if (st.query(top.first, top.first) == top.second) {
        st.update(top.first, top.first, -1);
      }
    }

    var repr = st.query(l, r);
    if (repr >= 0) {
      Debug(i);
      Debug(repr);
      dsu.merge(i, repr);
    }
    st.update(r, r, i);
    heap.push(MakePair(r, i));
  }

  Vec<Vec<int>> groups(K);
  for (int i = 0; i < K; i++) {
    groups[dsu.find(i)].push_back(ints[i].first);
    groups[dsu.find(i)].push_back(ints[i].second + 1);
  }
  ints.clear();
  for (var &g : groups) {
    MakeUniqueAndSort(g);
    for (int i = 0; i + 1 < Size(g); i++) {
      int l = g[i];
      int r = g[i + 1] - 1;
      ints.push_back(MakePair(l, r));
    }
  }
  Sort(All(ints),
       [&](var &a, var &b) { return a.second - a.first < b.second - b.first; });
  Debug(ints);
  IntervalMap<int> map;
  math::Combination<Mi> comb(N + 1);
  var catalan = [&](int n) -> Mi {
    if (n % 2 != 0) {
      return 0;
    }
    return comb.combination(n, n / 2) - comb.combination(n, n / 2 + 1);
  };
  Mi ans = 1;
  for (var &pair : ints) {
    int l = pair.first;
    int r = pair.second;
    int now = map.query(l, r + 1);
    int added = r - l + 1 - now;
    map.add(l, r + 1);
    ans *= catalan(added);
  }
  out << ans << '\n';
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}
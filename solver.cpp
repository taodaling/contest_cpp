#pragma once
#include "all"
#include "version_array.cpp"
using namespace dalt;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  Vec<TreeSet<int>> g(N);
  for(int i = 0; i < M; i++) {
    int a, b;
    in >> a >> b;
    a--;
    b--;
    g[a].insert(b);
    g[b].insert(a);
  }
  //Debug(g);
  var pes = graph::ChordalGraph(g);
  Assert(pes.is_some());
  Reverse(All((*pes)));
  Vec<int> colors(N, -1);
  VersionArray<int> va(N + 1);
  int maxColorId = 0;
  for(var x : *pes) {
    va.clear();
    for(int t : g[x]) {
      if(colors[t] >= 0) {
        va[colors[t]] = true;
      }
    }
    colors[x] = 0;
    while(va[colors[x]]) {
      colors[x]++;
    }
    Chmax(maxColorId, colors[x]);
  }
  Debug(*pes);
  Debug(colors);
  out << maxColorId + 1 << '\n';
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
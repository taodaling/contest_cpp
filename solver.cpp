#pragma once
#include "common.cpp"
using namespace dalt;
#include "cut_vertex.cpp"
using namespace graph;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int n, m;
  in >> n >> m;
  using E = BiBaseEdge;
  Graph<E> g(n);
  for(int i = 0; i < m; i++) {
    int x, y;
    in >> x >> y;
    x--;
    y--;
    AddBiEdge(g, x, y);
  }
  auto res = CutVertex(g);
  auto& cut = std::get<0>(res);
  Vec<int> ans;
  for(int i = 0; i < n; i++) {
    if(cut[i]) {
      ans.push_back(i);
    }
  }
  out << Size(ans) << '\n';
  for(auto x : ans) {
    out << x + 1 << ' ';
  }
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    SolveOne(i + 1, in, out);
  }
}
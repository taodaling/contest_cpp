#pragma once
#include "common.cpp"
using namespace dalt;
#include "strongly_connected_component.cpp"
#include "gcd.cpp"
using namespace graph;

void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  using E = DiBaseEdge;
  Graph<E> g(N);
  for(int i = 0; i < M; i++) {
    int u, v;
    in >> u >> v;
    u--;
    v--;
    AddDiEdge(g, u, v);
  }
  var set = StronglyConnectedComponentDi(g);
  Vec<bool> in_root(N);
  for(int i = 0; i < N; i++) {
    if(set[i] == set[0]) {
      in_root[i] = true;
    }
  }
  Vec<int> depth(N, -1);
  Vec<bool> instk(N);
  Vec<int> loop;
  var dfs = [&](var &dfs, int root, int p) -> void {
    Debug(root);
    if(depth[root] != -1) {
      if(instk[root]) {
        loop.push_back(Abs(depth[root] - depth[p]) + 1);
      }
      return;
    }
    depth[root] = p == -1 ? 0 : depth[p] + 1;
    instk[root] = true;
    for(var &e : g[root]) {
      if(in_root[e.to]) {
        dfs(dfs, e.to, root);
      }
    }
    instk[root] = false;
  };
  dfs(dfs, 0, -1);
  int gcd = 0;
  for(int x : loop) {
    gcd = Gcd(gcd, x); 
  }
  while(gcd != 0 && gcd % 2 == 0) {
    gcd /= 2;
  }
  while(gcd != 0 && gcd % 5 == 0) {
    gcd /= 5;
  }
  if(gcd == 1) {
    out << "Yes";
  } else {
    out << "No";
  }
  out << '\n';

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
#pragma once
#include "common.cpp"
using namespace dalt;
#include "graph.cpp"
using namespace graph;
#include "math.cpp"
#include "optional.cpp"
struct Edge : BiBaseEdge, WithWeight<i64> {};

void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  Graph<Edge> g(N);
  Vec<Tuple<int, int, int>> edges;
  for (int i = 0; i < M; i++) {
    int a, b, c;
    in >> a >> b >> c;
    a--;
    b--;
    edges.push_back(MakeTuple(a, b, c));
    AddBiEdge(g, a, b);
    g[b].back().weight = g[a].back().weight = c;
  }
  // dist, label
  using Dist = Tuple<int, int>;
  int inf = 1e9;
  var find_ssp = [&](int root) {
    Vec<Dist> dists(N, MakeTuple(inf, root));
    Vec<bool> used(N);
    dists[root] = MakeTuple(0, root);

    for (int i = 0; i < N; i++) {
      int take = -1;
      for (int j = 0; j < N; j++) {
        if (used[j]) continue;
        if (take == -1 || dists[take] > dists[j]) {
          take = j;
        }
      }
      var node = take;
      used[node] = true;
      var[len, label] = dists[node];
      for (varr e : g[node]) {
        Chmin(dists[e.to],
              MakeTuple(len + e.weight, label == root ? e.to : label));
      }
    }
    return dists;
  };

  var find_q = [&](int root) -> Tuple<Vec<Dist>, i64, int, int> {
    var dists = find_ssp(root);
    var best = MakeTuple(inf, -1, -1);
    for (int i = 0; i < N; i++) {
      for (varr e : g[i]) {
        var a = i;
        var b = e.to;
        var c = e.weight;
        if (Get1(dists[a]) == Get1(dists[b]) || Get1(dists[a]) == a && b == root || a == root && Get1(dists[b]) == b) {
          continue;
        }
        int total = c + Get0(dists[a]) + Get0(dists[b]);
        Chmin(best, MakeTuple(total, a == root ? b : Get1(dists[a]), b == root ? a : Get1(dists[b])));
      }
    }
    var[dist, a, b] = best;
    return MakeTuple(dists, dist, a, b);
  };

  int best = inf;
  for (int i = 0; i < N; i++) {
    Debug(i);
    var[dists, ssp, a, b] = find_q(i);
    Debug(ssp);
    Debug(a);
    Debug(b);
    if (a == -1) {
      continue;
    }
    for (varr e : g[i]) {
      if (e.to == a || e.to == b) {
        continue;
      }
      Chmin(best, e.weight + ssp);
    }

    for (varr x : {a, b}) {
      for (varr e : g[i]) {
        if (e.to != x) {
          continue;
        }
        int backup = e.weight;
        e.weight = g[e.to][e.rev].weight = inf;

        var[dists, ssp, a, b] = find_q(i);
        Chmin(best, ssp + backup);

        e.weight = g[e.to][e.rev].weight = backup;
      }
    }

    Debug(best);
  }

  out << (best >= inf ? -1 : best);
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
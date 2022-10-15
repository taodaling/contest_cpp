#pragma once
#include "graph.cpp"
#include "math.cpp"
#include "dsu.cpp"
namespace dalt {
namespace graph {
  //return O(V) edges
  //create a new graph with K nodes which is full graph
  //there is an edge (a, b) with weight dist(a, b) in g
  //O(|E| log |E| log K)
template <class E, class T = typename E::weight_type>
enable_if_t<is_base_of_v<BiBaseEdge, E> && is_base_of_v<WithWeight<T>, E>,
            TreeSet<Tuple<int, int, T>>>
DistanceMinimumSpanningTree(const Graph<E> &g, int K, T inf) {
  int N = Size(g);
  TreeSet<Tuple<int, int, T>> ans;

  DSU dsu(K);

  int last_cc = 2 * K;
  while (true) {
    int cc = 0;
    for (int i = 0; i < K; i++) {
      if (dsu.find(i) == i) {
        cc++;
      }
    }
    if (cc == 1) {
      break;
    }
    Assert(last_cc / 2 >= cc);

    using Tag = Pair<i64, int>;
    Tag inf_tag = MakePair(inf, -1);
    Vec<Array<Tag, 2>> dists(N, Array<Tag, 2>{inf_tag, inf_tag});

    var update = [&](int id, Tag cand) {
      for (int i = 0; i < 2; i++) {
        if (dists[id][i] > cand) {
          dists[id][i] = cand;
          return true;
        }
        if (dsu.find(dists[id][i].second) == dsu.find(cand.second)) {
          return false;
        }
      }
      return false;
    };

    MinHeap<Pair<Tag, int>> pq;
    for (int i = 0; i < K; i++) {
      pq.push(MakePair(Tag{0, i}, i));
    }
    while (!pq.empty()) {
      var head = pq.top();
      pq.pop();
      int root = head.second;
      if (!update(root, head.first)) {
        continue;
      }
      for (var &e : g[root]) {
        pq.push(MakePair(Tag{head.first.first + e.weight, head.first.second},
                         e.to));
      }
    }

    // make graph
    Vec<Tuple<i64, int, int>> min_edge(K, MakeTuple(inf, -1, -1));
    for (int i = 0; i < K; i++) {
      for (int j = 0; j < 2; j++) {
        if (dsu.find(i) == dsu.find(dists[i][j].second)) {
          continue;
        }
        int to = dists[i][j].second;
        Chmin(min_edge[dsu.find(i)],
              MakeTuple(dists[i][j].first, Min(i, to), Max(i, to)));
        break;
      }
    }
    for (var &t : min_edge) {
      var c = std::get<0>(t);
      var a = std::get<1>(t);
      var b = std::get<2>(t);
      if (a == -1) {
        continue;
      }
      dsu.merge(a, b);
      ans.insert(MakeTuple(a, b, c));
    }
  }

  return ans;
}
}
}  // namespace dalt
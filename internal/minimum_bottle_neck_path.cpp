#pragma once
#include "dsu.cpp"
#include "graph.cpp"
#include "lowest_common_ancestor.cpp"
namespace dalt {
namespace graph {
  //only for connected component
  
  template<class E>
  struct MinBottleNeckPath {
    using weight_type = typename E::weight_type;
    static_assert(is_base_of_v<BiBaseEdge, E>);
    static_assert(is_base_of_v<WithWeight<weight_type>, E>);
    int N;
    Vec<weight_type> weights;
    LowestCommonAncestorBySchieberVishkin<BiBaseEdge> *lca;
    // O(E\log E) for construction
    MinBottleNeckPath(const Graph<E> &g) {
      N = Size(g);
      DSU dsu(N * 2);
      Vec<int> top(N * 2);
      for(int i = 0; i < N * 2; i++) {
        top[i] = i;
      }
      weights.reserve(N);
      Vec<const E*> edges;
      int edge_cnt = 0;
      for(var &e : g) {
        edge_cnt += Size(e);
      } 
      edges.reserve(edge_cnt);
      for(int i = 0; i < N; i++) {
        for(var &e : g[i]) {
          edges.push_back(&e);
        }
      }
      Sort(All(edges), [&](var& a, var &b) {
        return a->weight < b->weight;
      });
      Graph<BiBaseEdge> tree(N * 2);
      for(var &e : edges) {
        int a = e->to;
        int b = g[e->to][e->rev].to;
        var w = e->weight;
        if(dsu.find(a) == dsu.find(b)) {
          continue;
        }
        int id = Size(weights) + N;
        weights.push_back(w);
        // DebugFmtln("add (%d, %d, %d)", a, top[dsu.find(a)], id);
        // DebugFmtln("add (%d, %d, %d)", b, top[dsu.find(b)], id);
        AddBiEdge(tree, top[dsu.find(a)], id);
        AddBiEdge(tree, top[dsu.find(b)], id);

        dsu.merge(a, b);
        top[dsu.find(a)] = id;
      }
      lca = new LowestCommonAncestorBySchieberVishkin<BiBaseEdge>(tree, [&](int i) {return i == (N + Size(weights) - 1);});
    }

    //O(1)
    weight_type bottle(int a, int b) const {
      if(a == b) {
        return weight_type(0);
      }
      int id = lca->lca(a, b);
      return weights[id - N];
    }

    ~MinBottleNeckPath() {
      delete lca;
    }
  };
}
}  // namespace dalt

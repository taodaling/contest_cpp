#pragma once
// copied from
// https://github.com/indy256/codelibrary/blob/master/java/combinatorics/PruferCode.java
//  https://en.wikipedia.org/wiki/Pr%C3%BCfer_sequence
#include "graph.cpp"
namespace dalt {
namespace graph {
// O(n) complexity
void PruferCode2Tree(const Vec<int> &prufer_code,
                     const Consumer<Pair<int, int>> &consumer) {
  int n = prufer_code.size() + 2;
  Vec<int> degree(n, 1);
  for (int v : prufer_code) ++degree[v];
  int ptr = 0;
  while (degree[ptr] != 1) ++ptr;
  int leaf = ptr;
  for (int v : prufer_code) {
    consumer(MakePair(v, leaf));
    --degree[leaf];
    --degree[v];
    if (degree[v] == 1 && v < ptr) {
      leaf = v;
    } else {
      while (degree[++ptr] != 1)
        ;
      leaf = ptr;
    }
  }
  for (int v = 0; v < n - 1; v++) {
    if (degree[v] == 1) {
      consumer(MakePair(v, n - 1));
    }
  }
}
// precondition: n >= 2
// O(n) complexity
template <class E>
IsBiGraph(E, Vec<int>) Tree2PruferCode(const Graph<E> &tree) {
  Assert(Size(tree) >= 2);
  int n = tree.size();
  Vec<int> parent(n);
  parent[n - 1] = -1;
  var dfs = [&](var &dfs, int u) {
    for (var &e : tree[u]) {
      int v = e.to;
      if (v != parent[u]) {
        parent[v] = u;
        dfs(dfs, v);
      }
    }
  };

  dfs(dfs, n - 1);
  Vec<int> degree(n);
  int ptr = -1;
  for (int i = 0; i < n; ++i) {
    degree[i] = tree[i].size();
    if (degree[i] == 1 && ptr == -1) ptr = i;
  }
  Vec<int> res(n - 2);
  for (int i = 0, leaf = ptr; i < n - 2; ++i) {
    int next = parent[leaf];
    res[i] = next;
    --degree[next];
    if (degree[next] == 1 && next < ptr) {
      leaf = next;
    } else {
      while (degree[++ptr] != 1)
        ;
      leaf = ptr;
    }
  }
  return res;
}
}  // namespace graph
}  // namespace dalt
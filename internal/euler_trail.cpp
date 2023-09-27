#include "graph.cpp"
#include "optional.cpp"
namespace dalt {
namespace graph {
template <class E>
IsBiGraph(E, Optional<Pair<Vec<int> COMMA Vec<int>>>) EulerTraceBi(Graph<E> g) {
  Vec<int> odd;
  odd.reserve(2);
  for (int i = 0; i < Size(g); i++) {
    if (Size(g[i]) & 1) {
      odd.push_back(i);
    }
  }
  int root = -1;
  for (int i = 0; i < Size(g); i++) {
    if (Size(g[i]) > 0) {
      root = i;
      break;
    }
  }
  if (Size(odd) > 2 || root < 0) {
    return {};
  }
  if (Size(odd) > 0) {
    root = odd[0];
  }
  Vec<int> nodes;
  Vec<int> edges;
  var dfs = [&](var &dfs, int v, int e) -> void {
    while (!g[v].empty()) {
      var next = g[v].back();
      g[v].pop_back();
      if (next.to == -1) {
        continue;
      }
      g[next.to][next.rev].to = -1;
      dfs(dfs, next.to, next.rev);
    }
    nodes.push_back(v);
    edges.push_back(e);
  };
  dfs(dfs, root, -1);
  for (int i = 0; i < Size(g); i++) {
    if (Size(g[i]) > 0) {
      return {};
    }
  }
  Reverse(All(nodes));
  Reverse(All(edges));
  return {{nodes, edges}};
}
template <class E>
IsDiGraph(E, Optional<Pair<Vec<int> COMMA Vec<int>>>) EulerTraceDi(Graph<E> g) {
  int N = Size(g);
  Vec<int> begin;
  Vec<int> end;
  Vec<int> indeg(N);
  Vec<int> outdeg(N);
  for (int i = 0; i < N; i++) {
    for (var &e : g[i]) {
      outdeg[i]++;
      indeg[e.to]++;
    }
  }
  int root = -1;
  for (int i = 0; i < N; i++) {
    if (Size(g[i]) > 0) {
      root = i;
    }
    if (indeg[i] == outdeg[i]) {
      continue;
    } else if (indeg[i] == outdeg[i] + 1) {
      end.push_back(i);
    } else if (indeg[i] + 1 == outdeg[i]) {
      begin.push_back(i);
    } else {
      return {};
    }
  }
  if (Size(begin) >= 2 || root < 0) {
    return {};
  }
  if (Size(begin) > 0) {
    root = begin.front();
  }
  Vec<int> nodes;
  Vec<int> edges;
  var dfs = [&](var &dfs, int v, int e) -> void {
    while (!g[v].empty()) {
      var next = g[v].back();
      g[v].pop_back();
      dfs(dfs, next.to, Size(g[v]));
    }
    nodes.push_back(v);
    edges.push_back(e);
  };
  dfs(dfs, root, -1);
  for (int i = 0; i < Size(g); i++) {
    if (Size(g[i]) > 0) {
      return {};
    }
  }
  Reverse(All(nodes));
  Reverse(All(edges));
  return {{nodes, edges}};
}
}  // namespace graph
}  // namespace dalt
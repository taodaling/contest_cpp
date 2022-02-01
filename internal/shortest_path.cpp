#include "graph.cpp"

namespace dalt {
namespace graph {
template <class T, class E,
          class = enable_if_t<is_base_of_v<WithTo, E> &&
                              is_base_of_v<WithWeight<T>, E>>>
Tuple<Vec<T>, Vec<int>> ShortestPathWeightElogE(const Graph<E> &g,
                                                const Checker<int> &is_source,
                                                T inf) {
  using State = Tuple<T, int, int>;
  int n = Size(g);
  MinHeap<State> heap;
  Vec<T> dist(n, inf);
  Vec<int> prev(n, -1);
  for (int i = 0; i < n; i++) {
    if (is_source(i)) {
      heap.push(State(0, i, -1));
    }
  }
  while (!heap.empty()) {
    auto state = heap.top();
    heap.pop();
    int root = Get(state, 1);
    T d = Get(state, 0);
    if (dist[root] <= d) {
      continue;
    }
    dist[root] = d;
    prev[root] = Get(state, 2);
    for (auto &e : g[root]) {
      heap.push(State(d + e.weight, e.to, root));
    }
  }

  return Tuple<Vec<T>, Vec<int>>(dist, prev);
}
template <class T, class E,
          class = enable_if_t<is_base_of_v<WithTo, E> &&
                              is_base_of_v<WithWeight<T>, E>>>
Tuple<Vec<T>, Vec<int>> ShortestPathWeightElogV(const Graph<E> &g,
                                                const Checker<int> &is_source,
                                                T inf) {
  int n = Size(g);
  Vec<T> dist(n, inf);
  Vec<int> prev(n, -1);
  TreeSet<i32, Comparator<i32>> set([&](auto a, auto b) {
    return Tuple<T, i32>(dist[a], a) < Tuple<T, i32>(dist[b], b);
  });
  for (int i = 0; i < n; i++) {
    if (is_source(i)) {
      dist[i] = 0;
      set.insert(i);
    }
  }
  while (!set.empty()) {
    auto top = set.begin();
    int root = *top;
    set.erase(top);
    for (auto &e : g[root]) {
      if (dist[e.to] > dist[root] + e.weight) {
        set.erase(e.to);
        dist[e.to] = dist[root] + e.weight;
        prev[e.to] = root;
        set.insert(e.to);
      }
    }
  }

  return Tuple<Vec<T>, Vec<int>>(dist, prev);
}
} // namespace graph
} // namespace dalt
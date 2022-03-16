#include "common.cpp"
#include "binary.cpp"
#include "graph.cpp"
namespace dalt {
namespace graph {
template <class T, class E>
enable_if_t<is_base_of_v<DiBaseEdge, E>, Tuple<T, Vec<bool>>>
MaxIndependentSet(const Graph<E> &g, const Vec<T> &weights) {
  int n = Size(weights);
  Assert(n <= 60);
  Vec<Vec<bool>> edges(n, Vec<bool>(n));
  for(int i = 0; i < n; i++) {
    for(auto &e : g[i]) {
      edges[e.to][i] = edges[i][e.to] = true;
    }
  }
  Vec<u64> adj(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      if (edges[i][j] || edges[j][i]) {
        adj[i] = SetBit(adj[i], j);
      }
    }
  }

  int left_half = (n + 1) / 2;
  int right_half = n - left_half;

  Vec<int> subsets(1 << left_half);
  Vec<T> left_sum(1 << left_half);
  int log = 0;
  for (int i = 1; i < 1 << left_half; i++) {
    while((1 << (log + 1)) <= i) {
        log++;
    }
    int highest = 1 << log;
    left_sum[i] = left_sum[i - highest] + weights[log];
    subsets[i] = subsets[i - highest];
    int possible = subsets[(int)((i - highest) & (~adj[log]))];
    if (left_sum[subsets[i]] < left_sum[possible] + weights[log]) {
      subsets[i] = possible | highest;
    }
  }

  int mask = (1 << left_half) - 1;
  Vec<T> right_sum(1 << right_half);
  Vec<u64> nearby(1 << right_half);

  u64 solution = subsets[mask];
  T ans = left_sum[subsets[mask]];
  T inf = std::numeric_limits<T>::max() / 2;
  log = 0;
  for (int i = 1; i < 1 << right_half; i++) {
        while((1 << (log + 1)) <= i) {
        log++;
    }
    int highest = 1 << log;
    right_sum[i] = KthBit(nearby[i - highest], left_half + log) == 1
                       ? -inf
                       : (right_sum[i - highest] + weights[left_half + log]);
    nearby[i] = nearby[i - highest] | adj[left_half + log];

    int leftSubset = subsets[(int)(mask & (~nearby[i]))];
    T cand = right_sum[i] + left_sum[leftSubset];
    if (cand > ans) {
      ans = cand;
      solution = ((u64)i << left_half) | leftSubset;
    }
  }

  Vec<bool> selections(n);
  for (int i = 0; i < n; i++) {
    selections[i] = KthBit(solution, i) == 1;
  }
  return {ans, selections};
}
}
} // namespace dalt
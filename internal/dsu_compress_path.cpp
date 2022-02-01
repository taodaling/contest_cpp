#pragma once
#include "../common.cpp"
#include "nil.cpp"

namespace dalt {

template <class C = Nil, class P = Nil> struct DSUCompressPath {
  using Self = DSUCompressPath<C, P>;

private:
  Vec<int> fa;
  Vec<int> size;
  Vec<C> sum_of_connected_commponent;
  Vec<P> sum_of_path_to_root;

public:
  DSUCompressPath(Vec<C> weights)
      : fa(weights.size()), size(weights.size()),
        sum_of_path_to_root(weights.size()),
        sum_of_connected_commponent(move(weights)) {
    int n = int(fa.size());
    for (int i = 0; i < n; i++) {
      fa[i] = i;
      size[i] = 1;
    }
  }
  int find(int i) {
    if (fa[fa[i]] == fa[i]) {
      return fa[i];
    }
    int prev_fa = fa[i];
    fa[i] = find(prev_fa);
    sum_of_path_to_root[i] =
        sum_of_path_to_root[i] + sum_of_path_to_root[prev_fa];
    return fa[i];
  }
  P path_to_root(int i) {
    find(i);
    return sum_of_path_to_root[i];
  }
  // a - b = delta
  void merge(int a, int b, P delta = P()) {
    delta = delta + path_to_root(b) - path_to_root(a);
    a = find(a);
    b = find(b);
    if (a == b) {
      return;
    }
    if (size[a] < size[b]) {
      Swap(a, b);
    }
    sum_of_connected_commponent[a] =
        sum_of_path_to_root[a] + sum_of_path_to_root[b];
    size[a] = size[a] + size[b];
    fa[b] = a;
    sum_of_path_to_root[b] = delta;
  }

  Vec<i32> to_vec() {
    Vec<i32> res;
    int n = Size(fa);
    res.reserve(n);
    for (int i = 0; i < n; i++) {
      int root = fa[i];
      while (fa[root] != root) {
        root = fa[root];
      }
      res.push_back(root);
    }
    return res;
  }
};
} // namespace dalt
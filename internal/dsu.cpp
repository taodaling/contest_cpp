#pragma once
#include "common.cpp"
#include "nil.cpp"
namespace dalt {
template <bool COMPRESS = true, bool ROLLBACK = false, class C = Nil, class P = Nil>
struct DSU {
  using Self = DSU<COMPRESS, ROLLBACK, C, P>;

  Vec<int> fa;
  Vec<int> size;
  Vec<C> sum_of_connected_commponent;
  Vec<P> sum_of_path_to_root;

 public:
  DSU(int n): DSU(Vec<C>(n)) {}
  DSU(Vec<C> weights): sum_of_connected_commponent(move(weights)) {
    int n = int(sum_of_connected_commponent.size());
    sum_of_path_to_root.resize(n);
    size.resize(n);
    fa.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i;
      size[i] = 1;
    }
  }

  IsBool(COMPRESS, int) find(int i) {
    if (fa[fa[i]] == fa[i]) {
      return fa[i];
    }
    int prev_fa = fa[i];
    fa[i] = find(prev_fa);
    sum_of_path_to_root[i] =
        sum_of_path_to_root[i] + sum_of_path_to_root[prev_fa];
    return fa[i];
  }
  IsBool(!COMPRESS, int) find(int i) const {
    while (fa[i] != i) {
      i = fa[i];
    }
    return i;
  }

  Pair<C, int> query_sum(int i) {
    auto root = find(i);
    return MakePair(sum_of_connected_commponent[root], root);
  }
  IsBool(COMPRESS, Pair<P COMMA int>) path_to_root(int i) {
    auto root = find(i);
    return MakePair(sum_of_path_to_root[i], root);
  }
  IsBool(!COMPRESS, Pair<P COMMA int>) path_to_root(int i) const {
    P sum = P();
    while (fa[i] != i) {
      sum = sum + sum_of_path_to_root[i];
      i = fa[i];
    }
    return MakePair(sum, i);
  }


  IsBool(!COMPRESS && ROLLBACK, Pair<Consumer<Tuple<int COMMA int>&> COMMA Consumer<Tuple<int COMMA int>&>>) wrap_as_function(int a, int b, P delta = P()) {
    return MakePair(
      [&, a, b, delta](Tuple<int COMMA int>& context) {
       // Trace(do);
      //  Debug(to_vec());

        Get0(context) = find(a);
        Get1(context) = find(b);
        merge(a, b, delta);
      },
      [&](Tuple<int COMMA int>& context) {
        int a = Get0(context);
        int b = Get1(context);
        if(a == b) {
          return;
        }
        if(fa[b] != a) {
          Swap(a, b);
        }
        assert(fa[b] == a);
        sum_of_path_to_root[b] = P();
        fa[b] = b;
        size[a] = size[a] - size[b];
        sum_of_connected_commponent[a] =
          sum_of_connected_commponent[a] - sum_of_connected_commponent[b];

      //  Trace(undo);
       // Debug(to_vec());
      }
    );
  }

  // a - b = delta
  // a - ra = x
  // b - rb = y
  // ra - rb = (a - x) - (b - y)
  void merge(int a, int b, P delta = P()) {
    auto pa = path_to_root(a);
    auto pb = path_to_root(b);
    delta = delta + pb.first - pa.first;
    a = pa.second;
    b = pb.second;
    if (a == b) {
      return;
    }
    if (size[a] < size[b]) {
      Swap(a, b);
    } else {
      delta = P() - delta;
    }
    sum_of_connected_commponent[a] =
        sum_of_connected_commponent[a] + sum_of_connected_commponent[b];
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
}  // namespace dalt
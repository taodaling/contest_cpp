#include "graph.cpp"
#include "nil.cpp"
namespace dalt {
namespace graph {
// reference: https://codeforces.com/blog/entry/74847
// Binary lifting with O(n) memory and time complexity for preprocessing
template <class T = Nil> struct BinaryLiftCompress {
  using Self = BinaryLiftCompress<T>;

private:
  Vec<int> p;
  Vec<int> depth;
  Vec<int> jump;
  Vec<T> sum;
  Vec<T> weight;
  Adder<T> adder;
  T s_nil;

  void consider(i32 root) {
    if (root == -1 || jump[root] != -1) {
      return;
    }

    auto fa = p[root];
    consider(fa);
    add_leaf(root, fa);
  }

  void add_leaf(i32 leaf, i32 pid) {
    if (pid == -1) {
      jump[leaf] = leaf;
    } else if (depth[pid] - depth[jump[pid]] ==
               depth[jump[pid]] - depth[jump[jump[pid]]]) {
      jump[leaf] = jump[jump[pid]];
      sum[leaf] = adder(adder(weight[leaf], sum[pid]), sum[jump[pid]]);
    } else {
      jump[leaf] = pid;
      sum[leaf] = weight[leaf];
    }
  }

public:
  BinaryLiftCompress(T _s_nil, Vec<i32> _p, Vec<i32> _depth, Vec<T> _weight,
                     const Adder<T> &_adder)
      : s_nil(_s_nil), p(move(_p)), depth(move(_depth)), weight(move(_weight)),
        adder(_adder) {
    Assert(p.size() == depth.size());
    Assert(p.size() == weight.size());
    int n = Size(p);
    jump = Vec<int>(n, -1);
    sum = Vec<T>(n, s_nil);
    for (int i = 0; i < n; i++) {
      consider(i);
    }
  }

  Tuple<int, T> first_true(int node, const BiChecker<int, T> &pred) {
    auto s = s_nil;
    while (!pred(node, s)) {
      auto cand = adder(s, sum[node]);
      auto fa = jump[node];
      if (pred(fa, adder(cand, weight[node]))) {
        s = adder(s, weight[node]);
        node = p[node];
      } else {
        s = cand;
        if (node == fa) {
          return {-1, adder(s, weight[node])};
        }
        node = fa;
      }
    }
    return {node, adder(s, weight[node])};
  }

  Tuple<int, T> last_true(int node, const BiChecker<i32, T> &pred) {
    auto s = s_nil;
    if (!pred(node, s)) {
      return Tuple<int, T>(-1, s);
    }
    while (true) {
      auto cand = adder(s, sum[node]);
      auto p = jump[node];
      if (pred(p, adder(cand, weight[p]))) {
        if (node == jump[node]) {
          return Tuple<int, T>(node, adder(cand, weight[node]));
        }
        s = cand;
        node = jump[node];
      } else {
        auto cand = adder(s, weight[node]);
        auto p = p[node];
        if (pred(p, adder(cand, weight[node]))) {
          s = cand;
          node = p;
        } else {
          return Tuple<int, T>(node, cand);
        }
      }
    }
  }
  int first_true_raw(int node, const Checker<int> &pred) {
    while (!pred(node)) {
      auto fa = jump[node];
      if (pred(fa)) {
        node = p[node];
      } else {
        if (node == fa) {
          return -1;
        }
        node = fa;
      }
    }
    return node;
  }
  int last_true_raw(int node, const Checker<int> &pred) {
    if (!pred(node)) {
      return -1;
    }
    while (true) {
      auto p = jump[node];
      if (pred(p)) {
        if (node == jump[node]) {
          return node;
        }
        node = jump[node];
      } else {
        auto p = p[node];
        if (pred(p)) {
          node = p;
        } else {
          return node;
        }
      }
    }
  }

  int kth_ancestor(i32 node, i32 k) {
    int target = depth[node] - k;
    return first_true_raw(node, [&](auto i) { return depth[i] <= target; });
  }

  // lowest common ancestor in O(log_2 n)
  i32 lca(int a, int b) {
    if (depth[a] > depth[b]) {
      a = kth_ancestor(a, depth[a] - depth[b]);
    } else {
      b = kth_ancestor(b, depth[b] - depth[a]);
    }
    while (a != b) {
      if (jump[a] == jump[b]) {
        a = p[a];
        b = p[b];
      } else {
        a = jump[a];
        b = jump[b];
      }
    }
    return a;
  }
};
} // namespace graph
} // namespace dalt
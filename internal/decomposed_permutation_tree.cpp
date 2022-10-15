#pragma once
#include "common.cpp"
#include "static_rmq.cpp"
namespace dalt {
struct DecomposedPermutationTree {
  using Self = DecomposedPermutationTree;
  Vec<Self *> adj;
  // it's a permutation of [l,r]
  int l;
  int r;
  //合点（join node）
  bool join;
  // it's P[ll..rr]
  int ll;
  int rr;
  // for building
  Self *fail;
  int fail_min;
  int fail_max;
  DecomposedPermutationTree(): fail(NULL) {
  } 
  bool increment() const {
    return l == r || adj[0]->l == l;
  }
  int length() const { return r - l + 1; }
};
DecomposedPermutationTree *BuildDecomposedPermutationTree(
    const Vec<int> &perm,
    const Supplier<DecomposedPermutationTree *> &supplier = []() {return new DecomposedPermutationTree();}) {
  int n = Size(perm);
  Vec<int> index(n);
  for (int i = 0; i < n; i++) {
    index[perm[i]] = i;
  }
  StaticRMQ range_max(n, [&](int a, int b) { return index[a] > index[b]; });
  Deque<DecomposedPermutationTree *> dq;
  for (int k = 0; k < n; k++) {
    var x = supplier();
    x->fail_min = x->fail_max = x->l = x->r = perm[k];
    x->ll = x->rr = k;
    x->join = true;

    while (!dq.empty()) {
      // step 1
      var y = dq.back();
      if (y->join && y->adj.size() >= 2 &&
          (x->r == y->l - 1 && !y->increment() ||
           x->l == y->r + 1 && y->increment())) {
        dq.pop_back();
        y->adj.push_back(x);
        y->l = Min(y->l, x->l);
        y->r = Max(y->r, x->r);
        y->rr = x->rr;
        x = y;
        continue;
      }

      // step 2
      if (y->r + 1 == x->l || x->r + 1 == y->l) {
        dq.pop_back();
        var z = supplier();
        z->adj.push_back(y);
        z->adj.push_back(x);
        z->join = true;
        z->l = Min(y->l, x->l);
        z->r = Max(y->r, x->r);
        z->ll = y->ll;
        z->rr = x->rr;
        x = z;
        continue;
      }

      // step 3
      // cut node has at least 4 children
      x->fail_min = x->l;
      x->fail_max = x->r;
      x->fail = y;
      bool find = false;

      for (var node = y; node; node = node->fail) {
        int l = Min(x->fail_min, node->l);
        int r = Max(x->fail_max, node->r);

        if (index[range_max.query(l, r)] > k) {
          // fail here
          break;
        }

        int cnt = k - node->ll + 1;
        if (cnt == r - l + 1) {
          find = true;
          // can be merged into a cut node
          var fa = supplier();
          fa->join = false;
          fa->adj.push_back(x);
          fa->l = l;
          fa->r = r;
          fa->ll = node->ll;
          fa->rr = k;
          while (!dq.empty()) {
            var tail = dq.back();
            dq.pop_back();
            fa->adj.push_back(tail);
            if (tail == node) {
              break;
            }
          }
          Reverse(All(fa->adj));
          x = fa;
          break;
        }

        x->fail_min = Min(x->fail_min, node->fail_min);
        x->fail_max = Max(x->fail_max, node->fail_max);
        x->fail = node->fail;
      }

      if (!find) {
        break;
      }
    }

    if (dq.empty()) {
      x->fail_min = x->l;
      x->fail_max = x->r;
    }
    dq.push_back(x);
  }

  Assert(dq.size() == 1);

  return dq.front();
}
}  // namespace dalt
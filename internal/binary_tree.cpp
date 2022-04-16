#pragma once
#include "binary.cpp"
#include "common.cpp"
#include "segtree_common.cpp"
namespace dalt {
namespace sbt {
struct BinaryTree {
  struct Node {
    Array<Node *, 2> next;
    i64 size;
    Node *get_left() { return next[0]; }
    Node *get_right() { return next[1]; }
    const Node *get_left() const { return next[0]; }
    const Node *get_right() const { return next[1]; }
    Node *create_or_get(int i) {
      if (!next[i]) {
        next[i] = new Node();
      }
      return next[i];
    }
    i64 get_child_size(int i) const {
      if (!next[i]) {
        return 0;
      }
      return next[i]->size;
    }
    ~Node() {
      delete next[0];
      delete next[1];
    }
  };
  Node *root;
  i32 H;
  BinaryTree(u64 max_val) {
    root = new Node();
    H = Log2Floor(max_val);
  }
  void add(u64 x, i64 cnt) {
    auto dfs = [&](auto &dfs, int index, Node *root) {
      root->size += cnt;
      if (index < 0) {
        return;
      }
      int bit = KthBit(x, index);
      dfs(dfs, index - 1, root->create_or_get(bit));
    };
    dfs(dfs, H, root);
  }
  void remove(u64 x, i64 cnt) { add(x, -cnt); }
  i64 query_sum(u64 L, u64 R) const {
    if (L > R) {
      return 0;
    }
    auto dfs = [&](auto &dfs, Node *root, int l, int r) -> i64 {
      if (sbt::SegmentNoIntersection(L, R, l, r) || root == NULL) {
        return 0;
      }
      if (sbt::SegmentCover(L, R, l, r)) {
        return root->size;
      }
      int m = (l + r) / 2;
      return dfs(dfs, root->get_left(), l, m) +
             dfs(dfs, root->get_right(), m + 1, r);
    };
    return dfs(dfs, root, 0, (1 << (H + 1)) - 1);
  }
  i64 total() const { return root->size; }
  u64 kth_xor(u64 x, i64 k = 1) const {
    u64 ans = 0;
    auto dfs = [&](auto &dfs, Node *root, int index) -> void {
      if (index < 0) {
        return;
      }
      int prefer = KthBit(x, index);
      if (root->get_child_size(prefer) < k) {
        k -= root->get_child_size(prefer);
        prefer ^= 1;
      }
      ans |= u64(prefer) << index;
      dfs(dfs, root->create_or_get(prefer), index - 1);
    };
    dfs(dfs, root, H);
    return ans;
  }

  Vec<Pair<u64, i64>> to_vec() const {
    u64 trace = 0;
    Vec<Pair<u64, i64>> ans;
    auto dfs = [&](auto &dfs, Node *root, int index) {
      if (root == NULL) {
        return;
      }
      if (index < 0) {
        if (root->size != 0) {
          ans.emplace_back(trace, root->size);
        }
        return;
      }
      for (int i = 0; i < 2; i++) {
        trace ^= u64(i) << index;
        dfs(dfs, root->next[i], index - 1);
        trace ^= u64(i) << index;
      }
    };
    dfs(dfs, root, H);
    return ans;
  }

#ifdef DROP
  ~BinaryTree() { delete root; }
#endif
};
}  // namespace sbt
}  // namespace dalt
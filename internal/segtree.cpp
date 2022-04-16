#pragma once
#include "optional.cpp"
#include "segtree_common.cpp"
#include "tag.cpp"
namespace dalt {
namespace sbt {
#define CID -202202131500
template <class S, class U, bool P = false, i64 ID = 0>
struct SegTree : public SelfBalanceTreeBase<S, U, ID, -1> {
  struct Node {
    using Self = Node;
    Self *left;
    Self *right;
    S sum;
    U upd;

#ifdef DROP
    ~Node() {
      delete left;
      delete right;
    }
#endif
    IsBool(P,Node *) clone() { return new Node(*this); }
    IsBool(!P,Node *) clone() { return this; }

    void push_up() { sum = SegTree::s_s(left->sum, right->sum); }
    void push_down() {
      left = left->clone();
      right = right->clone();
      if (upd != SegTree::u_nil) {
        left->modify(upd);
        right->modify(upd);
        upd = SegTree::u_nil;
      }
    }
    void modify(const U &u) {
      sum = SegTree::s_u(sum, u);
      upd = SegTree::SegTree::u_u(upd, u);
    }
  };
  using Self = SegTree<S, U, P, ID>;

  Node *tree;
  int n;

 private:
  Node *make_node() {
    Node *ans = new Node{
        .left = NULL,
        .right = NULL,
        .sum = SegTree::s_nil,
        .upd = SegTree::u_nil,
    };
    return ans;
  }

  IsBool(P,Node *) make_tree() {
    Node *root = make_node();
    root->left = root->right = root;
    return root;
  }
  IsBool(!P,Node *) make_tree() {
    Node *root = make_node();
    return root;
  }

 public:
  Self clone() const {
    Self ans = *this;
    ans.tree = ans.tree->clone();
    return ans;
  }

  SegTree(
      int _n = 0,
      const Indexer<S> &indexer = [](int index) { return SegTree::s_nil; })
      : n(_n) {
    auto dfs = [&](auto &dfs, int l, int r) -> Node * {
      Node *root = make_tree();
      root->upd = SegTree::u_nil;
      if (l == r) {
        root->sum = indexer(l);
      } else {
        int m = (l + r) / 2;
        root->left = dfs(dfs, l, m);
        root->right = dfs(dfs, m + 1, r);
        root->push_up();
      }
      return root;
    };
    tree = dfs(dfs, 0, n - 1);
  }
  
  IsBoolStatic(P, Self)
  MakePersistentTree(int n) {
    Self res(1);
    res.n = n;
    return res;
  }

  S query(int L, int R) {
    auto dfs = [&](auto &dfs, Node *root, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SegTree::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return root->sum;
      }
      root->push_down();
      int m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m);
      auto rsum = dfs(dfs, root->right, m + 1, r);
      return SegTree::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1);
  }
  S query_const(int L, int R) const {
    auto dfs = [&](auto &dfs, Node *root, int l, int r, const U &upd) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SegTree::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return SegTree::s_u(root->sum, upd);
      }
      U new_upd = SegTree::SegTree::u_u(root->upd, upd);
      int m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m, new_upd);
      auto rsum = dfs(dfs, root->right, m + 1, r, new_upd);
      return SegTree::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1, SegTree::u_nil);
  }
  void update(int L, int R, const U &upd) {
    auto dfs = [&](auto &dfs, Node *root, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        root->modify(upd);
        return;
      }
      root->push_down();
      int m = (l + r) / 2;
      dfs(dfs, root->left, l, m);
      dfs(dfs, root->right, m + 1, r);
      root->push_up();
    };
    dfs(dfs, tree, 0, n - 1);
  }
  void travel(const Consumer<S> &consumer) const {
    auto dfs = [&](auto &dfs, Node *root, const U &upd, int l, int r) {
      // is leaf
      if (l == r) {
        consumer(SegTree::s_u(root->sum, upd));
        return;
      }
      int m = (l + r) / 2;
      U new_upd = SegTree::SegTree::u_u(root->upd, upd);
      dfs(dfs, root->left, new_upd, l, m);
      dfs(dfs, root->right, new_upd, m + 1, r);
    };
    dfs(dfs, tree, SegTree::u_nil, 0, n - 1);
  }
  Vec<S> to_vec() const {
    Vec<S> res;
    res.reserve(n);
    travel([&](auto x) { res.push_back(x); });
    return res;
  }
  Optional<Tuple<int, S>> first_true(int L, int R, Checker<S> &checker) {
    S sum = SegTree::s_nil;
    auto dfs = [&](auto &dfs, Node *root, int l, int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SegTree::s_s(sum, root->sum);
        if (!checker(new_sum)) {
          sum = new_sum;
          return {};
        }
        if (l == r) {
          // leaf
          sum = new_sum;
          return l;
        }
      }
      root->push_down();
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    return res.map(
        [&](int x) -> Tuple<int, S> { return Tuple<int, S>(x, sum); });
  }
  Optional<Tuple<int, S>> last_true(int L, int R, const Checker<S> &checker) {
    S sum = SegTree::s_nil;
    auto dfs = [&](auto &dfs, Node *root, int l, int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SegTree::s_s(sum, root->sum);
        if (checker(new_sum)) {
          sum = new_sum;
          return r;
        }
        if (l == r) {
          return {};
        }
      }
      root->push_down();
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if (lres.s_some() || r < L) {
        auto rres = dfs(dfs, root->right, m + 1, r);
        if (rres.s_some()) {
          return rres;
        }
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    return res.map(
        [&](int x) -> Tuple<int, S> { return Tuple<int, S>(x, sum); });
  }
  Optional<Tuple<int, S>> first_true_const(int L, int R,
                                           Checker<S> &checker) const {
    S sum = SegTree::s_nil;
    auto dfs = [&](auto& dfs, Node *root, const U &upd, int l, int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SegTree::s_s(sum, SegTree::s_u(root->sum, upd));
        if (!checker(new_sum)) {
          sum = new_sum;
          return {};
        }
        if (l == r) {
          // leaf
          sum = new_sum;
          return l;
        }
      }
      U new_upd = SegTree::SegTree::u_u(root->upd, upd);
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, new_upd, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SegTree::u_nil, 0, n - 1);
    return res.map([&](auto x) { return Tuple<int, S>(x, sum); });
  }
  Optional<Tuple<int, S>> last_true_const(int L, int R,
                                          const Checker<S> &checker) const {
    S sum = SegTree::s_nil;
    auto dfs = [&](auto& dfs, Node *root, const U &upd, int l, int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SegTree::s_s(sum, SegTree::s_u(root->sum, upd));
        if (checker(new_sum)) {
          sum = new_sum;
          return r;
        }
        if (l == r) {
          // leaf
          return {};
        }
      }
      U new_upd = SegTree::SegTree::u_u(root->upd, upd);
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if (lres.is_some() || r < L) {
        auto rres = dfs(dfs, root->right, new_upd, m + 1, r);
        if (rres.is_some()) {
          return rres;
        }
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SegTree::u_nil, 0, n - 1);
    return res.map([&](auto x) { return Tuple<int, S>(x, sum); });
  }

  IsBool(!P,void) destroy() { delete tree; }
  IsBool(P,void) destroy() {}

#ifdef DROP
  ~SegTree() { destroy(); }
#endif
};
#undef CID
}  // namespace sbt
}  // namespace dalt
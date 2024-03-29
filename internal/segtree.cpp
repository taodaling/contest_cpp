#pragma once
#include "optional.cpp"
#include "segtree_common.cpp"
namespace dalt {
namespace sbt {
#define CLASS_ID -202202131500
template <class SBT, bool P = false, bool SPARSE = false, i64 ID = 0>
struct SegTree {
  static_assert(is_sbt_registry_v<SBT>);
  static_assert(i64(P) + i64(SPARSE) <= 1);
  using S = typename SBT::TypeS;
  using U = typename SBT::TypeU;
  struct Node {
    using Self = Node;
    Self *left;
    Self *right;
    S sum;
    U upd;

#ifdef DROP
    ~Node() {
      if (this == NIL) {
        return;
      }
      delete left;
      delete right;
    }
#endif
    Self* clone() {
      if (SPARSE) {
        if (this == NIL) {
          return new Node(*NIL);
        }
        return this;
      } else if (P) {
        return new Node(*this);
      } else {
        return this;
      }
    }
    void push_up() { sum = SBT::s_s(left->sum, right->sum); }
    void push_down() {
      left = left->clone();
      right = right->clone();
      if (upd != SBT::u_nil) {
        left->modify(upd);
        right->modify(upd);
        upd = SBT::u_nil;
      }
    }
    void modify(const U &u) {
      sum = SBT::s_u(sum, u);
      upd = SBT::u_u(upd, u);
    }
  };
  using Self = SegTree<SBT, P, SPARSE, ID>;
  static Node *NIL;
  Node *tree;
  i64 n;

 private:
  Node *make_node() {
    Node *ans = new Node{
        .left = NIL,
        .right = NIL,
        .sum = SBT::s_nil,
        .upd = SBT::u_nil,
    };
    return ans;
  }
  IsBool(P, Node *) make_tree() {
    Node *root = make_node();
    root->left = root->right = root;
    return root;
  }
  IsBool(!P, Node *) make_tree() {
    Node *root = make_node();
    return root;
  }

 public:
  IsBoolStatic(SPARSE, void)
      Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
               const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    SBT::Register(_s_nil, _u_nil, _s_s,
                                                      _s_u, _u_u);
    NIL = new Node();
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->upd = _u_nil;
    NIL->sum = _s_nil;
  }
  IsBoolStatic(!SPARSE, void)
      Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
               const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    SBT::Register(_s_nil, _u_nil, _s_s,
                                                      _s_u, _u_u);
  }
  Self clone() const {
    Self ans = *this;
    ans.tree = ans.tree->clone();
    return ans;
  }

  SegTree(
      i64 _n = 0,
      const Indexer<S> &indexer = [](i64 index) { return SBT::s_nil; })
      : n(_n) {
    auto dfs = [&](auto &dfs, i64 l, i64 r) -> Node * {
      Node *root = make_tree();
      root->upd = SBT::u_nil;
      if (l == r) {
        root->sum = indexer(l);
      } else {
        i64 m = (l + r) / 2;
        root->left = dfs(dfs, l, m);
        root->right = dfs(dfs, m + 1, r);
        root->push_up();
      }
      return root;
    };
    if(n <= 0) {
      tree = make_tree();
    } else {
      tree = dfs(dfs, 0, n - 1);
    }
  }
  IsBoolStatic(SPARSE, Self) MakeSparseTree(i64 n) {
    Self res(1);
    res.n = n;
    return res;
  }
  IsBoolStatic(P, Self) MakePersistentTree(i64 n) {
    Self res(1);
    res.n = n;
    return res;
  }

  S query(i64 L, i64 R) {
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SBT::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return root->sum;
      }
      root->push_down();
      i64 m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m);
      auto rsum = dfs(dfs, root->right, m + 1, r);
      return SBT::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1);
  }
  S query_const(i64 L, i64 R) const {
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r, const U &upd) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SBT::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return SBT::s_u(root->sum, upd);
      }
      U new_upd = SBT::u_u(root->upd, upd);
      i64 m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m, new_upd);
      auto rsum = dfs(dfs, root->right, m + 1, r, new_upd);
      return SBT::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1, SBT::u_nil);
  }
  void update(i64 L, i64 R, const U &upd) {
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        root->modify(upd);
        return;
      }
      root->push_down();
      i64 m = (l + r) / 2;
      dfs(dfs, root->left, l, m);
      dfs(dfs, root->right, m + 1, r);
      root->push_up();
    };
    dfs(dfs, tree, 0, n - 1);
  }
  void travel(const Consumer<S> &consumer) const {
    auto dfs = [&](auto &dfs, Node *root, const U &upd, i64 l, i64 r) {
      // is leaf
      if (l == r) {
        consumer(SBT::s_u(root->sum, upd));
        return;
      }
      i64 m = (l + r) / 2;
      U new_upd = SBT::u_u(root->upd, upd);
      dfs(dfs, root->left, new_upd, l, m);
      dfs(dfs, root->right, new_upd, m + 1, r);
    };
    dfs(dfs, tree, SBT::u_nil, 0, n - 1);
  }
  Vec<S> to_vec() const {
    Vec<S> res;
    res.reserve(n);
    travel([&](auto x) { res.push_back(x); });
    return res;
  }
  Optional<Tuple<i64, S>> first_true(i64 L, i64 R, const Checker<S> &checker) {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) -> Optional<i64> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, root->sum);
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
      i64 m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<i64, S>> last_true(i64 L, i64 R, const Checker<S> &checker) {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) -> Optional<i64> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, root->sum);
        if (checker(new_sum)) {
          sum = new_sum;
          return r;
        }
        if (l == r) {
          return {};
        }
      }
      root->push_down();
      i64 m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if ((lres.is_some() && lres.value() == m) || m < L) {
        auto rres = dfs(dfs, root->right, m + 1, r);
        if (rres.is_some()) {
          return rres;
        }
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<i64, S>> first_true_const(i64 L, i64 R,
                                           const Checker<S> &checker,
                                           const S& init_sum = SBT::s_nil) const {
    S sum = init_sum;
    auto dfs = [&](auto &dfs, Node *root, const U &upd, i64 l,
                   i64 r) -> Optional<i64> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, SBT::s_u(root->sum, upd));
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
      U new_upd = SBT::u_u(root->upd, upd);
      i64 m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, new_upd, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SBT::u_nil, 0, n - 1);
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<i64, S>> last_true_const(i64 L, i64 R,
                                          const Checker<S> &checker) const {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, const U &upd, i64 l,
                   i64 r) -> Optional<i64> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, SBT::s_u(root->sum, upd));
        if (checker(new_sum)) {
          sum = new_sum;
          return r;
        }
        if (l == r) {
          // leaf
          return {};
        }
      }
      U new_upd = SBT::u_u(root->upd, upd);
      i64 m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if ((lres.is_some() && lres.value() == m) || m < L) {
        auto rres = dfs(dfs, root->right, new_upd, m + 1, r);
        if (rres.is_some()) {
          return rres;
        }
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SBT::u_nil, 0, n - 1);
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }

  IsBool(!(P || SPARSE), void) destroy() { delete tree; }
  IsBool(P || SPARSE, void) destroy() {}
  // to support merge, only support single poi64 update
  IsBoolStatic(SPARSE, Self) merge(Self a, Self b, const Adder<S, S> &adder) {
    assert(a.n == b.n);
    auto dfs = [&](auto &dfs, Node *a, Node *b, i64 l, i64 r) -> Node * {
      if (a == NIL) {
        return b;
      }
      if (b == NIL) {
        return a;
      }
      if (l == r) {
        a->sum = adder(a->sum, b->sum);
        return a;
      }
      i64 m = (l + r) / 2;
      // a->push_down();
      // b->push_down();
      a->left = dfs(dfs, a->left, b->left, l, m);
      a->right = dfs(dfs, a->right, b->right, m + 1, r);
      a->push_up();
      return a;
    };
    a.tree = dfs(dfs, a.tree, b.tree, 0, a.n - 1);
    return a;
  }

#ifdef DROP
  ~SegTree() { destroy(); }
#endif
};
#undef CLASS_ID
template <class SBT, bool P, bool SPARSE, i64 ID>
typename SegTree<SBT, P, SPARSE, ID>::Node
    *SegTree<SBT, P, SPARSE, ID>::NIL = NULL;

}  // namespace sbt
}  // namespace dalt
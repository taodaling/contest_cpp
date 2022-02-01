#pragma once
#include "optional.cpp"
#include "segtree_common.cpp"
#include "tag.cpp"
namespace dalt {
namespace segtree {


template <class S, class U> struct SegTreeNode {
  using Self = SegTreeNode<S, U>;
  Self *left;
  Self *right;
  S sum;
  U upd;

  static void Destroy(Self *self) {
    if (self == NULL) {
      return;
    }
    Destroy(self->left);
    Destroy(self->right);
    delete self;
  }
};

template <
    class S, class U, class P = TransientTag,
    class = std::enable_if_t<is_same_v<P, TransientTag> || is_same_v<P, TransientTag>>>
struct SegTree {
  using Node = SegTreeNode<S, U>;

private:
  S s_nil;
  U u_nil;
  Adder<S, S> s_s;
  Adder<S, U> s_u;
  Adder<U, U> u_u;
  Node *tree;
  int n;

  Node* make_node() {
    Node *ans = new Node();
    ans->left = ans->right = NULL;
    ans->sum = s_nil;
    ans->upd = u_nil;
    return ans;
  }
  void modify(Node *root, const U &u) {
    root->sum = s_u(root->sum, u);
    root->upd = u_u(root->upd, u);
  }
  void push_up(Node *root) {
    root->sum = s_s(root->left->sum, root->right->sum);
  }
  IsType(TransientTag, P, void) push_down(Node *root) {
    if (root->upd != u_nil) {
      modify(root->left, root->upd);
      modify(root->right, root->upd);
      root->upd = u_nil;
    }
  }
  IsType(PermTag, P, void) push_down(Node *root) {
    root->left = new Node(*(root->left));
    root->right = new Node(*(root->right));
    modify(root->left, root->upd);
    modify(root->right, root->upd);
    root->upd = u_nil;
  }
  Node *make_tree(const Indexer<S> &indexer, int l, int r) {
    Node *root = make_node();
    root->upd = u_nil;
    if (l == r) {
      root->sum = indexer(l);
    } else {
      int m = (l + r) / 2;
      root->left = make_tree(indexer, l, m);
      root->right = make_tree(indexer, m + 1, r);
      push_up(root);
    }
    return root;
  }
  IsType(PermTag, P, Node *) make_tree() {
    Node *root = make_node();
    root->left = root->right = root;
    return root;
  }
  IsType(TransientTag, P, Node *) make_tree() {
    assert(false);
    return NULL;
  }
  S query_const_rec(Node *root, int L, int R, int l, int r,
                    const U &upd) const {
    if (SegmentNoIntersection(L, R, l, r)) {
      return s_nil;
    }
    if (SegmentCover(L, R, l, r)) {
      return s_u(root->sum, upd);
    }
    U new_upd = u_u(root->upd, upd);
    int m = (l + r) / 2;
    auto lsum = query_const_rec(root->left, L, R, l, m, new_upd);
    auto rsum = query_const_rec(root->right, L, R, m + 1, r, new_upd);
    return s_s(lsum, rsum);
  }
  S query_rec(Node *root, int L, int R, int l, int r) {
    if (SegmentNoIntersection(L, R, l, r)) {
      return s_nil;
    }
    if (SegmentCover(L, R, l, r)) {
      return root->sum;
    }
    push_down(root);
    int m = (l + r) / 2;
    auto lsum = query_rec(root->left, L, R, l, m);
    auto rsum = query_rec(root->right, L, R, m + 1, r);
    return s_s(lsum, rsum);
  }

  void update_rec(Node *root, int L, int R, int l, int r, const U &upd) {
    if (SegmentNoIntersection(L, R, l, r)) {
      return;
    }
    if (SegmentCover(L, R, l, r)) {
      modify(root, upd);
      return;
    }
    push_down(root);
    int m = (l + r) / 2;
    update_rec(root->left, L, R, l, m, upd);
    update_rec(root->right, L, R, m + 1, r, upd);
    push_up(root);
  }

  void travel_rec(Node *root, const U &upd, Consumer<S> &consumer, int l,
                  int r) const {
    // is leaf
    if (l == r) {
      consumer(s_u(root->sum, upd));
      return;
    }
    int m = (l + r) / 2;
    U new_upd = u_u(root->upd, upd);
    travel_rec(root->left, new_upd, consumer, l, m);
    travel_rec(root->right, new_upd, consumer, m + 1, r);
  }
  Optional<int> first_true_rec(Node *root, S &sum, int L, int R, int l, int r,
                               const Checker<S> &checker) {
    if (SegmentNoIntersection(L, R, l, r)) {
      return {};
    }
    if (SegmentCover(L, R, l, r)) {
      S new_sum = s_s(sum, root->sum);
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
    push_down(root);
    int m = (l + r) / 2;
    auto lres = first_true_rec(root->left, sum, L, R, l, m, checker);
    if (lres.is_none()) {
      return first_true_rec(root->right, sum, L, R, m + 1, r, checker);
    }
    return lres;
  }
  Optional<int> first_true_const_rec(Node *root, S &sum, const U &upd, int L,
                                     int R, int l, int r,
                                     const Checker<S> &checker) const {
    if (SegmentNoIntersection(L, R, l, r)) {
      return {};
    }
    if (SegmentCover(L, R, l, r)) {
      S new_sum = s_s(sum, s_u(root->sum, upd));
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
    U new_upd = u_u(root->upd, upd);
    push_down(root);
    int m = (l + r) / 2;
    auto lres =
        first_true_const_rec(root->left, sum, new_upd, L, R, l, m, checker);
    if (lres.is_none()) {
      return first_true_const_rec(root->right, sum, new_upd, L, R, m + 1, r,
                                  checker);
    }
    return lres;
  }
  Optional<int> last_true_const_rec(Node *root, S &sum, const U &upd, int L,
                                    int R, int l, int r,
                                    const Checker<S> &checker) const {
    if (SegmentNoIntersection(L, R, l, r)) {
      return {};
    }
    if (SegmentCover(L, R, l, r)) {
      S new_sum = s_s(sum, s_u(root->sum, upd));
      if (checker(new_sum)) {
        sum = new_sum;
        return r;
      }
      // false
      if (l == r) {
        return {};
      }
    }
    U new_upd = u_u(root->upd, upd);
    push_down(root);
    int m = (l + r) / 2;
    auto lres =
        last_true_const_rec(root->left, sum, new_upd, L, R, l, m, checker);
    if (m < L || lres.is_some() && lres.value() == m) {
      auto rres = last_true_const_rec(root->right, sum, new_upd, L, R, m + 1, r,
                                      checker);
      if (rres.is_some()) {
        return rres;
      }
    }
    return lres;
  }

public:
  using Self = SegTree<S, U, P>;
  SegTree(int _n, S _s_nil, U _u_nil, Adder<S, S> _s_s, Adder<U, U> _u_u,
          Adder<S, U> _s_u, const Indexer<S> &indexer)
      : n(_n), s_nil(_s_nil), u_nil(_u_nil), s_s(_s_s), u_u(_u_u), s_u(_s_u) {
    tree = make_tree(indexer, 0, n - 1);
  }
  SegTree(int _n, S _s_nil, U _u_nil, Adder<S, S> _s_s, Adder<U, U> _u_u,
          Adder<S, U> _s_u)
      : n(_n), s_nil(_s_nil), u_nil(_u_nil), s_s(_s_s), u_u(_u_u), s_u(_s_u) {
    tree = make_tree();
  }

  S query(int L, int R) { return query_rec(tree, L, R, 0, n - 1); }
  S query_const(int L, int R) const {
    return query_const_rec(tree, L, R, 0, n - 1, u_nil);
  }
  void update(int L, int R, const U &upd) {
    update_rec(tree, L, R, 0, n - 1, upd);
  }
  void travel(Consumer<S> &consumer) const {
    travel_rec(tree, u_nil, consumer, 0, n - 1);
  }
  Vec<S> to_vec() const {
    Vec<S> res;
    res.reserve(n);
    Consumer<S> consumer = [&](auto x) { res.push_back(x); };
    travel(consumer);
    return res;
  }
  Optional<Tuple<int, S>> first_true(int L, int R, Checker<S> &checker) {
    S sum = s_nil;
    auto res = first_true_rec(tree, sum, L, R, 0, n - 1, checker);
    TreeMapper<int, Tuple<int, S>> TreeMapper = [&](auto x) {
      return Tuple<int, S>(x, sum);
    };
    return res.TreeMap(TreeMapper);
  }
  Optional<Tuple<int, S>> last_true(int L, int R, const Checker<S> &checker) {
    S sum = s_nil;
    auto res = last_true_rec(tree, sum, L, R, 0, n - 1, checker);
    TreeMapper<int, Tuple<int, S>> TreeMapper = [&](auto x) {
      return Tuple<int, S>(x, sum);
    };
    return res.TreeMap(TreeMapper);
  }
  Optional<Tuple<int, S>> first_true_const(int L, int R,
                                           Checker<S> &checker) const {
    S sum = s_nil;
    auto res = first_true_rec(tree, sum, u_nil, L, R, 0, n - 1, checker);
    TreeMapper<int, Tuple<int, S>> TreeMapper = [&](auto x) {
      return Tuple<int, S>(x, sum);
    };
    return res.TreeMap(TreeMapper);
  }
  Optional<Tuple<int, S>> last_true_const(int L, int R,
                                          const Checker<S> &checker) const {
    S sum = s_nil;
    auto res = last_true_rec(tree, sum, u_nil, L, R, 0, n - 1, checker);
    TreeMapper<int, Tuple<int, S>> TreeMapper = [&](auto x) {
      return Tuple<int, S>(x, sum);
    };
    return res.TreeMap(TreeMapper);
  }

  IsType(PermTag, P, void) set_root(Node *root) { tree = root; }
  IsType(PermTag, P, Node *) get_root() { return tree; }
  IsType(TransientTag, P, void) destroy() { Node::Destroy(tree); }
  IsType(PermTag, P, void) destroy() {}

#ifdef DROP
  ~SegTree() { destroy(); }
#endif
};
} // namespace segtree
using segtree::SegTree;
} // namespace dalt
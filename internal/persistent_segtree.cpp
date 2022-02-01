#include "../common.cpp"
#include "segtree.cpp"

namespace dalt {
namespace persistent_segtree {
template <class S, class U> struct PersistentSegTree {
  using ST = SegTree<S, U, segtree::PermTag>;
  using Node = typename ST::Node;
  using Self = PersistentSegTree<S, U>;

private:
  ST *st;
  Node *root;
  PersistentSegTree(ST *_st) : st(_st), root(_st->get_root()) {}

public:
  inline PersistentSegTree(int _n, S _s_nil, U _u_nil, Adder<S, S> _s_s,
                           Adder<U, U> _u_u, Adder<S, U> _s_u,
                           const Indexer<S> &indexer) {
    st = new ST(_n, _s_nil, _u_nil, _s_s, _u_u, _s_u, indexer);
    root = st->get_root();
  }
  inline PersistentSegTree(int _n, S _s_nil, U _u_nil, Adder<S, S> _s_s,
                           Adder<U, U> _u_u, Adder<S, U> _s_u) {
    st = new ST(_n, _s_nil, _u_nil, _s_s, _u_u, _s_u);
    root = st->get_root();
  }
  inline S query(int L, int R) {
    st->set_root(root);
    return st->query_const(L, R);
  }
  inline Self update(int L, int R, const U &upd) {
    Node *root = new Node(*(this->root));
    st->set_root(root);
    st->update(L, R, upd);
    return Self(st);
  }
  inline Optional<Tuple<int, S>> first_true(int L, int R, Checker<S> &checker) {
    st->set_root(root);
    return st->first_true_const(L, R, checker);
  }
  inline Optional<Tuple<int, S>> last_true(int L, int R,
                                           const Checker<S> &checker) {
    st->set_root(root);
    return st->last_true_const(L, R, checker);
  };
  inline Node *get_root() { return root; }
  inline const Node *get_root() const { return root; }
  Vec<S> to_vec() {
    st->set_root(root);
    return st->to_vec();
  }
};
} // namespace persistent_segtree
using persistent_segtree::PersistentSegTree;
} // namespace dalt
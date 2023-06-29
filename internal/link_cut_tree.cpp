#pragma once
#include "sbt_common.cpp"
#include "sbt_reverse.cpp"
namespace dalt {
namespace sbt {
template <class SBT, bool DIR = false, i64 ID = 0>
struct LCTNode: public SbtReverse<SBT, DIR> {
  static_assert(is_sbt_registry_v<SBT>);
  using S = typename SBT::TypeS;
  using U = typename SBT::TypeU;
  using Self = LCTNode<SBT, DIR, ID>;
  static Self *NIL;
  Self *left;
  Self *right;
  Self *father;
  Self *tree_father;
  S sum;
  S weight;
  U upd;
  bool rev;
  i32 id;
  int tree_size;
  int vtree_size;
  i8 tree_weight;
  LCTNode(int _id = 0, const S &_weight = SBT::s_nil,
          const U &_upd = SBT::u_nil, i8 _tree_weight = 1) {
    init(_id, _weight, _upd, _tree_weight);
  }
  void init(int _id = 0, const S &_weight = SBT::s_nil,
            const U &_upd = SBT::u_nil, i8 _tree_weight = 1) {
    id = _id;
    left = right = father = tree_father = NIL;
    rev = false;
    tree_size = vtree_size = 0;
    sum = weight = _weight;
    upd = _upd;
    tree_weight = _tree_weight;
    this->init_sum_rev(_weight);
  }
  static void Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
                       const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    if (NIL != NULL) {
      delete NIL;
    }
    NIL = new LCTNode(-1, _s_nil, _u_nil, 0);
    NIL->left = NIL->right = NIL->father = NIL->tree_father = NIL;
    SBT::Register(_s_nil, _u_nil, _s_s, _s_u,  _u_u);
  }

  void reverse() {
    rev = !rev;
    this->swap_sum_rev(sum);
  }

  void set_left(Self *x) {
    left = x;
    x->father = this;
  }

  void set_right(Self *x) {
    right = x;
    x->father = this;
  }

  void change_child(Self *y, Self *x) {
    if (left == y) {
      set_left(x);
    } else {
      set_right(x);
    }
  }

  static void zig(Self *x) {
    Self *y = x->father;
    Self *z = y->father;
    Self *b = x->right;

    y->set_left(b);
    x->set_right(y);
    z->change_child(y, x);

    y->push_up();
  }

  static void zag(Self *x) {
    Self *y = x->father;
    Self *z = y->father;
    Self *b = x->left;

    y->set_right(b);
    x->set_left(y);
    z->change_child(y, x);

    y->push_up();
  }

  void modify(const U &upd) {
    Self *x = this;
    if (x == NIL) {
      return;
    }
    x->sum = SBT::s_u(x->sum, upd);
    x->weight = SBT::s_u(x->weight, upd);
    x->upd = SBT::u_u(x->upd, upd);
    this->apply_sum_rev(upd);
  }
  static Self* access(Self *x) {
    Self *last = NIL;
    while (x != NIL) {
      splay(x);
      x->right->father = NIL;
      x->right->tree_father = x;
      x->vtree_size += x->right->tree_size;
      x->set_right(last);
      x->vtree_size -= last->tree_size;
      x->push_up();

      last = x;
      x = x->tree_father;
    }
    return last;
  }

  static void make_root(Self *x) {
    access(x);
    splay(x);
    x->reverse();
  }

  static void cut(Self *y, Self *x) {
    make_root(y);
    access(x);
    splay(y);
    y->right->tree_father = NIL;
    y->right->father = NIL;
    y->set_right(NIL);
    y->push_up();
  }

  static void join(Self *y, Self *x) {
    make_root(x);
    make_root(y);
    x->tree_father = y;
    y->vtree_size += x->tree_size;
    y->push_up();
  }

  static void find_path(Self *x, Self *y) {
    make_root(x);
    access(y);
  }

  static void splay(Self *x) {
    if (x == NIL) {
      return;
    }
    Self *y, *z;
    while ((y = x->father) != NIL) {
      if ((z = y->father) == NIL) {
        y->push_down();
        x->push_down();
        if (x == y->left) {
          zig(x);
        } else {
          zag(x);
        }
      } else {
        z->push_down();
        y->push_down();
        x->push_down();
        if (x == y->left) {
          if (y == z->left) {
            zig(y);
            zig(x);
          } else {
            zig(x);
            zag(x);
          }
        } else {
          if (y == z->left) {
            zag(x);
            zig(x);
          } else {
            zag(y);
            zag(x);
          }
        }
      }
    }

    x->push_down();
    x->push_up();
  }
  Vec<Pair<int, S>> to_vec_sub_tree() const {
    Vec<Pair<int, S>> data;
    travel([&](auto a, auto b) { data.push_back({a, b}); });
    return data;
  }
  Vec<Pair<int, S>> to_vec_tree() const {
    const Self *root = this;
    while (root->father != NIL) {
      root = root->father;
    }
    return root->to_vec_sub_tree();
  }
  static Self *find_root(Self *x) {
    splay(x);
    x->push_down();
    while (x->left != NIL) {
      x = x->left;
      x->push_down();
    }
    splay(x);
    return x;
  }
  static const Self *find_root_slow(const Self *x) {
    while (x->father != NIL) {
      x = x->father;
    }
    return x;
  }
  void travel(const BiConsumer<int, S> &consumer, bool rev = false,
              const U &upd = SBT::u_nil) const {
    const Self *root = this;
    if (root == NIL) {
      return;
    }
    if (root->rev) {
      rev = !rev;
    }
    U new_upd = SBT::u_u(root->upd, upd);
    (rev ? root->right : root->left)->travel(consumer, rev, new_upd);
    consumer(root->id, SBT::s_u(root->weight, upd));
    (rev ? root->left : root->right)->travel(consumer, rev, new_upd);
  }

  void push_down() {
    Self *root = this;
    if (root == NIL) {
      return;
    }
    if (root->rev) {
      root->rev = false;

      Self *tmpNode = root->left;
      root->left = root->right;
      root->right = tmpNode;

      root->left->reverse();
      root->right->reverse();
    }

    root->left->tree_father = root->tree_father;
    root->right->tree_father = root->tree_father;

    if (root->upd != NIL->upd) {
      root->left->modify(root->upd);
      root->right->modify(root->upd);
      root->upd = NIL->upd;
    }
  }

  void push_up() {
    Self *root = this;
    if (root == NIL) {
      return;
    }
    root->sum =
        SBT::s_s(SBT::s_s(root->left->sum, root->weight), root->right->sum);
    this->push_up_sum_rev(*(root->left), *(root->right));
    root->tree_size = root->left->tree_size + root->right->tree_size +
                      root->vtree_size + root->tree_weight;
  }

  static Self *lca(Self *a, Self *b) {
    if (a == b) {
      return a;
    }
    access(a);
    return access(b);
  }

  static bool connected(Self *a, Self *b) {
    make_root(a);
    access(b);
    return find_root(b) == a;
  }
};
template <class SBT, bool DIR, i64 ID>
LCTNode<SBT, DIR, ID> *LCTNode<SBT, DIR, ID>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
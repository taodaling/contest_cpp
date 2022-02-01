#include "../common.cpp"

namespace dalt {
namespace link_cut_tree {
template <class S, class U> struct LCTNode {
  using Self = LCTNode<S, U>;
  Self *left;
  Self *right;
  Self *father;
  Self *tree_father;
  S sum;
  S weight;
  U upd;
  bool rev;

  int id;
  int tree_size;
  int vtree_size;
  char tree_weight;

  void init(Self *NIL, const S &_weight, const U &_upd, char _tree_weight) {
    left = right = father = tree_father = NIL;
    rev = false;
    tree_size = vtree_size = 0;
    sum = weight = _weight;
    upd = _upd;
    tree_weight = _tree_weight;
  }

  void reverse() { rev = !rev; }

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
};
template <class S, class U> struct LinkCutTree {
  using Node = LCTNode<S, U>;
  using Self = LinkCutTree<S, U>;
  Node *NIL;

private:
  Adder<S, S> s_s;
  Adder<S, U> s_u;
  Adder<U, U> u_u;
  Vec<Node> nodes;
  void zig(Node *x) {
    Node *y = x->father;
    Node *z = y->father;
    Node *b = x->right;

    y->set_left(b);
    x->set_right(y);
    z->change_child(y, x);

    push_up(y);
  }

  void zag(Node *x) {
    Node *y = x->father;
    Node *z = y->father;
    Node *b = x->left;

    y->set_right(b);
    x->set_left(y);
    z->change_child(y, x);

    push_up(y);
  }

  void modify(Node *x, const U &upd) {
    if (x == NIL) {
      return;
    }
    x->sum = s_u(x->sum, upd);
    x->weight = s_u(x->weight, upd);
    x->upd = u_u(x->upd, upd);
  }
  void access(Node *x) {
    Node *last = NIL;
    while (x != NIL) {
      splay(x);
      x->right->father = NIL;
      x->right->tree_father = x;
      x->vtree_size += x->right->tree_size;
      x->set_right(last);
      x->vtree_size -= last->tree_size;
      push_up(x);

      last = x;
      x = x->tree_father;
    }
  }

  void make_root(Node *x) {
    access(x);
    splay(x);
    x->reverse();
  }

  void cut(Node *y, Node *x) {
    make_root(y);
    access(x);
    splay(y);
    y->right->tree_father = NIL;
    y->right->father = NIL;
    y->set_right(NIL);
    push_up(y);
  }

  void join(Node *y, Node *x) {
    make_root(x);
    make_root(y);
    x->tree_father = y;
    y->vtree_size += x->tree_size;
    push_up(y);
  }

  void find_path(Node *x, Node *y) {
    make_root(y);
    access(x);
  }

  void splay(Node *x) {
    if (x == NIL) {
      return;
    }
    Node *y, *z;
    while ((y = x->father) != NIL) {
      if ((z = y->father) == NIL) {
        push_down(y);
        push_down(x);
        if (x == y->left) {
          zig(x);
        } else {
          zag(x);
        }
      } else {
        push_down(z);
        push_down(y);
        push_down(x);
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

    push_down(x);
    push_up(x);
  }

  Node *find_root(Node *x) {
    splay(x);
    push_down(x);
    while (x->left != NIL) {
      x = x->left;
      push_down(x);
    }
    splay(x);
    return x;
  }
  const Node *find_root_slow(const Node *x) const {
    while (x->father != NIL) {
      x = x->father;
    }
    return x;
  }
  void travel(const Node *root, bool rev, const U &upd,
              Consumer<S> &consumer) const {
    if (root == NIL) {
      return;
    }
    if (root->rev) {
      rev = !rev;
    }
    U new_upd = u_u(root->upd, upd);
    travel(rev ? root->right : root->left, rev, new_upd, consumer);
    consumer(s_u(root->weight, upd));
    travel(rev ? root->left : root->right, rev, new_upd, consumer);
  }

  void push_down(Node *root) {
    if (root == NIL) {
      return;
    }
    if (root->rev) {
      root->rev = false;

      Node *tmpNode = root->left;
      root->left = root->right;
      root->right = tmpNode;

      root->left->reverse();
      root->right->reverse();
    }

    root->left->tree_father = root->tree_father;
    root->right->tree_father = root->tree_father;

    if (root->upd != NIL->upd) {
      modify(root->left, root->upd);
      modify(root->right, root->upd);
      root->upd = NIL->upd;
    }
  }

  void push_up(Node *root) {
    if (root == NIL) {
      return;
    }
    root->sum = s_s(s_s(root->left->sum, root->weight), root->right->sum);
    root->tree_size = root->left->tree_size + root->right->tree_size +
                      root->vtree_size + root->tree_weight;
  }

  Node *lca(Node *a, Node *b) {
    if (a == b) {
      return a;
    }
    access(a);
    splay(a);
    access(b);
    splay(b);
    if (a->tree_father != NIL) {
      return a->tree_father;
    }
    if (a->father != NIL) {
      // in same splay
      return a;
    }
    return NIL;
  }

  bool connected(Node *a, Node *b) {
    return lca(a, b) != NIL;
    //        makeRoot(a);
    //        access(b);
    //        splay(b);
    //        return findRoot(b) == a;
  }
  Node *get_node(int i) {
    Node *node = &nodes[i];
    if (node->father != NIL) {
      splay(node);
    }
    return node;
  }

public:
  LinkCutTree(int n, S s_nil, U u_nil, Adder<S, S> _s_s, Adder<U, U> _u_u,
              Adder<S, U> _s_u, const Indexer<S> &indexer,
              const Indexer<char> &weight_indexer)
      : nodes(n + 1), s_s(_s_s), u_u(_u_u), s_u(_s_u) {
    NIL = &nodes[n];
    NIL->id = -1;
    NIL->init(NIL, s_nil, u_nil, char(0));
    push_up(NIL);
    for (int i = 0; i < n; i++) {
      nodes[i].id = i;
      nodes[i].init(NIL, indexer(i), u_nil, weight_indexer(i));
      push_up(&nodes[i]);
    }
  }
  void splay(int root) { splay(&nodes[root]); }
  void access(int root) { access(&nodes[root]); }
  void modify_subtree(int root, const U &upd) { modify(&nodes[root], upd); }
  void make_root(int root) { make_root(&nodes[root]); }
  void cut(int y, int x) { cut(&nodes[y], &nodes[x]); }
  void join(int y, int x) { join(&nodes[y], &nodes[x]); }
  void find_path(int x, int y) { find_path(&nodes[x], &nodes[y]); }
  int find_root(int x) { return find_root(&nodes[x])->id; }
  int lca(int a, int b) { return lca(&nodes[a], &nodes[b])->id; }
  void travel(int root, Consumer<S> &consumer) const {
    const Node *tree = find_root_slow(&nodes[root]);
    travel(tree, false, NIL->upd, consumer);
  }
  Vec<S> to_vec_tree(int id) const {
    Vec<S> res;
    res.reserve(Size(nodes) - 1);
    Consumer<S> consumer = [&](auto s) { res.push_back(s); };
    travel(id, consumer);
    return res;
  }
  Vec<Vec<S>> to_vec_tree() const {
    Vec<Vec<S>> res;
    for (int i = 0; i < Size(nodes) - 1; i++) {
      const Node *node = &nodes[i];
      if (node->father == NIL) {
        res.push_back(to_vec_tree(i));
      }
    }
    return res;
  }
  Vec<S> to_vec() {
    Vec<S> res;
    int n = Size(nodes) - 1;
    res.reserve(n);
    for (int i = 0; i < n; i++) {
      res.push_back(get_weight(i));
    }
    return res;
  }

  S &get_sum(int root) { return get_node(root)->sum; }

  S &get_weight(int root) { return get_node(root)->weight; }

  int get_tree_size(int root) { return get_node(root)->tree_size; }
};
} // namespace link_cut_tree

using link_cut_tree::LinkCutTree;
} // namespace dalt
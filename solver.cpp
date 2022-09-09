#pragma once
#include "common.cpp"
using namespace dalt;
#pragma once
#include "sbt_common.cpp"
#include "sbt_reverse.cpp"
namespace dalt {
namespace sbt {
template <class SBT, bool DIR = false, i64 ID = 0>
struct LCTNode {
  static_assert(is_sbt_registry_v<SBT>);
  using S = typename SBT::TypeS;
  using U = typename SBT::TypeU;
  using Self = LCTNode<SBT, DIR, ID>;
  static Self *NIL;
  Self *left;
  Self *right;
  Self *father;
  Self *tree_father;
  S weight;
  U upd;
  bool rev;
  i32 id;
  LCTNode(int _id = 0, const S &_weight = SBT::s_nil,
          const U &_upd = SBT::u_nil) {
    init(_id, _weight, _upd);
  }
  void init(int _id = 0, const S &_weight = SBT::s_nil,
            const U &_upd = SBT::u_nil) {
    id = _id;
    left = right = father = tree_father = NIL;
    rev = false;
    weight = _weight;
    upd = _upd;
  }
  static void Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
                       const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    if (NIL != NULL) {
      delete NIL;
    }
    NIL = new LCTNode(-1, _s_nil, _u_nil);
    NIL->left = NIL->right = NIL->father = NIL->tree_father = NIL;
    SBT::Register(_s_nil, _u_nil, _s_s, _s_u, _u_u);
  }

  void reverse() {
    rev = !rev;
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
    x->weight = SBT::s_u(x->weight, upd);
    x->upd = SBT::u_u(x->upd, upd);
  }
  static void access(Self *x) {
    Self *last = NIL;
    while (x != NIL) {
      splay(x);
      x->right->father = NIL;
      x->right->tree_father = x;
      x->set_right(last);
      x->push_up();

      last = x;
      x = x->tree_father;
    }
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
  }

  static Self *lca(Self *a, Self *b) {
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

  static bool connected(Self *a, Self *b) {
    return lca(a, b) != NIL;
    //        makeRoot(a);
    //        access(b);
    //        splay(b);
    //        return findRoot(b) == a;
  }
};
template <class SBT, bool DIR, i64 ID>
LCTNode<SBT, DIR, ID> *LCTNode<SBT, DIR, ID>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
#include "math/mat3d.cpp"
using namespace math;
using V3 = math::Vec3<int>;
using M3 = math::Mat3<int>;
using REG = sbt::SelfBalanceTreeRegistry<V3, M3>;
using LCT = sbt::LCTNode<REG>;

#pragma once
#include "collection.cpp"
#include "common.cpp"
#include "nil.cpp"

namespace dalt {
namespace seq {
template <class T = char>
struct SuffixAutomaton {
  struct Node {
    TreeMap<T, Node*> next;
    Node* fail;
    i32 maxlen;
    i32 id;
    i32 smallest_right;
    i32 get_max_length() { return maxlen; }
    i32 get_min_length() { return fail == NULL ? 0 : fail->maxlen + 1; }
    Node() : fail(NULL), maxlen(0), smallest_right(-1) {}
  };
  struct Right {
    i32 cnt;
    i32 leftest_right;
    i32 rightest_right;
    Right()
        : leftest_right(std::numeric_limits<i32>::max()),
          rightest_right(std::numeric_limits<i32>::min()) {}
  };
  struct Matcher {
    SuffixAutomaton* sa;
    Node* match_last;
    i32 match_length;
    void match(T c) {
      T index = c;
      auto candidate = GetOrDefault<Node*>(match_last->next, index, NULL);
      if (candidate != NULL) {
        match_last = candidate;
        match_length = match_length + 1;
        return;
      }
      while (match_last != NULL &&
             (candidate = GetOrDefault<Node*>(match_last->next, index, NULL)) ==
                 NULL) {
        match_last = match_last->fail;
      }
      if (match_last == NULL) {
        match_last = sa->root;
        match_length = 0;
      } else {
        match_length = match_last->maxlen + 1;
        match_last = candidate;
      }
    }
  };
  Matcher matcher() {
    return Matcher{
        .sa = this,
        .match_last = root,
        .match_length = 0,
    };
  }
  Node* build_last;
  Vec<Node*> all;

 private:
  Node* root;
  i64 distinct_substr;
  bool sorted;

  Node* add_node(Node* node) {
    all.push_back(node);
    all.back()->id = Size(all) - 1;
    lcts.push_back(new LCT());
    lcts.back()->id = all.back()->id;
    return node;
  }
  Node* alloc() { return add_node(new Node()); }
  Node* clone(Node* id) { 
    var ans = add_node(new Node(*id)); 
    var last_lct = lcts.back();
    LCT::splay(lcts[id->id]);
    var item = lcts[id->id]->weight;
    LCT::splay(last_lct);
    last_lct->weight = item;
    last_lct->push_up();
    return ans;
  }


 public:
  //min_length right 
  MinHeap<Tuple<int, int, int>> heap;
  Vec<LCT*> lcts; 
  void process(Node *node) {
    heap.emplace(MakeTuple(node->get_min_length(), node->smallest_right, node->id));
  }
  void change_father(Node *node, Node* father) {
    if(node->fail) {
      LCT::cut(lcts[node->id], lcts[node->fail->id]);
    }
    node->fail = father;
    LCT::join(lcts[node->id], lcts[node->fail->id]);
    process(node);
  }

  void enable_distinct_substr() {
    if (distinct_substr == -1) {
      distinct_substr = 0;
    }
  }
  decltype(distinct_substr) get_distinct_substr() const {
    return distinct_substr;
  }
  SuffixAutomaton(i32 cap) : distinct_substr(-1) {
    all.reserve(cap * 2 + 1);
    lcts.reserve(cap * 2 + 1);
    build_last = root = alloc();
  }

  Node* visit(T index, Node* trace, Node* target, Node* replacement) {
    while (trace != NULL &&
           GetOrDefault<Node*>(trace->next, index, NULL) == target) {
      trace->next[index] = replacement;
      trace = trace->fail;
    }
    return trace;
  }
  void build_next() { build_last = root; }
  void build(T c, int right = -1) {
    sorted = false;
    T index = c;
    Node* candidate = build_last->next[c];
    // generic sam
    if (candidate != NULL && build_last->maxlen == candidate->maxlen + 1) {
      build_last = candidate;
      return;
    }
    auto now = alloc();
    now->smallest_right = right;
    now->maxlen = build_last->maxlen + 1;
    Node* p = visit(index, build_last, NULL, now);
    build_last = now;
    if (p == NULL) {
      change_father(now, root);
    } else {
      auto q = p->next[index];
      if (q->maxlen == p->maxlen + 1) {
        change_father(now, q);
      } else {
        auto clone = this->clone(q);
        clone->maxlen = p->maxlen + 1;
        clone->fail = NULL;
        change_father(clone, q->fail);
        change_father(now, clone);
        change_father(q, clone);
        visit(index, p, q, clone);
        // generic sam
        if (p->maxlen + 1 == now->maxlen) {
          build_last = clone;
        }
      }
    }
    if (distinct_substr != -1) {
      distinct_substr += now->maxlen - now->fail->maxlen;
    }
  }
  Vec<Node*>& topo_sort() {
    if (sorted) {
      return all;
    }
    sorted = true;
    Vec<i32> indeg(Size(all));
    Deque<Node*> dq;
    for (auto node : all) {
      if (node->fail != NULL) {
        indeg[node->fail->id]++;
      }
    }
    for (auto node : all) {
      if (indeg[node->id] == 0) {
        dq.push_back(node);
      }
    }
    all.clear();
    while (!dq.empty()) {
      auto head = dq.front();
      dq.pop_front();
      all.push_back(head);
      if (head->fail != NULL) {
        indeg[head->fail->id]--;
        if (indeg[head->fail->id] == 0) {
          dq.push_back(head->fail);
        }
      }
    }
    return all;
  }
  Vec<Right> calculate_right(const Indexer<T>& s, int n) {
    topo_sort();
    Vec<Right> res(n);
    Matcher matcher = this->matcher();
    for (int i = 0; i < n; i++) {
      matcher.match(s(i));
      i32 id = matcher.match_last->id;
      res[id].cnt++;
      res[id].leftest_right = Min(res[id].leftest_right, i);
      res[id].rightest_right = Max(res[id].rightest_right, i);
    }
    for (auto node : all) {
      if (node->fail != NULL) {
        i32 id = node->id;
        i32 fid = node->fail->id;
        res[fid].cnt += res[id].cnt;
        res[fid].leftest_right =
            Min(res[fid].leftest_right, res[id].leftest_right);
        res[fid].rightest_right =
            Max(res[fid].rightest_right, res[id].rightest_right);
      }
    }
    return res;
  }
};
}  // namespace seq
}  // namespace dalt

void SolveOne(int test_id, IStream &in, OStream &out) {
  LCT::Register(V3{0, 1, 1}, M3 {
    V3 {1, 0, 0},
    V3 {0, 1, 0},
    V3 {0, 0, 1},
  },
  [&](var &a, var &b) {return a + b;},
  [&](var &a, var &b) {return b * a;},
  [&](var &a, var &b) {return b * a;});
  int N;
  in >> N;

  seq::SuffixAutomaton<> sa(2e5);
  Vec<int> ids(2e5);
  var &nodes = sa.all;
  var &lcts = sa.lcts;
  var &pq = sa.heap;
  int plus = 0;
  for(int i = 0; i < N; i++) {
    Str s;
    in >> s;
    bool add = s[s.size() - 1] == '+';
    if(add) {
      plus++;
      s = s.substr(0, s.size() - 1);
    }
    Debug(s);
    sa.build_next();
    int index = 0;
    for(char c : s) {
      sa.build(c, i == 0 ? index : -1);
      index++;
    }

    ids.clear();
    var matcher = sa.matcher();
    for(var c : s) {
      matcher.match(c);
      ids.push_back(matcher.match_last->id);
    }
    Debug(ids);
    LCT::make_root(lcts[0]);
    for(int id : ids) {
      LCT::access(lcts[id]);
      LCT::splay(lcts[id]);
      lcts[id]->modify(M3 {
        V3 {1, add ? 1 : -1, 0},
        V3 {0, 0, 0},
        V3 {0, 0, 1},
      });
    }
    for (int id : ids) {
      //LCT::access(lcts[id]);
      LCT::splay(lcts[id]);
      lcts[id]->modify(M3{
          V3{1, 0, 0},
          V3{0, 0, 1},
          V3{0, 0, 1},
      });
    }
    Debug(i);
    DebugRun({
      Vec<V3> weights;
      for(int i = 0; i < Size(lcts); i++) {
        LCT::splay(lcts[i]);
        weights.push_back(lcts[i]->weight);
      }
      Debug(weights);
    });
    while(!pq.empty()) {
      var top = pq.top();
      var id = std::get<2>(top);
      if (nodes[id]->get_min_length() == std::get<0>(top) &&
          nodes[id]->smallest_right == std::get<1>(top) &&
          nodes[id]->smallest_right != -1) {
        LCT::splay(lcts[id]);
        if (lcts[id]->weight[0] == plus){ 
          break;
        }
      }
      pq.pop();
    }
    if(pq.empty()) {
      out << "-1 -1" << '\n';
    } else {
      var top = pq.top();
      var min_length = std::get<0>(top);
      var right = std::get<1>(top);
      int l = right - min_length + 1;
      out << l << ' ' << right << '\n';
    }
  }
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}
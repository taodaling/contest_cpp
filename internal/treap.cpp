#pragma once
#include "common.cpp"
#include "function.cpp"
#include "optional_field.cpp"
#include "sbt_common.cpp"
#include "sbt_reverse.cpp"
namespace dalt {
namespace sbt {
template <class SBT, i64 ID = 0, bool P = false, bool DIR = false>
struct Treap: public SbtReverse<SBT, DIR> {
 static_assert(is_sbt_registry_v<SBT>);
  using S = typename SBT::TypeS;
  using U = typename SBT::TypeU;
 private:
  using Self = Treap<SBT, ID, P, DIR>;
  using AT2 = Array<Self *, 2>;
  AT2 split_by_weight_first_true(const Checker<S> &checker, bool &find) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (checker(weight)) {
      res = left->split_by_weight_first_true(checker, find);
      if (!find) {
        res[1] = right;
        right = NIL;
        res->left = res[0];
        res[0] = this;
        find = true;
      } else {
        left = res[1];
        res[1] = this;
      }
    } else {
      res = right->split_by_weight_first_true(checker, find);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  IsBool(!P,void) do_perm() {}
  IsBool(P, void) do_perm() {
    left = left->clone();
    right = right->clone();
  }
  Treap(bool x) {}
  void travel(const U &u, const bool &rev_upd,
              const Consumer<S> &consumer) const {
    if (this == NIL) {
      return;
    }
    U new_upd = SBT::u_u(upd, u);
    bool new_rev_upd = rev_upd != rev;
    (new_rev_upd ? right : left)->travel(new_upd, new_rev_upd, consumer);
    consumer(SBT::s_u(weight, u));
    (new_rev_upd ? left : right)->travel(new_upd, new_rev_upd, consumer);
  }

 public:
  static Self *NIL;
  static void Register(S s_nil, U u_nil, const Adder<S, S> &_s_s,
                       const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    if (NIL != NULL) {
      delete NIL;
    }
    NIL = new Self(true);
    NIL->sum = s_nil;
    NIL->upd = u_nil;
    NIL->weight = s_nil;
    NIL->size = 0;
    NIL->id = -1;
    NIL->rev = false;
    NIL->left = NIL->right = NIL;

    SBT::Register(s_nil, u_nil, _s_s, _s_u,
                                                 _u_u);
  }
  Treap(i64 _id = 0, S _sum = S())
      : sum(_sum),
        weight(_sum),
        id(_id),
        size(1),
        upd(NIL->upd),
        left(NIL),
        right(NIL),
        rev(false) {
    this->init_sum_rev(SBT::s_nil);
  }
  S sum;
  U upd;
  S weight;
  int size;
  i64 id;
  Self *left;
  Self *right;
  bool rev;
  void reverse() {
    rev = !rev;
    this->swap_sum_rev(sum);
  }
  Self *find_by_rank(int rank) {
    push_down();
    if(left->size >= rank) {
      return left->find_by_rank(rank);
    }
    if(left->size + 1 == rank) {
      return this;
    }
    return right->find_by_rank(rank - (left->size + 1));
  }
  Self *clone() {
    if (this == NIL) {
      return this;
    }
    return new Self(*this);
  }
  void push_up() {
    if (this == NIL) {
      return;
    }
    sum = SBT::s_s(SBT::s_s(left->sum, weight), right->sum);
    this->push_up_sum_rev(*left, *right);
    size = left->size + 1 + right->size;
  }
  void modify(const U &u) {
    if (this == NIL) {
      return;
    }
    sum = SBT::s_u(sum, u);
    upd = SBT::u_u(upd, u);
    weight = SBT::s_u(weight, u);
    this->apply_sum_rev(u);
  }

  void push_down() {
    if (this == NIL) {
      return;
    }
    do_perm();
    if (rev) {
      Swap(left, right);
      left->reverse();
      right->reverse();
      rev = false;
    }
    if (upd != NIL->upd) {
      left->modify(upd);
      right->modify(upd);
      upd = NIL->upd;
    }
  }
  AT2 split_by_rank(int k) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (left->size >= k) {
      res = left->split_by_rank(k);
      left = res[1];
      res[1] = this;
    } else {
      res = right->split_by_rank(k - 1 - left->size);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  AT2 split_by_id(i64 k) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (id > k) {
      res = left->split_by_id(k);
      left = res[1];
      res[1] = this;
    } else {
      //id <= k
      res = right->split_by_id(k);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  AT2 split_by_weight(S k){
    return split_by_weight_last_true([&](var &s) {
      return s <= k;
    });
  } 
  AT2 split_by_weight_first_true(const Checker<S> &checker) {
    bool find = false;
    return split_by_weight_first_true(checker, find);
  }
  AT2 split_by_weight_last_true(const Checker<S> &checker) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (!checker(weight)) {
      res = left->split_by_weight_last_true(checker);
      left = res[1];
      res[1] = this;
    } else {
      res = right->split_by_weight_last_true(checker);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  AT2 split_by_sum_first_true(const Checker<S> &checker, S &s) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    S s_1 = SBT::s_s(s, left->sum);
    if (checker(s_1)) {
      res = left->split_by_sum_first_true(checker, s);
      left = res[1];
      res[1] = this;
    } else {
      s = s_1;
      S s_2 = SBT::s_s(s, weight);
      if (checker(s_2)) {
        res[0] = this;
        res[1] = right;
        right = NIL;
      } else {
        s = s_2;
        res = right->split_by_sum_first_true(checker, s);
        right = res[0];
        res[0] = this;
      }
    }
    push_up();
    return res;
  }
  AT2 split_by_sum_last_true(const Checker<S> &checker, S &s) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    S s_1 = SBT::s_s(SBT::s_s(s, left->sum), weight);
    if (checker(s_1)) {
      s = s_1;
      res = right->split_by_sum_last_true(checker, s);
      right = res[0];
      res[0] = this;
    } else {
      res = left->split_by_sum_last_true(checker, s);
      left = res[1];
      res[1] = this;
    }
    push_up();
    return res;
  }
  static Self *MakeTree(int n, const_ref(Indexer<Self*>) indexer) {
    var dfs = [&](var &dfs, int l, int r) {
      if (l > r) {
        return NIL;
      }
      int mid = (l + r) / 2;
      var node = indexer(mid);
      node->left = dfs(dfs, l, mid - 1);
      node->right = dfs(dfs, mid + 1, r);
      node->push_up();
      return node;
    };
    return dfs(dfs, 0, n - 1);
  }
  static Self *merge(AT2 ab) { return merge(ab[0], ab[1]); }
  static Self *merge(Self *a, Self *b) {
    if (a == NIL) {
      return b;
    }
    if (b == NIL) {
      return a;
    }
    if (random_choice(1, a->size + b->size) <= a->size) {
      a->push_down();
      a->right = merge(a->right, b);
      a->push_up();
      return a;
    } else {
      b->push_down();
      b->left = merge(a, b->left);
      b->push_up();
      return b;
    }
  }


  void travel(const Consumer<S> &consumer) const {
    bool rev_upd = false;
    travel(NIL->upd, rev_upd, consumer);
  }

  Vec<S> to_vec() const {
    Vec<S> res;
    travel(NIL->upd, false, [&](auto x) { res.push_back(x); });
    return res;
  }
};
template <class SBT, i64 ID, bool P, bool DIR>
Treap<SBT, ID, P, DIR> *Treap<SBT, ID, P, DIR>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
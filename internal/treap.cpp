#pragma once
#include "../common.cpp"
#include "function.cpp"
#include "tag.cpp"
namespace dalt {
namespace treap {
#define TEMPLATE_ARG_LIST                                                      \
  template <class S, class U, int ID = 0, class P = TransientTag,              \
            class DIR = BidTag>
TEMPLATE_ARG_LIST struct Treap {
  static_assert(is_same_v<P, TransientTag> || is_same_v<P, PermTag>);
  static_assert(is_same_v<DIR, BidTag> || is_same_v<DIR, DiTag>);

private:
  using Self = Treap<S, U, ID, P, DIR>;
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
        right = NULL;
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
  IsType(TransientTag, P, void) do_perm() {}
  IsType(PermTag, P, void) do_perm() {
    left = left->clone();
    right = right->clone();
  }
  Treap(bool x) {}
  void travel(const U &u, const bool &rev_upd,
              const Consumer<S> &consumer) const {
    if (this == NIL) {
      return;
    }
    U new_upd = u_u(upd, u);
    bool new_rev_upd = rev_upd != rev;
    (new_rev_upd ? right : left)->travel(new_upd, new_rev_upd, consumer);
    consumer(s_u(weight, u));
    (new_rev_upd ? left : right)->travel(new_upd, new_rev_upd, consumer);
  }

public:
  static Adder<S, S> s_s;
  static Adder<S, U> s_u;
  static Adder<U, U> u_u;
  static Self *NIL;
  static void cinit(S s_nil, U u_nil, const Adder<S, S> &_s_s,
                    const Adder<U, U> &_u_u, const Adder<S, U> &_s_u) {
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
    s_s = _s_s;
    u_u = _u_u;
    s_u = _s_u;
  }
  Treap(int _id = 0, S _sum = S())
      : sum(_sum), weight(_sum), id(_id), size(1), upd(NIL->upd), left(NIL),
        right(NIL), rev(false) {}
  S sum;
  U upd;
  S weight;
  int size;
  int id;
  Self *left;
  Self *right;
  bool rev;
  IsType(DiTag, DIR, void) reverse() {
    rev = !rev;
    sum.reverse();
  }

  IsType(BidTag, DIR, void) reverse() { rev = !rev; }
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
    sum = s_s(s_s(left->sum, weight), right->sum);
    size = left->size + 1 + right->size;
  }
  void modify(const U &u) {
    if (this == NIL) {
      return;
    }
    sum = s_u(sum, u);
    upd = u_u(upd, u);
    weight = s_u(weight, u);
  }

  void push_down() {
    if (this == NIL) {
      return;
    }
    do_perm();
    if (rev) {
      swap(left, right);
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
    S s_1 = s_s(s, left->sum);
    if (checker(s_1)) {
      res = left->split_by_weight_first_true(checker, s);
      left = res[1];
      res[1] = this;
    } else {
      s = s_1;
      S s_2 = s_s(s, weight);
      if (checker(s_2)) {
        res[1] = right;
        right = NULL;
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
    S s_1 = s_s(s_s(s, left->sum), weight);
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
template <class S, class U, int ID, class P, class DIR>
Adder<S, S> Treap<S, U, ID, P, DIR>::s_s;
template <class S, class U, int ID, class P, class DIR>
Adder<U, U> Treap<S, U, ID, P, DIR>::u_u;
template <class S, class U, int ID, class P, class DIR>
Adder<S, U> Treap<S, U, ID, P, DIR>::s_u;
template <class S, class U, int ID, class P, class DIR>
Treap<S, U, ID, P, DIR> *Treap<S, U, ID, P, DIR>::NIL = NULL;
} // namespace treap
using treap::Treap;
} // namespace dalt
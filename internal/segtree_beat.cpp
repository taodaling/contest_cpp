#pragma once
#include "common.cpp"
#include "segtree_common.cpp"

namespace dalt {
namespace sbt {
// verify by: https://cses.fi/problemset/task/2416
template <class T>
struct SegTreeBeat {
  using Self = SegTreeBeat<T>;
  static_assert(is_arithmetic_v<T>);
  struct Node {
    using Self = Node;
    const static T INF = std::numeric_limits<T>::max() / 2;
    Node *left;
    Node *right;
    T first;
    T second;
    int first_cnt;
    T sum;

    Node(i32 l, i32 r, const Indexer<T> &indexer) {
      left = right = NULL;
      if (l < r) {
        int m = (l + r) / 2;
        left = new Self(l, m, indexer);
        right = new Self(m + 1, r, indexer);
        push_up();
      } else {
        sum = first = indexer(l);
        second = -INF;
        first_cnt = 1;
      }
    }

    void push_up() {
      first = Max(left->first, right->first);
      second = Max(left->first == first ? left->second : left->first,
                   right->first == first ? right->second : right->first);
      first_cnt = (left->first == first ? left->first_cnt : 0) +
                  (right->first == first ? right->first_cnt : 0);
      sum = left->sum + right->sum;
    }

    void push_down() {
      left->set_min(first);
      right->set_min(first);
    }

    void set_min(const T &x) {
      if (first <= x) {
        return;
      }
      sum -= (first - x) * first_cnt;
      first = x;
    }

    void update_min(int L, int R, int l, int r, const T &x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        if (first <= x) {
          return;
        }
        if (second < x) {
          set_min(x);
          return;
        }
      }
      push_down();
      int m = (l + r) / 2;
      left->update_min(L, R, l, m, x);
      right->update_min(L, R, m + 1, r, x);
      push_up();
    }

    T query_sum(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return 0;
      }
      if (SegmentCover(L, R, l, r)) {
        return sum;
      }
      push_down();
      int m = (l + r) / 2;
      return left->query_sum(L, R, l, m) + right->query_sum(L, R, m + 1, r);
    }

    T query_max(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return -INF;
      }
      if (SegmentCover(L, R, l, r)) {
        return first;
      }
      push_down();
      int m = (l + r) / 2;
      return Max(left->query_max(L, R, l, m), right->query_max(L, R, m + 1, r));
    }

    void travel(const Consumer<T> &consumer, T min_val) const {
      min_val = Min(min_val, first);
      if (left == NULL) {
        consumer(min_val);
        return;
      }
      left->travel(consumer, min_val);
      right->travel(consumer, min_val);
    }

    ~Node() {
      delete left;
      delete right;
    }
  };

 private:
  Node *tree;
  int n;

 public:
  SegTreeBeat(int _n, const Indexer<T> &indexer) : n(_n) {
    tree = new Node(0, n - 1, indexer);
  }

  inline void update_min(int L, int R, const T &min_val) {
    tree->update_min(L, R, 0, n - 1, min_val);
  }
  inline T query_max(int L, int R) { return tree->query_max(L, R, 0, n - 1); }
  inline T query_sum(int L, int R) { return tree->query_sum(L, R, 0, n - 1); }
  void travel(const Consumer<T> &consumer) const {
    tree->travel(consumer, Node::INF);
  }
  Vec<T> to_vec() const {
    Vec<T> res;
    res.reserve(n);
    travel([&](auto x) { res.push_back(x); });
    return res;
  }
#ifdef DROP
  ~SegTreeBeat() { delete tree; }
#endif
};
} 
}  // namespace dalt
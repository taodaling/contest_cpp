// verify by: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
#pragma once
#include "common.cpp"
#include "segtree_common.cpp"

namespace dalt {
namespace sbt {

#define ASSERTION_STUB                     \
  Assert(first_largest >= second_largest); \
  Assert(first_smallest <= second_smallest);

template <class T>
struct SegTreeBeatExt {
  static_assert(is_arithmetic_v<T>);

 private:
  struct Node {
    static const T INF = std::numeric_limits<T>::max() / 2;
    using Self = Node;
    Self *left;
    Self *right;
    T first_largest;
    T second_largest;
    int first_largest_cnt;
    T first_smallest;
    T second_smallest;
    int first_smallest_cnt;
    T dirty;
    int size;
    T sum;

    void set_min(T x) {
      if (first_largest <= x) {
        return;
      }
      sum -= (first_largest - x) * first_largest_cnt;
      first_largest = x;

      if (first_smallest >= x) {
        first_smallest = x;
      }
      second_smallest = Min(second_smallest, x);
      if (second_smallest == first_smallest) {
        second_smallest = INF;
      }

      ASSERTION_STUB
    }

    void set_max(T x) {
      if (first_smallest >= x) {
        return;
      }
      sum += (x - first_smallest) * first_smallest_cnt;
      first_smallest = x;

      if (first_largest <= x) {
        first_largest = x;
      }
      second_largest = Max(second_largest, x);
      if (second_largest == first_largest) {
        second_largest = -INF;
      }

      ASSERTION_STUB
    }

    void modify(T x) {
      dirty += x;
      sum += x * size;
      first_smallest += x;
      first_largest += x;
      second_smallest += x;
      second_largest += x;
      ASSERTION_STUB
    }

    void push_up() {
      first_largest = Max(left->first_largest, right->first_largest);
      second_largest =
          Max(left->first_largest == first_largest ? left->second_largest
                                                   : left->first_largest,
              right->first_largest == first_largest ? right->second_largest
                                                    : right->first_largest);
      first_largest_cnt =
          (left->first_largest == first_largest ? left->first_largest_cnt : 0) +
          (right->first_largest == first_largest ? right->first_largest_cnt
                                                 : 0);

      first_smallest = Min(left->first_smallest, right->first_smallest);
      second_smallest =
          Min(left->first_smallest == first_smallest ? left->second_smallest
                                                     : left->first_smallest,
              right->first_smallest == first_smallest ? right->second_smallest
                                                      : right->first_smallest);
      first_smallest_cnt =
          (left->first_smallest == first_smallest ? left->first_smallest_cnt
                                                  : 0) +
          (right->first_smallest == first_smallest ? right->first_smallest_cnt
                                                   : 0);

      sum = left->sum + right->sum;
      size = left->size + right->size;

      ASSERTION_STUB
    }

    void push_down() {
      if (dirty != 0) {
        left->modify(dirty);
        right->modify(dirty);
        dirty = 0;
      }
      left->set_min(first_largest);
      right->set_min(first_largest);
      left->set_max(first_smallest);
      right->set_max(first_smallest);
    }

    Node(int l, int r, const Indexer<T> &indexer) : left(NULL), right(NULL) {
      if (l < r) {
        int m = (l + r) / 2;
        left = new Self(l, m, indexer);
        right = new Self(m + 1, r, indexer);
        push_up();
      } else {
        sum = first_smallest = first_largest = indexer(l);
        first_smallest_cnt = first_largest_cnt = 1;
        second_smallest = INF;
        second_largest = -INF;
        size = 1;
        ASSERTION_STUB
      }
    }

    void update_min(int L, int R, int l, int r, T x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        if (first_largest <= x) {
          return;
        }
        if (second_largest < x) {
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

    void update_max(int L, int R, int l, int r, T x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        if (first_smallest >= x) {
          return;
        }
        if (second_smallest > x) {
          set_max(x);
          return;
        }
      }
      push_down();
      int m = (l + r) / 2;
      left->update_max(L, R, l, m, x);
      right->update_max(L, R, m + 1, r, x);
      push_up();
    }

    void update(int L, int R, int l, int r, T x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        modify(x);
        return;
      }
      push_down();
      int m = (l + r) / 2;
      left->update(L, R, l, m, x);
      right->update(L, R, m + 1, r, x);
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
        return first_largest;
      }
      push_down();
      int m = (l + r) / 2;
      return Max(left->query_max(L, R, l, m), right->query_max(L, R, m + 1, r));
    }

    T query_min(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return -INF;
      }
      if (SegmentCover(L, R, l, r)) {
        return first_smallest;
      }
      push_down();
      int m = (l + r) / 2;
      return Max(left->query_min(L, R, l, m), right->query_min(L, R, m + 1, r));
    }

    void travel(T max_val, T min_val, T mod, Consumer<T> &consumer) const {
      if (left == NULL) {
        T ans = sum + mod;
        ans = Min(ans, max_val);
        ans = Max(ans, min_val);
        consumer(ans);
        return;
      }
      T new_mod = dirty + mod;
      T new_max_val = Min(max_val, first_largest + mod);
      T new_min_val = Max(min_val, first_smallest + mod);
      left->travel(new_max_val, new_min_val, new_mod, consumer);
      right->travel(new_max_val, new_min_val, new_mod, consumer);
    }
#ifdef DROP
    ~Node() {
      delete left;
      delete right;
    }
#endif
  };
  Node *tree;
  int n;

 public:
  using Self = SegTreeBeatExt<T>;
  SegTreeBeatExt(int _n, const Indexer<T> &indexer) : n(_n) {
    tree = new Node(0, n - 1, indexer);
  }
  inline void update_min(int L, int R, T x) {
    tree->update_min(L, R, 0, n - 1, x);
  }
  inline void update_max(int L, int R, T x) {
    tree->update_max(L, R, 0, n - 1, x);
  }
  inline void update(int L, int R, T x) { tree->update(L, R, 0, n - 1, x); }
  inline T query_sum(int L, int R) { return tree->query_sum(L, R, 0, n - 1); }
  inline T query_max(int L, int R) { return tree->query_max(L, R, 0, n - 1); }
  inline T query_min(int L, int R) { return tree->query_min(L, R, 0, n - 1); }
  void travel(Consumer<T> &consumer) const {
    tree->travel(Node::INF, -Node::INF, 0, consumer);
  }
  Vec<T> to_vec() const {
    Vec<T> res;
    res.reserve(n);
    Consumer<T> consumer = [&](auto x) { res.push_back(x); };
    travel(consumer);
    return res;
  }
#ifdef DROP
  ~SegTreeBeatExt() { delete tree; }
#endif
};
#undef ASSERTION_STUB
}  // namespace sbt
}  // namespace dalt
#pragma once
#include "common.cpp"
#include "function.cpp"
#include "sparse_table.cpp"

namespace dalt {
const i32 SHIFT = 5;
const i32 BLOCK_SIZE = 1 << SHIFT;
const i32 AND_MASK = BLOCK_SIZE - 1;

struct StaticRMQ {
 private:
  Vec<i32> to_left;
  Comparator<i32> comparator;
  SparseTable<i32> st;
  int n;
  i32 minor_one(i32 a, i32 b) const { return !comparator(b, a) ? a : b; }

 public:
  using Self = StaticRMQ;
  int size() const { return n; }
  StaticRMQ() : n(0) {}
  StaticRMQ(int n, Comparator<i32> arg_comparator)
      : comparator(Move(arg_comparator)) {
    this->n = n;
    int consider_part = ((n - 1) >> SHIFT) + 1;
    Vec<i32> min_indices = Vec<i32>(consider_part, -1);
    to_left = Vec<i32>(n);
    for (int i = 0; i < n; i++) {
      int to = i >> SHIFT;
      if (min_indices[to] == -1 || comparator(i, min_indices[to])) {
        min_indices[to] = i;
      }
    }
    st = SparseTable<i32>(consider_part, MakeIndexer<i32>(min_indices),
                          [&](int a, int b) { return minor_one(a, b); });
    int mask = 0;
    for (int i = 0; i < n; i++) {
      if ((i & AND_MASK) == 0) {
        mask = 0;
      }
      int b = i >> SHIFT;
      while (mask != 0) {
        int head = HighestOneBitOffset(mask);
        if (!comparator((b << SHIFT) | head, i)) {
          mask = ClearBit(mask, head);
        } else {
          break;
        }
      }
      mask = SetBit(mask, i & AND_MASK);
      to_left[i] = mask;
    }
  }

  // return -1 if l > r
  i32 query_with_check(int l, int r) const {
    l = Max(l, 0);
    r = Min(n - 1, r);
    if (l > r) {
      return -1;
    }
    return query(l, r);
  }

  // get the index of minimum element in range [l, r]
  i32 query(int l, int r) const {
    Assert(n > 0);
    Assert(l <= r);
    int bl = l >> SHIFT;
    int br = r >> SHIFT;
    int tl = l & AND_MASK;
    //        int tr = r & AND_MASK;
    if (bl == br) {
      return TrailingZeroNumber(to_left[r] & HighestKOnes32(32 - tl)) |
             (bl << SHIFT);
    }
    int res1 = TrailingZeroNumber(to_left[(bl << SHIFT) | AND_MASK] &
                                  HighestKOnes32(32 - tl)) |
               (bl << SHIFT);
    int res2 = TrailingZeroNumber(to_left[r]) | (br << SHIFT);
    int best = minor_one(res1, res2);
    if (bl + 1 < br) {
      best = minor_one(best, st.query(bl + 1, br - 1));
    }
    return best;
  }
};
}  // namespace dalt
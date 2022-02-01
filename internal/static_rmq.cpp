#pragma once
#include "../common.cpp"
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
  SparseTable<i32> *st;

  i32 minor(i32 a, i32 b) { return comparator(a, b) <= 0 ? a : b; }

public:
  using Self = StaticRMQ;
  StaticRMQ(int n, Comparator<i32> arg_comparator)
      : comparator(arg_comparator) {
    int consider_part = ((n - 1) >> SHIFT) + 1;
    Vec<i32> min_indices = Vec<i32>(consider_part, -1);
    to_left = Vec<i32>(n);
    for (int i = 0; i < n; i++) {
      int to = i >> SHIFT;
      if (min_indices[to] == -1 || comparator(i, min_indices[to])) {
        min_indices[to] = i;
      }
    }
    st = new SparseTable<i32>(consider_part, MakeIndexer(min_indices),
                              comparator);
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

  i32 query(int l, int r) {
    assert(l <= r);
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
    int best = minor(res1, res2);
    if (bl + 1 < br) {
      best = minor(best, st->query(bl + 1, br - 1));
    }
    return best;
  }

#ifdef DROP
  ~StaticRMQ() { delete st; }
#endif
};
} // namespace dalt
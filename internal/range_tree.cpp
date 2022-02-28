#pragma once
#include "common.cpp"
#include "binary.cpp"
namespace dalt {
// like treeset
// - time: O(\log_64 n)
// - memory: O(n/8)
struct RangeTree {
private:
  Vec<Vec<u64>> data;
  static const int BIT_SHIFT = 6;
  static const int BIT_SHIFT_VALUE = 1 << BIT_SHIFT;
  static const int BIT_SHIFT_VALUE_MASK = BIT_SHIFT_VALUE - 1;
  int size;
  int n;

  int calc_level(int n) {
    int level = 0;
    while (n > 64) {
      level++;
      n = (n + 63) / 64;
    }
    level++;
    return level;
  }

  bool check(int i) const { return i >= 0 && i < n; }

  int last_set(int i, int x) const {
    Assert(i < 0 || data[i][x] != 0);
    for (; i >= 0; i--) {
      int offset = HighestOneBitOffset(data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }

  int first_set(int i, int x) const {
    Assert(i < 0 || data[i][x] != 0);
    for (; i >= 0; i--) {
      int offset = LowestOneBitOffset(data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }

  int last_clear(int i, int x) const {
    Assert(i < 0 || data[i][x] != -1);
    for (; i >= 0; i--) {
      int offset = HighestOneBitOffset(~data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }

  int first_clear(int i, int x) const {
    Assert(i < 0 || data[i][x] != -1);
    for (; i >= 0; i--) {
      int offset = LowestOneBitOffset(~data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }

public:
  RangeTree(int _n) : n(_n), size(0) {
    int level = calc_level(n);
    data.resize(level);
    for (int i = 0, m = (n + 63) / 64; i < level; i++, m = (m + 63) / 64) {
      data[i] = Vec<u64>(m);
    }
  }

  bool contains(int x) const {
    return ((data[0][x >> BIT_SHIFT] >> (x & BIT_SHIFT_VALUE_MASK)) & 1) == 1;
  }

  int get_size() const { return size; }

  void add(int x) {
    if (contains(x)) {
      return;
    }
    size++;
    for (int i = 0; i < Size(data); i++) {
      int offset = x & BIT_SHIFT_VALUE_MASK;
      x >>= BIT_SHIFT;
      data[i][x] = SetBit(data[i][x], offset);
    }
  }

  void remove(int x) {
    if (!contains(x)) {
      return;
    }
    size--;
    u64 last_value = 0;
    for (int i = 0; i < Size(data) && last_value == 0; i++) {
      int offset = x & BIT_SHIFT_VALUE_MASK;
      x >>= BIT_SHIFT;
      last_value = data[i][x] = ClearBit(data[i][x], offset);
    }
  }

  int floor(int x) const {
    if (x < 0) {
      return -1;
    }
    if (contains(x)) {
      return x;
    }
    for (int i = 0, y = x; i < Size(data); i++) {
      int offset = y & BIT_SHIFT_VALUE_MASK;
      y = y >> BIT_SHIFT;
      u64 head_mask = LowestKOnes64(offset);
      if ((data[i][y] & head_mask) != 0) {
        return last_set(i - 1, (y << BIT_SHIFT) |
                                   HighestOneBitOffset(data[i][y] & head_mask));
      }
    }
    return -1;
  }

  int ceil(int x) const {
    if (x >= n) {
      return -1;
    }
    if (contains(x)) {
      return x;
    }
    for (int i = 0, y = x; i < Size(data); i++) {
      int offset = y & BIT_SHIFT_VALUE_MASK;
      y = y >> BIT_SHIFT;
      u64 tail_mask = HighestKOnes64(63 - offset);
      if ((data[i][y] & tail_mask) != 0) {
        return first_set(i - 1, (y << BIT_SHIFT) |
                                    LowestOneBitOffset(data[i][y] & tail_mask));
      }
    }
    return -1;
  }

  int first() const {
    if (size == 0) {
      return -1;
    }
    return first_set(Size(data) - 1, 0);
  }

  int last() const {
    if (size == 0) {
      return -1;
    }
    return last_set(Size(data) - 1, 0);
  }

  Vec<i32> to_vec() const {
    Vec<i32> ans;
    ans.reserve(size);
    for (int i = first(); i != -1; i = ceil(i + 1)) {
      ans.push_back(i);
    }
    return ans;
  }

  void clear() {
    size = 0;
    for (int i = 0; i < Size(data); i++) {
      Fill(All(data[i]), 0);
    }
  }
};
} // namespace dalt
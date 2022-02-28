#include "common.cpp"
#include "binary.cpp"
namespace dalt {
struct BitSet {
private:
  Vec<u64> data;
  u64 tail_available;
  int capacity;
  int m;

  static const int SHIFT = 6;
  static const int LOW = 63;
  static const int BITS_FOR_EACH = 64;
  static const u64 ALL_ONE = ~u64(0);
  static const u64 ALL_ZERO = u64(0);
  static const int MAX_OFFSET = 63;
  static const int MIN_OFFSET = 0;

  static int word(int i) { return i >> SHIFT; }

  static int offset(int i) { return i & LOW; }

public:
  BitSet(int n) {
    capacity = n;
    this->m = (capacity + 64 - 1) / 64;
    data.resize(m);
    tail_available = IntervalOnes64(0, offset(capacity - 1));
  }

  BitSet interval(int l, int r) {
    if (r < l) {
      return BitSet(0);
    }
    return BitSet(*this, l, r);
  }

  BitSet(const BitSet &bs, int l, int r) { copyInterval(bs, l, r); }

  void copyInterval(const BitSet &bs, int l, int r) {
    capacity = r - l + 1;
    tail_available = IntervalOnes64(0, offset(capacity - 1));
    int req_length = word(r) - word(l) + 1;
    auto offset = bs.data.begin() + l;
    data = Vec<u64>(offset, offset + req_length);
    this->m = req_length;
    left_shift(this->offset(l));
    this->m = (capacity + 64 - 1) / 64;
    data[m - 1] &= tail_available;
    for (int i = m; i < req_length; i++) {
      data[i] = 0;
    }
  }

  int get(int i) const { return data[word(i)] & (u64(1) << offset(i)); }

  void set(int i) { data[word(i)] |= (u64(1) << offset(i)); }

  void set(int i, int val) {
    if (val) {
      set(i);
    } else {
      clear(i);
    }
  }

  void fill(bool val) {
    if (val) {
      set_range(0, get_capacity() - 1);
    } else {
      clear_range(0, get_capacity() - 1);
    }
  }

  void set_range(int l, int r) {
    if (r < l) {
      return;
    }
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      data[i] = ALL_ONE;
    }
    // lword
    if (left_word == right_word) {
      data[left_word] |= IntervalOnes64(offset(l), offset(r));
    } else {
      data[left_word] |= IntervalOnes64(offset(l), MAX_OFFSET);
      data[right_word] |= IntervalOnes64(0, offset(r));
    }
  }

  void clear(int i) { data[word(i)] &= ~(u64(1) << offset(i)); }

  void inverse(int i) { data[word(i)] ^= (u64(1) << offset(i)); }

  void clear_range(int l, int r) {
    if (r < l) {
      return;
    }
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      data[i] = ALL_ZERO;
    }
    // lword
    if (left_word == right_word) {
      data[left_word] &= ~IntervalOnes64(offset(l), offset(r));
    } else {
      data[left_word] &= ~IntervalOnes64(offset(l), MAX_OFFSET);
      data[right_word] &= ~IntervalOnes64(0, offset(r));
    }
  }

  void flip(int i) { data[word(i)] ^= (u64(1) << offset(i)); }

  void flip(int l, int r) {
    if (r < l) {
      return;
    }
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      data[i] ^= ALL_ONE;
    }
    // lword
    if (left_word == right_word) {
      data[left_word] ^= IntervalOnes64(offset(l), offset(r));
    } else {
      data[left_word] ^= IntervalOnes64(offset(l), MAX_OFFSET);
      data[right_word] ^= IntervalOnes64(0, offset(r));
    }
  }

  int get_capacity() const { return capacity; }

  bool empty() const { return next_set_bit(0) >= get_capacity(); }

  int size() const {
    int ans = 0;
    for (u64 x : data) {
      ans += CountBit(x);
    }
    return ans;
  }

  int size(int l, int r) const {
    if (r < l) {
      return 0;
    }
    int ans = 0;
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      ans += CountBit(data[i]);
    }
    // lword
    if (left_word == right_word) {
      ans += CountBit(data[left_word] & IntervalOnes64(offset(l), offset(r)));
    } else {
      ans += CountBit(data[left_word] & IntervalOnes64(offset(l), MAX_OFFSET));
      ans += CountBit(data[right_word] & IntervalOnes64(0, offset(r)));
    }
    return ans;
  }

  void copy(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    data = bs.data;
  }

  void or_op(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    for (int i = 0; i < n; i++) {
      data[i] |= bs.data[i];
    }
  }

  void and_op(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    for (int i = 0; i < n; i++) {
      data[i] &= bs.data[i];
    }
  }

  void xor_op(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    for (int i = 0; i < n; i++) {
      data[i] ^= bs.data[i];
    }
  }

  int next_set_bit(int start) const {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != 0) {
      u64 mask = IntervalOnes64(offset, MAX_OFFSET);
      if ((data[w] & mask) != 0) {
        return TrailingZeroNumber(data[w] & mask) + w * BITS_FOR_EACH;
      }
      w++;
    }

    while (w < m && data[w] == ALL_ZERO) {
      w++;
    }
    if (w >= m) {
      return get_capacity();
    }
    return TrailingZeroNumber(data[w]) + w * BITS_FOR_EACH;
  }

  int previous_set_bit(int start) const {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != MAX_OFFSET) {
      u64 mask = IntervalOnes64(0, offset);
      if ((data[w] & mask) != 0) {
        return MAX_OFFSET - LeadingZeroNumber(data[w] & mask) +
               w * BITS_FOR_EACH;
      }
      w--;
    }

    while (w >= 0 && data[w] == ALL_ZERO) {
      w--;
    }
    if (w < 0) {
      return -1;
    }
    return MAX_OFFSET - LeadingZeroNumber(data[w]) + w * BITS_FOR_EACH;
  }

  int next_clear_bit(int start) {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != 0) {
      u64 mask = IntervalOnes64(offset, MAX_OFFSET);
      if ((~data[w] & mask) != 0) {
        return TrailingZeroNumber(~data[w] & mask) + w * BITS_FOR_EACH;
      }
      w++;
    }

    while (w < m && data[w] == ALL_ONE) {
      w++;
    }
    if (w >= m) {
      return get_capacity();
    }
    return TrailingZeroNumber(~data[w]) + w * BITS_FOR_EACH;
  }

  int prev_clear_bit(int start) {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != MAX_OFFSET) {
      u64 mask = IntervalOnes64(0, offset);
      if ((~data[w] & mask) != 0) {
        return MAX_OFFSET - LeadingZeroNumber(~data[w] & mask) +
               w * BITS_FOR_EACH;
      }
      w--;
    }

    while (w >= 0 && data[w] == ALL_ONE) {
      w--;
    }
    if (w < 0) {
      return -1;
    }
    return MAX_OFFSET - LeadingZeroNumber(~data[w]) + w * BITS_FOR_EACH;
  }

  void left_shift(int n) {
    int word_move = word(n);
    int offset_move = offset(n);
    int rshift = MAX_OFFSET - (offset_move - 1);

    if (offset_move != 0) {
      // slightly
      for (int i = 0; i < m; i++) {
        if (i > 0) {
          data[i - 1] |= data[i] << rshift;
        }
        data[i] >>= offset_move;
      }
    }
    if (word_move > 0) {
      for (int i = 0; i < m; i++) {
        if (i >= word_move) {
          data[i - word_move] = data[i];
        }
        data[i] = 0;
      }
    }
  }

  void right_shift(int n) {
    int word_move = word(n);
    int offset_move = offset(n);
    int lShift = MAX_OFFSET + 1 - offset_move;

    if (offset_move != 0) {
      // slightly
      for (int i = m - 1; i >= 0; i--) {
        if (i + 1 < m) {
          data[i + 1] |= data[i] >> lShift;
        }
        data[i] <<= offset_move;
      }
    }
    if (word_move > 0) {
      for (int i = m - 1; i >= 0; i--) {
        if (i + word_move < m) {
          data[i + word_move] = data[i];
        }
        data[i] = 0;
      }
    }

    data[m - 1] &= tail_available;
  }

  Vec<i32> to_vec() const {
    Vec<i32> ans;
    for (int i = 0; i < capacity; i++) {
      if (get(i)) {
        ans.push_back(i);
      }
    }
    return ans;
  }
  BitSet clone() const { return *this; }
  int operator[](int i) { return get(i); }
  friend bool operator==(const_ref(BitSet) a, const_ref(BitSet) b);
  friend bool operator<(const_ref(BitSet) a, const_ref(BitSet) b);
  BitSet &operator|=(const_ref(BitSet) b) {
    or_op(b);
    return *this;
  }
  BitSet &operator&=(const_ref(BitSet) b) {
    and_op(b);
    return *this;
  }
  BitSet &operator^=(const_ref(BitSet) b) {
    xor_op(b);
    return *this;
  }
  BitSet &operator>>=(int k) {
    right_shift(k);
    return *this;
  }
  BitSet &operator<<=(int k) {
    left_shift(k);
    return *this;
  }
  BitSet operator>>(int k) { return clone() >>= k; }
  BitSet operator<<(int k) { return clone() <<= k; }
  void swap(BitSet &b) {
    data.swap(b.data);
    Swap(tail_available, b.tail_available);
    Swap(capacity, b.capacity);
    Swap(m, b.m);
  }
};

inline bool operator==(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.capacity == b.capacity &&
         memcmp((void *)a.data.data(), (void *)b.data.data(), a.capacity) == 0;
}
inline bool operator!=(const_ref(BitSet) a, const_ref(BitSet) b) {
  return !(a == b);
}
inline bool operator<(const_ref(BitSet) a, const_ref(BitSet) b) {
  Assert(a.capacity == b.capacity);
  return memcpy((void *)a.data.data(), (void *)b.data.data(), a.capacity) < 0;
}
inline BitSet operator|(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.clone() |= b;
}
inline BitSet operator&(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.clone() &= b;
}
BitSet operator^(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.clone() ^= b;
}
} // namespace dalt
#pragma once
#include "binary.cpp"
#include "common.cpp"
#include "optional.cpp"
namespace dalt {
namespace math {
template <int B>
struct LinearBasis {
  using Type = std::bitset<B>;
  Type map[B];
  int expires[B];
  Type source[B];
  Type set;

  int size() const { return set.count(); }
  const Type& get_set() const { return set; }
  Optional<Type> representation(Type x) const {
    Type ans;
    for (int i = B - 1; i >= 0; i--) {
      if (!x[i] || !set[i]) {
        continue;
      }
      x ^= map[i];
      ans.flip(i);
    }
    if (x == Type()) {
      return ans;
    }
    return {};
  }
  Optional<Type> representation_original(Type x) const {
    Type ans;
    for (int i = B - 1; i >= 0; i--) {
      if (!x[i] || !set[i]) {
        continue;
      }
      x ^= map[i];
      ans ^= source[i];
    }
    if (x == Type()) {
      return ans;
    }
    return {};
  }
  int get_expiry(int i) const { return expires[i]; }
  int min_expiry(Type x) const {
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < B; i++) {
      if (x[i]) {
        ans = Min(ans, expires[i]);
      }
    }
    return ans;
  }
  int max_expiry(Type x) const {
    int ans = std::numeric_limits<int>::min();
    for (int i = 0; i < B; i++) {
      if (x[i]) {
        ans = Max(ans, expires[i]);
      }
    }
    return ans;
  }
  Vec<Type> to_vec() const {
    Vec<Type> ans;
    ans.reserve(size());
    for (int i = B - 1; i >= 0; i--) {
      if (set[i]) {
        ans.push_back(map[i]);
      }
    }
    return ans;
  }
  int add(Type val, int expiry = std::numeric_limits<int>::max()) {
    Type state;
    for (int i = B - 1; i >= 0; i--) {
      if (!val[i] || !set[i]) {
        continue;
      }
      val ^= map[i];
      state ^= source[i];
    }
    if (val != Type()) {
      int log = B - 1;
      while (!val[log]) {
        log--;
      }
      set[log] = true;
      map[log] = val;
      source[log] = state;
      source[log].set(log);
      expires[log] = expiry;
      upward(log);
      return log;
    }
    int min_index = -1;
    int min_expiry = std::numeric_limits<int>::max();
    for (int i = 0; i < B; i++) {
      if (!state[i]) {
        continue;
      }
      if (expires[i] < min_expiry) {
        min_expiry = expires[i];
        min_index = i;
      }
    }
    if (min_expiry < expiry) {
      Type xor_val = state;
      xor_val[min_index] = false;
      for (int i = 0; i < B; i++) {
        if (source[i][min_index]) {
          source[i] ^= xor_val;
        }
      }
      expires[min_index] = expiry;
      return min_index;
    }
    return -1;
  }

  bool contain(Type val) const {
    for (int i = B - 1; i >= 0; i--) {
      if (val[i]) {
        if (!set[i]) {
          return false;
        }
        val ^= map[i];
      }
    }
    return val == Type();
  }
  i64 xor_number_count() const { return i64(1) << size(); }
  Type the_kth(Type k) const {
    i64 ID = 0;
    Type num;
    for (int i = 0; i < B; i++) {
      if (!set[i]) {
        continue;
      }
      if (k[id]) {
        num ^= map[i];
      }
      id++;
    }
    return num;
  }
  Type the_rank(Type n) const {
    int index = size() - 1;
    Type rank;
    for (int i = B - 1; i >= 0; i--) {
      if (!set[i]) {
        continue;
      }
      if (n[i]) {
        rank.set(index);
        n ^= map[i];
      }
      index--;
    }
    return rank;
  }
  Type the_max_xor(Type x) const {
    for (int i = B - 1; i >= 0; i--) {
      if (!set[i]) {
        continue;
      }
      if (!x[i]) {
        x ^= map[i];
      }
    }
    return x;
  }
  Type the_min_xor(Type x) const {
    for (int i = B - 1; i >= 0; i--) {
      if (!map[i]) {
        continue;
      }
      if (x[i]) {
        x ^= map[i];
      }
    }
    return x;
  }

 private:
  void upward(int row) {
    Assert(map[row][row]);
    for (int i = row + 1; i < B; i++) {
      if (map[i][row]) {
        map[i] ^= map[row];
        source[i] ^= source[row];
      }
    }
  }
};
}  // namespace math
}  // namespace dalt
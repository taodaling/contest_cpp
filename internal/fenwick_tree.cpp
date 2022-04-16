#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct FenwickTree {
 private:
  // data[i] = \sum_{j \in (i-lowbit(i), i]} A[i]
  Vec<T> data;
  int n;

 public:
  FenwickTree(int _n = 0) {
    n = _n;
    data = Vec<T>(n + 1);
  }

  // A[0] + ... + A[i]
  T query(int i) {
    i += 1;
    i = Min(i, n);
    T sum = 0;
    for (; i > 0; i -= i & -i) {
      sum = sum + data[i];
    }
    return sum;
  }

  // A[l] + ... + A[r]
  T query(int l, int r) const {
    if (l > r) {
      return T();
    }
    return query(r) - query(l - 1);
  }

  // A[i] += mod
  void update(int i, T mod) {
    i += 1;
    if (i <= 0) {
      return;
    }
    for (; i <= n; i += i & -i) {
      data[i] += mod;
    }
  }

  void update(int l, int r, T mod) {
    if (l > r) {
      return;
    }
    l = Max(l, 0);
    update(l, mod);
    update(r + 1, -mod);
  }

  int size() { return n; }

  // A[i] = x
  void set(int i, T x) { update(i, x - query(i, i)); }

  FenwickTree(const Indexer<T> &initial_value, i32 _n) : FenwickTree(_n) {
    for (int i = 1; i <= n; i++) {
      data[i] = initial_value(i - 1);
    }
    for (int i = 1; i <= n; i++) {
      int to = i + (i & -i);
      if (to <= n) {
        data[to] += data[i];
      }
    }
  }

  Vec<T> to_vec() {
    Vec<T> ans(n);
    for (int i = 0; i < n; i++) {
      ans[i] = query(i, i);
    }
    return ans;
  }
};
}  // namespace dalt
#pragma once
#include "binary.cpp"
#include "common.cpp"
namespace dalt {
template <class T>
struct FenwickTree {
 private:
  // data[i] = \sum_{j \in (i-lowbit(i), i]} A[i]
  Vec<T> data;
  int n;
  int hb;

 public:
  FenwickTree(int _n = 0) {
    n = _n;
    data = Vec<T>(n + 1);
    hb = HighestOneBit(n);
  }
  // find the smallest index i while A[0] + ... + A[i] >= v, if no such index, n will be returned
  T lower_bound(T v) const {
    T sum = T();
    int pos = 0;
    for (int i = hb; i > 0; i >>= 1) {
      int np = pos + i;
      if (np <= n && sum + data[np] < v) {
        sum += data[np];
        pos = np;
      }
    }
    return pos;
  }

  // A[0] + ... + A[i]
  T query(int i) const {
    i += 1;
    i = Min(i, n);
    T sum = T();
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

  FenwickTree(i32 _n, const Indexer<T> &initial_value) : FenwickTree(_n) {
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
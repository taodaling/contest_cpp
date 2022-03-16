#pragma once
namespace dalt {
template <class T>
struct FenwickTreeExt {
 private:
  Vec<T> delta;
  Vec<T> idelta;
  int n;
  void update(int i, T x) {
    i++;
    T x1 = x;
    T x2 = x * i;
    for (; i <= n; i += i & -i) {
      delta[i] = delta[i] + x1;
      idelta[i] = idelta[i] + x2;
    }
  }

 public:
  FenwickTreeExt(int _n) : n(_n) {
    delta = Vec<T>(n + 1);
    idelta = Vec<T>(n + 1);
  }
  FenwickTreeExt(int _n, const Indexer<T>& indexer) : FenwickTreeExt(_n) {
    for (int i = 1; i <= n; i++) {
      delta[i] = indexer(i - 1);
    }
    for (int i = n; i > 0; i--) {
      delta[i] = delta[i] - delta[i - 1];
      idelta[i] = delta[i] * i;
    }
    for (int i = 1; i <= n; i++) {
      int to = i + (i & -i);
      if (to <= n) {
        delta[to] = delta[to] + delta[i];
        idelta[to] = idelta[to] + idelta[i];
      }
    }
  }

  void update(int l, int r, T x) {
    update(l, x);
    update(r + 1, -x);
  }

  // prefix sum
  T query(int x) const {
    x++;
    T ans1 = 0;
    T ans2 = 0;
    for (int i = x; i > 0; i -= (i & -i)) {
      ans1 = ans1 + delta[i];
      ans2 = ans2 + idelta[i];
    }
    return (x + 1) * ans1 - ans2;
  }

  T query(int l, int r) const { return query(r) - query(l - 1); }
  Vec<T> to_vec() const {
    Vec<T> res(n);
    for (int i = 0; i < n; i++) {
      res[i] = query(i, i);
    }
    return res;
  }
};
}  // namespace dalt
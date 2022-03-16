#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct FenwickTree2Ext {
 private:
  Vec<Vec<T>> delta;
  Vec<Vec<T>> idelta;
  Vec<Vec<T>> jdelta;
  Vec<Vec<T>> ijdelta;
  int n;
  int m;

  void update(int x, int y, T mod) {
    x++;
    y++;
    T x1 = mod;
    T x2 = mod * x;
    T x3 = mod * y;
    T x4 = mod * x * y;
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        delta[i][j] = delta[i][j] + x1;
        idelta[i][j] = idelta[i][j] + x2;
        jdelta[i][j] = jdelta[i][j] + x3;
        ijdelta[i][j] = ijdelta[i][j] + x4;
      }
    }
  }

 public:
 //O(nm)
  FenwickTree2Ext(int _n, int _m) : n(_n), m(_m) {
    delta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    idelta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    jdelta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    ijdelta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
  }
  // O(nm)
  FenwickTree2Ext(int _n, int _m, const Indexer2<T>& indexer)
      : FenwickTree2Ext(_n, _m) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        delta[i][j] = indexer(i - 1, j - 1);
      }
    }
    for (int i = n; i > 0; i--) {
      for (int j = n; j > 0; j--) {
        delta[i][j] = delta[i][j] - delta[i - 1][j] - delta[i][j - 1] +
                      delta[i - 1][j - 1];
        idelta[i][j] = i * delta[i][j];
        jdelta[i][j] = j * delta[i][j];
        ijdelta[i][j] = j * idelta[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int ni = i + (i & -i);
        int nj = j + (j & -j);
        if (ni <= n) {
          delta[ni][j] = delta[ni][j] + delta[i][j];
          idelta[ni][j] = idelta[ni][j] + idelta[i][j];
          jdelta[ni][j] = jdelta[ni][j] + jdelta[i][j];
          ijdelta[ni][j] = ijdelta[ni][j] + ijdelta[i][j];
        }
        if (nj <= m) {
          delta[i][nj] = delta[i][nj] + delta[i][j];
          idelta[i][nj] = idelta[i][nj] + idelta[i][j];
          jdelta[i][nj] = jdelta[i][nj] + jdelta[i][j];
          ijdelta[i][nj] = ijdelta[i][nj] + ijdelta[i][j];
        }
        if (ni <= n && nj <= m) {
          delta[ni][nj] = delta[ni][nj] - delta[i][j];
          idelta[ni][nj] = idelta[ni][nj] - idelta[i][j];
          jdelta[ni][nj] = jdelta[ni][nj] - jdelta[i][j];
          ijdelta[ni][nj] = ijdelta[ni][nj] - ijdelta[i][j];
        }
      }
    }
  }

  // O(\log n \log m)
  void update(int b, int t, int l, int r, T mod) {
    update(b, l, mod);
    update(t + 1, l, -mod);
    update(b, r + 1, -mod);
    update(t + 1, r + 1, mod);
  }
  // O(\log n \log m)
  T query(int x, int y) const {
    x++;
    y++;
    T ans1 = 0;
    T ans2 = 0;
    T ans3 = 0;
    T ans4 = 0;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        ans1 = ans1 + delta[i][j];
        ans2 = ans2 + idelta[i][j];
        ans3 = ans3 + jdelta[i][j];
        ans4 = ans4 + ijdelta[i][j];
      }
    }
    return ans1 * (x + 1) * (y + 1) - ans2 * (y + 1) - ans3 * (x + 1) + ans4;
  }
  // O(\log n \log m)
  T query(int b, int t, int l, int r) const {
    T ans = query(t, r);
    if (b > 0) {
      ans = ans - query(b - 1, r);
    }
    if (l > 0) {
      ans = ans - query(t, l - 1);
    }
    if (b > 0 && l > 0) {
      ans = ans + query(b - 1, l - 1);
    }
    return ans;
  }
  Vec<Vec<T>> to_vec() const {
    Vec<Vec<T>> res(n, Vec<T>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = query(i, i, j, j);
      }
    }
    return res;
  }
};
}  // namespace dalt
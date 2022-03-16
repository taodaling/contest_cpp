#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct FenwickTree2 {
 private:
  Vec<Vec<T>> data;
  int n;
  int m;

 public:
  // 创建大小A[1...n][1..,m]
  // O(nm)
  FenwickTree2(int _n, int _m) : n(_n), m(_m) {
    data = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
  }
  // O(nm)
  FenwickTree2(int _n, int _m, const Indexer2<T>& indexer)
      : FenwickTree2(_n, _m) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        data[i][j] = indexer(i - 1, j - 1);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int ni = i + (i & -i);
        int nj = j + (j & -j);
        if (ni <= n) {
          data[ni][j] = data[ni][j] + data[i][j];
        }
        if (nj <= m) {
          data[i][nj] = data[i][nj] + data[i][j];
        }
        if (ni <= n && nj <= m) {
          data[ni][nj] = data[ni][nj] - data[i][j];
        }
      }
    }
  }

  // 查询左上角为(1,1)，右下角为(x,y)的矩形和
  // O(\log n \log m)
  T query(int x, int y) const {
    x++;
    y++;
    T sum = T();
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        sum = sum + data[i][j];
      }
    }
    return sum;
  }

  // 查询左上角为(b,l)，右下角为(t,r)的矩形和
  // O(\log n \log m)
  T query(int b, int t, int l, int r) const {
    return query(t, r) - query(b - 1, r) - query(t, l - 1) +
           query(b - 1, l - 1);
  }

  // 将A[x][y] 更新为A[x][y]+mod
  // O(\log n \log m)
  void update(int x, int y, T mod) {
    x++;
    y++;
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        data[i][j] = data[i][j] + mod;
      }
    }
  }

  // 将A[x][y] 更新为mod
  // O(\log n \log m)
  void set(int r, int c, T mod) { update(r, c, mod - query(r, r, c, c)); }
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
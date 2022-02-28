#pragma once
#include "binary.cpp"
#include "common.cpp"
namespace dalt {
template <class T>
struct SparseTable2 {
 private:
  Vec<Vec<Vec<Vec<T>>>> data;
  Reducer<T> reducer;

 public:
  SparseTable2(int n, int m, const Indexer2<T> &indexer,
               const Reducer<T> &_reducer)
      : reducer(_reducer) {
    int logn = Log2Floor(n);
    int logm = Log2Floor(m);
    data = Vec<Vec<Vec<Vec<T>>>>(
        logn + 1, Vec<Vec<Vec<T>>>(n, Vec<Vec<T>>(logm + 1, Vec<T>(m))));
    for (int i = 0; i <= logn; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k <= logm; k++) {
          for (int t = 0; t < m; t++) {
            if (i == 0 && k == 0) {
              data[i][j][k][t] = indexer(j, t);
            } else if (i == 0) {
              data[i][j][k][t] =
                  reducer(data[i][j][k - 1][t],
                          data[i][j][k - 1][Min(t + (1 << k - 1), m - 1)]);
            } else if (k == 0) {
              data[i][j][k][t] =
                  reducer(data[i - 1][j][k][t],
                          data[i - 1][Min(j + (1 << i - 1), n - 1)][k][t]);
            } else {
              T ans = reducer(data[i - 1][j][k][t],
                              data[i - 1][Min(j + (1 << i - 1), n - 1)][k][t]);
              ans = reducer(data[i - 1][j][k - 1][Min(t + (1 << k - 1), m - 1)],
                            ans);
              ans = reducer(data[i - 1][Min(j + (1 << i - 1), n - 1)][k - 1]
                                [Min(t + (1 << k - 1), m - 1)],
                            ans);
              data[i][j][k][t] = ans;
            }
          }
        }
      }
    }
  }
  T query(int b, int t, int l, int r) const {
    int h = t - b + 1;
    int w = r - l + 1;
    int logh = Log2Floor(h);
    int logw = Log2Floor(w);

    T ans = reducer(data[logh][b][logw][l],
                    data[logh][t + 1 - (1 << logh)][logw][l]);
    ans = reducer(data[logh][b][logw][r + 1 - (1 << logw)], ans);
    ans = reducer(data[logh][t + 1 - (1 << logh)][logw][r + 1 - (1 << logw)],
                  ans);
    return ans;
  }
};
}  // namespace dalt
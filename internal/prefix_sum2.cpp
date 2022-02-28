#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct PrefixSum2 {
 private:
  Vec<Vec<T>> data;

 public:
  PrefixSum2(int n, int m, const Indexer2<T> &indexer) {
    data = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        data[i][j] = data[i][j - 1] + indexer(i - 1, j - 1);
      }
      for (int j = 1; j <= m; j++) {
        data[i][j] = data[i][j] + data[i - 1][j];
      }
    }
  }
  T query(int b, int t, int l, int r) const {
    r++;
    t++;
    return data[t][r] - data[t][l] - data[b][r] + data[b][l];
  }
  Vec<Vec<T>> to_vec() const { return data; }
};
}  // namespace dalt
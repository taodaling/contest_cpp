#pragma once
#include "../common.cpp"
#include "binary.cpp"
namespace dalt {
template <class T> struct SparseTable {
private:
  Vec<Vec<T>> table;
  Reducer<T> reducer;

public:
  using Self = SparseTable<T>;
  SparseTable(int n, const Indexer<T> &data, Reducer<T> f) : reducer(f) {
    i32 m = Log2Floor(u32(n));
    table = Vec<Vec<T>>(m + 1, Vec<T>(n));
    for(int i = 0; i < n; i++){
      table[0][i] = data(i);
    }
    for (i32 i = 0; i < m; i++) {
      i32 step = 1 << i;
      for (i32 j = 0; j < n; j++) {
        if (j + step < n) {
          table[i + 1][j] = reducer(table[i][j], table[i][j + step]);
        } else {
          table[i + 1][j] = table[i][j];
        }
      }
    }
  }

  T query(i32 l, i32 r) const {
    int len = r - l + 1;
    int log_floor = Log2Floor(u32(len));
    return reducer(table[log_floor][l],
                   table[log_floor][r + 1 - (1 << log_floor)]);
  }
};
} // namespace dalt
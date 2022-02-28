#pragma once
#include "common.cpp"
using namespace dalt;
#include "sparse_table2.cpp"
#include "binary_search.cpp"
void SolveOne(IStream &in, OStream &out) {
  int n, m;
  in >> n >> m;
  Vec<Vec<u16>> data(n, Vec<u16>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      in >> data[i][j];
    }
  }
  Vec<Vec<u16>> squares(n + 1, Vec<u16>(m + 1));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      squares[i][j] = (Min(Min(squares[i + 1][j], squares[i][j + 1]),
                           squares[i + 1][j + 1]) +
                       1) *
                      data[i][j];
    }
  }
  Debug(squares);
  SparseTable2<u16> st(
      n, m, [&](int i, int j) { return squares[i][j]; },
      [&](auto a, auto b) { return Max(a, b); });
  
  int t;
  in >> t;
  for(int i = 0; i < t; i++) {
    int x1, y1, x2, y2;
    in >> x1 >> y1 >> x2 >> y2;
    x1--;
    y1--;
    x2--;
    y2--;
    auto bres = LastTrue<i32>(1, Min(x2 - x1, y2 - y1) + 1, [&](int m) -> bool {
      int b = x1;
      int l = y1;
      //t + m - 1 <= x2
      int t = x2 + 1 - m;
      int r = y2 + 1 - m;
      return st.query(b, t, l, r) >= m;
    }); 
    int ans = bres.is_none() ? 0 : *bres;
    out << ans << '\n';
  }
}

void SolveMulti(IStream &in, OStream &out) {
  int num_of_input = 1;
  for (int i = 0; i < num_of_input; i++) {
    SolveOne(in, out);
  }
}
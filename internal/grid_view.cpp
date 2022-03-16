#pragma once
#include "common.cpp"
namespace dalt {
template <class T = int>
struct GridView {
  using A3 = Array<T, 3>;
  using Mat3 = Array<A3, 3>;
  using A2 = Array<T, 2>;

 private:
  int n;
  int m;
  Mat3 mat;
  Mat3 inv_mat;
  static Mat3 mul(const Mat3 &a, const Mat3 &b) {
#define MAT3_MUL(i, j) a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j]
    return Mat3{A3{MAT3_MUL(0, 0), MAT3_MUL(0, 1), MAT3_MUL(0, 2)},
                A3{MAT3_MUL(1, 0), MAT3_MUL(1, 1), MAT3_MUL(1, 2)},
                A3{MAT3_MUL(2, 0), MAT3_MUL(2, 1), MAT3_MUL(2, 2)}};
#undef MAT3_MUL
  }
  static A3 mul(const Mat3 &a, const A3 &b) {
#define MAT3_MUL(i) a[i][0] * b[0] + a[i][1] * b[1] + a[i][2] * b[2]
    return A3{MAT3_MUL(0), MAT3_MUL(1), MAT3_MUL(2)};
#undef MAT3_MUL
  }
  static int mul(const A3 &a, const A3 &b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  }
  void add_right(const Mat3 &x, const Mat3 &inv_x) {
    mat = mul(mat, x);
    inv_mat = mul(inv_x, inv_mat);
  }
  void add_left(const Mat3 &x, const Mat3 &inv_x) {
    mat = mul(x, mat);
    inv_mat = mul(inv_mat, inv_x);
  }
  void add_right(const Mat3 &x) { add_right(x, x); }
  void add_left(const Mat3 &x) { add_left(x, x); }

 public:
  GridView(int _n, int _m)
      : n(_n),
        m(_m),
        mat(Mat3{A3{1, 0, 0}, A3{0, 1, 0}, A3{0, 0, 1}}),
        inv_mat(Mat3{A3{1, 0, 0}, A3{0, 1, 0}, A3{0, 0, 1}}) {}

  int width() const { return m; }
  int height() const { return n; }
  GridView clone() const { return *this; }
  GridView &flip_x() {
    add_left(Mat3{A3{-1, 0, n - 1}, A3{0, 1, 0}, A3{0, 0, 1}});
    return *this;
  }
  GridView &flip_y() {
    add_left(Mat3{A3{1, 0, 0}, A3{0, -1, m - 1}, A3{0, 0, 1}});
    return *this;
  }
  GridView &swap_x_y() {
    Swap(n, m);
    add_left(Mat3{A3{0, 1, 0}, A3{1, 0, 0}, A3{0, 0, 1}});
    return *this;
  }
  A2 global_to_view(const A2 &xy) const {
    auto ans = mul(mat, A3{xy[0], xy[1], 1});
    return A2{ans[0], ans[1]};
  }
  A2 view_to_global(const A2 &xy) const {
    auto ans = mul(inv_mat, A3{xy[0], xy[1], 1});
    return A2{ans[0], ans[1]};
  }
  GridView &rect(T xl, T xr, T yl, T yr) {
    Assert(xr - xl + 1 <= n);
    Assert(yr - yl + 1 <= m);
    add_left(Mat3{A3{1, 0, -xl}, A3{0, 1, -yl}, {0, 0, 1}},
             Mat3{A3{1, 0, xl}, A3{0, 1, yl}, {0, 0, 1}});
    n = xr - xl + 1;
    m = yr - yl + 1;
    return *this;
  }
};
}  // namespace dalt
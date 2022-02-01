#pragma once
#include "../common.cpp"
#include "modint.cpp"
#include "modint_sum.cpp"
namespace dalt {
template <class T> struct Matrix {
  using Self = Matrix<T>;
  Vec<T> data;
  int m;
  Matrix(int _n = 0, int _m = 0) : data(_n * _m), m(_m) {}
  static Self mul_identity(int n) {
    Self res(n, n);
    for (int i = 0; i < n; i++) {
      res[i][i] = T(1);
    }
    return res;
  }
  T *operator[](int i) { return data.data() + i * m; }
  const T *operator[](int i) const { return data.data() + i * m; }
  Array<i32, 2> shape() const { return {Size(data) / m, m}; }
  i32 row_num() const { return Size(data) / m; }
  i32 col_num() const { return m; }
  bool square() const { return row_num() == col_num(); }
  Self operator+(const Self &rhs) const {
    const Self &lhs = *this;
    Assert(lhs.shape() == rhs.shape());
    int n = Size(lhs.data);
    Self res(lhs.row_num(), lhs.col_num());
    for (int i = 0; i < n; i++) {
      res[i][0] = lhs[i][0] + rhs[i][0];
    }
    return res;
  }
  Self operator-(const Self &rhs) const {
    const Self &lhs = *this;
    Assert(lhs.shape() == rhs.shape());
    int n = Size(lhs.data);
    Self res(lhs.row_num(), lhs.col_num());
    for (int i = 0; i < n; i++) {
      res[i][0] = lhs[i][0] - rhs[i][0];
    }
    return res;
  }
  Self operator/(const Self &rhs) const {
    return *this * (*rhs.possible_inv());
  }
  template <class V = T>
  enable_if_t<is_same_v<V, T> &&
                  !(is_modint_v<T> && is_same_v<i32, typename T::Type>),
              Self>
  operator*(const Self &rhs) const {
    const Self &lhs = *this;
    Assert(lhs.col_num() == rhs.row_num());
    int n = lhs.row_num();
    int mid = lhs.col_num();
    int m = rhs.col_num();
    Self res(n, m);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < mid; k++) {
        for (int j = 0; j < m; j++) {
          res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
        }
      }
    }
    return res;
  }
  // fast way to achievc matrix mutiplication, reduce the number of modular
  // operation
  template <class V = T>
  enable_if_t<is_same_v<V, T> &&
                  (is_modint_v<T> && is_same_v<i32, typename T::Type>),
              Self>
  operator*(const Self &rhs) const {
    using Modular = typename T::Modular;
    const Self &lhs = *this;
    Assert(lhs.col_num() == rhs.row_num());
    int n = lhs.row_num();
    int mid = lhs.col_num();
    int m = rhs.col_num();
    Vec<u64> accummulate(n * m);
    u64 threshold = std::numeric_limits<u64>::max() -
                    u64(Modular::modulus - 1) * u64(Modular::modulus - 1);
    Self res(n, m);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < mid; k++) {
        for (int j = 0; j < m; j++) {
          i32 ij = i * m + j;
          if (accummulate[ij] > threshold) {
            accummulate[ij] %= Modular::modulus;
          }
          accummulate[ij] += u64(lhs[i][k].value) * rhs[k][j].value;
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = ModInt<Modular>(accummulate[i * m + j] % Modular::modulus);
      }
    }
    return res;
  }
  T determinant() const {
    Assert(row_num() == col_num());
    Self self = *this;
    let n = m;
    let ans = T(1);
    for (int i = 0; i < n; i++) {
      let max_row = i;
      for (int j = i; j < n; j++) {
        if (self[j][i] != T(0)) {
          max_row = j;
          break;
        }
      }
      if (self[max_row][i] == T(0)) {
        return T(0);
      }
      if (i != max_row) {
        self.row_swap(i, max_row);
        ans = T(0) - ans;
      }
      ans = ans * self[i][i];
      self.row_mul(i, T(1) / self[i][i]);
      for (int j = i + 1; j < n; j++) {
        if (self[j][i] == T(0)) {
          continue;
        }
        let f = T(0) - self[j][i];
        self.row_add(j, i, f);
      }
    }
    return ans;
  }
  Optional<Self> possible_inv() const {
    if (row_num() != col_num()) {
      return {};
    }
    let n = row_num();
    Self l = *this;
    Self r = mul_identity(n);

    for (int i = 0; i < n; i++) {
      let max_row = i;
      for (int j = i; j < n; j++) {
        if (l[j][i] != T(0)) {
          max_row = j;
          break;
        }
      }
      if (l[max_row][i] == T(0)) {
        return {};
      }
      l.row_swap(i, max_row);
      r.row_swap(i, max_row);
      let inv = T(1) / l[i][i];
      r.row_mul(i, inv);
      l.row_mul(i, inv);
      for (int j = 0; j < n; j++) {
        if (i == j) {
          continue;
        }
        if (l[j][i] == T(0)) {
          continue;
        }
        r.row_add(j, i, T(0) - l[j][i]);
        l.row_add(j, i, T(0) - l[j][i]);
      }
    }
    return {r};
  }

private:
  void row_swap(int i, int j) {
    T *offset_i = (*this)[i];
    T *offset_j = (*this)[j];
    for (int k = 0; k < m; k++) {
      Swap(offset_i[k], offset_j[k]);
    }
  }
  void row_mul(int r, T x) {
    T *ptr = (*this)[r];
    for (int k = 0; k < m; k++) {
      ptr[k] = ptr[k] * x;
    }
  }
  void row_add(int r, T x) {
    T *ptr = (*this)[r];
    for (int k = 0; k < m; k++) {
      ptr[k] = ptr[k] + x;
    }
  }
  void row_add(int a, int b, T f) {
    T *ptr_a = (*this)[a];
    T *ptr_b = (*this)[b];
    for (int i = 0; i < m; i++) {
      ptr_a[i] = ptr_a[i] + ptr_b[i] * f;
    }
  }
  Vec<Vec<T>> to_vec() const {
    Vec<Vec<T>> res(row_num(), Vec<T>(col_num()));
    for (int i = 0; i < row_num(); i++) {
      for (int j = 0; j < col_num(); j++) {
        res[i][j] = (*this)[i][j];
      }
    }
    return res;
  }
};
} // namespace dalt
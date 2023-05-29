#pragma once
#include "common.cpp"
#include "optional.cpp"
namespace dalt {
template <class T>
struct GuassElimination {
 private:
  Vec<Vec<T>> data;
  Vec<T> inv;
  int n;
  int rank;
  void sub(Vec<T>& x, const Vec<T>& row, T f) {
    for (int i = 0; i < n; i++) {
      x[i] -= row[i] * f;
    }
  }

 public:
  GuassElimination(int _n) : data(_n + 1), inv(_n + 1), n(_n + 1), rank(0) {}

  int add(Vec<T> e) {
    Assert(Size(e) == n);
    for (int i = 0; i < n; i++) {
      if (data[i].empty() || e[i] == T(0)) {
        continue;
      }
      sub(e, data[i], e[i] * inv[i]);
    }
    int index = -1;
    for (int i = 0; i < n; i++) {
      if (e[i] != T(0)) {
        index = i;
        break;
      }
    }
    if (index != -1) {
      data[index] = e;
      inv[index] = T(1) / e[index];
      rank++;
    }
    return index;
  }
  int get_rank() const { return rank - int(Size(data[n - 1]) > 0); }
  bool has_solution() const { return Size(data[n - 1]) == 0; }
  Optional<Vec<T>> any_solution() const {
    if (!has_solution()) {
      return {};
    }
    Vec<T> ans(n - 1, T(0));
    for (int i = n - 2; i >= 0; i--) {
      if (data[i].empty()) {
        continue;
      }
      T sum = data[i][n - 1];
      for (int j = n - 2; j > i; j--) {
        sum -= data[i][j] * ans[j];
      }
      ans[i] = sum * inv[i];
    }
    return ans;
  }
  Vec<Vec<T>> to_vec() const { return data; }
};


}  // namespace dalt
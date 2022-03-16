#pragma once
#include "common.cpp"

namespace dalt {
template <class T> struct PrefixSum {
private:
  Vec<T> sum;
  int n;

public:
  using Self = PrefixSum<T>;
  PrefixSum(Vec<T> data = Vec<T>()) : sum(move(data)) {
    if (sum.empty()) {
      sum.push_back(T());
    }
    n = int(sum.size());
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + sum[i];
    }
  }
  T prefix(int i) const {
    if (i < 0) {
      return T();
    }
    i = Min(i, n - 1);
    return sum[i];
  }
  T suffix(int i) const { return sum.back() - prefix(i - 1); }
  T query(int l, int r) const {
    if (l > r) {
      return 0;
    }
    return prefix(r) - prefix(l - 1);
  }
  Vec<T> to_vec() const {
    return sum;
  }
};
} // namespace dalt
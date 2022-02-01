#pragma once
#include "convolution.cpp"
#include "poly.cpp"
#include "binary.cpp"
namespace dalt {
namespace poly {
template <class Conv> struct Polynomial {
  static_assert(is_convolution_v<Conv>);
  using T = typename Conv::Type;
  using Seq = Vec<T>;
  using Self = Polynomial<Conv>;
  Seq data;
  Polynomial() : Seq({0}) {}
  Polynomial(Vec<T> &&_data) : data(_data) { Normalize(data); }
  Polynomial(const Vec<T> &_data) : data(_data) { Normalize(data); }
  Self integral() const {
    let rank = this->rank();
    Vec<T> range(rank + 1);
    for (int i = 0; i <= rank; i++) {
      range[i] = i + 1;
    }
    let inv = InverseBatch(move(range));
    Vec<T> ans(rank + 2);
    for (int i = 0; i <= rank; i++) {
      ans[i + 1] = inv[i] * data[i];
    }
    return Self(ans);
  }
  Self differential() const {
    Vec<T> ans(rank());
    for (int i = 1; i <= Size(ans); i++) {
      ans[i - 1] = data[i] * T(i);
    }
    return Self(ans);
  }
  Self modular(i32 n) const {
    if (Size(data) < n) {
      return Self(*this);
    } else {
      Vec<T> ans;
      ans.reserve(n);
      ans.insert(ans.begin(), data.begin(), data.begin() + n);
      return Self(ans);
    }
  }
  static Self of(T val) { return Self(Vec<T>{val}); }
  Self ln(i32 n) const {
    Assert(data[0] == T(1));
    let diff = differential().modular(n);
    let inv = inverse(n);
    return (diff * inv).integral().modular(n);
  }
  Self exp(i32 n) const {
    if (n == 0) {
      return Self::of(T(0));
    }
    auto dfs = [&](auto &dfs, i32 n) -> Self {
      if (n == 1) {
        return Self::of(T(1));
      }
      let ans = dfs(dfs, (n + 1) / 2);
      let ln = this->modular(n) - ans.ln(n);
      ln.data[0] = ln.data[0] + T(1);
      return (ans * ln).modular(n);
    };
    return dfs(dfs, n);
  }
  int rank() const { return Size(data) - 1; }
  Self operator*(const Self &rhs) const {
    const Self &lhs = *this;
    return Self(Conv::conv(lhs.data, rhs.data));
  }
  Self operator/(const Self &rhs) const {
    auto a = data;
    auto b = rhs.data;
    if (a.size() < b.size()) {
      return Self::of(T(0));
    }
    Reverse(All(a));
    Reverse(All(b));
    i32 c_rank = Size(a) - Size(b);
    i32 proper_len = 1 << Log2Ceil(c_rank * 2 + 1);
    a.resize(proper_len);
    b.resize(proper_len);
    Vec<T> c = Conv::inverse(move(b), c_rank + 1);
    Vec<T> prod = Conv::conv(move(a), move(c));
    prod.resize(c_rank + 1);
    Reverse(All(prod));
    return Self(prod);
  }
  Self operator%(const Self &rhs) const { return *this - (*this / rhs) * rhs; }
  Self operator+(const Self &rhs) const {
    const Self &lhs = *this;
    int n = Size(lhs.data);
    int m = Size(rhs.data);
    Vec<T> res(Max(n, m));
    for (int i = 0; i < n; i++) {
      res[i] = lhs.data[i];
    }
    for (int i = 0; i < m; i++) {
      res[i] = res[i] + rhs.data[i];
    }
    return Self(move(res));
  }
  Self operator-(const Self &rhs) const {
    const Self &lhs = *this;
    int n = Size(lhs.data);
    int m = Size(rhs.data);
    Vec<T> res(Max(n, m));
    for (int i = 0; i < n; i++) {
      res[i] = lhs.data[i];
    }
    for (int i = 0; i < m; i++) {
      res[i] = res[i] - rhs.data[i];
    }
    return Self(move(res));
  }
  T &operator[](int index) { return data[index]; }
  const T &operator[](int index) const { return data[index]; }
  T get(int index) const {
    if (index < Size(data)) {
      return data[index];
    }
    return T(0);
  }
  bool operator==(const_ref(Self) rhs) const { return data == rhs.data; }
  bool operator!=(const_ref(Self) rhs) const { return !(*this == rhs); }
  Vec<T> to_vec() const { return data; }
  Self inverse(int n) const { return Self(Conv::inverse(data, n)); }
};

} // namespace poly
} // namespace dalt
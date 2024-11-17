#pragma once
#include "binary.cpp"
#include "brute_force_conv.cpp"
#include "convolution.cpp"
#include "math.cpp"
#include "mod_inverse.cpp"
#include "modint.cpp"
#include "poly.cpp"
#include "combination.cpp"
namespace dalt {
namespace poly {
const static int POLY_FAST_MAGIC_THRESHOLD = 64;
MakeAnnotation(polynomial);
template <class Conv>
struct Polynomial {
  static_assert(is_convolution_v<Conv>);
  using T = typename Conv::Type;
  using Type = T;
  using Seq = Vec<T>;
  using Self = Polynomial<Conv>;
  Seq data;
  Polynomial(T v = T(0)): Polynomial(Vec<T>{v}) {}
  Polynomial(Vec<T> _data) : data(Move(_data)) { Normalize(data); }
  T operator()(T x) const { return Apply(data, x); }
  T apply(T x) const { return (*this)(x); }
  Self integral() const {
    let rank = this->rank();
    Vec<T> range(rank + 1);
    for (int i = 0; i <= rank; i++) {
      range[i] = i + 1;
    }
    let inv = math::InverseBatch(move(range));
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
  void self_modular(i32 n) {
    if(data.size() >= n) {
      data.resize(n);
      Normalize(data);
    }
  }
  Self modular(i32 n) const { return Self(CopyAndExtend(data, n)); }
  //x^n = 1
  Self circular_modular(i32 n) const {
    //equivalent to mod x^n - 1
    Vec<T> ans(Min(Size(data), n));
    for(int i = 0; i < Size(data); i++) {
      ans[i % n] += data[i];
    }
    return Self(ans);
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
    // if (Min(lhs.rank(), rhs.rank()) < POLY_FAST_MAGIC_THRESHOLD) {
    //   return Self(BruteForceConv<T>::conv(lhs.data, rhs.data));
    // }
    return Self(Conv::conv(lhs.data, rhs.data));
  }
  Self operator*(const T &rhs) const {
    Vec<T> res = data;
    for (int i = 0; i < Size(res); i++) {
      res[i] = res[i] * rhs;
    }
    return Self(res);
  }
  Self &operator*=(const T &rhs) {
    for (int i = 0; i < Size(data); i++) {
      data[i] = data[i] * rhs;
    }
    Normalize(data);
    return *this;
  }
  Self operator+(const T &rhs) const {
    Vec<T> res = data;
    res[0] = res[0] + rhs;
    return Self(res);
  }
  Self operator+=(const T &rhs) const {
    data[0] = data[0] + rhs;
    Normalize(data);
    return data;
  }
  Self operator-(const T &rhs) const {
    Vec<T> res = data;
    res[0] = res[0] - rhs;
    return Self(res);
  }
  Self operator-=(const T &rhs) const {
    data[0] = data[0] - rhs;
    Normalize(data);
    return data;
  }
  Self operator>>(i32 n) const {
    if (n < 0) {
      return *this << -n;
    }
    if (*this == Self::of(T(0))) {
      return Self::of(T(0));
    }
    Vec<T> res(Size(data) + n);
    for (int i = 0; i < Size(data); i++) {
      res[i + n] = data[i];
    }
    return Self(res);
  }
  Self operator<<(i32 n) const {
    if (n < 0) {
      return *this >> -n;
    }
    if (Size(data) < n) {
      return Self::of(T(0));
    }
    Vec<T> res(Size(data) - n);
    for (int i = 0; i < Size(res); i++) {
      res[i] = data[i + n];
    }
    return Self(res);
  }
  Self operator/(const Self &rhs) const {
    auto a = data;
    auto b = rhs.data;
    if (a.size() < b.size()) {
      return Self::of(T(0));
    }
    if (b.size() <= POLY_FAST_MAGIC_THRESHOLD) {
      return BruteForceConv<T>::div_and_rem(Move(a), Move(b))[0];
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
  Self operator%(const Self &rhs) const {
    if (Min(rank(), rhs.rank()) < POLY_FAST_MAGIC_THRESHOLD) {
      return BruteForceConv<T>::div_and_rem(data, rhs.data)[1];
    }
    return *this - (*this / rhs) * rhs;
  }
  //return this(x + s)
  Self shift(T s) const {
    int r = rank();
    var comb = math::Combination<T>(r + 1);
    Vec<T> A(r + 1), B(r + 1);
    T s_pow = 1;
    for(int i = 0; i <= r; i++, s_pow *= s) {
      A[i] = data[i] * comb.fact[i];
      B[i] = s_pow * comb.inv_fact[i];
    }
    var C = Self(Move(A)).delta_convolution(Self(Move(B)));
    for(int i = 0; i <= C.rank(); i++) {
      C.data[i] *= comb.inv_fact[i];
    }
    Normalize(C.data); 
    return C;
  }
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

  T operator[](int index) const {
    return get(index);
  }
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
  static Self mulmod(const Self &a, const Self &b, int mod) {
    return (a * b).modular(mod);
  }
  //O(n ln n ln n)
  Self powmod_binary_lift(i64 n, i32 mod) const {
    if (n == 0) {
      return Self::of(T(1)).modular(mod);
    }
    Self res = powmod_binary_lift(n / 2, mod);
    res = (res * res).modular(mod);
    if (n % 2 == 1) {
      res = (res * *this).modular(mod);
    }
    return res;
  }

  //O(n ln n)
  Self powmod_fast(i32 n_mod_modulus, i32 n_mod_phi, i64 estimate,
                   i32 mod) const {
    static_assert(is_modint_v<T>);
    static_assert(is_same_v<i32, typename T::Type>);
    if (estimate == 0) {
      return Self::of(T(1)).modular(mod);
    }
    if (*this == Self::of(T(0))) {
      return *this;
    }
    i32 k = 0;
    while (data[k] == T(0)) {
      k++;
    }
    if (MulLimit<i64>(k, estimate, mod) >= mod) {
      return Self::of(T(0));
    }
    auto expln = [&](const Self &p, i32 n_mod_modulus, i32 mod) -> Self {
      return (p.ln(mod) *= T(n_mod_modulus)).exp(mod);
    };
    auto expln_ext = [&](Self p, i32 n_mod_modulus, i32 n_mod_phi,
                         i32 mod) -> Self {
      T val = p[0];
      T inv = T(1) / p[0];
      p *= inv;
      Self res = expln(p, n_mod_modulus, mod);
      res *= PowBinaryLift(val, n_mod_phi);
      return res;
    };
    if (k == 0) {
      return expln_ext(*this, n_mod_modulus, n_mod_phi, mod);
    }
    Self trim = (*this) << k;
    Self res = expln_ext(Move(trim), n_mod_modulus, n_mod_phi, mod);
    return (res >> k * estimate).modular(mod);
  }
  static Self product(const Vec<Self> &data) {
    if (data.empty()) {
      return Self(Vec<T>{Type(1)});
    }
    auto dfs = [&](auto &dfs, int l, int r) {
      if (l == r) {
        return data[l];
      }
      int m = (l + r) / 2;
      return dfs(dfs, l, m) * dfs(dfs, m + 1, r);
    };
    return dfs(dfs, 0, Size(data) - 1);
  }
  //ret[i] = \sum_{j} this[i + j] * rhs[j]
  Self delta_convolution(const Self& rhs) const {
    Vec<T> lhs = data;
    Reverse(All(lhs));
    auto ans = Conv::conv(lhs, rhs.data);
    ans.resize(Size(lhs));
    Reverse(All(ans));
    return Self(Move(ans));
  }
};
AssignAnnotationTemplate(Polynomial, polynomial, class);
}  // namespace poly
}  // namespace dalt
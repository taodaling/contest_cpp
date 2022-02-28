#pragma once
#include "common.cpp"
namespace dalt {
namespace poly {
template <class T>
Vec<T> CopyAndExtend(const Vec<T> &data, int n) {
  Vec<T> res;
  res.reserve(n);
  if (n <= Size(data)) {
    res.insert(res.begin(), data.begin(), data.begin() + n);
  } else {
    res.insert(res.begin(), All(data));
    res.resize(n);
  }
  return res;
}
template <class T>
void Normalize(Vec<T> &p) {
  while (!p.empty() && p.back() == T(0)) {
    p.pop_back();
  }
  if (p.empty()) {
    p.push_back(T(0));
  }
}
template <class T>
void Extend(Vec<T> &p, int cap) {
  while (Size(p) < cap) {
    p.push_back(T());
  }
}
template <class T>
Vec<T> DotMul(const Vec<T> &a, const Vec<T> &b) {
  int n = Min(Size(a), Size(b));
  Vec<T> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = a[i] * b[i];
  }
  return ans;
}
template <class T>
void DotMulInplace(Vec<T> &a, const Vec<T> &b) {
  int n = Size(b);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i] = a[i] * b[i];
  }
}
template <class T>
void DotMulPlus(Vec<T> &a, const Vec<T> &b, Vec<T> &res) {
  int n = Min(Size(a), Size(b));
  for (int i = 0; i < n; i++) {
    res[i] = res[i] + a[i] * b[i];
  }
}
template <class T>
T Apply(const Vec<T> &a, T x) {
  T sum = 0;
  for (int i = Size(a) - 1; i >= 0; i--) {
    sum = sum * x + a[i];
  }
  return sum;
}
}  // namespace poly
}  // namespace dalt

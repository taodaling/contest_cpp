#pragma once
#include "brute_force_conv.cpp"
#include "hashmap.cpp"
#include "poly.cpp"
#include "polynomial.cpp"
namespace dalt {
namespace poly {
template <class T> struct GravityLargrangeInterpolation {
  hash::HashMap<T, T> points;
  Vec<T> xs;
  Vec<T> ys;
  Vec<T> lx;
  Vec<T> inv_w;
  GravityLargrangeInterpolation(i32 cap) {
    xs.reserve(cap);
    ys.reserve(cap);
    lx = Vec<T>{T(1)};
    inv_w.reserve(cap);
  }
  void add(T x, T y) {
    if (points.find(x) != points.end()) {
      return;
    }
    points[x] = y;
    i32 n = Size(xs);
    xs.push_back(x);
    ys.push_back(y);
    lx = BruteForceConv<T>::conv(Vec<T>{T(0) - x, T(1)}, lx);
    inv_w.push_back(T(1));
    for (int i = 0; i < n; i++) {
      inv_w[i] = inv_w[i] * (xs[i] - x);
      inv_w[n] = inv_w[n] * (x - xs[i]);
    }
  }
  T estimate_point(T x) const {
    auto iter = points.find(x);
    if (iter != points.end()) {
      return iter->second;
    }
    T y = Apply(lx, x);
    T sum = T(0);
    for (int i = 0; i < Size(xs); i++) {
      T val = ys[i] / (inv_w[i] * (x - xs[i]));
      sum = sum + val;
    }
    return y * sum;
  }
  template <class Conv = BruteForceConv<T>>
  enable_if_t<is_convolution_v<Conv>, Polynomial<Conv>> interpolate() const {
    i32 n = Size(xs);
    Vec<T> ans(n);
    for (int i = 0; i < n; i++) {
      T c = ys[i] / inv_w[i];
      T div = BruteForceConv<T>::div_and_rem(lx, Vec<T>{T(0) - xs[i], T(1)})[0];
      for (int j = 0; j < Size(div); j++) {
        ans[j] = ans[j] + div[j] * c;
      }
    }
    return Polynomial<Conv>(ans);
  }
};
} // namespace poly
} // namespace dalt
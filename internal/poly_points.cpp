#pragma once
#include "polynomial.cpp"
namespace dalt {
namespace poly {
// internal usage
template <class P>
struct PolynomialTree {
  static_assert(is_polynomial_v<P>);
  using T = typename P::Type;
  PolynomialTree* left;
  PolynomialTree* right;
  P p;
  PolynomialTree() : left(NULL), right(NULL) {}

  PolynomialTree(const Vec<T>& x, int l, int r) : PolynomialTree() {
    if (l == r) {
      p = P(Vec<T>{T(0) - x[l], T(1)});
    } else {
      int m = (l + r) / 2;
      left = new PolynomialTree(x, l, m);
      right = new PolynomialTree(x, m + 1, r);
      p = left->p * right->p;
    }
  }
  void multi_apply(const P& p, const Vec<T>& x, Vec<T>& y, int l, int r) {
    if (r - l + 1 <= POLY_FAST_MAGIC_THRESHOLD) {
      for (int i = l; i <= r; i++) {
        y[i] = p.apply(x[i]);
      }
      return;
    }
    auto rem = p % this->p;
    int m = (l + r) / 2;
    left->multi_apply(rem, x, y, l, m);
    right->multi_apply(rem, x, y, m + 1, r);
  }
#ifdef DROP
  ~PolynomialTree() {
    delete left;
    delete right;
  }
#endif
};

//- time: O(|p|\log |p| + |x|(log |x|)^2)
template <class P, class T = typename P::Type>
enable_if_t<is_polynomial_v<P> && is_same_v<T, typename P::Type>, Vec<T>>
MultiApplyFast(const P& p, const Vec<T>& x) {
  int n = Size(x);
  Vec<T> y(n);
  auto tree = new PolynomialTree<P>(x, 0, n - 1);
  tree->multi_apply(p, x, y, 0, n - 1);
  delete tree;
  return y;
}
//- time: O(|p|\log |p| + |x|(log |x|)^2)
template <class P, class T = typename P::Type>
enable_if_t<is_polynomial_v<P> && is_same_v<T, typename P::Type>, P>
InterpolationFast(const Vec<T>& xs, const Vec<T>& ys) {
  Assert(Size(xs) == Size(ys));
  i32 n = Size(xs);
  auto tree = new PolynomialTree<P>(xs, 0, n - 1);
  auto diff_m = tree->p.differential();
  Vec<T> v(Size(xs));
  tree->multi_apply(diff_m, xs, v, 0, n - 1);
  Vec<T> inv = math::InverseBatch<T>(v);
  for (int i = 0; i < n; i++) {
    v[i] = ys[i] * inv[i];
  }
  auto interpolate = [&](auto& interpolate, int l, int r,
                         PolynomialTree<P>* tree) -> P {
    if (l == r) {
      return P::of(v[l]);
    }
    int m = (l + r) / 2;
    auto f0 = interpolate(interpolate, l, m, tree->left);
    auto f1 = interpolate(interpolate, m + 1, r, tree->right);
    auto a = f0 * tree->right->p;
    auto b = f1 * tree->left->p;
    return a + b;
  };
  auto ans = interpolate(interpolate, 0, n - 1, tree);
  delete tree;
  return ans;
}
}  // namespace poly
}  // namespace dalt
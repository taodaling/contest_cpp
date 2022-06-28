#pragma once
#include "circle2.cpp"
#include "common.cpp"
#include "fenwick_tree.cpp"
#include "point2.cpp"
namespace dalt {
namespace adhoc {
using namespace geo2;
// get the number of pairs of points that intersect with solid circle
// O(n\log_2n)
template <class T>
enable_if_t<is_near_value_v<T>, i64> PairOfPointIntersectWithCircle(
    const Vec<Point<T>> &pts, const Circle<T> &circle) {
  int n = Size(pts);
  using Type = typename T::Type;
  using A2 = Array<Type, 2>;
  Vec<A2> ints;
  ints.reserve(n);
  Vec<Point<T>> out1;
  Vec<Point<T>> out2;
  for (int i = 0; i < n; i++) {
    if (circle.contain(pts[i])) {
      continue;
    }
    out1.clear();
    out2.clear();
    auto res = Circle<T>::tangent(circle, Circle<T>(pts[i], 0), out1, out2);
    auto &tangent_points = out1;
    A2 thetas = A2{(tangent_points[0] - circle.center).atan2(),
                   (tangent_points[1] - circle.center).atan2()};
    if (thetas[0] > thetas[1]) {
      Swap(thetas[0], thetas[1]);
    }
    ints.push_back(thetas);
  }
  int m = Size(ints);
  Vec<int> left(m);
  Vec<int> right(m);
  for (int i = 0; i < m; i++) {
    left[i] = right[i] = i;
  }
  Sort(All(left), [&](int a, int b) { return ints[a][0] < ints[b][0]; });
  Sort(All(right), [&](int a, int b) { return ints[a][1] < ints[b][1]; });
  Vec<int> to_rank(m);
  for (int i = 0; i < m; i++) {
    to_rank[left[i]] = i;
  }
  FenwickTree<int> fwt(m);
  auto left_iter = left.begin();
  auto right_iter = right.begin();
  int total = 0;
  i64 ans = 0;
  while (right_iter != right.end()) {
    if (left_iter != left.end() &&
        ints[*right_iter][1] >= ints[*left_iter][0]) {
      int id = *left_iter;
      ++left_iter;

      fwt.update(to_rank[id], 1);
      total++;
    } else {
      int id = *right_iter;
      ++right_iter;

      total--;
      fwt.update(to_rank[id], -1);

      ans += total - fwt.query(to_rank[id]);
    }
  }

  return (i64)n * (n - 1) / 2 - ans;
}
// check if there is a pair of points that intersect with solid circle
// O(n\log_2n) but fast
template <class T>
enable_if_t<is_near_value_v<T>, bool> PairOfPointIntersectWithCircleFastCheck(
    const Vec<Point<T>> &pts, const Circle<T> &circle) {
  int n = Size(pts);
  using Type = typename T::Type;
  using A2 = Array<Type, 2>;
  Vec<A2> ints;
  ints.reserve(n);
  Vec<Point<T>> out1;
  Vec<Point<T>> out2;
  for (int i = 0; i < n; i++) {
    if (circle.contain(pts[i])) {
      return true;
    }
    out1.clear();
    out2.clear();
    auto res = Circle<T>::tangent(circle, Circle<T>(pts[i], 0), out1, out2);
    auto &tangent_points = out1;
    A2 thetas = A2{tangent_points[0].atan2(), tangent_points[1].atan2()};
    if (thetas[0] > thetas[1]) {
      Swap(thetas[0], thetas[1]);
    }
    ints.push_back(thetas);
  }
  Sort(All(ints));
  for (int i = 1; i < Size(ints); i++) {
    if (ints[i][1] <= ints[i - 1][1] || ints[i - 1][1] <= ints[i][0]) {
      return true;
    }
  }
  return false;
}
}  // namespace adhoc
}  // namespace dalt
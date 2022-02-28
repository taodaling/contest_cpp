#pragma once
#include "convexhull.cpp"
namespace dalt {
namespace geo2 {
template <class T, class C>
//- time: O(Size(ch))
enable_if_t<is_base_of_v<ConvexHull<T>, C>, Pair<Point<T>, Point<T>>>
TheFarthestPoingPair(const C& ch) {
  using Pt = Point<T>;
  using F = typename T::FType;
  int n = Size(ch);
  if (n <= 2) {
    return {ch[0], ch[1 % n]};
  }
  Pt x = ch[0];
  Pt y = ch[1];
  for (int i = 0, j = 0; i < n; i++) {
    while (Pt::dist2(ch[i], ch[j % n]) < Pt::dist2(ch[i], ch[(j + 1) % n])) {
      j++;
    }
    if (Pt::dist2(x, y) < Pt::dist2(ch[i], ch[j % n])) {
      x = ch[i];
      y = ch[j % n];
    }
  }
  return {x, y};
}
}  // namespace geo2
}  // namespace dalt
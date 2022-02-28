#pragma once
#include "polygon2.cpp"
namespace dalt {
namespace geo2 {
// credited to:
// https://github.com/bqi343/USACO/blob/58968ef3ea1e18247292ffb5ec399668c791515a/Implementations/content/geometry%20(13)/Misc/ClosestPair%20(13.2).h
// verified by: https://cses.fi/problemset/task/2194/
template <class T, class POLYGON = Polygon<T>>
enable_if_t<is_base_of_v<Polygon<T>, POLYGON>, Pair<Point<T>, Point<T>>>
TheNearestPointPair(POLYGON polygon) {
  using P = Point<T>;
  using Type = typename P::Type;
  using FType = typename P::FType;
  static_assert(is_same_v<FType, f80>);
  Vec<P> v(Move(polygon.data));
  Pair<FType, Pair<P, P>> bes = {(v[0] - v[1]).abs(), {v[0], v[1]}};
  T INF = T::max() / T(2);
  TreeSet<P> S;
  int ind = 0;
  Sort(All(v));
  for (int i = 0; i < Size(v); i++) {
    if (i && v[i] == v[i - 1]) {
      Debug("same");
      return {v[i], v[i]};
    }
    for (; FType(v[i].x - v[ind].x) >= bes.first; ++ind)
      S.erase(P{v[ind].y, v[ind].x});
    for (auto it = S.upper_bound(P{std::floor(FType(v[i].y) - bes.first), INF});
         it != S.end() && FType(it->x - v[i].y) < bes.first; ++it) {
      P t = {it->y, it->x};
      bes = std::min(bes, {(t - v[i]).abs(), {t, v[i]}});
    }
    S.insert(P{v[i].y, v[i].x});
  }
  return bes.second;
}
}  // namespace geo2
}  // namespace dalt
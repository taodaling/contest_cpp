#include "../common.cpp"
namespace dalt {
namespace math {
template <class T>
T SimpsonIntegral(T l, T r, Function<T(T)> y, T eps = 1e-10,
                  T threshold = 1e50) {
  static_assert(is_floating_point_v<T>);
  var simpson = [&](T l, T r) {
    return (r - l) / 6 * (y(l) + 4 * y((l + r) / 2) + y(r));
  };
  var dfs = [&](var &dfs, T l, T r, T totalArea) {
    Assert(!std::isnan(totalArea));
    T m = (l + r) / 2;
    T lArea = simpson(l, m);
    T rArea = simpson(m, r);
    if (r - l <= threshold && Abs(lArea + rArea - totalArea) <= 15 * eps) {
      return lArea + rArea + (lArea + rArea - totalArea) / 15;
    }
    return dfs(dfs, l, m, lArea) + dfs(dfs, m, r, rArea);
  };
  return dfs(dfs, l, r, simpson(l, r));
}
}  // namespace math
}  // namespace dalt
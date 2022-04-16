#include "dsu.cpp"
#include "root_tree.cpp"
namespace dalt {
namespace graph {
template <class E>
enable_if_t<is_base_of_v<BiBaseEdge, E>, Tuple<i32, i32, i32>>
TreeDiameter(const Graph<E> &g) {
  auto depth0 = DepthOnTree(g, [&](i32 i) { return i == 0; });
  int a = *std::max_element(All(depth0));
  auto depth1 = DepthOnTree(g, [&](i32 i) { return i == a; });
  int b = *std::max_element(All(depth1));
  return Tuple<i32, i32, i32>(depth1[b], a, b);
}
template <class T, class E>
enable_if_t<is_base_of_v<BiBaseEdge, E> && is_base_of_v<WithWeight<T>, E>,
            Tuple<T, i32, i32>>
TreeDiameterWeight(const Graph<E> &g) {
  auto depth0 = DepthOnTreeWeight<T>(g, [&](auto i) { return i == 0; });
  int a = std::max_element(All(depth0)) - depth0.begin();
  auto depth1 = DepthOnTreeWeight<T>(g, [&](auto i) { return i == a; });
  int b = std::max_element(All(depth1)) - depth1.begin();
  return Tuple<T, i32, i32>(depth1[b], a, b);
}
template <class E>
enable_if_t<is_base_of_v<BiBaseEdge, E>, Tuple<i32, i32, i32>>
ForestDiameter(const Graph<E> &g) {
  int n = Size(g);
  DSU dsu(n);
  for (int i = 0; i < n; i++) {
    for (auto &e : g[i]) {
      dsu.merge(i, e.to);
    }
  }
  auto depth0 = DepthOnTree(g, [&](auto i) { return dsu.find(i) == i; });
  Vec<i32> roots(n, -1);
  for (int i = 0; i < n; i++) {
    int p = dsu.find(i);
    if (roots[p] == -1 || depth0[roots[p]] < depth0[i]) {
      roots[p] = i;
    }
  }
  auto depth1 = DepthOnTree(g, [&](auto i) { return roots[dsu.find(i)] == i; });
  int b = *std::max_element(All(depth1));
  return Tuple<i32, i32, i32>(depth1[b], roots[dsu.find(b)], b);
}
template <class T, class E>
enable_if_t<is_base_of_v<WithWeight<T>, E> && is_base_of_v<BiBaseEdge, E>,
            Tuple<T, i32, i32>>
ForestDiameter(const Graph<E> &g) {
  int n = Size(g);
  DSU dsu(n);
  for (int i = 0; i < n; i++) {
    for (auto &e : g[i]) {
      dsu.merge(i, e.to);
    }
  }
  auto depth0 = DepthOnTree(g, [&](auto i) { return dsu.find(i) == i; });
  Vec<i32> roots(n, -1);
  for (int i = 0; i < n; i++) {
    int p = dsu.find(i);
    if (roots[p] == -1 || depth0[roots[p]] < depth0[i]) {
      roots[p] = i;
    }
  }
  auto depth1 = DepthOnTree(g, [&](auto i) { return roots[dsu.find(i)] == i; });
  int b = *std::max_element(All(depth1));
  return Tuple<T, i32, i32>(depth1[b], roots[dsu.find(b)], b);
}
} // namespace graph
} // namespace dalt
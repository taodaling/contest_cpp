#pragma once
#include "graph.cpp"
namespace dalt {
namespace graph {
// O(V)
Vec<bool> MaximumIndependentSetFromMinimumVertexCover(Vec<bool> minimum_vertex_cover) {
  for (int i = 0; i < Size(minimum_vertex_cover); i++) {
    minimum_vertex_cover[i] = !minimum_vertex_cover[i];
  }
  return minimum_vertex_cover;
}
}  // namespace graph
}  // namespace dalt
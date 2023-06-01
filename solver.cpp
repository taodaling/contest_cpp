#pragma once
#include "common.cpp"
using namespace dalt;
#include "bound_flow.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int H, W;
  in >> H >> W;
  Vec<String> mat(H);
  in >> mat;
  var id_of = [&](int i, int j) { return i * W + j; };
  var src = H * W;
  var dst = src + 1;
  using namespace graph;
  using E = BoundFlowEdge<int>;
  int dirs[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  Graph<E> g(H * W + 2);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      if (mat[i][j] == '1') {
        continue;
      }
      if ((i + j) % 2 == 0) {
        AddBoundFlowEdge(g, src, id_of(i, j), 1, mat[i][j] == '2');
      } else {
        AddBoundFlowEdge(g, id_of(i, j), dst, 1, mat[i][j] == '2');
      }
      if ((i + j) % 2 == 0) {
        for (var &d : dirs) {
          int ni = i + d[0];
          int nj = j + d[1];
          if(ni < 0 || ni >= H || nj < 0 || nj >= W || mat[ni][nj] == '1') {
            continue;
          }

          AddBoundFlowEdge(g, id_of(i, j), id_of(ni, nj), 1, 0);
        }
      }
    }
  }
  if (FeasibleFlow(g, src, dst)) {
    out << "Yes";
  } else {
    out << "No";
  }
}

void SolveMulti(IStream &in, OStream &out) {
  // std::ifstream input("in");
  int num_of_input = 1;
  // in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    // SolveOne(i + 1, input, out);
    SolveOne(i + 1, in, out);
  }
}
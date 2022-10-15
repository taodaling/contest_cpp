#pragma once
#include "common.cpp"
using namespace dalt;
#include "D:\source\contest_cpp\internal\decomposed_permutation_tree.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;
  Vec<int> P(N);
  in >> P;
  int total = 0;
  var root = BuildDecomposedPermutationTree(P, [&]() {
    total++;
    return new DecomposedPermutationTree();
  });
  int id_allocator = 0;
  var dfs = [&](var &dfs, DecomposedPermutationTree *root) -> void {
    int id = id_allocator++;
    out << ' ' << root->ll << ' ' << root->rr << ' '
        << (root->join ? "linear" : "prime") << '\n';
    for (var node : root->adj) {
      out << id;
      dfs(dfs, node);
    }
  };
  out << total << '\n' << -1;
  dfs(dfs, root);
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}
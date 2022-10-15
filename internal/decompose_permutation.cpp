#pragma once
#include "common.cpp"
namespace dalt {
struct DecompsePermutation {
  //in each run, groups[i][j] => groups[i][j + 1]
  Vec<Vec<int>> groups;
  Vec<Array<int, 2>> ids;
  DecompsePermutation(Vec<int> perm) {
    int n = Size(perm);
    Vec<bool> visited(n);
    Vec<int> buf(n);
    ids.resize(n);
    auto add = [&](int x) {
      ids[x][0] = Size(groups);
      ids[x][1] = Size(buf);
      buf.push_back(x);
      visited[x] = true;
    };
    for (int i = 0; i < n; i++) {
      if (visited[i]) {
        continue;
      }
      buf.clear();
      int iter = i;
      while (!visited[iter]) {
        add(iter);
        iter = perm[iter];
      }
      groups.push_back(buf);
    }
  }
  Vec<Vec<int>> to_vec() const { return groups; }
  struct PowView {
    u64 k;
    const DecompsePermutation* ptr;
    int operator[](int i) const {
      auto &g = ptr->groups[ptr->ids[i][0]];
      return g[(ptr->ids[i][1] + k) % Size(g)];
    }
  };
  PowView pow(u64 k = 0) const {
    return PowView{
        .k = k,
        .ptr = this,
    };
  }
};
}  // namespace dalt
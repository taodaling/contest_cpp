#pragma once
#include "common.cpp"
using namespace dalt;
#include "cartesian_tree.cpp"
#include "binary_search.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, Q;
  in >> N >> Q;
  Vec<int> P(N);
  Vec<int> A(N);
  in >> P >> A;
  int K = 0;
  for(int a : A) {
    K += a == 0;
  }
  Vec<int> S(K - 1);
  in >> S;
  using Node = CartesianTree;
  Node *root = Node::from(N, [&](int a, int b) {return P[a] > P[b];});
  bool ok = true;
  Vec<Pair<int, int>> intervals;
  var dfs = [&](var &dfs, Node *root, int max_from_ancestor) -> int {
    if(root == NULL) {
      return 0;
    }
    int index = root->index;
    if(A[index] > 0) {
      if(max_from_ancestor <= A[index]) {
        ok = false;
      }
      max_from_ancestor = A[index];
    }
    int left = dfs(dfs, root->left, max_from_ancestor);
    int right = dfs(dfs, root->right, max_from_ancestor);
    int max_from_children = Max(left, right);
    if(A[index] > 0) {
      if(max_from_children >= A[index]) {
        ok = false;
      }
      max_from_children = A[index];
    } else {
      intervals.push_back(MakePair(max_from_children, max_from_ancestor));
    }
    return max_from_children;
  };
  MakeUniqueAndSort(S);
  ok = ok && Size(S) == K - 1;
  Sort(All(intervals), [&](var &a, var &b) {
    return a.second < b.second;
  });
  var try_solution = [&](Vec<int> pts, Vec<Pair<int, int>> intervals, bool chance) -> Pair<int, int> {
    Pair<int, int> ans(0, 1e9);
    MultiTreeSet<int> pts_set;
    for(var x : pts) {
      pts_set.insert(x);
    }
    for(var &interval : intervals) {
      var iter = pts_set.lower_bound(interval.first + 1);
      if(iter == pts_set.end() || *iter >= interval.second) {
        if(chance) {
          chance = false;
          ans = interval;
        } else {
          return MakePair(0, -1);
        }
      } else {
        pts_set.erase(iter);
      }
    }
    return ans;
  };
  var extra = try_solution(S, intervals, true);
  if(extra.first > extra.second) {
    ok = false;
  }
  Pair<int, int> range(-1, -1);
  if(ok) {
    var checker = [&](int M) {
      Vec<int> data;
      data.reserve(K);
      data.insert(data.end(), All(S));
      data.push_back(M);
      var ans = try_solution(data, intervals, false);
      return ans.first <= ans.second;
    };
    int L = FirstTrue<int>(0, extra.first + 1, checker);
    int R = LastTrue<int>(extra.second - 1, (int)1e6, checker);
    range = MakePair(L, R);
  }
  
}

void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}

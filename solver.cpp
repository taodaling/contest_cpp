#pragma once
#include "common.cpp"
using namespace dalt;
#include "cartesian_tree.cpp"
#include "math.cpp"
#include "prefix_sum.cpp"
#include "fenwick_tree_ext.cpp"
#include "interval_map.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, Q;
  in >> N >> Q;
  Vec<int> P(N);
  in >> P;
  Vec<int> A(N);
  in >> A;
  using Node = CartesianTree;
  var root = CartesianTree::from(N, [&](int i, int j) { return P[i] > P[j]; });
  bool ok = true;
  Vec<Pair<int, int>> range;
  var dfs = [&](var &dfs, Node *root, int max_from_p) -> int {
    if(root == NULL) {
      return 0;
    }
    if(A[root->index] != 0) {
      if(max_from_p <= A[root->index]) {
        ok = false;
      }
      Chmin(max_from_p, A[root->index]);
    }
    int max_left = dfs(dfs, root->left, max_from_p);
    int max_right = dfs(dfs, root->right, max_from_p);
    int max_child = Max(max_left, max_right);
    if (A[root->index] != 0) {
      if (max_child >= A[root->index]) {
        ok = false;
      }
      Chmax(max_child, A[root->index]);
    } else {
      range.push_back(MakePair(max_child, max_from_p));
    }
    return max_child;
  };
  dfs(dfs, root, 1e9);
  for(var &r : range) {
    if(r.first + 1 >= r.second) { 
      ok = false;
    }
  }
  Vec<int> existing;
  int k = 0;
  for(int i = 0; i < N; i++) {
    if(A[i] != 0) {
      existing.push_back(A[i]);
    } else {
      k++;
    }
  }
  Vec<int> S(k - 1);
  in >> S;
  existing.insert(existing.end(), All(S));
  MakeUniqueAndSort(existing);
  if(Size(existing) != N - 1) {
    ok = false;
  }
  Sort(All(S));
  Vec<int> begin(k - 1);
  Vec<int> end(k - 1);
  Vec<Pair<int, int>> bs_range;
  for(var &r : range) {
    int index_begin = UpperBound(All(S), r.first) - S.begin();
    int index_end = LowerBound(All(S), r.second) - S.begin();
    if(index_begin < index_end) {
      if (index_begin < k - 1) {
        begin[index_begin]++;
      }
      if(index_end < k - 1) {
        end[index_end]++;
      }
    }
    bs_range.push_back(MakePair(index_begin, index_end));
  }
  Debug(begin);
  Debug(end);
  Debug(range);
  PrefixSum<int> begin_ps(k - 1, MakeIndexer<int>(begin));
  PrefixSum<int> end_ps(k - 1, MakeIndexer<int>(end));
  int inf = 1e9;
  int min_x_r = inf;
  int min_x_r_index = k;
  Line(ft);
  FenwickTreeExt<i64> ft(k + 1);
  for(int i = k - 2; i >= 0; i--) {
    int x = begin_ps.prefix(i);
    if(min_x_r > x - i) {
      min_x_r = x - i;
      min_x_r_index = i;
    }
    if(min_x_r < end_ps.prefix(i) - i + 1) {
      ok = false;
    } else if (min_x_r == end_ps.prefix(i) - i + 1) {
      Assert(i <= min_x_r_index);
      ft.update(i, min_x_r_index, 1);
    }
  }
  Debug(ft.to_vec());
  Debug(bs_range);
  Line(im);
  IntervalMap<int> im;
  if(ok) {
    var iter = bs_range.begin();
    for(var &r : range) {
      if(ft.query(iter->first, iter->second - 1) == 0) {
        im.add(r.first + 1, r.second);
      }
      ++iter;
    }
  }
  Debug(im.to_vec());
  Line(solve);
  for(int i = 0; i < Q; i++) {
    int x;
    in >> x;
    var iter = LowerBound(All(existing), x);
    if((iter == existing.end() || *iter != x) && im.cover_line(x).is_some()) {
      out << "YES";
    } else {
      out << "NO";
    }
    out << '\n';
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
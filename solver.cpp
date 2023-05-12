#pragma once
#include "common.cpp"
using namespace dalt;
#include "math.cpp"
#include "trie.cpp"
const int C = 27;
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N;
  in >> N;
  using Tr = trie::Trie<i64, C>;
  Tr::Register(0);
  var tree = new Tr();
  Trace(input);
  for (int i = 0; i < N; i++) {
    Str T;
    i64 P;
    in >> T >> P;
    Reverse(All(T));
    var iter = tree;
    for (var c : T) {
      iter = iter->get_or_create(c - 'a');
    }
    iter->sum = P;
  }
  Vec<Vec<Vec<i64>>> profit(C, Vec<Vec<i64>>(C, Vec<i64>(C)));
  for (int i = 0; i < C; i++) {
    for (int j = 0; j < C; j++) {
      for (int k = 0; k < C; k++) {
        var iter = tree;
        for (var c : Vec<int>{k, j, i}) {
          iter = iter->get_or_create(c);
          profit[i][j][k] += iter->sum;
        }
      }
    }
  }

  i64 inf = 1e18;
  Vec<Vec<i64>> dists(C, Vec<i64>(C, -inf));
  Vec<Vec<bool>> inq(C, Vec<bool>(C));
  Vec<Vec<int>> inq_times(C, Vec<int>(C));
  dists[C - 1][C - 1] = 0;
  using A2 = Array<int, 2>;
  Deque<A2> dq;

  var add = [&](int i, int j) {
    if (!inq[i][j]) {
      inq[i][j] = true;
      inq_times[i][j]++;
      dq.push_back(A2{i, j});
    }
  };
  add(C - 1, C - 1);
  while (!dq.empty()) {
    var head = dq.front();
    dq.pop_front();
    inq[head[0]][head[1]] = false;
    if (inq_times[head[0]][head[1]] > Size(dists)) {
      out << "Infinity";
      return;
    }
    for (int i = 0; i < C - 1; i++) {
      if (dists[head[1]][i] <
          dists[head[0]][head[1]] + profit[head[0]][head[1]][i]) {
        dists[head[1]][i] =
            dists[head[0]][head[1]] + profit[head[0]][head[1]][i];
        add(head[1], i);
      }
    }
  }

  Debug(dists);
  i64 max = -inf;
  for (int i = 0; i < C; i++) {
    for (int j = 0; j < C; j++) {
      if(i == C - 1 && j == C - 1) {
        continue;
      }
      Chmax(max, dists[i][j]);
    }
  }
  out << max << '\n';
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
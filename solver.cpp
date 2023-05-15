#pragma once
#include "common.cpp"
using namespace dalt;
#include "min_queue.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, M;
  in >> N >> M;
  TreeMap<int, int> cnts;
  int current = 0;
  for(int i = 0; i < N; i++) {
    int a, b;
    in >> a >> b;
    cnts[b - a]++;
    current += a;
  }
  int inf = 1e9;
  Vec<int> min_cost(M + 1, inf);
  Debug(current);
  min_cost[current] = 0;
  MinQueue<int> mq;
  Debug(min_cost);
  for(var p : cnts) {
    var v = p.first;
    var c = p.second;
    if(v == 0) {
      continue;
    }
    Vec<int> next(M + 1, inf);
    if(v > 0) {
      for(int i = 0; i < v; i++) {
        mq.clear();
        for(int j = i; j <= M; j += v) {
          mq.push_back(min_cost[j] - j / v);
          next[j] = mq.min() + j / v;
          if(j - c * v >= 0) {
            mq.pop_front();
          }
        }
        Debug(i);
        Debug(next);
      }
    } else {
      v = -v;
      for(int i = 0; i < v; i++) {
        mq.clear();
        for(int j = M - i; j >= 0; j -= v) {
          mq.push_back(min_cost[j] + j / v);
          next[j] = mq.min() - j / v;
          if(j + c * v <= M) {
            mq.pop_front();
          }
        }
      }
    }
    min_cost = Move(next);
    Debug(p);
    Debug(min_cost);
  }

  for(int i = 0; i <= M; i++) {
    if(min_cost[i] > N) {
      out << -1;
    } else {
      out << min_cost[i];
    }
    out << ' ';
  }
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
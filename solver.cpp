#pragma once
#include "common.cpp"
using namespace dalt;
#include "binary_search.cpp"
void SolveOne(int test_id, IStream &in, OStream &out) {
  int MAX = 600;
  int N;
  in >> N;
  Vec<Tuple<int, int, int>> stus;
  for(int i = 0; i < N; i++) {
    int a, b, c;
    in >> a >> b >> c;
    stus.emplace_back(a, b, c);
  }
  Sort(All(stus), [&](var &a, var &b) {
    return Get0(a) < Get0(b);
  });
  var checker = [&](int start) {
    int cur = start;
    Deque<Tuple<int, int>> heap;
    var iter = stus.begin();
    while(Size(heap) > 0 || iter != stus.end()) {
      while(iter != stus.end() && Get0(*iter) + start <= cur) {
        heap.emplace_back(Get2(*iter), Get1(*iter));
        ++iter;
      }
      if(heap.empty()) {
        Debug(*iter);
        cur = Get0(*iter) + start;
      } else {
        var top = heap.front();
        heap.pop_front();
        if(Get1(top) + cur > Get0(top)) {
          return false;
        }
        cur += Get1(top);
      }
    }
    return true; 
  };
  var last_true = LastTrue<int>(-1e9, 0, checker);
  Debug(last_true);
  out << -(*last_true);
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
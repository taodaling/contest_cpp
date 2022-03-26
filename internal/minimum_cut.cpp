#pragma once
#include "flow.cpp"
namespace dalt {
namespace graph {
  //g should be max flow (it means there is no augment path from s to t)
  //time complexity: O(V+E)
  template<class E>
  IsFlow(E, Vec<bool>) FindSetST(const Graph<E> &g, int s, int t) {
    int n = Size(g);
    Vec<bool> res(n);
    Deque<int> dq;
    dq.push_back(s);
    res[s] = true;
    while(!dq.empty()) {
      int head = dq.front();
      dq.pop_front();
      for (auto &e : g[head]) {
        if(g[e.to][e.rev].flow > 0 && !res[e.to]) {
          res[e.to] = true;
          dq.push_back(e.to);
        }
      }
    }
    Assert(!res[t]);
    return res;
  } 
}
}  // namespace dalt
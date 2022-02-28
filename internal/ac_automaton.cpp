#pragma once
#include "common.cpp"
namespace dalt {
namespace seq {
template <int C = 26>
struct ACAutomaton {
  Vec<Array<i32, C>> next;
  Vec<i32> fails;

 private:
  int alloc_indicator;
  void init() { alloc_indicator = 1; }
  int alloc() { return alloc_indicator++; }

 public:
  int size() { return alloc_indicator; }
  ACAutomaton(int cap) {
    next.resize(cap + 1);
    fails.resize(cap + 1);
    init();
  }

  struct Builder {
    int build_last;
    ACAutomaton* ac;
    void build(int c) {
      if (ac->next[build_last][c] == 0) {
        ac->next[build_last][c] = ac->alloc();
      }
      build_last = ac->next[build_last][c];
    }
  };
  Builder builder() {
    return Builder{
        .build_last = 0,
        .ac = this,
    };
  }

  struct Matcher {
    int match_last;
    ACAutomaton* ac;
    void match(int c) { match_last = ac->next[match_last][c]; }
  };
  Matcher matcher() {
    return Matcher{
        .match_last = 0,
        .ac = this,
    };
  }

  Vec<i32> topo_sort() {
    Vec<i32> dq(alloc_indicator);
    int dq_tail = 1;
    int dq_head = 1;
    fails[0] = -1;
    for (int i = 0; i < C; i++) {
      if (next[0][i] != 0) {
        dq[dq_tail++] = next[0][i];
        fails[next[0][i]] = 0;
      }
    }

    while (dq_head < dq_tail) {
      int head = dq[dq_head++];
      for (int i = 0; i < C; i++) {
        if (next[head][i] != 0) {
          dq[dq_tail++] = next[head][i];
          int fail = visit(fails[head], i);
          if (fail == -1) {
            fail = 0;
          } else {
            fail = next[fail][i];
          }
          fails[next[head][i]] = fail;
        }
      }
    }

    dq_tail = 1;
    dq_head = 1;
    for (int i = 0; i < C; i++) {
      if (next[0][i] != 0) {
        dq[dq_tail++] = next[0][i];
      }
    }
    while (dq_head < dq_tail) {
      int head = dq[dq_head++];
      for (int i = 0; i < C; i++) {
        if (next[head][i] != 0) {
          dq[dq_tail++] = next[head][i];
        } else {
          next[head][i] = next[fails[head]][i];
        }
      }
    }

    Reverse(All(dq));
    Assert(dq_tail == alloc_indicator);
    return dq;
  }

  int visit(int trace, int index) {
    while (trace != -1 && next[trace][index] == 0) {
      trace = fails[trace];
    }
    return trace;
  }
};
}  // namespace seq
}  // namespace dalt
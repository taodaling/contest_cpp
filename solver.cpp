#pragma once
#include "all"
using namespace dalt;
using real = long double;
void SolveOne(int test_id, IStream &in, OStream &out) {
  Str s;
  int N;
  in >> s >> N;
  hash::HashBase::ensure(N + Size(s));
  using HU = hash::HashUnit;
  using SBTR = sbt::SelfBalanceTreeRegistry<HU, Nil>;
  using Tp = sbt::Treap<SBTR>;
  Tp::Register(HU::nil(), Nil(), 
  [&](var& a, var& b) {
    return a + b;
  },
  [&](var& a, var &b) {
    return a;
  },
  [&](var &a, var &b) {
    return a;
  });
  Tp *root = Tp::NIL;
  for(char c : s) {
   // Debug(c);
    root = Tp::merge({root, new Tp(0, HU::of(c))});
  }
  var hash_range = [&](int l, int r) {
    var split1 = root->split_by_rank(r);
    var split2 = split1[0]->split_by_rank(l - 1);
    var ans = split2[1]->sum;
    split1[0] = Tp::merge(split2);
    root = Tp::merge(split1);
    //DebugFmtln("[%d, %d, %d] = %lld", l, r, ans.size, ans.val);
    return ans;
  };

  for(int i = 0; i < N; i++) {
    //Debug(root->to_vec());
    //Debug(i);
    char c;
    in >> c;
    if(c == 'Q') {
      int x, y;
      in >> x >> y;
      if(x > y) {
        Swap(x, y);
      }
      var pt = LastTrue<int>(0, root->size - y, [&](int len) {
        return hash_range(x, x + len) == hash_range(y, y + len);
      });
      if(pt.is_some()) {
        out << *pt + 1;
      } else {
        out << 0;
      }
      out << '\n';
    } else if(c == 'R') {
      char c;
      int x;
      in >> x >> c;
      var split1 = root->split_by_rank(x);
      var split2 = split1[0]->split_by_rank(x - 1);
      split2[1]->weight = HU::of(c);
      split2[1]->push_up();
      split1[0] = Tp::merge(split2);
      root = Tp::merge(split1);
    } else {
      char c;
      int x;
      in >> x >> c;
      var split1 = root->split_by_rank(x);
      split1[0] = Tp::merge(split1[0], new Tp(0, HU::of(c)));
      root = Tp::merge(split1);
    }
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
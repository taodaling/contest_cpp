#pragma once
#include "../common.cpp"
#include "optional.cpp"
namespace dalt {
namespace trie {
template <class S, int C = 26, int ID = 0> struct Trie {
  using Self = Trie<S, C, ID>;
  static S s_nil;
  static void cinit(S _s_nil) { s_nil = _s_nil; }
  S sum;
  Self *next[C];
  Trie() : sum(s_nil) { memset(next, 0, sizeof(Self *) * C); }
  Self *get_or_create(int index) {
    if (next[index] == NULL) {
      next[index] = new Self();
    }
    return next[index];
  }
  Optional<Self *> get(int index) {
    if (next[index] == NULL) {
      return {};
    } else {
      return next[index];
    }
  }
  bool exist(int index) { return next[index] != NULL; }
  Self *operator[](int index) { return get_or_create(index); }
};
template <class S, int C, int ID> S Trie<S, C, ID>::s_nil = S();
} // namespace trie
using trie::Trie;
} // namespace dalt
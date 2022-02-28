#pragma once
#include "common.cpp"
namespace dalt {
namespace seq {
template <class T>
struct KMP {
  Vec<T> data;
  Vec<int> fail;

  KMP(int cap = 0) {
    cap += 1;
    data.reserve(cap);
    data.resize(1);
    fail.reserve(cap);
    fail.push_back(-1);
  }

  int size() const { return data.size() - 1; }

  void build(T c) {
    fail.push_back(visit(c, fail.back()) + 1);
    data.push_back(c);
  }

  // length of longest suffix(not whole) which is also a prefix
  int max_border(int i) const { return fail[i + 1]; }

  struct Matcher {
    int match_length;
    KMP &kmp;
    
    bool match_fully() const { return match_length == kmp.size(); }
    void match(T c) { 
      if(match_fully()) {
        match_length = kmp.fail[match_length];
      }
      match_length = kmp.visit(c, match_length) + 1; }
    int get_match_length() const { return match_length; }
  };

  Matcher matcher() {
    return Matcher{
        .match_length = 0,
        .kmp = *this,
    };
  }

 private:
  int visit(T c, int trace) const {
    while (trace >= 0 && data[trace + 1] != c) {
      trace = fail[trace];
    }
    return trace;
  }
};
}  // namespace seq
}  // namespace dalt
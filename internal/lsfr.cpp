#pragma once
#include "common.cpp"
namespace dalt {
template <class T> struct LinearFeedbackShiftRegister {
  Vec<T> cm;
  i32 m;
  T dm;
  Vec<T> cn;
  Vec<T> seq;

  LinearFeedbackShiftRegister(i32 cap) {
    seq.reserve(cap + 1);
    m = -1;
    cn.push_back(T(1));
  }

  void push(T x) {
    let n = Size(seq);
    seq.push_back(x);
    let dn = estimate_delta();
    if(dn == T(0)) {
      return;
    }
    if(m == -1) {
      cm = cn;
      dm = dn;
      m = n;
      cn.resize(n + 2, T(0));
      return;
    }
    let ln = Size(cn) - 1;
    let len = Max(ln, n + 1 - ln);
    let buf = Vec<T>(len + 1);
    for(int i = 0; i < Size(cn); i++) {
      buf[i] = cn[i];
    }
    T factor = dn / dm;
    for(int i = n - m, R = n - m + Size(cm); i < R; i++) {
      buf[i] = buf[i] - factor * cm[i - (n - m)];
    }
    if(Size(cn) < Size(buf)) {
      cn.swap(cm);
      m = n;
      dm = dn;
    }
    cn = buf;
  }
  //[1, -c1, -c2, ...]
  const Vec<T>& to_vec() const {
    return cn;
  }


private:
  T estimate_delta() const {
    T ans = T(0);
    i32 n = Size(seq) - 1;
    for (int i = 0; i < Size(cn); i++) {
      ans = ans + cn[i] * seq[n - i];
    }
    return ans;
  }
};
} // namespace dalt
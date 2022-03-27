#pragma once
#include "common.cpp"
#include "tag.cpp"
namespace dalt {
// verified by:
//  - https://www.luogu.com.cn/problem/P1886
template <class T, class COMPARER = Less<T>, bool SUPPORT_MAX = false>
struct MinQueue {
 private:
  // maintain incremental sequence
  Deque<T> data;
  Deque<T> inc;
  Deque<T> dec;
  COMPARER comparer;

  IsBool(SUPPORT_MAX, void) push_max(const T& x) {
    while (!dec.empty() && comparer(dec.back(), x)) {
      dec.pop_back();
    }
    dec.push_back(x);
  }

  IsBool(!SUPPORT_MAX, void) push_max(const T& x) {}
  IsBool(SUPPORT_MAX, void) pop_max(const T& x) {
    // dec.front() >= x
    if (!comparer(x, dec.front())) {
      dec.pop_front();
    }
  }
  IsBool(!SUPPORT_MAX, void) pop_max(const T& x) {}

 public:
  MinQueue(COMPARER _comparer = COMPARER()) : comparer(_comparer) {}
  void push_back(T x) {
    data.push_back(x);
    while (!inc.empty() && comparer(x, inc.back())) {
      inc.pop_back();
    }
    inc.push_back(x);
    push_max(x);
    // Debug(inc);
    // Debug(dec);
  }
  const T& front() const { return data.front(); }
  T& front() { return data.front(); }
  void pop_front() {
    T ans = data.front();
    data.pop_front();
    // inc.front() >= ans
    if (!comparer(inc.front(), ans)) {
      inc.pop_front();
    }
    pop_max(ans);
  }
  bool empty() const { return data.empty(); }
  decltype(data.size()) size() const { return data.size(); }
  const T& min() const { return inc.front(); }
  IsBool(SUPPORT_MAX, const T&) max() const { return dec.front(); }
};
}  // namespace dalt
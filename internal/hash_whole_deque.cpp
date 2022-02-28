#pragma once
#include "hash_base.cpp"
namespace dalt {
namespace hash {
template <class T>
struct HashWholeDeque {
  static_assert(is_integral_v<T>);
  using Mi = HashBase::Mi;
  Deque<T> dq;
  Mi sum;
  void push_back(T x) {
    sum = sum + HashBase::pow(Size(dq)) * Mi(x);
    dq.push_back(x);
  }
  void push_front(T x) {
    sum = sum * HashBase::x + x;
    dq.push_front(x);
  }
  void clear() {
    dq.clear();
    sum = Mi();
  }
  bool empty() const { return dq.empty(); }
  int size() const { return dq.size(); }
  const T& front() const { return dq.front(); }
  const T& back() const { return dq.back(); }
  void pop_back() {
    sum = sum - HashBase::pow(Size(dq) - 1) * Mi(dq.back());
    dq.pop_back();
  }
  void pop_front() {
    sum = (sum - Mi(dq.front())) * HashBase::inv_x;
    dq.pop_front();
  }
  i64 hash() const { return sum.value; }
  i64 hash_verbose() const { return HashBase::verbose(sum, Size(dq)).value; }
};
}  // namespace hash
}  // namespace dalt
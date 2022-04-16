#pragma once
#include "common.cpp"
namespace dalt {
template <class T, class F>
Vec<T> Cast(const Vec<F>& data) {
  int n = Size(data);
  Vec<T> ans;
  ans.reserve(n);
  for (int i = 0; i < n; i++) {
    ans.push_back(T(data[i]));
  }
  return ans;
}
template <class V, class C, class K>
V GetOrDefault(const C& data, const K& key, const V& def = V()) {
  auto res = data.find(key);
  if (res == data.end()) {
    return def;
  }
  return res->second;
}
template <class V, class C>
V PopFront(C& data) {
  V res = V(data.front());
  data.pop_front();
  return res;
}
template <class V, class C>
V PopBack(C& data) {
  V res = V(data.back());
  data.pop_back();
  return res;
}
}  // namespace dalt
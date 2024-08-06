#pragma once
#include "common.cpp"

namespace dalt {
template <class T, class C>
Indexer<T> MakeIndexer(const C &data) {
  return [&](auto i) -> T { return data[i]; };
}
template <class T, class C>
Indexer<T> MakeReverseIndexer(const C &data) {
  return [&](auto i) -> T { return data[Size(data) - 1 - i]; };
}
template <class T>
Vec<T> ExpandIndexer(int n, const Indexer<T> &indexer) {
  Vec<T> ans;
  ans.reserve(n);
  for (int i = 0; i < n; i++) {
    ans.push_back(indexer(i));
  }
  return ans;
}
Indexer<i32> SelfIndexer() {
  return [](auto i) { return i; };
}
template <class T>
Indexer<T> ConstantIndexer(const T &val) {
  return [=](auto i) { return val; };
}
template <class A, class B>
Mapper<A, B> ConstructorMapper() {
  return [&](auto a) { return B(a); };
}
template <class T>
Adder<T> NaturalAdder() {
  return [](auto a, auto b) { return a + b; };
}
template <class A, class B, class C>
constexpr Adder<A, B, C> EmptyAdder() {
  return [](auto a, auto b) { return C(); };
}
template <class A, class B = A>
constexpr Adder<A, B, A> ReturnLeftAdder() {
  return [](auto a, auto b) { return a; };
}
template <class A, class B = A>
constexpr Adder<A, B, B> ReturnRightAdder() {
  return [](auto a, auto b) { return b; };
}
template <class T>
Indexer<int> BinaryIndexer(const T& val) {
  return [=](int i) {return int((val >> i) & 1);};
}
template <class T>
Indexer<int> ReverseIndexer(int n, Indexer<T> indexer) {
  return [=](int i) {return indexer(n - 1 - i);};
}
Vec<int> MakeIndexVec(int n) {
  Vec<int> ans(n);
  for(int i = 0; i < n; i++) ans[i] = i;
  return ans;
}
}  // namespace dalt
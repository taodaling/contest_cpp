#pragma once
#include "std_include.cpp"
template <class T, int S>
struct MDVecDef {
  using Type = std::vector<typename MDVecDef<T, S - 1>::Type>;

  template <typename... Args>
  static Type Make(int n, Args... args) {
    return Type(n, typename MDVecDef<T, S - 1>::Make(args));
  }
};
template <class T>
struct MDVecDef<T, 0> {
  using Type = T;
  static Type Make(T val = T()) { return val; }
};
template <class T, int S = 1>
using MDVec = typename MDVecDef<T, S>::Type;
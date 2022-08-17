#pragma once
#include "common.cpp"
#include "math.cpp"
namespace dalt {
  template<class T>
  struct Radix {
    Vec<T> base;
    Radix(T x) {
      static const T MAX_VALUE =
          std::numeric_limits<T>::max();
      base.push_back(1);
      T y;
      while((y = MulLimit(base.back(), x, MAX_VALUE, T(0))) != T(0)) {
        base.push_back(y);
      }
    }
    T get(T x, int kth) const {
      if(kth >= Size(base)) {
        return T(0);
      }
      return x / base[kth] % base[1];
    }
    T set(T x, int kth, T val) const {
      return x + (val - get(x, kth)) * base[kth];
    }
  };
}
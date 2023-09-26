#pragma once
#include "common.cpp"
#include "number.cpp"
namespace dalt {
  template<class T, class E, class C = Less<E>>
  enable_if_t<is_integral_v<T>, T> TernarySearchArgMax(T l, T r, const Function<E(T)> &f, const C &c = C()) {
    while(r - l > 2) {
      var ml = l + DivFloor(r - l, T(3));
      var mr = r - DivCeil(r - l, T(3));
      if(c(f(ml), f(mr))) {
        l = ml;
      } else {
        r = mr;
      }
    }
    while(l < r) {
      if(!c(f(l), f(r))) {
        r--;
      } else {
        l++;
      }
    }
    return l;
  }
  template <class T, class E, class C = Less<E>>
  enable_if_t<is_floating_point_v<T>, T> TernarySearchArgMax(T l, T r,
                                                       const Function<E(T)> &f,
                                                       int round = 100,
                                                       const C &c = C()) {
    while(round-- > 0) {
      T dist = (r - l) / 3;
      var ml = l + dist;
      var mr = r - dist;
      if (c(f(ml), f(mr))) {
        l = ml;
      } else {
        r = mr;
      }
    }
    return (l + r) / 2;
  }
}
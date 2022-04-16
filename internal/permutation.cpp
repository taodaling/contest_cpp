#pragma once
#include "common.cpp"
namespace dalt {
struct Permutation : public Vec<int> {
  using Self = Permutation;
  Permutation(int n = 0) : Permutation(Vec<int>(n)) {}
  Permutation(Vec<int> data) : Vec<int>(Move(data)) {}
  friend Self operator+(const Self &a, const Self &b) {
    int n = Size(a);
    Self res(n);
    for (int i = 0; i < n; i++) {
      res[i] = b[a[i]];
    }
    return res;
  }
  friend Self operator*(const Self& a, const Self& b) {
    return a + b;
  }
  friend bool operator<(const Self &a, const Self &b) {
    if(Size(a) != Size(b)) {
      return Size(a) < Size(b);
    }
    for (int i = 0; i < Size(a); i++) {
      if (a[i] < b[i]) {
        return true;
      }
      if (a[i] > b[i]) {
        return false;
      }
    }
    return false;
  }
  ImplDefaultComparision(Self);
  Vec<int> to_vec() const { return Vec<int>(*this); }
  template<class E>
  Vec<E> apply(const Vec<E>& data) const {
    Vec<E> res(Size(data));
    for(int i = 0; i < Size(data); i++) {
      res[i] = data[(*this)[i]];
    }
    return res;
  }
};
}
#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct VersionArray {
  using Self = VersionArray<T>;
  Vec<T> data;
  Vec<int> version;
  int timestamp = 0;
  T def;
  VersionArray(int n, T _def = T()) : def(_def) {
    data = Vec<T>(n);
    version = Vec<int>(n);
    timestamp = 1;
  }
  void access(int i) {
    if (version[i] < timestamp) {
      version[i] = timestamp;
      data[i] = def;
    }
  }
  T& operator[](int i) {
    access(i);
    return data[i];
  }
  const T& operator[](int i) const {
    access(i);
    return data[i];
  }
  int size() { return Size(data); }
  void clear(T _def = T()) {
    def = _def;
    timestamp++;
  }
};
}  // namespace dalt
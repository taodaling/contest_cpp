#pragma once
#include "common.cpp"
#include "hashmap.cpp"
#include "nil.cpp"
namespace dalt {
namespace math {
template <class T, bool SWAP = false>
Vec<T> MonoidSpanningSet(int n, const Indexer<T>& indexer, T zero = T()) {
  Vec<T> data;
  data.reserve(n + 1);
  auto try_add = [&](const T& ele) {
    for (auto& v : data) {
      if (v == ele) {
        return;
      }
    }
    data.push_back(ele);
  };
  for (int i = 0; i < n; i++) {
    try_add(indexer(i));
  }
  for (int i = 0; i < Size(data); i++) {
    for (int j = 0; j <= i; j++) {
      try_add(data[i] + data[j]);
      if (!SWAP && i < j) {
        try_add(data[j] + data[i]);
      }
    }
  }
  try_add(zero);
  return data;
}
}  // namespace math
}  // namespace dalt
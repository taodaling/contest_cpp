#pragma once
#include "common.cpp"
namespace dalt {
namespace misc {
MakeAnnotation(factory);
template <class T>
struct Factory {
  Vec<T> data;
  const Indexer<T> &indexer;
  void ensure(int n) {
    if (Size(data) < n) {
      data.reserve(n);
      while (Size(data) < n) {
        data.push_back(indexer(Size(data)));
      }
    }
  }
  T get(int index) {
    ensure(index + 1);
    return data[index];
  }
  Factory(int cap, const Indexer<T> &_indexer) : indexer(_indexer) {
    ensure(cap);
  }
};
template <class T>
struct IndexerFactory {
  const Indexer<T> &indexer;
  IndexerFactory(const Indexer<T> &_indexer) : indexer(_indexer) {}
  void ensure(int n) {}
  T get(int i) { return indexer(i); }
};
template <class T>
struct is_factory<IndexerFactory<T>> {
  static const bool value = true;
};
}  // namespace misc
}  // namespace dalt
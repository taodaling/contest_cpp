#pragma once
#include "fenwick_tree.cpp"
#include "hash_base.cpp"
namespace dalt {
namespace hash {
template <class T>
struct HashRangeFenwickTree {
  static_assert(is_integral_v<T>);
  using Mi = HashBase::Mi;
  FenwickTree<Mi> ft;
  HashRangeFenwickTree(const Indexer<T>& data, i32 n) {
    HashBase::ensure(n + 1);
    ft = decltype(ft)([&](auto i) { return Mi(data(i)); }, n);
  }
  HashRangeFenwickTree(i32 n) : ft(n) { HashBase::ensure(n + 1); }
  //- time: O(\log n)
  void set(int index, T val) { ft.set(index, Mi(val) * HashBase::xp[index]); }
  //- time: O(\log n)
  i64 hash(int l, int r) const {
    return (ft.query(l, r) * HashBase::inv_xp[l]).value;
  }
  //- time: O(\log n)
  i64 hash_verbose(int l, int r) const {
    return ((ft.query(l, r) + HashBase::xp[r + 1]) * HashBase::inv_xp[l]).value;
  }
};
}  // namespace hash
}  // namespace dalt
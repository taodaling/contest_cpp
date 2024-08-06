#pragma once
#include "hash_base.cpp"
#include "hash_unit.cpp"
namespace dalt {
namespace hash {
template <class T>
struct HashRange {
  using Self = HashRange;
  using Mi = HashBase::Mi;
  Vec<Mi> data;
  HashRange(){}
  HashRange(int n, const Indexer<T>& s) {
    static_assert(is_integral_v<T>);
    HashBase::ensure(n + 2);
    data.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      data[i] = Mi(s(i - 1)) * HashBase::xp[i] + data[i - 1];
    }
  }
  HashUnit hash(int l, int r) const {
    if (l > r) {
      return HashUnit::nil();
    }
    return HashUnit{
        .val = (data[r + 1] - data[l]) * HashBase::inv_xp[l + 1],
        .size = r - l + 1,
    };
  }
};

};  // namespace hash
}  // namespace dalt
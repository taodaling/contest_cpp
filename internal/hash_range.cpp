#pragma once
#include "hash_base.cpp"
namespace dalt {
namespace hash {
template <class T>
struct HashRange {
  using Self = HashRange;
  using Mi = HashBase::Mi;
  Vec<Mi> data;
  HashRange(int n, const Indexer<T>& s) {
    static_assert(is_integral_v<T>);
    HashBase::ensure(n + 2);
    data.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      data[i] = Mi(s(i - 1)) * HashBase::xp[i] + data[i - 1];
    }
  }
  struct Range {
    Vec<Mi>& data;
    Mi sum;
    i32 size;

    Range& append(int l, int r) {
      if (l > r) {
        return *this;
      }
      sum = sum + (data[r + 1] - data[l]) * HashBase::pow(size - (l + 1));
      size += r - l + 1;
      return *this;
    }
    i64 hash() const { return sum.value; }
    i64 hash_verbose() const { return HashBase::verbose(sum, size).value; }
  };
  Range range() {
    return Range{
        .data = data,
        .sum = Mi(0),
        .size = 0,
    };
  }
  i64 hash(int l, int r) {
    if (l > r) {
      return 0;
    }
    return ((data[r + 1] - data[l]) * HashBase::inv_xp[l + 1]).value;
  }
  i64 hash_verbose(int l, int r) {
    if (l > r) {
      return 0;
    }
    return HashBase::verbose(((data[r + 1] - data[l]) * HashBase::inv_xp[l + 1]), r - l + 1).value;
  }
};

};  // namespace hash
}  // namespace dalt
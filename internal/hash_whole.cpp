#pragma once
#include "hash_base.cpp"
namespace dalt {
namespace hash {
template <class T>
struct HashWhole {
  static_assert(is_integral_v<T>);
  using Mi = HashBase::Mi;
  Vec<T> data;
  Mi sum;
  void HashWhole(i32 n) : data(n), sum(0) { HashBase::ensure(n + 1); }
  void set(i32 index, T x) {
    sum = sum + (Mi(x) - Mi(data[index])) * HashBase::xp[index];
    data[index] = x;
  }
  const T& get(i32 index) const { return data[index]; }
  i64 hash() const { return sum; }
  i64 hash_verbose() const { return HashBase::vebose(sum, Size(data)).value; }
};
}  // namespace hash
}  // namespace dalt
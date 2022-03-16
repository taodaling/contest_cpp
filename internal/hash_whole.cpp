#pragma once
#include "hash_base.cpp"
#include "rwelement.cpp"
namespace dalt {
namespace hash {
template <class T>
struct HashWhole {
  static_assert(is_integral_v<T>);
  using Self = HashWhole<T>;
  using Mi = HashBase::Mi;
  Vec<T> data;
  Mi sum;
  HashWhole(i32 n) : data(n), sum(0) { HashBase::ensure(n + 1); }
  void write(i32 index, const T& x) {
    sum = sum + (Mi(x) - Mi(data[index])) * HashBase::xp[index];
    data[index] = x;
  }
  const T& read(i32 index) const {
    return data[index];
  }
  RWElement<Self, T, int> operator[](i32 index) {
    return RWElement<Self, T, int>(this, index);
  }
  const T& operator[](i32 index) const { return read(index); }
  i64 hash() const { return sum.value; }
  i64 hash_verbose() const { return HashBase::verbose(sum, Size(data)).value; }
  Vec<T> to_vec() const {
    return data;
  }
};
}  // namespace hash
}  // namespace dalt
#pragma once
#include "hash_base.cpp"
namespace dalt {
namespace hash {
struct HashUnit {
  using Mi = HashBase::Mi;
  using Self = HashUnit;
  Mi val;
  int size;

  static Self nil() {
    return Self{
        .val = Mi(0),
        .size = 0,
    };
  }
  template<class T>
  static enable_if_t<is_integral_v<T>, Self> of(T val) {
    return Self {
      .val = Mi::of(val),
      .size = 1,
    };
  }
};
HashUnit operator+(const HashUnit& a, const HashUnit& b) {
  return HashUnit{.val = a.val + b.val * HashBase::xp[a.size],
                  .size = a.size + b.size};
}
bool operator==(const HashUnit& a, const HashUnit& b) {
  return a.val == b.val && a.size == b.size;
}
bool operator!=(const HashUnit& a, const HashUnit& b) {
  return !(a == b);
}
OStream& operator<<(OStream& os, const HashUnit& a) {
  os << "{" << a.val << ", " << a.size << "}";
  return os;
}
}  // namespace hash
}  // namespace dalt
#pragma once
#include "common.cpp"
namespace dalt {
template <class T>
struct XorValue {
  using Self = XorValue<T>;
  static_assert(is_integral_v<T>);
  T value;
  XorValue(T _value) : value(_value) {}
  bool operator==(const Self& rhs) { return value == rhs.value; }
  bool operator!=(const Self& rhs) { return value != rhs.value; }
  Self operator+(const Self& rhs) { return value ^ rhs.value; }
  Self operator-(const Self& rhs) { return value ^ rhs.value; }
};
template <class T>
OStream& operator<<(OStream& os, const XorValue<T>& rhs) {
  os << rhs.value;
  return os;
}
}  // namespace dalt
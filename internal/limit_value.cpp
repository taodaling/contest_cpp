#pragma once
#include "common.cpp"
#include "math.cpp"
namespace dalt {
template <class T, T MAX = std::numeric_limits<T>::max()>
struct LimitValue {
  static_assert(is_integral_v<T>);
  using Self = LimitValue<T, MAX>;
  T value;
  LimitValue(T _value = T(0)) : value(_value) {}
  bool is_max() const { return value == MAX; }
  Self operator*(const Self& rhs) const {
    return Self(MulLimit(value, rhs.value, MAX));
  }
  Self operator+(const Self& rhs) const {
    return Self(AddLimit(value, rhs.value, MAX));
  }
  bool operator<(const Self& rhs) const {
    return value < rhs.value;
  }
  ImplDefaultComparision(Self);
  ImplArithmeticAssignOperation(Self);
  Self operator==(const Self& rhs) const { return value == rhs.value; }
  Self operator!=(const Self& rhs) const { return !(*this == rhs); }
  template <class E>
  static enable_if_t<is_integral_v<E>, Self> from(const E& e) {
    return e >= MAX ? Self(MAX) : Self(T(e));
  }
  template <class E>
  enable_if_t<is_integral_v<E>, Self> pow(E exp) {
    if (value == T(0)) {
      return exp == E(0) ? T(1) : T(0);
    }
    if (value == T(1)) {
      return value;
    }
    if (exp >= sizeof(T) || value == MAX) {
      return MAX;
    }
    return PowBinaryLift(*this, exp);
  }
};
template <class T, T MAX>
OStream& operator<<(OStream& os, const LimitValue<T, MAX>& lv) {
  os << lv.value;
  return os;
}
}  // namespace dalt
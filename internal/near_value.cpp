#pragma once
#include "common.cpp"
#include "math.cpp"
namespace dalt {
MakeAnnotation(near_value);
template <class T, int EPS_DIGIT = 10, class F = f80>
struct NearValue {
  static_assert(is_floating_point_v<F>);
  using Self = NearValue<T, EPS_DIGIT, F>;
  using Type = T;
  using FType = F;
  struct AccurateComparer {
    bool operator()(const Self& lhs, const Self& rhs) const {
      return lhs.value < rhs.value;
    }
  };
  static constexpr F EPS = PowBinaryLift(F(0.1), EPS_DIGIT);
  T value;
  NearValue(T _value = T()) : value(_value) {}
  CastToAllScalar(value);
  static Self max() { return Self(std::numeric_limits<T>::max()); }
  static Self min() { return Self(std::numeric_limits<T>::min()); }
  static Self max(const Self& lhs, const Self& rhs) {
    return Self(Max(lhs.value, rhs.value));
  }
  static Self min(const Self& lhs, const Self& rhs) {
    return Self(Min(lhs.value, rhs.value));
  }
  Self operator+(const Self& rhs) const { return Self(value + rhs.value); }
  Self operator-(const Self& rhs) const { return Self(value - rhs.value); }
  Self operator*(const Self& rhs) const { return Self(value * rhs.value); }
  Self operator/(const Self& rhs) const { return Self(value / rhs.value); }
  template <class V>
  operator NearValue<V, EPS_DIGIT>() const {
    return NearValue<V, EPS_DIGIT>(value);
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, bool> operator==(
      const Self& rhs) const {
    auto delta = value - rhs.value;
    return delta >= -EPS && delta <= EPS;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, bool> operator==(
      const Self& rhs) const {
    return value == rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, bool> operator<(
      const Self& rhs) const {
    return value + EPS < rhs.value;
  }
  bool operator<=(const Self& rhs) const { return !(*this > rhs); }
  bool operator>=(const Self& rhs) const { return !(*this < rhs); }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, bool> operator<(
      const Self& rhs) const {
    return value < rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, bool> operator>(
      const Self& rhs) const {
    return value - EPS > rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, bool> operator>(
      const Self& rhs) const {
    return value > rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, int> sign() const {
    return value < -EPS ? -1 : value > EPS ? 1 : 0;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, int> sign() const {
    return value < 0 ? -1 : value > 0 ? 1 : 0;
  }
  bool operator!=(const Self& rhs) const { return !(*this == rhs); }
  static AccurateComparer accurate_comparer() { return AccurateComparer(); }
  F sin() const { return std::sin(F(value)); }
  F cos() const { return std::cos(F(value)); }
  F tan() const { return std::tan(F(value)); }
  F sqrt() const { return std::sqrt(F(value)); }
  F ln() const { return std::log(F(value)); }
  F exp() const { return std::exp(F(value)); }
  F asin() const { return std::asin(F(value)); }
  F acos() const { return std::acos(F(value)); }
  F atan() const { return std::atan(F(value)); }
  Self pow(const Self& exp) const { return Self(std::pow(value, exp.value)); }
  Self abs() const { return Self(std::abs(value)); }
  Self operator-() const { return Self(-value); }
};
template <class T, int EPS_DIGIT, class F>
struct is_near_value<NearValue<T, EPS_DIGIT, F>> {
  static const bool value = true;
};
template <class T, int EPS_DIGIT, class F>
OStream& operator<<(OStream& os, const NearValue<T, EPS_DIGIT, F>& rhs) {
  os << rhs.value;
  return os;
}
template <class T, int EPS_DIGIT, class F>
IStream& operator>>(IStream& in, NearValue<T, EPS_DIGIT, F>& rhs) {
  in >> rhs.value;
  return in;
}
}  // namespace dalt
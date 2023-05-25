#pragma once
#include "common.cpp"
#include "gcd.cpp"
namespace dalt {
namespace math {
template <class T>
enable_if_t<is_integral_v<T>, Str> FormatFraction(
    T a, T b, bool force_decimal_fraction = false, bool force_circular = false,
    const Str& digits = "0123456789") {
  int base = Size(digits);
  int sign = 0;
  if (a < 0) {
    a = -a;
    sign++;
  }
  if (b < 0) {
    b = -b;
    sign++;
  }
  Str ans;
  if (sign & 1) {
    ans += "-";
  }
  T large_part = a / b;
  T small_part = a - b * large_part;
  Str large_str;
  if (large_part == T(0)) {
    large_str += digits[0];
  }
  while (large_part != T(0)) {
    T div = large_part / base;
    large_str += digits[large_part - T(base) * div];
    large_part = div;
  }
  Reverse(All(large_str));
  ans += large_str;
  if (small_part == T(0) && !force_decimal_fraction) {
    return ans;
  }
  ans += ".";
  T top = small_part;
  T bot = b;
  Vec<int> index_map(bot, -1);
  while (top != T(0)) {
    if (index_map[top] != -1) {
      ans.insert(index_map[top], "(");
      ans += ")";
      break;
    }
    index_map[top] = Size(ans);
    top = top * T(base);
    var div = top / bot;
    var mod = top - div * bot;
    ans += digits[div];
    top = mod;
  }
  if (force_circular && ans.back() != ')') {
    ans += "(";
    ans += digits[0];
    ans += ")";
  }
  return ans;
}

template <class T>
class Fraction {
  static_assert(is_integral_v<T>);
  using Self = Fraction<T>;
  T a, b;
  void Normalize() {
    if (b < 0) {
      a = -a;
      b = -b;
    }
    var g = Gcd(Abs(a), b);
    a /= g;
    b /= g;
  }

 public:
  Fraction(T a = T(0), T b = T(1)) {
    this->a = a;
    this->b = b;
    Normalize();
  }
  int sign() const { return a < 0 ? -1 : a > 0 ? 1 : 0; }
  Self operator+(const Self& other) const {
    return Self(a * other.b + b * other.a, b * other.b);
  }
  Self operator-(const Self& other) const {
    return Self(a * other.b - b * other.a, b * other.b);
  }
  Self operator*(const Self& other) const {
    return Self(a * other.a, b * other.b);
  }
  Self operator/(const Self& other) const {
    return Self(a * other.b, b * other.a);
  }
  bool operator<(const Self& other) const { return (*this - other).sign() < 0; }
  bool operator==(const Self& other) const {
    return a == other.a && b == other.b;
  }
  bool operator!=(const Self& other) const { return !(*this == other); }
  ImplArithmeticAssignOperation(Self) ImplDefaultComparision(Self)

      Str format() const {
    return FormatFraction(a, b);
  }
  friend OStream& operator<<(OStream& out, const Self& f) {
    return out << f.format();
  }
  friend IStream& operator>>(IStream& in, Self& f) { return in >> f.a >> f.b; }
  T denominator() const { return b; }
  T numerator() const { return a; }
  bool is_integer() const { return b == 1; }
};
}  // namespace math
}  // namespace dalt
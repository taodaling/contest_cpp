#pragma once
#include "common.cpp"
namespace dalt {
struct uint128 {
  u64 high, low;
  uint128(u64 _low = 0, u64 _high = 0) : high(_high), low(_low) {}
  using Self = uint128;
  CastToAllScalar(low);
  friend Self operator+(const Self& a, const Self& b) {
    Self ans(a.low + b.low, a.high + b.high);
    if (ans.low < a.low) {
      ans.high++;
    }
    return ans;
  }
  friend Self operator-(const Self& a, const Self& b) {
    u64 h = a.high - b.high;
    u64 l = a.low - b.low;
    if(a.low < b.low) {
      l = -l;
      h--;
    }
    return Self(l, h);
  }
  friend OStream& operator<<(OStream &os, const Self& x) {
    if(x.high) {
      os << x.high;
    }
    os << x.low;
    return os;
  }
  friend IStream& operator>>(IStream &is, Self& x) {
    x.high = 0;
    is >> x.low;
    return is;
  }
  friend Self operator*(const Self& a, const Self& b) {
    static u64 mask = ((u64(1) << 32) - 1);
    u64 all = a.low & mask;
    u64 bll = b.low & mask;
    u64 alh = a.low >> 32;
    u64 blh = b.low >> 32;
    Self ans(0, a.high * b.low + a.low * b.high + alh * blh + (all * blh >> 32) +
                 (alh * bll >> 32));
    ans += all * bll;
    ans += ((all * blh) & mask) << 32;
    ans += ((bll * alh) & mask) << 32;
    return ans;
  }
  Self& operator+=(const u64& rhs) {
    low += rhs;
    if (low < rhs) {
      high++;
    }
    return *this;
  }
  bool operator<(const Self& rhs) const {
    return MakePair(high, low) < MakePair(rhs.high, rhs.low);
  }
  ImplDefaultComparision(Self);
  ImplArithmeticAssignOperation(Self);
  //ImplArithmeticAssignOperation(Self);
  bool operator==(const Self& rhs) const {
    return high == rhs.high && low == rhs.low;
  }
  bool operator!=(const Self& rhs) const { return !(*this == rhs); }
  // x < 2 ^ 31
  u32 modular(u32 x) const {
    static u64 max = std::numeric_limits<u64>::max();
    u64 ans = low < x ? low : low % x;
    if (high > 0) {
      ans = ans + (high >= x ? high % x : high) * (max % x + 1);
      ans %= x;
    }
    return ans;
  }
  u32 operator%(u32 x) const {
    return modular(x);
  }
  Self operator/(u32 x) const {
    static const u32 ALL_ONE = -1;
    u64 y = high;
    u64 top = y / x;
    y = y - top * x;
    y = (y << 32) | (low >> 32);
    u64 low_high = y / x;
    y = y - low_high * x;
    y = (y << 32) | (low & ALL_ONE);
    u64 low_low = y / x;
    return Self(low_low | (low_high << 32), top);  
  }
};
using u128 = uint128;

}  // namespace dalt
#include "common.cpp"
#include "optional.cpp"
namespace dalt {
namespace nimber {
// copied from https://judge.yosupo.jp/submission/92319
template <bool prec = false, int half = 32>
constexpr uint64_t mul(uint64_t a, uint64_t b);

constexpr int small = 1 << 16;

auto prec = []() -> Array<Array<uint16_t, small>, 2> {
  Array<uint16_t, small> pw, lg;
  pw[0] = 1;
  uint16_t base = -1;
  for (int i = 1; i < small - 1; i++) {
    pw[i] = mul<true>(pw[i - 1], base);
    lg[pw[i]] = i;
  }
  return {pw, lg};
}();

auto pw = prec[0], lg = prec[1];

template <bool prec, int half>
constexpr uint64_t mul(uint64_t a, uint64_t b) {
  if (a <= 1 || b <= 1) {
    return a * b;
  }
  if constexpr (!prec) {
    if (a < small && b < small) {
      int t = (int)lg[a] + lg[b];
      return pw[t >= small - 1 ? t - (small - 1) : t];
    }
  }
  auto mask = (1ULL << half) - 1;
  auto [a0, a1] = MakePair(a & mask, a >> half);
  auto [b0, b1] = MakePair(b & mask, b >> half);
  auto A = mul<prec, half / 2>(a0, b0);
  auto C = mul<prec, half / 2>(a1, b1);
  auto B = mul<prec, half / 2>(a0 ^ a1, b0 ^ b1) ^ A ^ C;

  if constexpr (half) {
    B <<= half;
    C = (C << half) ^ mul<prec, half / 2>(C, 1ULL << (half - 1));
  }

  return A ^ B ^ C;
}
struct Nimber {
  u64 value;
  static Nimber MulIdentity() {
    return Nimber(1);
  }
  static Nimber AddIdentity() {
    return Nimber(0);
  } 
  Nimber(u64 x = 0) : value(x) {}

  friend Nimber operator+(const Nimber& a, const Nimber& b) {
    return Nimber(a.value ^ b.value);
  }
  friend Nimber operator-(const Nimber& a, const Nimber& b) {
    return Nimber(a.value ^ b.value);
  }
  friend Nimber operator*(const Nimber& a, const Nimber& b) {
    return Nimber(mul(a.value, b.value));
  }
  friend Nimber operator/(const Nimber& a, const Nimber& b) {
    return Nimber(-1);
  }
  friend bool operator==(const Nimber& a, const Nimber& b) {
    return a.value == b.value;
  }
  friend bool operator!=(const Nimber& a, const Nimber& b) {
    return a.value != b.value;
  }
  friend bool operator<(const Nimber& a, const Nimber& b) {
    return a.value < b.value;
  }
  friend OStream& operator<<(OStream& os, const Nimber &b) {
    os << b.value;
    return os;
  }
  friend IStream& operator>>(IStream& is, Nimber& b) {
    is >> b.value;
    return is;
  }
  ImplArithmeticAssignOperation(Nimber) ImplDefaultComparision(Nimber)
};
}
}  // namespace dalt
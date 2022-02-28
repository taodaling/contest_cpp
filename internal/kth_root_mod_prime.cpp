#pragma once
#include "gcd.cpp"
#include "hashmap.cpp"
namespace dalt {
namespace math {
// credited to: https://judge.yosupo.jp/submission/5940
// return a^{1/p} (mod p) or -1 if not exists
i64 KthRootModPrime(i64 a, i64 k, i64 p) {
  auto pow = [](i64 a, i64 n, i64 p) -> i64 {
    i64 r = 1;
    for (; n > 0; n >>= 1, a = a * a % p)
      if (n % 2 == 1) r = r * a % p;
    return r;
  };
  auto inv = [](i64 a, i64 p) -> i64 {
    a %= p;
    i64 u = 1, v = 0;
    i64 b = p;
    while (b > 0) {
      i64 q = a / b;
      a %= b;
      u -= v * q % p;
      u = (u % p + p) % p;
      Swap(u, v);
      Swap(a, b);
    }
    return u < 0 ? u + p : u;
  };
  auto peth_root = [&](i64 a, i64 p, int e,
                       i64 mod) -> i64 {
    i64 q = mod - 1;
    int s = 0;
    while (q % p == 0) {
      q /= p;
      ++s;
    }
    i64 pe = pow(p, e, mod);
    i64 ans = pow(a, ((pe - 1) * inv(q, pe) % pe * q + 1) / pe, mod);
    i64 c = 2;
    while (pow(c, (mod - 1) / p, mod) == 1) ++c;
    c = pow(c, q, mod);
    i64 add = 1;
    int v = (int)std::sqrt((double)(s - e) * p) + 1;
    hash::HashMap<i64, int> map(v + 1);
    i64 mul = pow(c, v * pow(p, s - 1, mod - 1) % (mod - 1), mod);
    for (int i = 0; i <= v; ++i) {
      map[add] = i;
      add = add * mul % mod;
    }
    mul = inv(pow(c, pow(p, s - 1, mod - 1), mod), mod);
    for (int i = e; i < s; ++i) {
      i64 err = inv(pow(ans, pe, mod), mod) * a % mod;
      i64 target = pow(err, pow(p, s - 1 - i, mod - 1), mod);
      for (int j = 0; j <= v; ++j) {
        if (map.find(target) != map.end()) {
          int x = map[target];
          ans = ans *
                pow(c, (j + v * x) * pow(p, i - e, mod - 1) % (mod - 1), mod) %
                mod;
          break;
        }
        target = target * mul % mod;
        assert(j != v);
      }
    }
    return ans;
  };
  if (k > 0 && a == 0) return 0;
  k %= p - 1;
  i64 g = Gcd(k, p - 1);
  if (pow(a, (p - 1) / g, p) != 1) return -1;
  a = pow(a, inv(k / g, (p - 1) / g), p);
  for (i64 div = 2; div * div <= g; ++div) {
    int sz = 0;
    while (g % div == 0) {
      g /= div;
      ++sz;
    }
    if (sz > 0) {
      i64 b = peth_root(a, div, sz, p);
      a = b;
    }
  }
  if (g > 1) a = peth_root(a, g, 1, p);
  return a;
}

}  // namespace math
}  // namespace dalt
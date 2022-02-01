#include "miller_rabin.cpp"
namespace dalt {
// find any factor, if nothing find, return n, don't invoke it directly, turn to
// FindFactor instead
template <class T> enable_if_t<is_integral_v<T>, T> PollardRho(T n) {
  if (n <= 1) {
    return n;
  }
  if (n % 2 == 0) {
    return 2;
  }
  if (n % 3 == 0) {
    return 3;
  }
  T x = 0, y = x, t, q = 1, c = random_choice<T>(1, n - 2);
  for (int k = 2;; k <<= 1, y = x, q = 1) {
    for (int i = 1; i <= k; ++i) {
      x = AddMod(MulMod(x, x, n), c, n);
      q = MulMod(q, Abs(x - y), n);
      if ((i & 127) == 0) {
        t = Gcd(q, n);
        if (t > 1) {
          return t;
        }
      }
    }
    if ((t = Gcd(q, n)) > 1) {
      return t;
    }
  }
}
// find any factor, if nothing find, return n
template <class T> enable_if_t<is_integral_v<T>, T> FindFactor(T n) {
  Debug(n);
  if (n == 1) {
    return 1;
  }
  if (MillerRabin(n, 10)) {
    return n;
  }
  while (true) {
    T f = PollardRho(n);
    if (f != n) {
      return f;
    }
  }
  Debug("over");
}
// Find all factors of n
template <class T> enable_if_t<is_integral_v<T>, Vec<T>> Factorize(T n) {
  const static T SMALL_PRIMES[]{2, 3, 5, 7, 11, 13, 17, 19};
  Assert(n != 0);
  Vec<T> set;
  for (T p : SMALL_PRIMES) {
    if (n % p != 0) {
      continue;
    }
    set.push_back(p);
    while (n % p == 0) {
      n /= p;
    }
  }
  auto dfs = [&](auto &dfs, T n) {
    if (n == T(1)) {
      return;
    }
    T f = FindFactor(n);
    if (f == n) {
      set.push_back(f);
      return;
    }
    T otherPart = n / f;
    dfs(dfs, f);
    dfs(dfs, otherPart);
  };
  dfs(dfs, n);
  Sort(All(set));
  MakeUnique(set);
  return set;
}
} // namespace dalt
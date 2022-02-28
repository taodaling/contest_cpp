#pragma once
#include "euler_sieve.cpp"
#include "factorize.cpp"
#include "hashmap.cpp"
namespace dalt {
namespace math {
template <class I, class T, i64 CACHE = 0>
enable_if_t<is_integral_v<I>, T> BigMultiplicativeFunctionEval(
    I N, const Function<T(I, I)> &f) {
  static hash::HashMap<I, T> cache;
  if (N <= 1) {
    return T(N);
  }
  T ans;
  auto iter = cache.end();
  if (CACHE == 0 || (iter = cache.find(N)) == cache.end()) {
    if (N < Size(EulerSieve::is_comp)) {
      T res = 1;
      while (N > 1) {
        res = res * f(EulerSieve::smallest_prime_factor[N],
                      EulerSieve::exp_of_smallest_prime_factor[N]);
        N = N / EulerSieve::exp_of_smallest_prime_factor[N];
      }
      ans = res;
    } else {
      I factor = FindPrimeFactor(N);
      I a = 1;
      I b = N;
      while (b % factor == 0) {
        b = b / factor;
        a = a * factor;
      }
      ans = f(factor, a) * BigMultiplicativeFunctionEval(b, f);
    }
    if (CACHE != -1) {
      cache[N] = ans;
    }
  } else {
    ans = iter->second;
  }
  return ans;
}

template <class I>
I MobiusEval(I n) {
  return BigMultiplicativeFunctionEval<I, I>(
      n, [](auto x, auto xp) { return xp == x ? I(-1) : I(0); });
}

}  // namespace math
}  // namespace dalt
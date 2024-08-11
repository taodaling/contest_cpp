#pragma once
#include "common.cpp"
#include "math.cpp"
#include "modint.cpp"
namespace dalt {
namespace math {
struct EulerSieve {
 public:
  static Vec<int> primes;
  static Vec<bool> is_comp;
  static Vec<int> smallest_prime_factor;
  static Vec<int> exp_of_smallest_prime_factor;
  EulerSieve() {
    is_comp.resize(2);
    smallest_prime_factor.resize(2);
    exp_of_smallest_prime_factor.resize(2);
    ensure(100);
  }
  //trigger recompute if necessary
  static void ensure(int n) {
    int cur_size = is_comp.size();
    if (cur_size >= n) {
      return;
    }
    primes.reserve(n);
    is_comp.resize(n);
    smallest_prime_factor.resize(n);
    exp_of_smallest_prime_factor.resize(n);
    primes.clear();
    for (int i = 2; i < n; i++) {
      if (!is_comp[i]) {
        primes.push_back(i);
        exp_of_smallest_prime_factor[i] = smallest_prime_factor[i] = i;
      }
      int pi;
      for (int j = 0; j < Size(primes) && (pi = primes[j] * i) < n; j++) {
        smallest_prime_factor[pi] = primes[j];
        exp_of_smallest_prime_factor[pi] =
            smallest_prime_factor[i] == primes[j]
                ? (exp_of_smallest_prime_factor[i] *
                   exp_of_smallest_prime_factor[primes[j]])
                : exp_of_smallest_prime_factor[primes[j]];
        is_comp[pi] = true;
        if (i % primes[j] == 0) {
          break;
        }
      }
    }
  }

  //(factor, exp_factor)
  // O(n + n / ln(n) * O(per f) )
  template <class T>
  static Vec<T> calc_multiplicative_function(int n,
                                             const Function<T(int, int)>& f) {
    ensure(n);
    Vec<T> ans(n);
    if (n > 0) {
      ans[0] = T(0);
    }
    if (n > 1) {
      ans[1] = T(1);
    }
    for (int i = 2; i < n; i++) {
      if (exp_of_smallest_prime_factor[i] != i) {
        ans[i] = ans[exp_of_smallest_prime_factor[i]] *
                 ans[i / exp_of_smallest_prime_factor[i]];
      } else {
        ans[i] = f(smallest_prime_factor[i], i);
      }
    }
    return ans;
  }
  template <class T>
  static Vec<T> calc_totally_multiplicative_function(
      int n, const Function<T(int)>& f) {
    ensure(n);
    Vec<T> ans(n);
    if (n > 0) {
      ans[0] = f(0);
    }
    if (n > 1) {
      ans[1] = f(1);
    }
    for (int i = 2; i < n; i++) {
      if (smallest_prime_factor[i] != i) {
        ans[i] =
            ans[smallest_prime_factor[i]] * ans[i / smallest_prime_factor[i]];
      } else {
        ans[i] = f(i);
      }
    }
    return ans;
  }
  template <class T, class E>
  static Vec<T> powmod(int n, E k) {
    return calc_totally_multiplicative_function<T>(n, [&](auto x) -> T {
      return PowBinaryLift(T(x), k);
    });
  }

  static Vec<int> get_mobius(int n) {
    return calc_multiplicative_function<int>(
        n, [&](auto factor, auto exp_factor) -> int {
          if (factor == exp_factor) {
            return -1;
          } else {
            return 0;
          }
        });
  }

  static Vec<int> get_euler(int n) {
    return calc_multiplicative_function<int>(
        n, [&](auto factor, auto exp_factor) -> int {
          return exp_factor - exp_factor / factor;
        });
  }

  static Vec<int> get_factor(int n) {
    ensure(n);
    Vec<int> ans(n);
    if (n > 0) {
      ans[0] = 0;
    }
    if (n > 1) {
      ans[1] = 1;
    }
    for (int i = 2; i < n; i++) {
      if (!is_comp[i]) {
        ans[i] = 2;
      } else if (i == exp_of_smallest_prime_factor[i]) {
        ans[i] = 1 + ans[i / smallest_prime_factor[i]];
      } else {
        ans[i] = ans[exp_of_smallest_prime_factor[i]] *
                 ans[i / exp_of_smallest_prime_factor[i]];
      }
    }
    return ans;
  }
} __EULER_SIEVE__;
Vec<int> EulerSieve::primes;
Vec<bool> EulerSieve::is_comp;
Vec<int> EulerSieve::smallest_prime_factor;
Vec<int> EulerSieve::exp_of_smallest_prime_factor;
//void CONSTRUCT _InitEulerSieve() { EulerSieve::ensure(1e6); }
}  // namespace math
}  // namespace dalt
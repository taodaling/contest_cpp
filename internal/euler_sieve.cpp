#pragma once
#include "../common.cpp"
#include "math.cpp"
#include "modint.cpp"
namespace dalt {
struct EulerSieve {
private:
  Vec<int> primes;
  Vec<bool> is_comp;
  Vec<int> smallest_prime_factor;
  Vec<int> exp_of_smallest_prime_factor;
  int n;

public:
  Vec<int> &get_primes() { return primes; }
  Vec<bool> &get_is_comp() { return is_comp; }

  Vec<int> powmod(int k, int mod) const {
    static const int ID = -1;
    using Modular = DynamicModular<i32, ID>;
    using InternalMi = ModInt<Modular>;
    Modular::cinit(mod);
    Vec<int> ans(n + 1);
    if (k == 0) {
      ans[0] = 1;
    }
    if (n >= 1) {
      ans[1] = 1;
    }
    for (int i = 2; i <= n; i++) {
      if (!is_comp[i]) {
        ans[i] = PowBinaryLift(InternalMi(i), k).value;
      } else {
        ans[i] = (int)((i64)ans[i / smallest_prime_factor[i]] *
                       ans[smallest_prime_factor[i]] % mod);
      }
    }
    return ans;
  }

  Vec<int> get_mobius() const {
    Vec<int> mobius(n + 1);
    mobius[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!is_comp[i]) {
        mobius[i] = -1;
      } else {
        if (exp_of_smallest_prime_factor[i] != smallest_prime_factor[i]) {
          mobius[i] = 0;
        } else {
          mobius[i] = mobius[exp_of_smallest_prime_factor[i]] *
                      mobius[i / exp_of_smallest_prime_factor[i]];
        }
      }
    }
    return mobius;
  }

  Vec<int> get_euler() const {
    Vec<int> euler(n + 1);
    euler[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!is_comp[i]) {
        euler[i] = i - 1;
      } else {
        if (exp_of_smallest_prime_factor[i] == i) {
          euler[i] = i - i / smallest_prime_factor[i];
        } else {
          euler[i] = euler[exp_of_smallest_prime_factor[i]] *
                     euler[i / exp_of_smallest_prime_factor[i]];
        }
      }
    }
    return euler;
  }

  Vec<int> &get_smallest_prime_factor() { return smallest_prime_factor; }

  Vec<int> get_factor() const {
    Vec<int> factors(n + 1);
    factors[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!is_comp[i]) {
        factors[i] = 2;
      } else {
        if (exp_of_smallest_prime_factor[i] == i) {
          factors[i] = 1 + factors[i / smallest_prime_factor[i]];
        } else {
          factors[i] = factors[exp_of_smallest_prime_factor[i]] *
                       factors[i / exp_of_smallest_prime_factor[i]];
        }
      }
    }
    return factors;
  }

  EulerSieve(int _n) : n(_n) {
    is_comp = Vec<bool>(n + 1);
    primes.reserve(n + 1);
    exp_of_smallest_prime_factor = Vec<int>(n + 1);
    smallest_prime_factor = Vec<int>(n + 1);
    for (int i = 2; i <= n; i++) {
      if (!is_comp[i]) {
        primes.push_back(i);
        exp_of_smallest_prime_factor[i] = smallest_prime_factor[i] = i;
      }
      int until = n / i;
      for (int j = 0, until = n / i; j < Size(primes) && primes[j] <= until;
           j++) {
        int pi = primes[j] * i;
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
};
} // namespace dalt
#include "common.cpp"
#include "math.cpp"
namespace dalt {
// Find all primes in [2, n] and consume them.
// The time complexity is O(n log log n) and the space complexity is O(sqrt(n))
void EratosthenesSieve(int n, const Consumer<int> &consumer) {
  if (n <= 1) {
    return;
  }
  int block = std::round(std::sqrt(n));
  Vec<bool> is_comp(block + 1);
  Vec<int> primes(block + 1);
  int prime_cnt = 0;
  for (int i = 2; i <= block; i++) {
    if (is_comp[i]) {
      continue;
    }
    primes[prime_cnt++] = i;
    for (int j = i + i; j <= block; j += i) {
      is_comp[j] = true;
    }
  }
  for (int i = 0; i < prime_cnt; i++) {
    int p = primes[i];
    consumer(p);
  }
  for (int l = block + 1; l <= n; l += block) {
    int r = Min(l + block - 1, n);
    Fill(All(is_comp), false);
    for (int i = 0; i < prime_cnt; i++) {
      int p = primes[i];
      if (r < p * p) {
        break;
      }
      int top = Max(0, l - p * p);
      int bot = p;
      for (int j = (top + bot - 1) / bot * p + p * p; j <= r; j += p) {
        is_comp[j - l] = true;
      }
    }
    for (int j = l; j <= r; j++) {
      if (!is_comp[j - l]) {
        consumer(j);
      }
    }
  }
}
} // namespace dalt
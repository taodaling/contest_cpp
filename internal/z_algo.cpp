#include "common.cpp"
namespace dalt {
namespace seq {
template <class T>
Vec<i32> ZAlgorithm(const Indexer<T> &s, int n) {
  if (n == 0) {
    return Vec<i32>();
  }
  int l = 0;
  int r = -1;
  Vec<i32> z(n);
  z[0] = n;
  for (int i = 1; i < n; i++) {
    if (r < i) {
      l = r = i;
    } else {
      int t = i - l;
      int k = r - i + 1;
      if (z[t] < k) {
        z[i] = z[t];
        continue;
      }
      l = i;
      r++;
    }
    while (r < n && s(r - l) == s(r)) {
      r++;
    }
    r--;
    z[i] = r - l + 1;
  }
  return z;
}
}  // namespace seq
}  // namespace dalt
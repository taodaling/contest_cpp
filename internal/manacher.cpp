#include "common.cpp"
namespace dalt {
namespace seq {
template <class T>
// ret[0][i] * 2     = the longest palindrom centered at i - 1 and i with even length
// ret[1][i] * 2 - 1 = the longest palindrom centered at i with odd length
//- time: O(n)
Array<Vec<i32>, 2> Manacher(const Indexer<T> &s, int n) {
  Array<Vec<i32>, 2> res;
  {
    Vec<i32> ans(n);
    int c = -1;
    int mx = -1;
    ans[0] = 0;
    for (int i = 1; i < n; i++) {
      int len = 0;
      if (mx >= i) {
        int mirror = c - (i - c);
        len = Min(ans[mirror], mx - (i - 1));
      }
      while (i - (len + 1) >= 0 && i - 1 + (len + 1) < n &&
             s(i - (len + 1)) == s(i - 1 + (len + 1))) {
        len++;
      }
      ans[i] = len;
      if (mx < i - 1 + len) {
        mx = i - 1 + len;
        c = i;
      }
    }
    res[0] = Move(ans);
  }
  {
    Vec<i32> ans(n);
    int c = -1;
    int mx = -1;
    for (int i = 0; i < n; i++) {
      int len = 0;
      if (mx > i) {
        int mirror = c - (i - c);
        len = Min(ans[mirror] - 1, mx - i);
      }
      while (i - (len + 1) >= 0 && i + (len + 1) < n &&
             s(i - (len + 1)) == s(i + (len + 1))) {
        len++;
      }
      ans[i] = len + 1;
      if (mx < i + len) {
        mx = i + len;
        c = i;
      }
    }
    res[1] = Move(ans);
  }
  return res;
}
}  // namespace seq
}  // namespace dalt
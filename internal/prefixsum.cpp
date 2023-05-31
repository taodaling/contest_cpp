#include "common.cpp"
namespace dalt {
template <class T, int N>
struct PrefixSum {
  using Self = PrefixSum<T, N>;
  Vec<PrefixSum<T, N - 1>> ps;
  PrefixSum(const MDVec<T, N>& data) : ps(Size(data)) {
    int k = Size(data);
    for (int i = 0; i < k; i++) {
      data[i] = PrefixSum<T, N - 1>(data[i]);
      if (i > 0) {
        data[i] += data[i - 1];
      }
    }
  }

  friend Self& operator+=(Self& a, const Self& b) {
    for (int i = 0; i < Size(a); i++) {
      a[i] += b[i];
    }
  }
  template <typename... Args>
  T query(int l, int r, Args... args) const {
    return ps[r].Query(args...) - (l - 1 < 0 ? T() : ps[l - 1].Query(args...));
  }
};
template <class T>
struct PrefixSum<T, 0> {
  T data;
  PrefixSum(const MDVec<T, 0>& _data) : data(_data) {}
  friend Self& operator+=(Self& a, const Self& b) { a += b; }
  T query() const { return data; }
};
}  // namespace dalt
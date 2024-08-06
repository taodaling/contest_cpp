#include "common.cpp"
namespace dalt {
template <class T, int N>
struct PrefixSum {
  using Self = PrefixSum<T, N>;
  Vec<PrefixSum<T, N - 1>> ps;
  PrefixSum(){}
  PrefixSum(const MDVec<T, N>& data) {
    ps.reserve(Size(data));
    int k = Size(data);
    for (int i = 0; i < k; i++) {
      ps.emplace_back(data[i]);
      if (i > 0) {
        ps[i] += ps[i - 1];
      }
    }
  }
  int size() const {
    return ps.size();
  }
  const PrefixSum<T, N - 1>& operator[](int i) const {
    return ps[i];
  }

  friend Self& operator+=(Self& a, const Self& b) {
    for (int i = 0; i < Size(a); i++) {
      a.ps[i] += b.ps[i];
    }
    return a;
  }
  template <typename... Args>
  T query(int l, int r, Args... args) const {
    return ps[r].query(args...) - (l - 1 < 0 ? T() : ps[l - 1].query(args...));
  }
  template <typename... Args>
  T query_with_check(int l, int r, Args... args) const {
    l = Max(0, l);
    r = Min(r, Size(ps) - 1);
    if(l > r) {
      return T();
    }
    return ps[r].query_with_check(args...) -
           (l - 1 < 0 ? T() : ps[l - 1].query_with_check(args...));
  }
};
template <class T>
struct PrefixSum<T, 0> {
  using Self = PrefixSum<T, 0>;
  T data;
  PrefixSum(const MDVec<T, 0>& _data) : data(_data) {}
  friend Self& operator+=(Self& a, const Self& b) { a.data += b.data; return a; }
  T query() const { return data; }
  T query_with_check() const { return data; }
};
}  // namespace dalt
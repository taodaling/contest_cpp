#include "../common.cpp"
namespace dalt {
template <class F, class T> Vec<T> Cast(const Vec<F> &data) {
  int n = Size(data);
  Vec<T> ans;
  ans.reserve(n);
  for (int i = 0; i < n; i++) {
    ans.push_back(T(data[i]));
  }
  return ans;
}
} // namespace dalt
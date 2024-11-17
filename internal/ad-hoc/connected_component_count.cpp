#pragma once
#include "common.cpp"
namespace dalt {
namespace adhoc {
struct ConnectedComponentCount {
  Vec<int> another;
  using Callback = Function<void(int, int)>;
  Callback adder;
  Callback deleter;

  ConnectedComponentCount(
      int n, Callback _adder = [](int a, int b) {},
      Callback _deleter = [](int a, int b) {})
      : adder(_adder), deleter(_deleter) {
    another.resize(n, -1);
  }

  void insert(int i) {
    Assert(another[i] == -1);
    another[i] = i;
    adder(i, i);
    if (i > 0 && another[i - 1] >= 0) {
      join(another[i - 1], i);
    }
    if (i + 1 < Size(another) && another[i + 1] >= 0) {
      join(another[i], another[i + 1]);
    }
  }

 private:
  void join(int l, int r) {
    deleter(l, another[l]);
    deleter(another[r], r);
    another[l] = r;
    another[r] = l;
    adder(l, r);
  }
};
}  // namespace adhoc
}  // namespace dalt
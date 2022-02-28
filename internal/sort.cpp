#pragma once
#include "common.cpp"
namespace dalt {
namespace misc {
template <class T, class C = Less<T>, class I>
void QuickSort(I begin, I end, C comp = C()) {
  Shuffle(begin, end, std::mt19937(rng));
  auto dfs = [&](auto &dfs, auto begin, auto end) -> void {
    if (begin == end) {
      return;
    }
    auto l = begin;
    auto r = end;
    auto i = begin;
    for (++i; i < r; ++i) {
      if (comp(*i, *l)) {
        Swap(*i, *l);
        ++l;
      } else if (comp(*l, *i)) {
        --r;
        Swap(*r, *i);
        --i;
      }
    }
    dfs(dfs, begin, l);
    dfs(dfs, r, end);
  };
  dfs(dfs, begin, end);
}
}  // namespace misc
}  // namespace dalt
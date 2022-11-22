#pragma once
#include "common.cpp"
namespace dalt {
// reference: https://oi-wiki.org/misc/rollback-mo-algo/
// start with range [0, N)
// each block has size K
template <class T>
Vec<T> MoOnArray_OnlyDelete(int N, int K, const Vec<Pair<int, int>> &queries,
                            const Consumer<int> &adder,
                            const Consumer<int> &deleter,
                            const Mapper<Pair<int, int>, T> &solver,
                            const Function<void()> save,
                            const Function<void()> rollback) {
  Vec<T> ans(Size(queries));
  Vec<int> indices(Size(queries));
  for (int i = 0; i < Size(queries); i++) {
    indices[i] = i;
  }
  Sort(All(indices), [&](var a, var b) {
    return MakePair(queries[a].first / K, -queries[a].second) <
           MakePair(queries[b].first / K, -queries[b].second);
  });
  save();
  // handle query in single block
  int l = 0;
  int r = N - 1;
  for (var index : indices) {
    var &q = queries[index];
    int L = q.first;
    int R = q.second;
    int Lb = L / K;
    int to = Max(Lb * K, 0);
    if (l != to) {
      while (r < N - 1) {
        ++r;
        adder(r);
      }
      rollback();
      while (l < to) {
        deleter(l);
        l++;
      }
      save();
    }
    while (r > R) {
      deleter(r);
      r--;
    }
    save();
    while (l < L) {
      deleter(l);
      l++;
    }
    ans[index] = solver(q);
    while (l > to) {
      l--;
      adder(l);
    }
    rollback();
  }
  return ans;
}
// reference: https://oi-wiki.org/misc/rollback-mo-algo/
// start with range [0, 0)
// each block has size K
template <class T>
Vec<T> MoOnArray_OnlyAdd(int N, int K, const Vec<Pair<int, int>> &queries,
                         const Consumer<int> &adder,
                         const Consumer<int> &deleter,
                         const Mapper<Pair<int, int>, T> &solver,
                         const Function<void()> save,
                         const Function<void()> rollback) {
  Vec<T> ans(Size(queries));
  Vec<int> indices(Size(queries));
  for (int i = 0; i < Size(queries); i++) {
    indices[i] = i;
  }
  Sort(All(indices), [&](var a, var b) {
    return MakePair(queries[a].first / K, queries[a].second) <
           MakePair(queries[b].first / K, queries[b].second);
  });
  save();
  // handle query in single block
  for (int index : indices) {
    var &q = queries[index];
    int L = q.first;
    int R = q.second;
    int Lb = L / K;
    int Rb = R / K;
    if (Rb != Lb) {
      continue;
    }
    for (int i = L; i <= R; i++) {
      adder(i);
    }
    ans[index] = solver(q);
    for (int i = L; i <= R; i++) {
      deleter(i);
    }
    rollback();
    save();
  }
  int l = Min(K - 1, N - 1);
  int r = l - 1;
  for (int index : indices) {
    var &q = queries[index];
    int L = q.first;
    int R = q.second;
    int Lb = L / K;
    int Rb = R / K;
    if (Rb == Lb) {
      continue;
    }
    int to = Min((Lb + 1) * K - 1, N - 1);
    if (l != to) {
      while (l <= r) {
        deleter(l++);
      }
      rollback();
      save();
      l = to;
      r = l - 1;
    }
    while (r < R) {
      r++;
      adder(r);
    }
    save();
    while (l > L) {
      l--;
      adder(l);
    }
    ans[index] = solver(q);
    while (l < to) {
      deleter(l);
      l++;
    }
    rollback();
  }
  return ans;
}
}  // namespace dalt
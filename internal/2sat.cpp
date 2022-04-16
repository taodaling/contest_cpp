#pragma once
#include "strongly_connected_component.cpp"
#include "optional.cpp"
namespace dalt {
struct TwoSat {
private:
  using E = graph::DiBaseEdge;
  Vec<Vec<E>> g;
  void dep_on(int a, int b) {
    DebugFmtln("%d %d", a, b);
    g[a].push_back(E());
    g[a].back().to = b;
  }

public:
  TwoSat(int n) : g(2 * n) {}
  int id(int x) const { return x * 2; }
  int negate_id(int x) const { return x * 2 + 1; }
  int negate(int x) const { return x ^ 1; }
  void deduce(int a, int b) {
    dep_on(a, b);
    dep_on(negate(b), negate(a));
  }
  void or_rel(int a, int b) { deduce(negate(a), b); }
  void always_true(int a) { dep_on(negate(a), a); }
  void always_false(int a) { dep_on(a, negate(a)); }
  void same(int a, int b) {
    deduce(a, b);
    deduce(b, a);
  }
  void xor_rel(int a, int b) { same(a, negate(b)); }
  void at_least_one_false(int a, int b) { deduce(a, negate(b)); }
  void at_least_one_true(int a, int b) { or_rel(a, b); }
  Optional<Vec<bool>> solve() const {
    int n = Size(g) / 2;
    Vec<bool> values(2 * n);
    auto sets = graph::StronglyConnectedComponentDi(g);
    for (int i = 0; i < n; i++) {
      if (sets[id(i)] == sets[negate_id(i)]) {
        return {};
      }
    }
    Vec<bool> dfns(2 * n);
    auto assign = [&](auto assign, auto root) {
      if (dfns[root]) {
        return;
      }
      dfns[root] = true;
      for (auto &e : g[root]) {
        assign(assign, e.to);
      }
      if (sets[root] == root) {
        values[root] = !values[sets[negate(root)]];
      }
    };
    for (int i = 0; i < 2 * n; i++) {
      assign(assign, i);
      values[i] = values[sets[i]];
    }
    Vec<bool> res(n);
    for (int i = 0; i < n; i++) {
      res[i] = values[id(i)];
    }
    return res;
  }
};
} // namespace dalt
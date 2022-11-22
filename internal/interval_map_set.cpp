#pragma once
#include "common.cpp"
namespace dalt {
template <class K, class T, class C = Less<T>>
struct IntervalMapSet {
  TreeMap<K, Pair<K, T>> map;
  C comp;
  using CT = Consumer<Tuple<K, K, T>>;
  CT adder;
  CT deleter;
  IntervalMapSet(CT _adder, CT _deleter, C _comp = C())
      : comp(_comp), map(comp), adder(_adder), deleter(_deleter) {}

  void split(K i) {
    var floor = map.lower_bound(i);
    if (floor == map.begin()) {
      return;
    }
    --floor;
    // i >= r
    if (!comp(i, floor->second.first)) {
      return;
    }
    map[i] = MakePair(floor->second.first, floor->second.second);
    floor->second.first = i;
  }
  // set [l, r) = val
  void set(K l, K r, T val) {
    if (!comp(l, r)) {
      return;
    }
    split(l);
    split(r);
    var iter = map.lower_bound(l);
    //<=r
    while (iter != map.end() && !comp(r, iter->second.first)) {
      deleter(MakeTuple(iter->first, iter->second.first, iter->second.second));
      iter = map.erase(iter);
    }
    adder(MakeTuple(l, r, val));
    map[l] = MakePair(r, val);
  }
  Vec<Tuple<K, T, K>> to_vec() const {
    Vec<Tuple<K, T, K>> ans;
    for(var &iter : map) {
      ans.push_back(MakeTuple(iter->first, iter->second.second, iter->second.first));
    }
    return ans;
  }
};
}  // namespace dalt
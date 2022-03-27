#pragma once
#include "common.cpp"
#include "interval_test.cpp"
namespace dalt {
template <class T>
struct IntervalMap {
  static_assert(is_arithmetic_v<T>);
  using Self = IntervalMap<T>;
  //[l, r), left close, right open
  TreeMap<T, T> map;
  Function<void(T, T)> add_callback;
  Function<void(T, T)> del_callback;

 private:
  void add0(T l, T r) {
    if(l >= r) {
      return;
    }
    add_callback(l, r);
    map[l] = r;
  }
  decltype(map.begin()) del0(decltype(map.begin())& iter) {
    del_callback(iter->first, iter->second);
    return map.erase(iter);
  }

public:
  IntervalMap(
      const Function<void(T, T)>& _add_callback = [](T a, T b) {},
      const Function<void(T, T)>& _del_callback = [](T a, T b) {})
      : add_callback(_add_callback), del_callback(_del_callback) {}

  void add(T begin, T end) {
    auto iter = map.upper_bound(begin);
    if(iter != map.begin()) {
      --iter;
      if(iter->second < begin) {
        ++iter;
      }
    }
    while(iter != map.end() && !(iter->second < begin || iter->first > end)) {
      begin = Min(begin, iter->first);
      end = Max(end, iter->second);
      iter = del0(iter);
    }
    add0(begin, end);
  }
  void remove(T begin, T end) {
    auto iter = map.upper_bound(begin);
    if (iter != map.begin()) {
      --iter;
      if (iter->second < begin) {
        ++iter;
      }
    }
    while (iter != map.end() && !(iter->second < begin || iter->first > end)) {
      T l = iter->first;
      T r = iter->second;
      iter = del0(iter);
      add0(l, begin);
      add0(end, r);
    }
  }
  Vec<Pair<T, T>> to_vec() const {
    Vec<Pair<T, T>> res;
    res.insert(res.begin(), All(map));
    return res;
  }
};
}  // namespace dalt
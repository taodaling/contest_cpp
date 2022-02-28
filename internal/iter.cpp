#pragma once
#include "common.cpp"
namespace dalt {
// next() -> T
// has_next() -> bool
MakeAnnotation(iter);
template <class I, class F> struct MapperIter {
  static_assert(is_iter_v<I>);
  using Self = MapperIter<I, F>;
  using Type = typename I::Type;
  I &iter;
  Mapper<Type, F> mapper;
  MapperIter(I &_iter, const Mapper<Type, F> &_mapper)
      : iter(_iter), mapper(_mapper) {}
  bool has_next() const { return iter.has_next(); }
  F next() { return mapper(iter.next()); }
  template <class Z> MapperIter<Self, Z> map(const Mapper<F, Z> &f) {
    return MapperIter<Self, Z>(*this, f);
  }
  i32 size() const { return iter.size(); }
  Vec<F> to_vec() {
    Vec<F> res;
    res.reserve(size());
    while (has_next()) {
      res.push_back(next());
    }
    return res;
  }
};
template <class T> struct RangeIter {
  using Self = RangeIter<T>;
  using Type = T;
  T l;
  T r;
  T step;
  RangeIter(T _l, T _r, T _step) : l(_l), r(_r), step(_step) {}
  bool has_next() const { return l <= r; }
  T next() {
    T ans;
    if (step > T(0)) {
      ans = l;
      l = l + step;
    } else {
      ans = r;
      r = r - step;
    }
    return ans;
  }
  i32 size() const {
    if (l > r) {
      return 0;
    }
    T abs_step = Abs(step);
    return (r - l + abs_step) / abs_step;
  }
  Self step_by(T x) const { return Self(l, r, step * x); }
  Self reverse() const { return step_by(T(-1)); }
  template <class F> MapperIter<Self, F> map(const Mapper<T, F> &f) {
    return MapperIter<Self, F>(*this, f);
  }
  Vec<T> to_vec() {
    Vec<T> res;
    res.reserve(size());
    while (has_next()) {
      res.push_back(next());
    }
    return res;
  }
};
template <class T> struct is_iter<RangeIter<T>> {
  static const bool value = true;
};
template <class I, class F> struct is_iter<MapperIter<I, F>> {
  static const bool value = true;
};
template <class T> struct Range {
  T l;
  T r;
  Range(T _l, T _r) : l(_l), r(_r) {}
  T operator[](T index) const { return l + index; }
  RangeIter<T> iter() const { return RangeIter(l, r, T(1)); }
};
} // namespace dalt
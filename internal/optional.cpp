#pragma once
#include "common.cpp"

namespace dalt {
template <class T>
struct Optional {
  using Self = Optional<T>;

 private:
  T val;
  bool show_up;

 public:
  Optional(const T &arg_val) : val(arg_val), show_up(true) {}
  Optional(const T &&arg_val) : val(arg_val), show_up(true) {}
  Optional() : show_up(false) {}
  const T &value() const {
    Assert(show_up);
    return val;
  }
  T &value() {
    Assert(show_up);
    return val;
  }
  T &operator*() { return value(); }
  const T &operator*() const { return value(); }
  bool is_some() const { return show_up; }
  bool is_none() const { return !show_up; }
  const T *operator->() const {
    return &value();
  }
  T *operator->() { return &value(); }
  inline operator T() const { return value(); }
  T or_else(T def) const {
    if (is_some()) {
      return val;
    } else {
      return def;
    }
  }
  template <class E>
  Optional<E> map(const Mapper<T, E> &mapper) const {
    if (is_some()) {
      return mapper(value());
    } else {
      return Optional<E>();
    }
  }
  template <class E>
  friend bool operator==(const Optional<E> &a, const Optional<E> &b);
};
template <class E>
bool operator==(const Optional<E> &a, const Optional<E> &b) {
  return a.show_up == b.show_up && (!a.show_up || a.val == b.val);
}
template <class E>
bool operator!=(const Optional<E> &a, const Optional<E> &b) {
  return !(a == b);
}
template <class E>
OStream &operator<<(OStream &os, const Optional<E> &v) {
  if (v.is_none()) {
    os << "{}";
  } else {
    os << '{' << v.value() << '}';
  }
  return os;
}
}  // namespace dalt
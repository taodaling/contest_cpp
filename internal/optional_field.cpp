#pragma once
#include "common.cpp"
namespace dalt {
namespace misc {
template <class T, bool E>
struct OptionalField {};
template <class T>
struct OptionalField<T, true> {
  T value;
  T& operator->() { return value; }
  const T& operator->() const { return value; }
  T& operator*() { return value; }
  const T& operator*() const { return value; }
};
}  // namespace misc
}  // namespace dalt
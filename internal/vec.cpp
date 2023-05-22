#pragma once
#include "alias.cpp"
namespace dalt {
template <class T>
IStream& operator>>(IStream& is, Vec<T>& val) {
  for (auto& v : val) {
    is >> v;
  }
  return is;
}
#define VEC_OP(op)                         \
  template <class T>                       \
  Vec<T>& operator op(Vec<T>& data, T x) { \
    for (auto& v : data) {                 \
      v op x;                              \
    }                                      \
    return data;                           \
  }

VEC_OP(+=)
VEC_OP(-=)
VEC_OP(*=)
VEC_OP(/=)
VEC_OP(%=)
VEC_OP(^=)
VEC_OP(&=)
VEC_OP(|=)
VEC_OP(==)
VEC_OP(!=)
template <class T>
int Compare(const Vec<T>& lhs, const Vec<T>& rhs) {
  for(int i = 0; i < Size(lhs) && i < Size(rhs); i++) {
    if(lhs[i] != rhs[i]) {
      return lhs[i] < rhs[i] ? -1 : 1;
    }
  }
  return Size(lhs) < Size(rhs) ? -1 : Size(lhs) > Size(rhs) ? 1 : 0;
}
template <class T>
bool operator<(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) < 0;
}
template <class T>
bool operator>(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) > 0;
}
template <class T>
bool operator<=(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) <= 0;
}
template <class T>
bool operator>=(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) >= 0;
}
}  // namespace dalt
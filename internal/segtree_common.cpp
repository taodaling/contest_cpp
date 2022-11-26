#pragma once
#include "common.cpp"
#include "sbt_common.cpp"

namespace dalt {
namespace sbt {
template<class T = i32>
inline bool SegmentNoIntersection(T L, T R, T l, T r) {
  return R < l || r < L;
}
template <class T = i32>
inline bool SegmentCover(T L, T R, T l, T r) {
  return L <= l && r <= R;
}
}  // namespace sbt
}  // namespace dalt
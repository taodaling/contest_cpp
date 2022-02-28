#pragma once
#include "common.cpp"
#include "sbt_common.cpp"

namespace dalt {
namespace sbt {
inline bool SegmentNoIntersection(i32 L, i32 R, i32 l, i32 r) {
  return R < l || r < L;
}
inline bool SegmentCover(i32 L, i32 R, i32 l, i32 r) {
  return L <= l && r <= R;
}
}  // namespace sbt
}  // namespace dalt
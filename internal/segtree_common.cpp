#pragma once
#include "../common.cpp"

namespace dalt {
inline bool SegmentNoIntersection(i32 L, i32 R, i32 l, i32 r) {
  return R < l || r < L;
}
inline bool SegmentCover(i32 L, i32 R, i32 l, i32 r) {
  return L <= l && r <= R;
}
} // namespace dalt
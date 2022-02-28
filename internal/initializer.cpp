#pragma once
#include "common.cpp"
namespace dalt {
namespace misc {
template <i64 CID, i64 ID = 0>
struct InstanceInitializer {
  InstanceInitializer(const Function<void()>& f) { f(); }
};
template <i64 CID, i64 ID = 0>
struct ClassInitializer {
  static bool _prepare;
  ClassInitializer(const Function<void()>& f) {
    if (!_prepare) {
      f();
      _prepare = true;
    }
  }
};
template <i64 CID, i64 ID>
bool ClassInitializer<CID, ID>::_prepare = false;
}  // namespace misc
}  // namespace dalt
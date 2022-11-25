#pragma once
#include "treap.cpp"
namespace dalt {
namespace adhoc {
template <class T>
struct RangeUpdateSinglePointQuery {
  struct CID {};
  using Self = RangeUpdateSinglePointQuery<T>;
  using Treap = sbt::Treap<sbt::SelfBalanceTreeRegistry<T, T, Self::CID>>;
  struct Init {};
  Treap *root;
};
}  // namespace adhoc
}  // namespace dalt
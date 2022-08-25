#pragma once
#include "common.cpp"
#include "nil.cpp"
namespace dalt {
namespace sbt {
template <class S, class U, i64 ID = 0, class CID = Nil>
struct SelfBalanceTreeRegistry {
  using TypeS = S;
  using TypeU = U;
  static S s_nil;
  static U u_nil;
  static Adder<S, S> s_s;
  static Adder<S, U> s_u;
  static Adder<U, U> u_u;
  static void Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
                       const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    s_nil = _s_nil;
    u_nil = _u_nil;
    s_s = _s_s;
    s_u = _s_u;
    u_u = _u_u;
  }
};
template <class S, class U, i64 ID, class CID>
S SelfBalanceTreeRegistry<S, U, ID, CID>::s_nil;
template <class S, class U, i64 ID, class CID>
U SelfBalanceTreeRegistry<S, U, ID, CID>::u_nil;
template <class S, class U, i64 ID, class CID>
Adder<S, S> SelfBalanceTreeRegistry<S, U, ID, CID>::s_s;
template <class S, class U, i64 ID, class CID>
Adder<S, U> SelfBalanceTreeRegistry<S, U, ID, CID>::s_u;
template <class S, class U, i64 ID, class CID>
Adder<U, U> SelfBalanceTreeRegistry<S, U, ID, CID>::u_u;

MakeAnnotation(sbt_registry);
template<class S, class U, i64 ID, class CID>
struct is_sbt_registry<SelfBalanceTreeRegistry<S, U, ID, CID>> {
  static const bool value = true;
};

}  // namespace sbt
}  // namespace dalt
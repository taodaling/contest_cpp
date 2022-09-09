#pragma once
#include "optional_field.cpp"
namespace dalt {
namespace sbt {
template <class REG, bool EXIST>
struct SbtReverse {
  static_assert(is_sbt_registry_v<REG>);
  using S = typename REG::TypeS;
  using U = typename REG::TypeU;
  using Self = SbtReverse<REG, EXIST>;

 protected:
  misc::OptionalField<S, EXIST> sum_rev;
  IsBool(EXIST, void) init_sum_rev(const S& val) { sum_rev.value = val; }
  IsBool(!EXIST, void) init_sum_rev(const S& val) {}
  IsBool(EXIST, void) apply_sum_rev(const U& val) {
    sum_rev.value = REG::s_u(sum_rev.value, val);
  }
  IsBool(!EXIST, void) apply_sum_rev(const U& val) {}
  IsBool(EXIST, void) push_up_sum_rev(const Self& left, const Self& right) {
    sum_rev.value = REG::s_s(left.sum_rev.value, right.sum_rev.value);
  }
  IsBool(!EXIST, void) push_up_sum_rev(const Self& left, const Self& right) {}
  IsBool(EXIST, void) swap_sum_rev(S& val) { Swap(sum_rev.value, val); }
  IsBool(!EXIST, void) swap_sum_rev(S& val) {}
};

}  // namespace sbt
}  // namespace dalt
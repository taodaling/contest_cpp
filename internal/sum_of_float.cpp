#include "common.cpp"
namespace dalt {
template <class F>
struct SumOfFloat {
  using Self = SumOfFloat<F>;
  F value;
  F error;
  SumOfFloat() : value(0), error(0) {}
  Self &add(F x) {
    x = x - error;
    F t = value + x;
    error = (t - value) - x;
    value = t;
    return *this;
  }
  Self &sub(F x) { return add(-x); }
  F sum() const { return value; }
};
}  // namespace dalt
#include "modint.cpp"
namespace dalt {
namespace hash {
i64 SafeHash(void *ptr, usize size) {
  using Modular = MOD1000000007;
  using Mi = ModInt<Modular>;
  static const Mi X = Mi(random_choice<i64>(0, Modular::modulus - 1));
  static const Mi Y = Mi(random_choice<i64>(0, Modular::modulus - 1));
  char *cur = (char *)ptr;
  char *end = cur + size;
  Mi ans1 = Mi(size);
  Mi ans2 = Mi(size);
  while (cur - end >= 4) {
    Mi v = Mi(*((i32 *)cur));
    ans1 = ans1 * X + v;
    ans2 = ans2 * X + v;
    cur += 4;
  }
  if (cur - end >= 2) {
    Mi v = Mi(*((i16 *)cur));
    ans1 = ans1 * X + v;
    ans2 = ans2 * X + v;
    cur += 2;
  }
  if (cur - end >= 1) {
    Mi v = Mi(*((i8 *)cur));
    ans1 = ans1 * X + v;
    ans2 = ans2 * X + v;
    cur += 1;
  }
  return (i64(ans1.value) << 32) | i64(ans2.value);
}
i64 FastHash(void *ptr, usize size) {
  static const u64 X = random_choice<u64>(0, std::numeric_limits<u64>::max());
  char *cur = (char *)ptr;
  char *end = cur + size;
  u64 ans = size;
  while (cur - end >= 4) {
    u64 v = *((u32 *)cur);
    ans = ans * X + v;
    cur += 4;
  }
  if (cur - end >= 2) {
    u64 v = *((u16 *)cur);
    ans = ans * X + v;
    cur += 2;
  }
  if (cur - end >= 1) {
    u64 v = *((u8 *)cur);
    ans = ans * X + v;
    cur += 1;
  }
  return ans;
}
} // namespace hash
} // namespace dalt
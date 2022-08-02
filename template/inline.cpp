//Timestamp: 2022-07-24 22:55:36
#define DROP
#include <cassert>
#include <cmath>
#include <cstring>
#include <deque>
#include <fstream>
//#include <ext/pb_ds/assoc_container.hpp>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <type_traits>
#include <chrono>
#include <random>
#include <complex>
#include <bitset>
#include <set>
#include <list>
//#include "compiler_hint.cpp"
template <class T, int S>
struct MDVecDef {
  using Type = std::vector<typename MDVecDef<T, S - 1>::Type>;
};
template <class T>
struct MDVecDef<T, 0> {
  using Type = T;
};
template <class T, int S = 1>
using MDVec = typename MDVecDef<T, S>::Type;
#ifndef M_PI
#define M_PI 3.14159265358979323851280895940618620443274267017841L
#endif
#ifndef M_E
#define M_E 2.718281828459045235428168107993940338928950950503355L
#endif
#ifdef LOCAL
#define Assert(x) assert(x)
#define DebugRun(X) X
#define DebugPoint int x = 0; x++;
#else
#define Debug(...) 42
#define DebugFmtln(...) 42
#define Assert(x) 42
#define DebugRun(X)
#define DebugPoint
#endif
template<class T>
inline T DebugRet(T x) {
    Debug(x);
    return x;
}
#define const_ref(T) const T &
#define mut_ref(T) T &
#define let auto
#define var auto
#define Size(T) int((T).size())
#define All(data) data.begin(), data.end()
#define MakeUnique(data) data.resize(std::unique(All(data)) - data.begin())
#define MakeAttribute(struct_name, Type, attr_name)               \
  struct struct_name {                                            \
    using attr_name ## _type = Type;                              \
    Type attr_name;                                               \
    mut_ref(Type) get_##attr_name() { return attr_name; }         \
    const_ref(Type) get_##attr_name() const { return attr_name; } \
  };
#define MakeTemplateAttribute(struct_name, attr_name)          \
  template <class T>                                           \
  struct struct_name {                                         \
    using attr_name##_type = T;                             \
    T attr_name;                                               \
    mut_ref(T) get_##attr_name() { return attr_name; }         \
    const_ref(T) get_##attr_name() const { return attr_name; } \
  };
#define ImplDefaultEq(name)                        \
  bool operator==(const name &a, const name &b) {  \
    return std::memcmp(&a, &b, sizeof(name)) == 0; \
  }                                                \
  bool operator!=(const name &a, const name &b) { return !(a == b); }
#define ImplDefaultComparision(name)                                \
  bool operator>(const name &rhs) const { return rhs < *this; }     \
  bool operator<=(const name &rhs) const { return !(*this > rhs); } \
  bool operator>=(const name &rhs) const { return !(*this < rhs); }
#define ImplArithmeticAssignOperation(name)                                 \
  name &operator+=(const name &rhs) { return *this = (*this) + rhs; } \
  name &operator-=(const name &rhs) { return *this = (*this) - rhs; } \
  name &operator*=(const name &rhs) { return *this = (*this) * rhs; } \
  name &operator/=(const name &rhs) { return *this = (*this) / rhs; }
#define IsType(Type, param, ret_type)                                        \
  template <typename OnlyWhenArg = param>                                    \
  enable_if_t<is_same_v<OnlyWhenArg, param> && is_same_v<OnlyWhenArg, Type>, \
              ret_type>
#define IsBool(param, ret_type)       \
  template <bool OnlyWhenArg = param> \
  enable_if_t<OnlyWhenArg == (param) && OnlyWhenArg, ret_type>
#define IsBoolStatic(param, ret_type) \
  template <bool OnlyWhenArg = param> \
  static enable_if_t<OnlyWhenArg == (param) && OnlyWhenArg, ret_type>
#define MakeAnnotation(name)         \
  template <class T>                 \
  struct is_##name {                 \
    static const bool value = false; \
  };                                 \
  template <class T>                 \
  inline constexpr bool is_##name##_v = is_##name<T>::value;
#define AssignAnnotation(cls, annotation) \
  template <>                             \
  struct is_##annotation<cls> {           \
    static const bool value = true;       \
  };
#define AssignAnnotationTemplate(cls, annotation, type) \
  template <type T>                                     \
  struct is_##annotation<cls<T>> {                      \
    static const bool value = true;                     \
  };
#define FunctionAlias(from, to)                       \
  template <typename... Args>                         \
  inline auto to(Args &&...args)                      \
      ->decltype(from(std::forward<Args>(args)...)) { \
    return from(std::forward<Args>(args)...);         \
  }
#define CastToScalar(field, type) \
  operator type() const { return type(field); }
#define CastToAllScalar(field) \
  CastToScalar(field, i8);     \
  CastToScalar(field, u8);     \
  CastToScalar(field, i16);    \
  CastToScalar(field, u16);    \
  CastToScalar(field, i32);    \
  CastToScalar(field, u32);    \
  CastToScalar(field, i64);    \
  CastToScalar(field, u64);    \
  CastToScalar(field, f32);    \
  CastToScalar(field, f64);    \
  CastToScalar(field, f80);
#define COMMA ,
#ifndef LOCAL
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#else
std::mt19937 rng(0);
#endif
template <class T> T random_choice(T l, T r, std::mt19937 &gen = rng) {
  std::uniform_int_distribution<T> random(l, r);
  return random(gen);
}
namespace dalt {
#ifndef LOCAL
struct Timer {explicit Timer(const char* m) {}void stop() const {}};
#else
#endif
}
using i8 = char;
using i16 = short;
using i32 = int;
using i64 = long long;
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;
using usize = size_t;
using f32 = float;
using f64 = double;
// 16 exp, 64 precision
using f80 = long double;
FunctionAlias(std::lower_bound, LowerBound);
FunctionAlias(std::upper_bound, UpperBound);
FunctionAlias(std::unique, Unique);
FunctionAlias(std::swap, Swap);
FunctionAlias(std::min, Min);
FunctionAlias(std::max, Max);
FunctionAlias(std::abs, Abs);
FunctionAlias(std::sin, Sin);
FunctionAlias(std::asin, Asin);
FunctionAlias(std::cos, Cos);
FunctionAlias(std::acos, Acon);
FunctionAlias(std::tan, Tan);
FunctionAlias(std::atan, Atan);
FunctionAlias(std::sort, Sort);
FunctionAlias(std::fill, Fill);
FunctionAlias(std::move, Move);
FunctionAlias(std::reverse, Reverse);
FunctionAlias(std::max_element, MaxElement);
FunctionAlias(std::make_tuple, MakeTuple);
FunctionAlias(std::make_pair, MakePair);
FunctionAlias(std::clamp, Clamp);
FunctionAlias(std::shuffle, Shuffle);
FunctionAlias(std::to_string, ToString);
FunctionAlias(std::tie, Tie);
template <typename _Signature>
using Function = std::function<_Signature>;
using Str = std::string;
using String = Str;
using StringStream = std::stringstream;
using IStream = std::istream;
using OStream = std::ostream;
using std::enable_if;
using std::enable_if_t;
using std::is_base_of;
using std::is_base_of_v;
using std::is_floating_point;
using std::is_floating_point_v;
using std::is_integral;
using std::is_integral_v;
using std::is_arithmetic;
using std::is_arithmetic_v;
using std::is_same;
using std::is_same_v;
auto &Stderr = std::cerr;
auto &Stdin = std::cin;
auto &Stdout = std::cout;
template <class T>
using Less = std::less<T>;
template <class T>
using Greater = std::greater<T>;
template <typename _Key, typename _Tp, typename _Compare = Less<_Key>>
using TreeMap = std::map<_Key, _Tp, _Compare>;
template <typename _Key, typename _Compare = Less<_Key>>
using TreeSet = std::set<_Key, _Compare>;
template <typename _Key, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<_Key>>
using MultiTreeSet = std::multiset<_Key, _Compare, _Alloc>;
template <class T>
using Deque = std::deque<T>;
template <class T>
using Queue = std::queue<T>;
template <class T>
using Vec = std::vector<T>;
template <class T>
using Reducer = Function<T(const T &, const T &)>;
template <class T>
using Comparator = Function<bool(const T &, const T &)>;
template <class T>
using Indexer = Function<T(i32)>;
template <class T>
using Indexer2 = Function<T(i32, i32)>;
template <class A, class B = A, class C = A>
using Adder = Function<C(const A &, const B &)>;
template <class I>
using Checker = Function<bool(const I &)>;
template <class A, class B>
using BiChecker = Function<bool(const A &, const B &)>;
template <class T>
using Consumer = Function<void(const T &)>;
template <class FIRST, class SECOND>
using BiConsumer = Function<void(const FIRST &, const SECOND &)>;
template <class F, class T = F>
using Mapper = Function<T(const F &)>;
template <class T>
using MinHeap = std::priority_queue<T, Vec<T>, Greater<T>>;
template <class T>
using MaxHeap = std::priority_queue<T, Vec<T>, Less<T>>;
template <class T, usize S>
using Array = std::array<T, S>;
template <typename... _Elements>
using Tuple = std::tuple<_Elements...>;
template <class T, class = enable_if_t<is_floating_point_v<T>>>
using Complex = std::complex<T>;
template <class A, class B>
using Pair = std::pair<A, B>;
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
}  // namespace dalt
//#include "array_adder.cpp"
using namespace dalt;
namespace dalt {
template <class T>
inline T& Chmin(T& a, const T& b) {
  if (a > b) {
    a = b;
  }
  return a;
}
template <class T>
inline T& Chmin(T& a, const T& b, const Comparator<T> &comp) {
  if (comp(b, a)) {
    a = b;
  }
  return a;
}
template <class T>
inline T& Chmax(T& a, const T& b) {
  if (a < b) {
    a = b;
  }
  return a;
}
template <class T>
inline T& Chmax(T& a, const T& b, const Comparator<T>& comp) {
  if (comp(a, b)) {
    a = b;
  }
  return a;
}
template <class T>
inline T& AddTo(T& a, const T& b) {
  a = a + b;
  return a;
}
template <class T>
inline T& MulTo(T& a, const T& b) {
  a = a * b;
  return a;
}
template <class T>
inline T& SubFrom(T& a, const T& b) {
  a = a - b;
  return a;
}
template <class T>
inline T& DivFrom(T& a, const T& b) {
  a = a / b;
  return a;
}
template <class T, class E>
constexpr enable_if_t<is_integral_v<E>, T> PowBinaryLift(T x, E n) {
  if (n == E(0)) {
    return T(1);
  }
  auto ans = PowBinaryLift(x, n >> 1);
  ans = ans * ans;
  if (n & 1) {
    ans = ans * x;
  }
  return ans;
}
template <class T>
inline T MulLimit(T a, T b, T max, T def) {
  if (a == T(0) || b == T(0)) {
    return T(0);
  }
  // a * b <= max
  // a <= max / b
  // a <= floor(max / b)
  if (a <= max / b) {
    return a * b;
  } else {
    return def;
  }
}
template <class T>
inline T MulLimit(T a, T b, T max) {
  return MulLimit(a, b, max, max);
}
template <class T>
inline T AddLimit(T a, T b, T max, T def) {
  if (a <= max - b) {
    return a + b;
  } else {
    return def;
  }
}
template <class T>
inline T AddLimit(T a, T b, T max) {
  return AddLimit(a, b, max, max);
}
i64 Round(f32 x) { return roundf(x); }
i64 Round(f64 x) { return round(x); }
i64 Round(f80 x) { return roundl(x); }
//l + ... + r
template<class T>
T SumOfInterval(T l, T r) {
  if(l > r) {
    return T(0);
  }
  return (l + r) * (r - l + 1) / T(2);
}
template<class T>
T Pow2(T x) {
  return x * x;
}
}  // namespace dalt
namespace dalt {
template <class T>
struct Optional {
  using Self = Optional<T>;
 private:
  T val;
  bool show_up;
 public:
  Optional(const T &arg_val) : val(arg_val), show_up(true) {}
  Optional(const T &&arg_val) : val(arg_val), show_up(true) {}
  Optional() : show_up(false) {}
  const T &value() const {
    Assert(show_up);
    return val;
  }
  T &value() {
    Assert(show_up);
    return val;
  }
  T &operator*() { return value(); }
  const T &operator*() const { return value(); }
  bool is_some() const { return show_up; }
  bool is_none() const { return !show_up; }
  const T *operator->() const {
    return &value();
  }
  T *operator->() { return &value(); }
  inline operator T() const { return value(); }
  T or_else(T def) const {
    if (is_some()) {
      return val;
    } else {
      return def;
    }
  }
  template <class E>
  Optional<E> map(const Mapper<T, E> &mapper) const {
    if (is_some()) {
      return mapper(value());
    } else {
      return Optional<E>();
    }
  }
  bool operator==(const Self &b) const {
    return show_up == b.show_up && (!show_up || val == b.val);
  }
};
template <class E>
bool operator!=(const Optional<E> &a, const Optional<E> &b) {
  return !(a == b);
}
template <class E>
OStream &operator<<(OStream &os, const Optional<E> &v) {
  if (v.is_none()) {
    os << "{}";
  } else {
    os << '{' << v.value() << '}';
  }
  return os;
}
}  // namespace dalt
namespace dalt {
template <class T>
inline enable_if_t<is_integral_v<T>, T> Gcd(T a, T b) {
  while (b != 0) {
    a %= b;
    Swap(a, b);
  }
  return a;
}
// ret_value = [x, y, gcd(a,b)] that x * a + y * b = gcd(a, b)
template <class T>
inline enable_if_t<is_integral_v<T>, Array<T, 3>> ExtGcd(T a, T b) {
  if (b == 0) {
    return Array<T, 3>{1, 0, a};
  }
  auto div = a / b;
  auto ans = ExtGcd(b, a - b * div);
  auto x = ans[0];
  auto y = ans[1];
  return Array<T, 3>{y, x - a / b * y, ans[2]};
}
template <class T>
inline enable_if_t<is_integral_v<T>, Optional<T>> PossibleModInverse(
    T a, T modulus) {
  auto res = ExtGcd(a, modulus);
  if (res[2] == 1) {
    auto ans = res[0] % modulus;
    if (ans < 0) {
      ans += modulus;
    }
    return ans;
  }
  return {};
}
}  // namespace dalt
namespace dalt {
template <class T, class E>
T Modular(E val, T mod) {
  val = val % mod;
  if (val < 0) {
    val = val + mod;
  }
  return T(val);
}
inline i32 MulMod(i32 a, i32 b, i32 modulus) {
  i64 res = i64(a) * i64(b) % modulus;
  return i32(res);
}
inline i64 MulMod(i64 a, i64 b, i64 modulus) {
  i64 k = roundl((f80)a / modulus * b);
  i64 res = (a * b - k * modulus) % modulus;
  if (res < 0) {
    res += modulus;
  }
  return res;
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> AddMod(T a, T b, T modulus) {
  T res = a + b;
  if (res >= modulus) {
    res -= modulus;
  }
  return res;
}
template <class T, class E>
inline enable_if_t<is_integral_v<T> && is_integral_v<E>, T> PowMod(T x, E exp,
                                                                   T modulus) {
   Assert(exp >= E(0));                                                          
  if (exp == E(0)) {
    return modulus == T(1) ? T(0) : T(1);
  }
  T ans = PowMod(x, exp >> 1, modulus);
  ans = MulMod(ans, ans, modulus);
  if (exp & T(1)) {
    ans = MulMod(ans, x, modulus);
  }
  return ans;
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> SubMod(T a, T b, T modulus) {
  T res = a - b;
  if (res < T(0)) {
    res += modulus;
  }
  return res;
}
}  // namespace dalt
namespace dalt {
// using Type = T;
// static T modulus;
// static T primitive_root;
MakeAnnotation(modular);
template <class T, i64 M, i64 PR, i64 PHI = M - 1>
struct StaticModular {
  static_assert(is_integral_v<T>);
  const static T modulus = M;
  const static T primitive_root = PR;
  const static T phi = PHI;
  using Type = T;
};
template <class T, i64 M, i64 PR, i64 PHI>
struct is_modular<StaticModular<T, M, PR, PHI>> {
  static const bool value = true;
};
using MOD998244353 =
    StaticModular<i32, 998244353, 3>;
using MOD1000000007 = StaticModular<i32, 1000000007, 5>;
using MOD1000000009 = StaticModular<i32, 1000000009, 13>;
using MOD_BIG = StaticModular<i64, 2305843009213693951, -1>;
// last used: -2
template <class T = i32, i64 CID = 0, i64 ID = 0>
struct DynamicModular {
  static_assert(is_integral_v<T>);
  static T modulus;
  static T primitive_root;
  static T phi;
  static void Register(T _modulus, T _primitive_root = T(), T _phi = T()) {
    modulus = _modulus;
    primitive_root = _primitive_root;
    phi = _phi;
  }
  using Type = T;
};
template <class T, i64 CID, i64 ID>
T DynamicModular<T, CID, ID>::modulus = T();
template <class T, i64 CID, i64 ID>
T DynamicModular<T, CID, ID>::primitive_root = T();
template <class T, i64 CID, i64 ID>
T DynamicModular<T, CID, ID>::phi = T();
template <class T, i64 CID, i64 ID>
struct is_modular<DynamicModular<T, CID, ID>> {
  static const bool value = true;
};
MakeAnnotation(modint);
#define MOD MODULAR::modulus
#define SELF ModInt<MODULAR>
#define TEMPLATE_ARGS template <class MODULAR>
TEMPLATE_ARGS struct ModInt {
  using Modular = MODULAR;
  using Type = typename MODULAR::Type;
  static_assert(is_modular_v<MODULAR>);
  static_assert(is_integral_v<Type>);
  Type value;
  using Self = SELF;
  ModInt() : value(0) {}
  ModInt(const Type &v) {
    value = v;
    if (value < 0 || value >= MOD) {
      value %= MOD;
      if (value < 0) {
        value += MOD;
      }
    }
    Assert(value >= 0);
  }
  static Self nil() {
    Self res;
    res.value = -1;
    return res;
  }
  bool is_nil() {
    return value == -1;
  }
  explicit operator Type() const { return value; }
  static Type modulus() { return MOD; }
  static Type primitive_root() { return Modular::primitive_root; }
  Self operator-() const { return Self(0) - *this; }
  template <class F>
  static enable_if_t<is_integral_v<F>, Self> of(F v) {
    v %= MOD;
    if (v < 0) {
      v += MOD;
    }
    return Self(v);
  }
  Optional<Self> possible_inv() const {
    auto raw_optional_inv = PossibleModInverse(value, MOD);
    if (raw_optional_inv.is_some()) {
      return Self(raw_optional_inv.value());
    } else {
      return {};
    }
  }
  Self operator+(const Self &rhs) const {
    auto res = value + rhs.value;
    if (res >= MOD) {
      res -= MOD;
    }
    return res;
  }
  Self operator-(const Self &rhs) const {
    auto res = value - rhs.value;
    if (res < Type(0)) {
      res += MOD;
    }
    return res;
  }
  Self operator/(const SELF &rhs) const {
    auto inv = Self(rhs.possible_inv().value());
    return (*this) * inv;
  }
  bool operator==(const Self &b) const { return value == b.value; }
  bool operator!=(const Self &b) const { return value != b.value; }
  bool operator<(const Self &b) const { return value < b.value; }
  ImplDefaultComparision(Self);
  ImplArithmeticAssignOperation(Self);
  template <class E>
  enable_if_t<is_integral_v<E>, Self> pow(E n) {
    return PowBinaryLift(*this, n);
  }
  friend inline IStream &operator>>(IStream &is, Self &x) {
    Type val;
    is >> val;
    x = Self(val);
    return is;
  }
  friend inline OStream &operator<<(OStream &os, const Self &x) {
    os << x.value;
    return os;
  }
};
TEMPLATE_ARGS inline enable_if_t<!is_same_v<MODULAR, MOD_BIG>, SELF> operator*(
    const SELF &a, const SELF &b) {
  return SELF(MulMod(a.value, b.value, MOD));
}
TEMPLATE_ARGS inline enable_if_t<is_same_v<MODULAR, MOD_BIG>, SELF> operator*(
    const SELF &x, const SELF &y) {
  static u64 mask = (u64(1) << 32) - 1;
  static u64 mod = MOD_BIG::modulus;
  u64 a = x.value;
  u64 b = y.value;
  u64 l1 = a & mask;
  u64 h1 = (a >> 32) & mask;
  u64 l2 = b & mask;
  u64 h2 = (b >> 32) & mask;
  u64 l = l1 * l2;
  u64 m = l1 * h2 + l2 * h1;
  u64 h = h1 * h2;
  u64 ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + ((m << 35) >> 3) + 1;
  ret = (ret & mod) + (ret >> 61);
  ret = (ret & mod) + (ret >> 61);
  return SELF(ret - 1);
}
TEMPLATE_ARGS struct is_modint<ModInt<MODULAR>> {
  static const bool value = true;
};
#undef TEMPLATE_TYPE
#undef MOD
using ModInt998244353 = ModInt<MOD998244353>;
using ModInt1000000007 = ModInt<MOD1000000007>;
using ModInt1000000009 = ModInt<MOD1000000009>;
}  // namespace dalt
namespace dalt {
namespace math {
struct EulerSieve {
 public:
  static Vec<int> primes;
  static Vec<bool> is_comp;
  static Vec<int> smallest_prime_factor;
  static Vec<int> exp_of_smallest_prime_factor;
  EulerSieve() {
    is_comp.resize(2);
    smallest_prime_factor.resize(2);
    exp_of_smallest_prime_factor.resize(2);
    ensure(1e6 + 10);
  }
  //trigger recompute if necessary
  static void ensure(int n) {
    int cur_size = is_comp.size();
    if (cur_size >= n) {
      return;
    }
    primes.reserve(n);
    is_comp.resize(n);
    smallest_prime_factor.resize(n);
    exp_of_smallest_prime_factor.resize(n);
    primes.clear();
    for (int i = 2; i < n; i++) {
      if (!is_comp[i]) {
        primes.push_back(i);
        exp_of_smallest_prime_factor[i] = smallest_prime_factor[i] = i;
      }
      int pi;
      for (int j = 0; j < Size(primes) && (pi = primes[j] * i) < n; j++) {
        smallest_prime_factor[pi] = primes[j];
        exp_of_smallest_prime_factor[pi] =
            smallest_prime_factor[i] == primes[j]
                ? (exp_of_smallest_prime_factor[i] *
                   exp_of_smallest_prime_factor[primes[j]])
                : exp_of_smallest_prime_factor[primes[j]];
        is_comp[pi] = true;
        if (i % primes[j] == 0) {
          break;
        }
      }
    }
  }
  //(factor, exp_factor)
  // O(n + n / ln(n) * O(per f) )
  template <class T>
  static Vec<T> calc_multiplicative_function(int n,
                                             const Function<T(int, int)>& f) {
    ensure(n);
    Vec<T> ans(n);
    if (n > 0) {
      ans[0] = T(0);
    }
    if (n > 1) {
      ans[1] = T(1);
    }
    for (int i = 2; i < n; i++) {
      if (exp_of_smallest_prime_factor[i] != i) {
        ans[i] = ans[exp_of_smallest_prime_factor[i]] *
                 ans[i / exp_of_smallest_prime_factor[i]];
      } else {
        ans[i] = f(smallest_prime_factor[i], i);
      }
    }
    return ans;
  }
  template <class T>
  static Vec<T> calc_totally_multiplicative_function(
      int n, const Function<T(int)>& f) {
    ensure(n);
    Vec<T> ans(n);
    if (n > 0) {
      ans[0] = f(0);
    }
    if (n > 1) {
      ans[1] = f(1);
    }
    for (int i = 2; i < n; i++) {
      if (smallest_prime_factor[i] != i) {
        ans[i] =
            ans[smallest_prime_factor[i]] * ans[i / smallest_prime_factor[i]];
      } else {
        ans[i] = f(i);
      }
    }
    return ans;
  }
  template <class T>
  static enable_if_t<is_modint_v<T>, Vec<T>> powmod(int n, int k) {
    static const i64 ID = -1;
    return calc_totally_multiplicative_function<T>(n, [&](auto x) -> T {
      return PowBinaryLift(T(x), k);
    });
  }
  static Vec<int> get_mobius(int n) {
    return calc_multiplicative_function<int>(
        n, [&](auto factor, auto exp_factor) -> int {
          if (factor == exp_factor) {
            return -1;
          } else {
            return 0;
          }
        });
  }
  static Vec<int> get_euler(int n) {
    return calc_multiplicative_function<int>(
        n, [&](auto factor, auto exp_factor) -> int {
          return exp_factor - exp_factor / factor;
        });
  }
  static Vec<int> get_factor(int n) {
    ensure(n);
    Vec<int> ans(n);
    if (n > 0) {
      ans[0] = 0;
    }
    if (n > 1) {
      ans[1] = 1;
    }
    for (int i = 2; i < n; i++) {
      if (!is_comp[i]) {
        ans[i] = 2;
      } else if (i == exp_of_smallest_prime_factor[i]) {
        ans[i] = 1 + ans[i / smallest_prime_factor[i]];
      } else {
        ans[i] = ans[exp_of_smallest_prime_factor[i]] *
                 ans[i / exp_of_smallest_prime_factor[i]];
      }
    }
    return ans;
  }
} __EULER_SIEVE__;
Vec<int> EulerSieve::primes;
Vec<bool> EulerSieve::is_comp;
Vec<int> EulerSieve::smallest_prime_factor;
Vec<int> EulerSieve::exp_of_smallest_prime_factor;
//void CONSTRUCT _InitEulerSieve() { EulerSieve::ensure(1e6); }
}  // namespace math
}  // namespace dalt
namespace dalt {
// Check whether n is a prime s times, O(slog n)
template <class T> enable_if_t<is_integral_v<T>, bool> MillerRabin(T n, int s = 10) {
  using Modular = DynamicModular<T, -2>;
  using mi = ModInt<Modular>;
  Modular::Register(n);
  auto test = [&](auto &test, mi y, T exp, T n) -> bool {
    auto y2 = y * y;
    if (!(exp == n - 1 || test(test, y2, exp * 2, n))) {
      return false;
    }
    if (exp != n - 1 && y2.value != 1) {
      return true;
    }
    if (y.value != 1 && y.value != n - 1) {
      return false;
    }
    return true;
  };
  if (n <= 1) {
    return false;
  }
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }
  T m = n - 1;
  while (m % 2 == 0) {
    m /= 2;
  }
  for (int i = 0; i < s; i++) {
    T x = random_choice<T>(2, n - 1);
    if (!test(test, PowBinaryLift(mi(x), m), m, n)) {
      return false;
    }
  }
  return true;
}
} // namespace dalt
namespace dalt {
// find any factor, if nothing find, return n, don't invoke it directly, turn to
// FindFactor instead
template <class T>
enable_if_t<is_integral_v<T>, T> PollardRho(T n) {
  if (n <= 1) {
    return n;
  }
  if (n % 2 == 0) {
    return 2;
  }
  if (n % 3 == 0) {
    return 3;
  }
  T x = 0, y = x, t, q = 1, c = random_choice<T>(1, n - 2);
  for (int k = 2;; k <<= 1, y = x, q = 1) {
    for (int i = 1; i <= k; ++i) {
      x = AddMod(MulMod(x, x, n), c, n);
      q = MulMod(q, Abs(x - y), n);
      if ((i & 127) == 0) {
        t = Gcd(q, n);
        if (t > 1) {
          return t;
        }
      }
    }
    if ((t = Gcd(q, n)) > 1) {
      return t;
    }
  }
}
// find any factor, if nothing find, return n
template <class T>
enable_if_t<is_integral_v<T>, T> FindFactor(T n) {
  //Debug(n);
  if (n == 1) {
    return 1;
  }
  if (MillerRabin(n, 10)) {
    return n;
  }
  while (true) {
    T f = PollardRho(n);
    if (f != n) {
      return f;
    }
  }
  Debug("over");
}
template <class T>
enable_if_t<is_integral_v<T>, T> FindPrimeFactor(T n) {
  T res;
  while ((res = FindFactor(n)) != n) {
    n = res;
  }
  return n;
}
// Find all factors of n
template <class T>
enable_if_t<is_integral_v<T>, Vec<T>> Factorize(T n) {
  const static T SMALL_PRIMES[]{2, 3, 5, 7, 11, 13, 17, 19};
  Assert(n != 0);
  Vec<T> set;
  for (T p : SMALL_PRIMES) {
    if (n % p != 0) {
      continue;
    }
    set.push_back(p);
    while (n % p == 0) {
      n /= p;
    }
  }
  auto dfs = [&](auto &dfs, T n) {
    if (n == T(1)) {
      return;
    }
    T f = FindFactor(n);
    if (f == n) {
      set.push_back(f);
      return;
    }
    T otherPart = n / f;
    dfs(dfs, f);
    dfs(dfs, otherPart);
  };
  dfs(dfs, n);
  Sort(All(set));
  MakeUnique(set);
  return set;
}
}  // namespace dalt
#ifndef _builtin_clz
inline i32 _builtin_clz(u32 i) {
  // HD, Count leading 0's
  if (i <= 0) return i == 0 ? 32 : 0;
  int n = 31;
  if (i >= 1 << 16) {
    n -= 16;
    i >>= 16;
  }
  if (i >= 1 << 8) {
    n -= 8;
    i >>= 8;
  }
  if (i >= 1 << 4) {
    n -= 4;
    i >>= 4;
  }
  if (i >= 1 << 2) {
    n -= 2;
    i >>= 2;
  }
  return n - (i >> 1);
}
#endif
#ifndef _builtin_clzll
inline i32 _builtin_clzll(u64 i) {
  u32 x = u32(i >> 32);
  return x == 0 ? 32 + _builtin_clz((int)i) : _builtin_clz(x);
}
#endif
#ifndef _builtin_ctz
inline i32 _builtin_ctz(u32 i) {
  // HD, Figure 5-14
  int y;
  if (i == 0) return 32;
  int n = 31;
  y = i << 16;
  if (y != 0) {
    n = n - 16;
    i = y;
  }
  y = i << 8;
  if (y != 0) {
    n = n - 8;
    i = y;
  }
  y = i << 4;
  if (y != 0) {
    n = n - 4;
    i = y;
  }
  y = i << 2;
  if (y != 0) {
    n = n - 2;
    i = y;
  }
  return n - ((i << 1) >> 31);
}
#endif
#ifndef _builtin_ctzll
inline i32 _builtin_ctzll(u64 i) {
  // HD, Figure 5-14
  int x, y;
  if (i == 0) return 64;
  int n = 63;
  y = (int)i;
  if (y != 0) {
    n = n - 32;
    x = y;
  } else
    x = (int)(i >> 32);
  y = x << 16;
  if (y != 0) {
    n = n - 16;
    x = y;
  }
  y = x << 8;
  if (y != 0) {
    n = n - 8;
    x = y;
  }
  y = x << 4;
  if (y != 0) {
    n = n - 4;
    x = y;
  }
  y = x << 2;
  if (y != 0) {
    n = n - 2;
    x = y;
  }
  return n - ((x << 1) >> 31);
}
#endif
#ifndef _builtin_popcount
inline i32 _builtin_popcount(u32 i) {
  // HD, Figure 5-2
  i = i - ((i >> 1) & 0x55555555);
  i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
  i = (i + (i >> 4)) & 0x0f0f0f0f;
  i = i + (i >> 8);
  i = i + (i >> 16);
  return i & 0x3f;
}
#endif
#ifndef _builtin_popcountll
inline i32 _builtin_popcountll(u64 i) {
  // HD, Figure 5-2
  i = i - ((i >> 1) & 0x5555555555555555ll);
  i = (i & 0x3333333333333333ll) + ((i >> 2) & 0x3333333333333333ll);
  i = (i + (i >> 4)) & 0x0f0f0f0f0f0f0f0fll;
  i = i + (i >> 8);
  i = i + (i >> 16);
  i = i + (i >> 32);
  return (int)i & 0x7f;
}
#endif
namespace dalt {
inline i32 LeadingZeroNumber(u32 x) {
  if (x == 0) return 32;
  return _builtin_clz(x);
}
inline i32 LeadingZeroNumber(i32 x) { return LeadingZeroNumber(u32(x)); }
inline i32 LeadingZeroNumber(u64 x) {
  if (x == 0) return 64;
  return _builtin_clzll(x);
}
inline i32 LeadingZeroNumber(i64 x) { return LeadingZeroNumber(u64(x)); }
inline i32 TrailingZeroNumber(u32 x) {
  if (x == 0) return 32;
  return _builtin_ctz(x);
}
inline i32 TrailingZeroNumber(i32 x) { return TrailingZeroNumber(u32(x)); }
inline i32 TrailingZeroNumber(u64 x) {
  if (x == 0) return 64;
  return _builtin_ctzll(x);
}
inline i32 TrailingZeroNumber(i64 x) { return TrailingZeroNumber(u64(x)); }
inline i32 Log2Ceil(u32 x) {
  if (x == 0) {
    return 0;
  }
  return 32 - LeadingZeroNumber(x - 1);
}
inline i32 Log2Ceil(u64 x) {
  if (x == 0) {
    return 0;
  }
  return 64 - LeadingZeroNumber(x - 1);
}
inline i32 Log2Floor(u32 x) {
  if (x == 0) {
    return -1;
  }
  return 31 - LeadingZeroNumber(x);
}
inline i32 Log2Floor(u64 x) {
  if (x == 0) {
    return -1;
  }
  return 63 - LeadingZeroNumber(x);
}
inline i32 Log2Ceil(i32 x) { return Log2Ceil(u32(x)); }
inline i32 Log2Ceil(i64 x) { return Log2Ceil(u64(x)); }
inline i32 Log2Floor(i32 x) { return Log2Floor(u32(x)); }
inline i32 Log2Floor(i64 x) { return Log2Floor(u64(x)); }
inline i32 CountBit(u32 x) { return _builtin_popcount(x); }
inline i32 CountBit(i32 x) { return CountBit(u32(x)); }
inline i32 CountBit(u64 x) { return _builtin_popcountll(x); }
inline i32 CountBit(i64 x) { return CountBit(u64(x)); }
inline i32 HighestOneBitOffset(u32 x) { return Log2Floor(x); }
inline i32 HighestOneBitOffset(i32 x) { return HighestOneBitOffset(u32(x)); }
inline i32 HighestOneBitOffset(u64 x) { return Log2Floor(x); }
inline i32 HighestOneBitOffset(i64 x) { return HighestOneBitOffset(u64(x)); }
template <class T>
inline enable_if_t<is_integral_v<T>, T> LowestOneBit(T x) {
  return x & -x;
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> HighestOneBit(T x) {
  if (x == 0) {
    return x;
  }
  return T(1) << HighestOneBitOffset(x);
}
template <class T>
inline enable_if_t<is_integral_v<T>, i32> LowestOneBitOffset(T x) {
  if (x == 0) {
    return -1;
  }
  return HighestOneBitOffset(LowestOneBit(x));
}
inline u32 HighestKOnes32(i32 k) {
  if (k == 0) {
    return 0;
  }
  return (~u32()) << (32 - k);
}
inline u64 HighestKOnes64(i32 k) {
  if (k == 0) {
    return 0;
  }
  return (~u64()) << (64 - k);
}
inline u32 LowestKOnes32(i32 k) {
  if (k == 0) {
    return 0;
  }
  return (~u32()) >> (32 - k);
}
inline u64 LowestKOnes64(i32 k) {
  if (k == 0) {
    return 0;
  }
  return (~u64()) >> (64 - k);
}
inline u64 IntervalOnes64(i32 l, i32 r) {
  if (l > r) {
    return 0;
  }
  u64 high = r < 63 ? (u64(-1) << r + 1) : 0;
  u64 low = u64(-1) << l;
  return high ^ low;
}
inline u32 IntervalOnes32(i32 l, i32 r) {
  if (l > r) {
    return 0;
  }
  u32 high = r < 31 ? (u32(-1) << r + 1) : 0;
  u32 low = u32(-1) << l;
  return high ^ low;
}
template <class T>
inline enable_if_t<is_integral_v<T>, i32> KthBit(T x, i32 k) {
  return (x >> k) & 1;
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> SetBit(T x, i32 k) {
  return x | (T(1) << k);
}
template <class T>
inline enable_if_t<is_integral_v<T>, T> ClearBit(T x, i32 k) {
  return x & ~(T(1) << k);
}
}  // namespace dalt
namespace dalt {
namespace hash {
// https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
inline u64 Shuffle(u64 x) {
  static const uint64_t C = uint64_t(2e18 * M_PI) + 71;  // large odd number
  static const int RANDOM = rng();
  return __builtin_bswap64((x ^ RANDOM) * C);
}
i64 SafeHash(const void *ptr, usize size) {
  using Mi1 = ModInt1000000007;
  using Mi2 = ModInt1000000009;
  static const Mi1 X1 = Mi1(random_choice<i32>(1, Mi1::modulus() - 1));
  static const Mi2 X2 = Mi2(random_choice<i32>(1, Mi2::modulus() - 1));
  Mi1 ans1 = Mi1(size);
  Mi2 ans2 = Mi2(size);
  const char *cur = (const char *)ptr;
  int offset = 0;
  while (size - offset >= 4) {
    i32 v = *(i32 *)(cur + offset);
    ans1 = ans1 * X1 + Mi1(v);
    ans2 = ans2 * X2 + Mi2(v);
    offset += 4;
  }
  if (size - offset >= 2) {
    i32 v = *(i16 *)(cur + offset);
    ans1 = ans1 * X1 + Mi1(v);
    ans2 = ans2 * X2 + Mi2(v);
    offset += 2;
  }
  if (size - offset >= 1) {
    i32 v = *(i8 *)(cur + offset);
    ans1 = ans1 * X1 + Mi1(v);
    ans2 = ans2 * X2 + Mi2(v);
    offset += 1;
  }
  return (i64(ans1.value) << 32) | ans2.value;
}
i64 FastHash(const void *ptr, usize size) {
  static const i64 X = random_choice<i64>(std::numeric_limits<i64>::min(),
                                          std::numeric_limits<i64>::max());
  const char *cur = (const char *)ptr;
  int offset = 0;
  i64 ans = size;
  while (size - offset >= 8) {
    i64 v = *((i64 *)(cur + offset));
    ans = ans * X + v;
    offset += 8;
  }
  if (size - offset >= 4) {
    i64 v = *((i32 *)(cur + offset));
    ans = ans * X + v;
    offset += 4;
  }
  if (size - offset >= 2) {
    i64 v = *((i16 *)(cur + offset));
    ans = ans * X + v;
    offset += 2;
  }
  if (size - offset >= 1) {
    i64 v = *((u8 *)(cur + offset));
    ans = ans * X + v;
    offset += 1;
  }
  return ans;
}
template <class T>
inline i64 Hash(const T &val) {
  return SafeHash(&val, sizeof(T));
}
template <>
inline i64 Hash<i64>(const i64 &val) {
  return val;
}
template <>
inline i64 Hash<i32>(const i32 &val) {
  return val;
}
}  // namespace hash
}  // namespace dalt
namespace dalt {
template <class T> enable_if_t<is_integral_v<T>, T> DivFloor(T a, T b) {
  Assert(b > 0);
  auto ans = a / b;
  if (ans * b > a) {
    ans = ans - 1;
  }
  return ans;
}
template <class T> enable_if_t<is_integral_v<T>, T> DivCeil(T a, T b) {
  Assert(b > 0);
  auto ans = a / b;
  if (ans * b < a) {
    ans = ans + 1;
  }
  return ans;
}
template <class T>
enable_if_t<is_floating_point_v<T>, T> DivFloor(T a, T b) {
  return a / b;
}
template <class T>
enable_if_t<is_floating_point_v<T>, T> DivCeil(T a, T b) {
  return a / b;
}
template <class T>
enable_if_t<is_integral_v<T>, T> SmallerValue(T val) {
  return val - 1;
}
template <class T>
enable_if_t<is_integral_v<T>, T> LargerValue(T val) {
  return val + 1;
}
template <class T>
enable_if_t<is_floating_point_v<T>, T> SmallerValue(T val) {
  return val;
}
template <class T>
enable_if_t<is_floating_point_v<T>, T> LargerValue(T val) {
  return val;
}
} // namespace dalt
namespace dalt {
template <class T>
bool InRange(T l, T r, T x) {
  return l <= x && x <= r;
}
template <class T>
bool InRangeRotate(T l, T r, T x) {
  if (l <= r) {
    return InRange(l, r, x);
  } else {
    return !InRange(LargerValue(r), SmallerValue(l), x);
  }
}
}  // namespace dalt
namespace dalt {
struct Nil {};
Nil operator+(const Nil &a, const Nil &b) { return Nil(); }
Nil operator-(const Nil &a, const Nil &b) { return Nil(); }
Nil operator*(const Nil &a, const Nil &b) { return Nil(); }
Nil operator/(const Nil &a, const Nil &b) { return Nil(); }
bool operator==(const Nil &a, const Nil &b) { return true; }
bool operator!=(const Nil &a, const Nil &b) { return false; }
OStream &operator<<(OStream &os, const Nil &b) {
  os << "{}";
  return os;
}
} // namespace dalt
namespace dalt {
namespace hash {
template <class K, class V = Nil>
struct HashMap {
  using Self = HashMap<K, V>;
 private:
  static const i32 NON_EXIST = 0;
  Vec<Pair<K, V>> entries;
  Vec<i32> hash_val;
  i32 mask;
  i32 size;
  int index_of(const K& key, i32 h) const {
    i32 index = h & mask;
    while (hash_val[index] != NON_EXIST) {
      if (hash_val[index] == h && entries[index].first == key) {
        return index;
      }
      index = (index + 1) & mask;
    }
    return index;
  }
 public:
  struct CIter
      : public std::iterator<std::bidirectional_iterator_tag, Pair<K, V>> {
    const HashMap<K, V>* hm;
    i32 index;
    const Pair<K, V>& operator*() {
      Assert(index < Size(hm->entries));
      Assert(hm->hash_val[index] != NON_EXIST);
      return hm->entries[index];
    }
    const Pair<K, V>* operator->() const {
      return &hm->entries[index];
    }
    CIter& operator++() {
      index++;
      while (index < Size(hm->entries) && hm->hash_val[index] == NON_EXIST) {
        index++;
      }
      return *this;
    }
    CIter operator++(int) {
      auto ans = *this;
      ++(*this);
      return ans;
    }
    CIter& operator--() {
      index--;
      while (index >= 0 && hm->hash_val[index] == NON_EXIST) {
        index--;
      }
      return *this;
    }
    CIter operator--(int) {
      Iter ans = *this;
      --(*this);
    }
    bool operator<(const CIter& rhs) const { return index < rhs.index; }
    bool operator>(const CIter& rhs) const { return index > rhs.index; }
    bool operator==(const CIter& rhs) const { return index == rhs.index; }
    bool operator!=(const CIter& rhs) const { return index != rhs.index; }
  };
  struct Iter
      : public std::iterator<std::bidirectional_iterator_tag, Pair<K, V>> {
    HashMap<K, V>* hm;
    i32 index;
    Pair<K, V>& operator*() {
      Assert(index < Size(hm->entries));
      Assert(hm->hash_val[index] != NON_EXIST);
      return hm->entries[index];
    }
    const Pair<K, V>& operator*() const {
      Assert(index < Size(hm->entries));
      Assert(hm->hash_val[index] != NON_EXIST);
      return hm->entries[index];
    }
    Pair<K, V>* operator->() { return &hm->entries[index]; }
    Iter& operator++() {
      index++;
      while (index < Size(hm->entries) && hm->hash_val[index] == NON_EXIST) {
        index++;
      }
      return *this;
    }
    Iter operator++(int) {
      auto ans = *this;
      ++(*this);
      return ans;
    }
    Iter& operator--() {
      index--;
      while (index >= 0 && hm->hash_val[index] == NON_EXIST) {
        index--;
      }
      return *this;
    }
    Iter operator--(int) {
      Iter ans = *this;
      --(*this);
    }
    bool operator<(const Iter& rhs) { return index < rhs.index; }
    bool operator>(const Iter& rhs) { return index > rhs.index; }
    bool operator==(const Iter& rhs) { return index == rhs.index; }
    bool operator!=(const Iter& rhs) { return index != rhs.index; }
  };
  void recap(i32 cap) {
    cap = Max(cap, 2);
    decltype(entries) old_entry(cap);
    decltype(hash_val) old_hash_val(cap);
    entries.swap(old_entry);
    hash_val.swap(old_hash_val);
    mask = cap - 1;
    size = 0;
    for (int i = 0; i < Size(old_entry); i++) {
      if (old_hash_val[i] != NON_EXIST) {
        put(Move(old_entry[i]), old_hash_val[i]);
      }
    }
  }
  bool contain(const K& key) const {
    return find(key) != end();
  }
  i32 get_hash(i64 hash) const {
    hash = Shuffle(hash);
    if (hash == NON_EXIST) {
      hash = -1;
    }
    return hash;
  }
  bool check_health() {
    if (size * 2 > Size(entries)) {
      recap(Size(entries) * 2);
      return true;
    }
    return false;
  }
  void put(Pair<K, V> kv, i32 hash) {
    auto& key = kv.first;
    i32 pos = index_of(kv.first, hash);
    if (hash_val[pos] == NON_EXIST) {
      size++;
    }
    entries[pos] = Move(kv);
    hash_val[pos] = hash;
    check_health();
  }
 public:
  HashMap(i32 cap = 1) : size(0) {
    cap = 1 << Log2Ceil(cap);
    recap(cap * 2);
  }
  void put(Pair<K, V> kv) { put(Move(kv), get_hash(Hash(kv.first))); }
  void put(K key, V value) { put(Pair<K, V>(Move(key), Move(value))); }
  Iter find(const K& key) {
    i32 hash = get_hash(Hash(key));
    i32 pos = index_of(key, hash);
    if (hash_val[pos] != NON_EXIST) {
      return Iter{
          .hm = this,
          .index = pos,
      };
    }
    return end();
  }
  CIter find(const K& key) const {
    i32 hash = get_hash(Hash(key));
    i32 pos = index_of(key, hash);
    if (hash_val[pos] != NON_EXIST) {
      return CIter{
          .hm = this,
          .index = pos,
      };
    }
    return end();
    return end();
  }
  V& operator[](const K& key) {
    i32 hash = get_hash(Hash(key));
    i32 pos = index_of(key, hash);
    if (hash_val[pos] != NON_EXIST) {
      return entries[pos].second;
    }
    entries[pos] = Pair<K, V>(key, V());
    hash_val[pos] = hash;
    size++;
    if (check_health()) {
      return (*this)[key];
    }
    return entries[pos].second;
  }
  void remove(const K& key) {
    i32 hash = get_hash(Hash(key));
    i32 h = index_of(key, hash);
    if (hash_val[h] == NON_EXIST) {
      return;
    }
    size--;
    hash_val[h] = NON_EXIST;
    int iter = (h + 1) & mask;
    while (hash_val[iter] != NON_EXIST) {
      i32 insert_pos = hash_val[iter] & mask;
      if (InRangeRotate(iter + 1, h, insert_pos)) {
        Swap(entries[h], entries[iter]);
        Swap(hash_val[h], hash_val[iter]);
        h = iter;
      }
      iter = (iter + 1) & mask;
    }
  }
  CIter end() const {
    return CIter{
        .hm = this,
        .index = Size(hash_val),
    };
  }
  CIter rbegin() const {
    return --CIter{
        .hm = this,
        .index = Size(hash_val),
    };
  }
  CIter rend() const {
    return CIter{
        .hm = this,
        .index = -1,
    };
  }
  CIter begin() const {
    return ++CIter{
        .hm = this,
        .index = -1,
    };
  }
  Iter begin() {
    return ++Iter{
        .hm = this,
        .index = -1,
    };
  }
  Iter end() {
    return Iter{
        .hm = this,
        .index = Size(hash_val),
    };
  }
  Iter rbegin() {
    return --Iter{
        .hm = this,
        .index = Size(hash_val),
    };
  }
  Iter rend() {
    return Iter{
        .hm = this,
        .index = -1,
    };
  }
  Vec<Pair<K, V>> to_vec() const {
    Vec<Pair<K, V>> res;
    for (auto& kv : *this) {
      res.push_back(kv);
    }
    return res;
  }
};
}  // namespace hash
}  // namespace dalt
namespace dalt {
namespace math {
template <class I, class T, i64 CACHE = 0>
enable_if_t<is_integral_v<I>, T> BigMultiplicativeFunctionEval(
    I N, const Function<T(I, I)> &f) {
  static hash::HashMap<I, T> cache;
  if (N <= 1) {
    return T(N);
  }
  T ans;
  auto iter = cache.end();
  if (CACHE == 0 || (iter = cache.find(N)) == cache.end()) {
    if (N < Size(EulerSieve::is_comp)) {
      T res = 1;
      while (N > 1) {
        res = res * f(EulerSieve::smallest_prime_factor[N],
                      EulerSieve::exp_of_smallest_prime_factor[N]);
        N = N / EulerSieve::exp_of_smallest_prime_factor[N];
      }
      ans = res;
    } else {
      I factor = FindPrimeFactor(N);
      I a = 1;
      I b = N;
      while (b % factor == 0) {
        b = b / factor;
        a = a * factor;
      }
      ans = f(factor, a) * BigMultiplicativeFunctionEval(b, f);
    }
    if (CACHE != -1) {
      cache[N] = ans;
    }
  } else {
    ans = iter->second;
  }
  return ans;
}
template <class I>
I MobiusEval(I n) {
  return BigMultiplicativeFunctionEval<I, I>(
      n, [](auto x, auto xp) { return xp == x ? I(-1) : I(0); });
}
template <class I>
I EulerFunctionEval(I n) {
  return BigMultiplicativeFunctionEval<I, I>(
      n, [](auto x, auto xp) { return xp - xp / x; });
}
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace math {
template <class T>
struct CoprimeModLog {
  static_assert(is_modint_v<T>);
  using Type = T;
  using TType = typename T::Type;
  hash::HashMap<T, int> map;
  TType m;
  T inv_m;
  TType phi;
  CoprimeModLog(T x) {
    phi = EulerFunctionEval(T::modulus());
    m = std::ceil(std::sqrt(T::modulus()));
    map = hash::HashMap<T, int>(m);
    T inv_x = T(1) / x;
    inv_m = inv_x.pow(m);
    T prod = T(1);
    for (int i = 0; i < m; i++) {
      map[prod] = i;
      prod = prod * x;
    }
  }
  //return minimum t that satisfy x^t = y
  Optional<int> log(T y, TType atleast = 0) {
    T start = y;
    auto modular = T::modulus();
    for (decltype(modular) i = 0; i * m < modular; start *= inv_m, i++) {
      auto iter = map.find(start);
      if (iter != map.end()) {
        auto ans = (iter->second + i * m) % phi;
        if (ans >= atleast) {
          return ans;
        }
      }
    }
    return {};
  }
};
}  // namespace math
}  // namespace dalt
using Mod = DynamicModular<i64>;
using Mi = ModInt<Mod>;
void SolveOne(int test_id, IStream &in, OStream &out) {
  i64 a, n, p;
  in >> a >> n >> p;
  Mod::Register(p);
  Mi a_val = a;
  Mi n_val = n;
  if(a == 0) {
    if(n == 0) {
      out << 1;
    } else {
      out << "DNE";
    }
    return;
  }
  math::CoprimeModLog<Mi> loger(a);
  var ans = loger.log(n);
  if(ans.is_none()) {
    out << "DNE";
  } else {
    out << ans.value();
  }
}
void SolveMulti(IStream &in, OStream &out) {
  //std::ifstream input("in");
  int num_of_input = 1;
  //in >> num_of_input;
  for (int i = 0; i < num_of_input; i++) {
    //SolveOne(i + 1, input, out);
	SolveOne(i + 1, in, out);
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  Stdin.tie(0);
  Stdout << std::setiosflags(std::ios::fixed);
  Stdout << std::setprecision(15);
#ifdef STRESS
  stress::Stress();
#else
  SolveMulti(Stdin, Stdout);
#endif
  return 0;
}
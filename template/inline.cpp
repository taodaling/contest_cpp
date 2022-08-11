//Timestamp: 2022-08-11 17:10:32
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
#include <array>
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
template<class T>
inline T MulMod(T a, T b, T modulus) {
  i64 res = i64(a) * i64(b) % modulus;
  return T(res);
}
template<>
inline i64 MulMod<i64>(i64 a, i64 b, i64 modulus) {
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
      q = MulMod<T>(q, Abs(x - y), n);
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
namespace dalt {
namespace graph {
template <class E>
using Graph = Vec<Vec<E>>;
MakeAttribute(WithId, i32, id);
MakeAttribute(WithTo, i32, to);
MakeAttribute(WithRev, i32, rev);
MakeTemplateAttribute(WithWeight, weight);
struct DiBaseEdge: public WithTo {};
struct BiBaseEdge: public DiBaseEdge, public WithRev {};
#define IsDiGraph(E, ret) enable_if_t<is_base_of_v<DiBaseEdge, E>, ret>
#define IsBiGraph(E, ret) enable_if_t<is_base_of_v<BiBaseEdge, E>, ret>
template <class E>
IsDiGraph(E, void) AddDiEdge(Graph<E> &g, int s, int t) {
  E pos;
  pos.to = t;
  g[s].push_back(pos);
}
template <class E> IsBiGraph(E, void) AddBiEdge(Graph<E> &g, int s, int t) {
  E pos, neg;
  pos.to = t;
  neg.to = s;
  pos.rev = Size(g[t]);
  neg.rev = Size(g[s]);
  g[s].push_back(pos);
  g[t].push_back(neg);
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace graph {
template <class E>
enable_if_t<is_base_of_v<WithTo, E>, Vec<int>>
StronglyConnectedComponentDi(const Graph<E> &g) {
  int n = Size(g);
  Deque<int> dq;
  Vec<int> dfn(n);
  Vec<int> low(n);
  Vec<int> repr(n);
  Vec<bool> instk(n);
  int time = 0;
  auto dfs = [&](auto &dfs, int root) {
    if (dfn[root] != 0) {
      return;
    }
    dfn[root] = low[root] = ++time;
    instk[root] = true;
    dq.push_back(root);
    for (auto &e : g[root]) {
      dfs(dfs, e.to);
      if (instk[e.to]) {
        low[root] = Min(low[root], low[e.to]);
      }
    }
    if (dfn[root] == low[root]) {
      while (true) {
        int tail = dq.back();
        dq.pop_back();
        repr[tail] = root;
        instk[tail] = false;
        if (tail == root) {
          break;
        }
      }
    }
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  return repr;
}
template <class E>
enable_if_t<is_base_of_v<WithTo, E> && is_base_of_v<WithRev, E>, Vec<int>>
StronglyConnectedComponentBi(const Graph<E> &g) {
  int n = Size(g);
  Deque<int> dq;
  Vec<int> dfn(n);
  Vec<int> low(n);
  Vec<int> repr(n);
  Vec<bool> instk(n);
  int time = 0;
  auto dfs = [&](auto &dfs, int root, int rev) {
    if (dfn[root] != 0) {
      return;
    }
    dfn[root] = low[root] = ++time;
    instk[root] = true;
    dq.push_back(root);
    int m = Size(g[root]);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      dfs(dfs, e.to, e.rev);
      if (instk[e.to]) {
        low[root] = Min(low[root], low[e.to]);
      }
    }
    if (dfn[root] == low[root]) {
      while (true) {
        int tail = dq.back();
        dq.pop_back();
        repr[tail] = root;
        instk[tail] = false;
        if (root == tail) {
          break;
        }
      }
    }
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i, -1);
  }
  return repr;
}
} // namespace graph
} // namespace dalt
namespace dalt {
struct TwoSat {
private:
  using E = graph::DiBaseEdge;
  Vec<Vec<E>> g;
  void dep_on(int a, int b) {
    DebugFmtln("%d %d", a, b);
    g[a].push_back(E());
    g[a].back().to = b;
  }
public:
  TwoSat(int n) : g(2 * n) {}
  int id(int x) const { return x * 2; }
  int negate_id(int x) const { return x * 2 + 1; }
  int negate(int x) const { return x ^ 1; }
  void deduce(int a, int b) {
    dep_on(a, b);
    dep_on(negate(b), negate(a));
  }
  void or_rel(int a, int b) { deduce(negate(a), b); }
  void always_true(int a) { dep_on(negate(a), a); }
  void always_false(int a) { dep_on(a, negate(a)); }
  void same(int a, int b) {
    deduce(a, b);
    deduce(b, a);
  }
  void xor_rel(int a, int b) { same(a, negate(b)); }
  void at_least_one_false(int a, int b) { deduce(a, negate(b)); }
  void at_least_one_true(int a, int b) { or_rel(a, b); }
  Optional<Vec<bool>> solve() const {
    int n = Size(g) / 2;
    Vec<bool> values(2 * n);
    auto sets = graph::StronglyConnectedComponentDi(g);
    for (int i = 0; i < n; i++) {
      if (sets[id(i)] == sets[negate_id(i)]) {
        return {};
      }
    }
    Vec<bool> dfns(2 * n);
    auto assign = [&](auto assign, auto root) {
      if (dfns[root]) {
        return;
      }
      dfns[root] = true;
      for (auto &e : g[root]) {
        assign(assign, e.to);
      }
      if (sets[root] == root) {
        values[root] = !values[sets[negate(root)]];
      }
    };
    for (int i = 0; i < 2 * n; i++) {
      assign(assign, i);
      values[i] = values[sets[i]];
    }
    Vec<bool> res(n);
    for (int i = 0; i < n; i++) {
      res[i] = values[id(i)];
    }
    return res;
  }
};
} // namespace dalt
namespace dalt {
namespace seq {
template <int C = 26>
struct ACAutomaton {
  Vec<Array<i32, C>> next;
  Vec<i32> fails;
 private:
  int alloc_indicator;
  void init() { alloc_indicator = 1; }
  int alloc() { return alloc_indicator++; }
 public:
  int size() { return alloc_indicator; }
  ACAutomaton(int cap) {
    next.resize(cap + 1);
    fails.resize(cap + 1);
    init();
  }
  struct Builder {
    int build_last;
    ACAutomaton* ac;
    void build(int c) {
      if (ac->next[build_last][c] == 0) {
        ac->next[build_last][c] = ac->alloc();
      }
      build_last = ac->next[build_last][c];
    }
  };
  Builder builder() {
    return Builder{
        .build_last = 0,
        .ac = this,
    };
  }
  struct Matcher {
    int match_last;
    ACAutomaton* ac;
    void match(int c) { match_last = ac->next[match_last][c]; }
  };
  Matcher matcher() {
    return Matcher{
        .match_last = 0,
        .ac = this,
    };
  }
  Vec<i32> topo_sort() {
    Vec<i32> dq(alloc_indicator);
    int dq_tail = 1;
    int dq_head = 1;
    fails[0] = -1;
    for (int i = 0; i < C; i++) {
      if (next[0][i] != 0) {
        dq[dq_tail++] = next[0][i];
        fails[next[0][i]] = 0;
      }
    }
    while (dq_head < dq_tail) {
      int head = dq[dq_head++];
      for (int i = 0; i < C; i++) {
        if (next[head][i] != 0) {
          dq[dq_tail++] = next[head][i];
          int fail = visit(fails[head], i);
          if (fail == -1) {
            fail = 0;
          } else {
            fail = next[fail][i];
          }
          fails[next[head][i]] = fail;
        }
      }
    }
    dq_tail = 1;
    dq_head = 1;
    for (int i = 0; i < C; i++) {
      if (next[0][i] != 0) {
        dq[dq_tail++] = next[0][i];
      }
    }
    while (dq_head < dq_tail) {
      int head = dq[dq_head++];
      for (int i = 0; i < C; i++) {
        if (next[head][i] != 0) {
          dq[dq_tail++] = next[head][i];
        } else {
          next[head][i] = next[fails[head]][i];
        }
      }
    }
    Reverse(All(dq));
    Assert(dq_tail == alloc_indicator);
    return dq;
  }
  int visit(int trace, int index) {
    while (trace != -1 && next[trace][index] == 0) {
      trace = fails[trace];
    }
    return trace;
  }
};
}  // namespace seq
}  // namespace dalt
namespace dalt {
MakeAnnotation(near_value);
template <class T, int EPS_DIGIT = 10, class F = f80>
struct NearValue {
  static_assert(is_floating_point_v<F>);
  using Self = NearValue<T, EPS_DIGIT, F>;
  using Type = T;
  using FType = F;
  struct AccurateComparer {
    bool operator()(const Self& lhs, const Self& rhs) const {
      return lhs.value < rhs.value;
    }
  };
  static constexpr F EPS = PowBinaryLift(F(0.1), EPS_DIGIT);
  T value;
  NearValue(T _value = T()) : value(_value) {}
  CastToAllScalar(value);
  static Self max() { return Self(std::numeric_limits<T>::max()); }
  static Self min() { return Self(std::numeric_limits<T>::min()); }
  static Self max(const Self& lhs, const Self& rhs) {
    return Self(Max(lhs.value, rhs.value));
  }
  static Self min(const Self& lhs, const Self& rhs) {
    return Self(Min(lhs.value, rhs.value));
  }
  Self operator+(const Self& rhs) const { return Self(value + rhs.value); }
  Self operator-(const Self& rhs) const { return Self(value - rhs.value); }
  Self operator*(const Self& rhs) const { return Self(value * rhs.value); }
  Self operator/(const Self& rhs) const { return Self(value / rhs.value); }
  template <class V>
  operator NearValue<V, EPS_DIGIT>() const {
    return NearValue<V, EPS_DIGIT>(value);
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, bool> operator==(
      const Self& rhs) const {
    auto delta = value - rhs.value;
    return delta >= -EPS && delta <= EPS;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, bool> operator==(
      const Self& rhs) const {
    return value == rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, bool> operator<(
      const Self& rhs) const {
    return value + EPS < rhs.value;
  }
  bool operator<=(const Self& rhs) const { return !(*this > rhs); }
  bool operator>=(const Self& rhs) const { return !(*this < rhs); }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, bool> operator<(
      const Self& rhs) const {
    return value < rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, bool> operator>(
      const Self& rhs) const {
    return value - EPS > rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, bool> operator>(
      const Self& rhs) const {
    return value > rhs.value;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_floating_point_v<T>, int> sign() const {
    return value < -EPS ? -1 : value > EPS ? 1 : 0;
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<T>, int> sign() const {
    return value < 0 ? -1 : value > 0 ? 1 : 0;
  }
  bool operator!=(const Self& rhs) const { return !(*this == rhs); }
  static AccurateComparer accurate_comparer() { return AccurateComparer(); }
  i64 ceil() const { return std::ceil(value - EPS); }
  i64 floor() const { return std::floor(value + EPS); }
  F sin() const { return std::sin(F(value)); }
  F cos() const { return std::cos(F(value)); }
  F tan() const { return std::tan(F(value)); }
  F sqrt() const { return std::sqrt(F(value)); }
  F ln() const { return std::log(F(value)); }
  F exp() const { return std::exp(F(value)); }
  F asin() const { return std::asin(F(value)); }
  F acos() const { return std::acos(F(value)); }
  F atan() const { return std::atan(F(value)); }
  static F atan2(const T& y, const T& x) { return std::atan2(F(y), F(x)); }
  Self pow(const Self& exp) const { return Self(std::pow(value, exp.value)); }
  Self abs() const { return Self(std::abs(value)); }
  Self operator-() const { return Self(-value); }
  ImplArithmeticAssignOperation(Self);
};
template <class T, int EPS_DIGIT, class F>
struct is_near_value<NearValue<T, EPS_DIGIT, F>> {
  static const bool value = true;
};
template <class T, int EPS_DIGIT, class F>
OStream& operator<<(OStream& os, const NearValue<T, EPS_DIGIT, F>& rhs) {
  os << rhs.value;
  return os;
}
template <class T, int EPS_DIGIT, class F>
IStream& operator>>(IStream& in, NearValue<T, EPS_DIGIT, F>& rhs) {
  in >> rhs.value;
  return in;
}
}  // namespace dalt
namespace dalt {
namespace geo2 {
template <class T>
struct Point {
  static_assert(is_near_value_v<T>);
  using Self = Point<T>;
  using Type = T;
  using FType = typename T::FType;
  T x;
  T y;
  Point(T _x = T(0), T _y = T(0)) : x(_x), y(_y) {}
  Self operator+(const Self& rhs) const { return {x + rhs.x, y + rhs.y}; }
  Self operator-(const Self& rhs) const { return {x - rhs.x, y - rhs.y}; }
  T cross_product(const Self& rhs) { return x * rhs.y - y * rhs.x; }
  Self operator*(const Self& rhs) const {
    return {x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x};
  }
  Self operator/(const Self& rhs) const {
    return *this * rhs.conj() / rhs.square();
  }
  Self operator*(const T& rhs) const { return {x * rhs, y * rhs}; }
  Self operator/(const T& rhs) const { return {x / rhs, y / rhs}; }
  bool operator<(const Self& rhs) const {
    return MakePair(x, y) < MakePair(rhs.x, rhs.y);
  }
  ImplDefaultComparision(Self);
  bool operator==(const Self& rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(const Self& rhs) const { return !(*this == rhs); }
  T square() const { return Self::dot(*this, *this); }
  FType abs() const{ return square().sqrt(); }
  static T dist2(const Self& lhs, const Self& rhs) {
    return (lhs - rhs).square();
  }
  static FType dist(const Self& lhs, const Self& rhs) {
    return (lhs - rhs).abs();
  }
  Self operator-() const { return {-x, -y}; }
  FType atan2() const {
    return T::atan2(y, x);
  }
  static int half(T x, T y) {
    return y > T(0) || y == T(0) && x < T(0) ? 1 : 0;
  }
  int half() const { return half(x, y); }
  Self norm(T d = T(1)) const { return *this * d / abs(); }
  Self conj() const { return {x, -y}; }
  Self perpendicular() const { return {-y, x}; }
  static Self rotate(const Self& pt, FType cos, FType sin,
                     const Self& center = Self()) {
    auto a = pt - center;
    return {a.x * cos - a.y * sin, a.x * sin + a.y * cos};
  }
  static Self rotate(const Self& a, FType angle, const Self& center = Self()) {
    return rotate(a, Cos(angle), Sin(angle), center);
  }
  static T dot(const Self& lhs, const Self& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
  }
  static T cross(const Self& lhs, const Self& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
  }
  static T cross(const Self& base, const Self& lhs, const Self& rhs) {
    return cross(lhs - base, rhs - base);
  }
  static bool is_perpendicular(const Self& lhs, const Self& rhs) {
    return dot(lhs, rhs) == T(0);
  }
  static bool is_parallel(const Self& lhs, const Self& rhs) {
    return lhs.cross_product(rhs) == T(0);
  }
  // ret \in [0, pi)
  static FType angle(const Self& lhs, const Self& rhs) {
    return Acos(Clamp<FType>(lhs.dot(rhs) / lhs.abs() / rhs.abs(), -1, 1));
  }
  static int orient(const Self& b, const Self& c) { return cross(b, c).sign(); }
  //获取c处于ab的方向，-1表示順時針方向，1表示逆時針，0表示在綫上
  static int orient(const Self& a, const Self& b, const Self& c) {
    return orient(b - a, c - a);
  }
  static bool in_angle(const Self& b, const Self& c, const Self& p,
                       const Self& center = Self()) {
    if (orient(b, c, center) < 0) {
      Swap(b, c);
    }
    return orient(b, p, center) >= 0 && orient(c, p, center) <= 0;
  }
  static FType oriented_angle(const Self& a, const Self& b,
                              const Self& center = Self()) {
    FType angle = Self::angle(a - center, b - center);
    if (orient(a, b, center) >= 0) {
      return angle;
    } else {
      return 2 * M_PI - angle;
    }
  }
  Self linear_transform(const Self& p, const Self& fp, const Self& q,
                        const Self& fq) const {
    return fp + (*this - p) * ((fq - fp) / (q - p));
  }
  //判断c是否落在以a与b为直径两端的圆中（包含边界）
  static bool in_disk(const Self& a, const Self& b, const Self& c) {
    return dot(a - c, b - c).sign() <= 0;
  }
  //判断c是否在a到b的线段上
  static bool on_segment(const Self& a, const Self& b, const Self& c) {
    return orient(a, b, c) == 0 && in_disk(a, b, c);
  }
  //获取线段a->b与线段c->d的交点
  static Optional<Self> proper_intersect(const Self& a, const Self& b,
                                         const Self& c, const Self& d) {
    T oa = cross(d - c, a - c);
    T ob = cross(d - c, b - c);
    T oc = cross(b - a, c - a);
    T od = cross(b - a, d - a);
    if (oa * ob < T(0) && oc * od < T(0)) {
      return (a * (ob / (ob - oa))) + (b * (-oa / (ob - oa)));
    }
    return {};
  }
  static Optional<Self> intersect(const Self& a, const Self& b, const Self& c,
                                  const Self& d) {
    auto pt = proper_intersect(a, b, c, d);
    if (pt.is_none() && on_segment(a, b, c)) {
      pt = c;
    }
    if (pt.is_none() && on_segment(a, b, d)) {
      pt = d;
    }
    if (pt.is_none() && on_segment(c, d, a)) {
      pt = a;
    }
    if (pt.is_none() && on_segment(c, d, b)) {
      pt = b;
    }
    return pt;
  }
  static int above(const Self& a, const Self& b) { return b.y >= a.y ? 1 : 0; }
  static bool cross_ray(const Self& a, const Self& p, const Self& q) {
    return (above(a, q) - above(a, p)) * orient(a, p, q) > 0;
  }
  static Self mirror(const Self& symmetric_center, const Self& a) {
    return {symmetric_center.x * 2 - a.x, symmetric_center.y * 2 - a.y};
  }
  static FType distanceToLine(const Self& a, const Self& b, const Self& c) {
    FType len = dist(a, b);
    if (len == 0) {
      return dist(a, c);
    }
    FType area2 = FType(Abs(cross(a - c, b - c)));
    return area2 / len;
  }
  template <class Arg = Type>
  static enable_if_t<is_same_v<Arg, Type> && is_integral_v<typename Type::Type>,
                     Type>
  lattice_point_number_on_segment(const Self& a, const Self& b) {
    T dx = (a.x - b.x).abs();
    T dy = (a.y - b.y).abs();
    auto gcd = Gcd(dx.value, dy.value);
    return Type(gcd + 1);
  }
};
template <class T>
struct SortByPolarAngleAround {
  using Pt = Point<T>;
  Pt center;
  SortByPolarAngleAround(Pt _center = Pt()) : center(_center) {}
  bool operator()(const Pt& a, const Pt& b) const { return compare(a, b) < 0; }
  int compare(const Pt& a, const Pt& b) const {
    int a_half = (a - center).half();
    int b_half = (b - center).half();
    if (a_half != b_half) {
      return a_half - b_half;
    }
    return Pt::orient(center, b, a);
  }
};
template <class T>
OStream& operator<<(OStream& os, const Point<T>& pt) {
  os << MakeTuple(pt.x, pt.y);
  return os;
}
}  // namespace geo2
}  // namespace dalt
namespace dalt {
namespace geo2 {
template <class T>
struct Line {
  static_assert(is_near_value_v<T>);
  using Self = Line<T>;
  using Pt = Point<T>;
 private:
  T side0(const Pt& pt) const {
    Debug(Pt::cross(vec, pt) - c);
    return Pt::cross(vec, pt) - c;
  }
public:
 Pt vec;
 T c;
 Line(const Pt& _vec = Pt(), T _c = T()) : vec(_vec), c(_c) {}
 Pt any() const {
   T a = -vec.y;
   T b = vec.x;
   if (a.sign() != 0) {
     return Pt(c / a, T(0));
   } else {
     return Pt(T(0), c / b);
   }
  }
  //ax + by = c
  static Pt from_formula(T a, T b, T c) {
    return Self(Pt(b, -a), c);
  }
  static Self from_ends(const Pt& a, const Pt& b) {
    Pt vec = b - a;
    return Self(vec, Pt::cross(vec, a));
  }
  //如果pt在逆时针方向，返回1，顺时针方向返回-1，否则返回0
  int side(const Pt& pt) const {
     auto ans = side0(pt);
     return ans.sign();
  }
  T dist(const Pt& pt) const { return side0(pt).abs() / vec.abs(); }
  T square_dist(const Pt& pt) const { return Pow2(side0(pt)) / vec.square(); }
  Self perpendicular_through(const Pt& pt) const {
    return Self(pt, pt + vec.perpendicular());
  }
  //判断一条平行的直线处于当前的上方还是下方，上方为1，下方为-1，重合为0
  int side(const Self& line) const {
    return side(line.any());
  }
  Comparator<Pt> sort_point_on_line() const {
    return [=](const Pt& a, const Pt& b) {
      return Pt::dot(a, vec) < Pt::dot(b, vec); 
    };
  }
  Self translate(Pt pt) const {
    return Self(vec, c + Pt::cross(vec, pt));
  }
  friend Self operator+(const Self& line, const Pt& pt) {
    return line.translate(pt);
  }
  Self shift_left(T dist) const {
    return Self(vec, c + dist * vec.abs());
  }
  static Optional<Pt> intersect(const Self& a, const Self& b) {
    T d = Pt::cross(a.vec, b.vec);
    if(d.sign() == 0) {
      return {};
    }
    return (b.vec * a.c - a.vec * b.c) / d;
  }
  Pt projection(const_ref(Pt) pt) const {
    T factor = side0(pt) / vec.square();
    return Pt(pt.x - (-vec.y * factor), pt.y - vec.x * factor);
  }
  Pt reflect(const_ref(Pt) pt) const {
    return pt - vec.perpendicular() * (2 * side0(pt) / vec.square);
  } 
  Comparator<Pt> sort_point_along_line() const {
    return [=] (const Pt& a, const Pt& b) {
      return Pt::dot(vec, a) < Pt::dot(vec, b);
    };
  }
  friend OStream& operator<<(OStream& os, const Self& line) {
    os << -line.vec.y << "x + " << line.vec.x << "y = " << line.c;
    return os;
  }
};
}  // namespace geo2
}  // namespace dalt
namespace dalt {
namespace geo2 {
template <class T>
struct Circle {
  static_assert(is_near_value_v<T>);
  using Pt = Point<T>;
  using Ln = Line<T>;
  using Self = Circle<T>;
  Pt center;
  T r;
  Circle(Pt _pt, T _r) : center(_pt), r(_r) {}
  bool contain(Pt pt, bool include_boarder = true) const {
    if (include_boarder) {
      return Pt::dist2(center, pt) <= r * r;
    } else {
      return Pt::dist2(center, pt) < r * r;
    }
  }
  Vec<Pt> intersect(Ln line) const {
    Pt proj = line.projection(center);
    if (!contain(proj)) {
      return {};
    }
    T h = (r * r - Pt::dist2(proj, center)).sqrt();
    if (h == T(0)) {
      return {proj};
    } else {
      Pt vec = line.vec.norm(h);
      return {proj + vec, proj - vec};
    }
  }
  Vec<T> intersect(const Self& c1, const Self& c2) {
    Pt d = c2.center - c1.center;
    T d2 = d.square();
    if (d2 == T(0)) {
      return {T(0)};
    }
    T pd = (d2 + c1.r * c1.r - c2.r * c2.r) / T(2);
    T h2 = c1.r * c1.r - pd * pd / d2;
    if (h2 >= T(0)) {
      Pt p = c1.center + d * (pd / d2);
      if (h2 == T(0)) {
        return {p};
      }
      Pt h = d.perpendicular() * (h2 / d2).sqrt();
      return {p - h, p + h};
    }
    return {};
  }
  static T det(T a11, T a12, T a21, T a22, T a31, T a32) {
    return a11 * a22 - a21 * a12 - a11 * a32 + a31 * a12 + a21 * a32 -
           a31 * a22;
  }
  static Self from_diameter(Pt a, Pt b) {
    return Circle((a + b) / T(2), (a - b).abs());
  }
  static Self outer_circle_of_triangle(Pt A, Pt B, Pt C) {
    T a = Pt::dist(B, C);
    T b = Pt::dist(A, C);
    T c = Pt::dist(A, B);
    T area = Pt::cross(A, B, C).abs() / T(2);
    T r = a * b * c / T(4) / area;
    T bot = det(A.x, A.y, B.x, B.y, C.x, C.y) * T(2);
    T x = det(A.square(), A.y, B.square(), B.y, C.square(), C.y) / bot;
    T y = det(A.x, A.square(), B.x, B.square(), C.x, C.square()) / bot;
    return Self(Pt(x, y), r);
  }
  static Self inner_circle_of_triangle(Pt A, Pt B, Pt C) {
    T a = T::dist(B, C);
    T b = T::dist(A, C);
    T c = T::dist(A, B);
    T area = Pt::cross(A, B, C).abs() / T(2);
    T r = area * T(2) / (a + b + c);
    T x = (a * A.x + b * B.x + c * C.x) / (a + b + c);
    T y = (a * A.y + b * B.y + c * C.y) / (a + b + c);
    return Self(Pt(x, y), r);
  }
  Pt point_on_boarder(T radian) const {
    T x = radian.cos();
    T y = radian.sin();
    return center + Pt(x, y) * r;
  }
  static Self min_circle_cover(Vec<T> pts) {
    Shuffle(All(pts));
    Self circle(Pt(), T(0));
    for (int i = 0; i < Size(pts); i++) {
      if (circle.contain(pts[i])) {
        continue;
      }
      circle = Self(pts[i], 0);
      for (int j = 0; j < i; j++) {
        if (circle.contain(pts[j])) {
          continue;
        }
        circle = from_diameter(pts[i], pts[j]);
        for (int k = 0; k < j; k++) {
          if (circle.contain(pts[k])) {
            continue;
          }
          circle = outer_circle_of_triangle(pts[i], pts[j], pts[k]);
        }
      }
    }
    return circle;
  }
  static int tangent(const Self& c1, const Self& c2, Vec<Pt> &out1, Vec<Pt> &out2, bool inner = false) {
    Pt o1 = c1.center;
    T r1 = c1.r;
    Pt o2 = c2.center;
    T r2 = c2.r;
    if (inner) {
      r2 = -r2;
    }
    Pt d = o2 - o1;
    T dr = r1 - r2, d2 = d.square(), h2 = d2 - dr * dr;
    if (d2 == T(0) || h2 < T(0)) {
      Assert(h2 != T(0));
      return 0;
    }
    T sqrtH2 = h2.sqrt();
    for (int sign = -1; sign <= 1; sign += 2) {
      Pt v = d * (dr / d2) + d.perpendicular() * (sqrtH2 * T(sign) / d2);
      out1.push_back(o1 + v * r1);
      out2.push_back(o2 + v * r2);
    }
    return 2;
  }
};
}  // namespace geo2
}  // namespace dalt
namespace dalt {
template <class T>
struct FenwickTree {
 private:
  // data[i] = \sum_{j \in (i-lowbit(i), i]} A[i]
  Vec<T> data;
  int n;
 public:
  FenwickTree(int _n = 0) {
    n = _n;
    data = Vec<T>(n + 1);
  }
  // A[0] + ... + A[i]
  T query(int i) {
    i += 1;
    i = Min(i, n);
    T sum = 0;
    for (; i > 0; i -= i & -i) {
      sum = sum + data[i];
    }
    return sum;
  }
  // A[l] + ... + A[r]
  T query(int l, int r) const {
    if (l > r) {
      return T();
    }
    return query(r) - query(l - 1);
  }
  // A[i] += mod
  void update(int i, T mod) {
    i += 1;
    if (i <= 0) {
      return;
    }
    for (; i <= n; i += i & -i) {
      data[i] += mod;
    }
  }
  void update(int l, int r, T mod) {
    if (l > r) {
      return;
    }
    l = Max(l, 0);
    update(l, mod);
    update(r + 1, -mod);
  }
  int size() { return n; }
  // A[i] = x
  void set(int i, T x) { update(i, x - query(i, i)); }
  FenwickTree(const Indexer<T> &initial_value, i32 _n) : FenwickTree(_n) {
    for (int i = 1; i <= n; i++) {
      data[i] = initial_value(i - 1);
    }
    for (int i = 1; i <= n; i++) {
      int to = i + (i & -i);
      if (to <= n) {
        data[to] += data[i];
      }
    }
  }
  Vec<T> to_vec() {
    Vec<T> ans(n);
    for (int i = 0; i < n; i++) {
      ans[i] = query(i, i);
    }
    return ans;
  }
};
}  // namespace dalt
namespace dalt {
namespace adhoc {
using namespace geo2;
// get the number of pairs of points that intersect with solid circle
// O(n\log_2n)
template <class T>
enable_if_t<is_near_value_v<T>, i64> PairOfPointIntersectWithCircle(
    const Vec<Point<T>> &pts, const Circle<T> &circle) {
  int n = Size(pts);
  using Type = typename T::Type;
  using A2 = Array<Type, 2>;
  Vec<A2> ints;
  ints.reserve(n);
  Vec<Point<T>> out1;
  Vec<Point<T>> out2;
  for (int i = 0; i < n; i++) {
    if (circle.contain(pts[i])) {
      continue;
    }
    out1.clear();
    out2.clear();
    auto res = Circle<T>::tangent(circle, Circle<T>(pts[i], 0), out1, out2);
    auto &tangent_points = out1;
    A2 thetas = A2{(tangent_points[0] - circle.center).atan2(),
                   (tangent_points[1] - circle.center).atan2()};
    if (thetas[0] > thetas[1]) {
      Swap(thetas[0], thetas[1]);
    }
    ints.push_back(thetas);
  }
  int m = Size(ints);
  Vec<int> left(m);
  Vec<int> right(m);
  for (int i = 0; i < m; i++) {
    left[i] = right[i] = i;
  }
  Sort(All(left), [&](int a, int b) { return ints[a][0] < ints[b][0]; });
  Sort(All(right), [&](int a, int b) { return ints[a][1] < ints[b][1]; });
  Vec<int> to_rank(m);
  for (int i = 0; i < m; i++) {
    to_rank[left[i]] = i;
  }
  FenwickTree<int> fwt(m);
  auto left_iter = left.begin();
  auto right_iter = right.begin();
  int total = 0;
  i64 ans = 0;
  while (right_iter != right.end()) {
    if (left_iter != left.end() &&
        ints[*right_iter][1] >= ints[*left_iter][0]) {
      int id = *left_iter;
      ++left_iter;
      fwt.update(to_rank[id], 1);
      total++;
    } else {
      int id = *right_iter;
      ++right_iter;
      total--;
      fwt.update(to_rank[id], -1);
      ans += total - fwt.query(to_rank[id]);
    }
  }
  return (i64)n * (n - 1) / 2 - ans;
}
// check if there is a pair of points that intersect with solid circle
// O(n\log_2n) but fast
template <class T>
enable_if_t<is_near_value_v<T>, bool> PairOfPointIntersectWithCircleFastCheck(
    const Vec<Point<T>> &pts, const Circle<T> &circle) {
  int n = Size(pts);
  using Type = typename T::Type;
  using A2 = Array<Type, 2>;
  Vec<A2> ints;
  ints.reserve(n);
  Vec<Point<T>> out1;
  Vec<Point<T>> out2;
  for (int i = 0; i < n; i++) {
    if (circle.contain(pts[i])) {
      return true;
    }
    out1.clear();
    out2.clear();
    auto res = Circle<T>::tangent(circle, Circle<T>(pts[i], 0), out1, out2);
    auto &tangent_points = out1;
    A2 thetas = A2{tangent_points[0].atan2(), tangent_points[1].atan2()};
    if (thetas[0] > thetas[1]) {
      Swap(thetas[0], thetas[1]);
    }
    ints.push_back(thetas);
  }
  Sort(All(ints));
  for (int i = 1; i < Size(ints); i++) {
    if (ints[i][1] <= ints[i - 1][1] || ints[i - 1][1] <= ints[i][0]) {
      return true;
    }
  }
  return false;
}
}  // namespace adhoc
}  // namespace dalt
namespace dalt {
namespace adhoc {
template <class D, class V>
Vec<V> PrefixSum3DSparse(Vec<Tuple<D, D, D, V>> pts) {
  if(Size(pts) == 0) {
    return Vec<V>();
  }
  struct Event {
    int id;
    D x;
    D y;
    int z;
    V v;
    V s;
  };
  int n = Size(pts);
  Vec<D> all_z(n);
  for (int i = 0; i < n; i++) {
    all_z[i] = std::get<2>(pts[i]);
  }
  Sort(All(all_z));
  MakeUnique(all_z);
  Vec<Event> discrete_pts(n);
  for (int i = 0; i < n; i++) {
    discrete_pts[i].x =
        std::get<0>(pts[i]);
    discrete_pts[i].y =
        std::get<1>(pts[i]);
    discrete_pts[i].z =
        LowerBound(All(all_z), std::get<2>(pts[i])) - all_z.begin();
    discrete_pts[i].v = std::get<3>(pts[i]);
  }
  Vec<Event*> events(n);
  for (int i = 0; i < n; i++) {
    events[i] = &discrete_pts[i];
  }
  Sort(All(events), [&](auto a, auto b) {
    return MakeTuple(a->x, a->y, a->z, a->id) <
           MakeTuple(b->x, b->y, b->z, b->id);
  });
  auto sort_by_y = [&](auto a, auto b) { return a->y < b->y; };
  FenwickTree<V> fwt(n);
  Vec<Event*> buffer(n);
  auto dac = [&](auto &dac, int l, int r) -> void {
    if(l == r) {
      events[l]->s = events[l]->s + events[l]->v;
      return;
    }
    int m = (l + r) / 2;
    dac(dac, l, m);
    dac(dac, m + 1, r);
    //Sort(events.begin() + l, events.begin() + m + 1, sort_by_y);
    //Sort(events.begin() + m + 1, events.begin() + r + 1, sort_by_y);
    int iter_l = l;
    int iter_r = m + 1;
    while (iter_l <= m || iter_r <= r) {
      if (iter_l <= m &&
          (iter_r > r || events[iter_l]->y <= events[iter_r]->y)) {
        fwt.update(events[iter_l]->z, events[iter_l]->v);
        iter_l++;
      } else {
        events[iter_r]->s = events[iter_r]->s + fwt.query(events[iter_r]->z);
        iter_r++;
      }
    }
    for (int i = l; i <= m; i++) {
      fwt.update(events[i]->z, -events[i]->v);
    }
    //sort by y here
    iter_l = l;
    iter_r = m + 1;
    int wpos = l;
    while (iter_l <= m || iter_r <= r) {
      if (iter_l <= m &&
          (iter_r > r || events[iter_l]->y <= events[iter_r]->y)) {
        buffer[wpos++] = events[iter_l];
        iter_l++;
      } else {
        buffer[wpos++] = events[iter_r];
        iter_r++;
      }
    }
    for(int i = l; i <= r; i++) {
      events[i] = buffer[i];
    }
  };
  dac(dac, 0, n - 1);
  Vec<V> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = discrete_pts[i].s;
  }
  return ans;
}
}  // namespace adhoc
}  // namespace dalt
namespace dalt {
template <class T>
struct Affine {
  using Self = Affine;
  T a, b;
  Affine(T _a, T _b) : a(_a), b(_b) {}
  Affine(T _b = T(0)) : b(_b) {}
  friend Self operator+(const Self& lhs, const Self& rhs) {
    return Self(lhs.a + rhs.a, lhs.b + rhs.b);
  }
  friend Self operator-(const Self& lhs, const Self& rhs) {
    return Self(lhs.a - rhs.a, lhs.b - rhs.b);
  }
  static Self compose(const Self& lhs, const Self& rhs) {
    return Self(lhs.a * rhs.a, lhs.a * rhs.b + lhs.b);
  }
  friend Self operator*(const Self& lhs, const T& rhs) {
    return Self(lhs.a * rhs, lhs.b * rhs);
  }
  friend Self operator*(const T& lhs, const Self& rhs) { return rhs * lhs; }
  friend Self operator/(const Self& lhs, const T& rhs) {
    return Self(lhs.a / rhs, lhs.b / rhs);
  }
  T operator()(T x) const { return a * x + b; }
  static Self mul_identity() { return Self(T(1), T(0)); }
  static Self add_identity() { return Self(T(0), T(0)); }
};
}  // namespace dalt
// copied from
// https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Math/bigint.h
namespace external {
using namespace std;
namespace bigint {
// NOTE:
// This code contains various bug fixes compared to the original version from
// indy256
// (github.com/indy256/codelibrary/blob/master/cpp/numbertheory/bigint-full.cpp),
// including:
// - Fix overflow bug in mul_karatsuba.
// - Fix overflow bug in fft.
// - Fix bug in initialization from long long.
// - Optimized operators + - *.
//
// Tested:
// - https://www.e-olymp.com/en/problems/266: Comparison
// - https://www.e-olymp.com/en/problems/267: Subtraction
// - https://www.e-olymp.com/en/problems/271: Multiplication
// - https://www.e-olymp.com/en/problems/272: Multiplication
// - https://www.e-olymp.com/en/problems/313: Addition
// - https://www.e-olymp.com/en/problems/314: Addition/Subtraction
// - https://www.e-olymp.com/en/problems/317: Multiplication (simple /
// karatsuba / fft)
// - https://www.e-olymp.com/en/problems/1327: Multiplication
// - https://www.e-olymp.com/en/problems/1328
// - VOJ BIGNUM: Addition, Subtraction, Multiplication.
// - SGU 111: sqrt
// - SGU 193
// - SPOJ MUL, VFMUL: Multiplication.
// - SPOJ FDIV, VFDIV: Division.
const int BASE_DIGITS = 9;
const int BASE = 1000000000;
struct BigInt {
  int sign;
  vector<int> a;
  // -------------------- Constructors --------------------
  // Default constructor.
  BigInt() : sign(1) {}
  // Constructor from long long.
  BigInt(long long v) { *this = v; }
  BigInt &operator=(long long v) {
    sign = 1;
    if (v < 0) {
      sign = -1;
      v = -v;
    }
    a.clear();
    for (; v > 0; v = v / BASE) a.push_back(v % BASE);
    return *this;
  }
  // Initialize from string.
  BigInt(const string &s) { read(s); }
  // -------------------- Input / Output --------------------
  void read(const string &s) {
    sign = 1;
    a.clear();
    int pos = 0;
    while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
      if (s[pos] == '-') sign = -sign;
      ++pos;
    }
    for (int i = s.size() - 1; i >= pos; i -= BASE_DIGITS) {
      int x = 0;
      for (int j = max(pos, i - BASE_DIGITS + 1); j <= i; j++)
        x = x * 10 + s[j] - '0';
      a.push_back(x);
    }
    trim();
  }
  friend istream &operator>>(istream &stream, BigInt &v) {
    string s;
    stream >> s;
    v.read(s);
    return stream;
  }
  friend ostream &operator<<(ostream &stream, const BigInt &v) {
    if (v.sign == -1 && !v.isZero()) stream << '-';
    stream << (v.a.empty() ? 0 : v.a.back());
    for (int i = (int)v.a.size() - 2; i >= 0; --i)
      stream << setw(BASE_DIGITS) << setfill('0') << v.a[i];
    return stream;
  }
  // -------------------- Comparison --------------------
  bool operator<(const BigInt &v) const {
    if (sign != v.sign) return sign < v.sign;
    if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
    for (int i = ((int)a.size()) - 1; i >= 0; i--)
      if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
    return false;
  }
  bool operator>(const BigInt &v) const { return v < *this; }
  bool operator<=(const BigInt &v) const { return !(v < *this); }
  bool operator>=(const BigInt &v) const { return !(*this < v); }
  bool operator==(const BigInt &v) const {
    return !(*this < v) && !(v < *this);
  }
  bool operator!=(const BigInt &v) const { return *this < v || v < *this; }
  // Returns:
  // 0 if |x| == |y|
  // -1 if |x| < |y|
  // 1 if |x| > |y|
  friend int __compare_abs(const BigInt &x, const BigInt &y) {
    if (x.a.size() != y.a.size()) {
      return x.a.size() < y.a.size() ? -1 : 1;
    }
    for (int i = ((int)x.a.size()) - 1; i >= 0; --i) {
      if (x.a[i] != y.a[i]) {
        return x.a[i] < y.a[i] ? -1 : 1;
      }
    }
    return 0;
  }
  // -------------------- Unary operator - and operators +-
  // --------------------
  BigInt operator-() const {
    BigInt res = *this;
    if (isZero()) return res;
    res.sign = -sign;
    return res;
  }
  // Note: sign ignored.
  void __internal_add(const BigInt &v) {
    if (a.size() < v.a.size()) {
      a.resize(v.a.size(), 0);
    }
    for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry;
         ++i) {
      if (i == (int)a.size()) a.push_back(0);
      a[i] += carry + (i < (int)v.a.size() ? v.a[i] : 0);
      carry = a[i] >= BASE;
      if (carry) a[i] -= BASE;
    }
  }
  // Note: sign ignored.
  void __internal_sub(const BigInt &v) {
    for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
      a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
      carry = a[i] < 0;
      if (carry) a[i] += BASE;
    }
    this->trim();
  }
  BigInt operator+=(const BigInt &v) {
    if (sign == v.sign) {
      __internal_add(v);
    } else {
      if (__compare_abs(*this, v) >= 0) {
        __internal_sub(v);
      } else {
        BigInt vv = v;
        swap(*this, vv);
        __internal_sub(vv);
      }
    }
    return *this;
  }
  BigInt operator-=(const BigInt &v) {
    if (sign == v.sign) {
      if (__compare_abs(*this, v) >= 0) {
        __internal_sub(v);
      } else {
        BigInt vv = v;
        swap(*this, vv);
        __internal_sub(vv);
        this->sign = -this->sign;
      }
    } else {
      __internal_add(v);
    }
    return *this;
  }
  // Optimize operators + and - according to
  // https://stackoverflow.com/questions/13166079/move-semantics-and-pass-by-rvalue-reference-in-overloaded-arithmetic
  template <typename L, typename R>
  typename std::enable_if<std::is_convertible<L, BigInt>::value &&
                              std::is_convertible<R, BigInt>::value &&
                              std::is_lvalue_reference<R &&>::value,
                          BigInt>::type friend
  operator+(L &&l, R &&r) {
    BigInt result(std::forward<L>(l));
    result += r;
    return result;
  }
  template <typename L, typename R>
  typename std::enable_if<std::is_convertible<L, BigInt>::value &&
                              std::is_convertible<R, BigInt>::value &&
                              std::is_rvalue_reference<R &&>::value,
                          BigInt>::type friend
  operator+(L &&l, R &&r) {
    BigInt result(std::move(r));
    result += l;
    return result;
  }
  template <typename L, typename R>
  typename std::enable_if<std::is_convertible<L, BigInt>::value &&
                              std::is_convertible<R, BigInt>::value,
                          BigInt>::type friend
  operator-(L &&l, R &&r) {
    BigInt result(std::forward<L>(l));
    result -= r;
    return result;
  }
  // -------------------- Operators * / % --------------------
  friend pair<BigInt, BigInt> divmod(const BigInt &a1, const BigInt &b1) {
    assert(b1 > 0);  // divmod not well-defined for b < 0.
    long long norm = BASE / (b1.a.back() + 1);
    BigInt a = a1.abs() * norm;
    BigInt b = b1.abs() * norm;
    BigInt q = 0, r = 0;
    q.a.resize(a.a.size());
    for (int i = a.a.size() - 1; i >= 0; i--) {
      r *= BASE;
      r += a.a[i];
      long long s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
      long long s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
      long long d = ((long long)BASE * s1 + s2) / b.a.back();
      r -= b * d;
      while (r < 0) {
        r += b, --d;
      }
      q.a[i] = d;
    }
    q.sign = a1.sign * b1.sign;
    r.sign = a1.sign;
    q.trim();
    r.trim();
    auto res = make_pair(q, r / norm);
    if (res.second < 0) res.second += b1;
    return res;
  }
  BigInt operator/(const BigInt &v) const {
    if (v < 0) return divmod(-*this, -v).first;
    return divmod(*this, v).first;
  }
  BigInt operator%(const BigInt &v) const { return divmod(*this, v).second; }
  void operator/=(int v) {
    assert(v > 0);  // operator / not well-defined for v <= 0.
    if (llabs(v) >= BASE) {
      *this /= BigInt(v);
      return;
    }
    if (v < 0) sign = -sign, v = -v;
    for (int i = (int)a.size() - 1, rem = 0; i >= 0; --i) {
      long long cur = a[i] + rem * (long long)BASE;
      a[i] = (int)(cur / v);
      rem = (int)(cur % v);
    }
    trim();
  }
  BigInt operator/(int v) const {
    assert(v > 0);  // operator / not well-defined for v <= 0.
    if (llabs(v) >= BASE) {
      return *this / BigInt(v);
    }
    BigInt res = *this;
    res /= v;
    return res;
  }
  void operator/=(const BigInt &v) { *this = *this / v; }
  long long operator%(long long v) const {
    assert(v > 0);  // operator / not well-defined for v <= 0.
    assert(v < BASE);
    int m = 0;
    for (int i = a.size() - 1; i >= 0; --i)
      m = (a[i] + m * (long long)BASE) % v;
    return m * sign;
  }
  void operator*=(int v) {
    if (llabs(v) >= BASE) {
      *this *= BigInt(v);
      return;
    }
    if (v < 0) sign = -sign, v = -v;
    for (int i = 0, carry = 0; i < (int)a.size() || carry; ++i) {
      if (i == (int)a.size()) a.push_back(0);
      long long cur = a[i] * (long long)v + carry;
      carry = (int)(cur / BASE);
      a[i] = (int)(cur % BASE);
      // asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
      /*
       int val;
       __asm {
       lea esi, cur
       mov eax, [esi]
       mov edx, [esi+4]
       mov ecx, base
       div ecx
       mov carry, eax
       mov val, edx;
       }
       a[i] = val;
       */
    }
    trim();
  }
  BigInt operator*(int v) const {
    if (llabs(v) >= BASE) {
      return *this * BigInt(v);
    }
    BigInt res = *this;
    res *= v;
    return res;
  }
  // Convert BASE 10^old --> 10^new.
  static vector<int> convert_base(const vector<int> &a, int old_digits,
                                  int new_digits) {
    vector<long long> p(max(old_digits, new_digits) + 1);
    p[0] = 1;
    for (int i = 1; i < (int)p.size(); i++) p[i] = p[i - 1] * 10;
    vector<int> res;
    long long cur = 0;
    int cur_digits = 0;
    for (int i = 0; i < (int)a.size(); i++) {
      cur += a[i] * p[cur_digits];
      cur_digits += old_digits;
      while (cur_digits >= new_digits) {
        res.push_back((long long)(cur % p[new_digits]));
        cur /= p[new_digits];
        cur_digits -= new_digits;
      }
    }
    res.push_back((int)cur);
    while (!res.empty() && !res.back()) res.pop_back();
    return res;
  }
  void fft(vector<complex<double> > &x, bool invert) const {
    int n = (int)x.size();
    for (int i = 1, j = 0; i < n; ++i) {
      int bit = n >> 1;
      for (; j >= bit; bit >>= 1) j -= bit;
      j += bit;
      if (i < j) swap(x[i], x[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
      double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
      complex<double> wlen(cos(ang), sin(ang));
      for (int i = 0; i < n; i += len) {
        complex<double> w(1);
        for (int j = 0; j < len / 2; ++j) {
          complex<double> u = x[i + j];
          complex<double> v = x[i + j + len / 2] * w;
          x[i + j] = u + v;
          x[i + j + len / 2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert)
      for (int i = 0; i < n; ++i) x[i] /= n;
  }
  void multiply_fft(const vector<int> &x, const vector<int> &y,
                    vector<int> &res) const {
    vector<complex<double> > fa(x.begin(), x.end());
    vector<complex<double> > fb(y.begin(), y.end());
    int n = 1;
    while (n < (int)max(x.size(), y.size())) n <<= 1;
    n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(n);
    long long carry = 0;
    for (int i = 0; i < n; ++i) {
      long long t = (long long)(fa[i].real() + 0.5) + carry;
      carry = t / 1000;
      res[i] = t % 1000;
    }
  }
  BigInt mul_simple(const BigInt &v) const {
    BigInt res;
    res.sign = sign * v.sign;
    res.a.resize(a.size() + v.a.size());
    for (int i = 0; i < (int)a.size(); ++i)
      if (a[i])
        for (int j = 0, carry = 0; j < (int)v.a.size() || carry; ++j) {
          long long cur = res.a[i + j] +
                          (long long)a[i] * (j < (int)v.a.size() ? v.a[j] : 0) +
                          carry;
          carry = (int)(cur / BASE);
          res.a[i + j] = (int)(cur % BASE);
        }
    res.trim();
    return res;
  }
  typedef vector<long long> vll;
  static vll karatsubaMultiply(const vll &a, const vll &b) {
    int n = a.size();
    vll res(n + n);
    if (n <= 32) {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) res[i + j] += a[i] * b[j];
      return res;
    }
    int k = n >> 1;
    vll a1(a.begin(), a.begin() + k);
    vll a2(a.begin() + k, a.end());
    vll b1(b.begin(), b.begin() + k);
    vll b2(b.begin() + k, b.end());
    vll a1b1 = karatsubaMultiply(a1, b1);
    vll a2b2 = karatsubaMultiply(a2, b2);
    for (int i = 0; i < k; i++) a2[i] += a1[i];
    for (int i = 0; i < k; i++) b2[i] += b1[i];
    vll r = karatsubaMultiply(a2, b2);
    for (int i = 0; i < (int)a1b1.size(); i++) r[i] -= a1b1[i];
    for (int i = 0; i < (int)a2b2.size(); i++) r[i] -= a2b2[i];
    for (int i = 0; i < (int)r.size(); i++) res[i + k] += r[i];
    for (int i = 0; i < (int)a1b1.size(); i++) res[i] += a1b1[i];
    for (int i = 0; i < (int)a2b2.size(); i++) res[i + n] += a2b2[i];
    return res;
  }
  BigInt mul_karatsuba(const BigInt &v) const {
    vector<int> x6 = convert_base(this->a, BASE_DIGITS, 6);
    vector<int> y6 = convert_base(v.a, BASE_DIGITS, 6);
    vll x(x6.begin(), x6.end());
    vll y(y6.begin(), y6.end());
    while (x.size() < y.size()) x.push_back(0);
    while (y.size() < x.size()) y.push_back(0);
    while (x.size() & (x.size() - 1)) x.push_back(0), y.push_back(0);
    vll c = karatsubaMultiply(x, y);
    BigInt res;
    res.sign = sign * v.sign;
    long long carry = 0;
    for (int i = 0; i < (int)c.size(); i++) {
      long long cur = c[i] + carry;
      res.a.push_back((int)(cur % 1000000));
      carry = cur / 1000000;
    }
    res.a = convert_base(res.a, 6, BASE_DIGITS);
    res.trim();
    return res;
  }
  void operator*=(const BigInt &v) { *this = *this * v; }
  BigInt operator*(const BigInt &v) const {
    if (a.size() * v.a.size() <= 1000111) return mul_simple(v);
    if (a.size() > 500111 || v.a.size() > 500111) return mul_fft(v);
    return mul_karatsuba(v);
  }
  BigInt mul_fft(const BigInt &v) const {
    BigInt res;
    res.sign = sign * v.sign;
    multiply_fft(convert_base(a, BASE_DIGITS, 3),
                 convert_base(v.a, BASE_DIGITS, 3), res.a);
    res.a = convert_base(res.a, 3, BASE_DIGITS);
    res.trim();
    return res;
  }
  // -------------------- Misc --------------------
  BigInt abs() const {
    BigInt res = *this;
    res.sign *= res.sign;
    return res;
  }
  void trim() {
    while (!a.empty() && !a.back()) a.pop_back();
    if (a.empty()) sign = 1;
  }
  bool isZero() const { return a.empty() || (a.size() == 1 && !a[0]); }
  friend BigInt gcd(const BigInt &a, const BigInt &b) {
    return b.isZero() ? a : gcd(b, a % b);
  }
  friend BigInt lcm(const BigInt &a, const BigInt &b) {
    return a / gcd(a, b) * b;
  }
  friend BigInt sqrt(const BigInt &a1) {
    BigInt a = a1;
    while (a.a.empty() || a.a.size() % 2 == 1) a.a.push_back(0);
    int n = a.a.size();
    int firstDigit = (int)sqrt((double)a.a[n - 1] * BASE + a.a[n - 2]);
    int norm = BASE / (firstDigit + 1);
    a *= norm;
    a *= norm;
    while (a.a.empty() || a.a.size() % 2 == 1) a.a.push_back(0);
    BigInt r = (long long)a.a[n - 1] * BASE + a.a[n - 2];
    firstDigit = (int)sqrt((double)a.a[n - 1] * BASE + a.a[n - 2]);
    int q = firstDigit;
    BigInt res;
    for (int j = n / 2 - 1; j >= 0; j--) {
      for (;; --q) {
        BigInt r1 =
            (r - (res * 2 * BigInt(BASE) + q) * q) * BigInt(BASE) *
                BigInt(BASE) +
            (j > 0 ? (long long)a.a[2 * j - 1] * BASE + a.a[2 * j - 2] : 0);
        if (r1 >= 0) {
          r = r1;
          break;
        }
      }
      res *= BASE;
      res += q;
      if (j > 0) {
        int d1 = res.a.size() + 2 < r.a.size() ? r.a[res.a.size() + 2] : 0;
        int d2 = res.a.size() + 1 < r.a.size() ? r.a[res.a.size() + 1] : 0;
        int d3 = res.a.size() < r.a.size() ? r.a[res.a.size()] : 0;
        q = ((long long)d1 * BASE * BASE + (long long)d2 * BASE + d3) /
            (firstDigit * 2);
      }
    }
    res.trim();
    return res / norm;
  }
};
}  // namespace bigint
}  // namespace external
namespace dalt {
namespace graph {
// reference: https://codeforces.com/blog/entry/74847
// Binary lifting with O(n) memory and time complexity for preprocessing
template <class T = Nil> struct BinaryLiftCompress {
  using Self = BinaryLiftCompress<T>;
private:
  Vec<int> p;
  Vec<int> depth;
  Vec<int> jump;
  Vec<T> sum;
  Vec<T> weight;
  Adder<T> adder;
  T s_nil;
  void consider(i32 root) {
    if (root == -1 || jump[root] != -1) {
      return;
    }
    auto fa = p[root];
    consider(fa);
    add_leaf(root, fa);
  }
  void add_leaf(i32 leaf, i32 pid) {
    if (pid == -1) {
      jump[leaf] = leaf;
    } else if (depth[pid] - depth[jump[pid]] ==
               depth[jump[pid]] - depth[jump[jump[pid]]]) {
      jump[leaf] = jump[jump[pid]];
      sum[leaf] = adder(adder(weight[leaf], sum[pid]), sum[jump[pid]]);
    } else {
      jump[leaf] = pid;
      sum[leaf] = weight[leaf];
    }
  }
public:
  BinaryLiftCompress(T _s_nil, Vec<i32> _p, Vec<i32> _depth, Vec<T> _weight,
                     const Adder<T> &_adder)
      : s_nil(_s_nil), p(move(_p)), depth(move(_depth)), weight(move(_weight)),
        adder(_adder) {
    Assert(p.size() == depth.size());
    Assert(p.size() == weight.size());
    int n = Size(p);
    jump = Vec<int>(n, -1);
    sum = Vec<T>(n, s_nil);
    for (int i = 0; i < n; i++) {
      consider(i);
    }
  }
  Tuple<int, T> first_true(int node, const BiChecker<int, T> &pred) {
    auto s = s_nil;
    while (!pred(node, s)) {
      auto cand = adder(s, sum[node]);
      auto fa = jump[node];
      if (pred(fa, adder(cand, weight[node]))) {
        s = adder(s, weight[node]);
        node = p[node];
      } else {
        s = cand;
        if (node == fa) {
          return {-1, adder(s, weight[node])};
        }
        node = fa;
      }
    }
    return {node, adder(s, weight[node])};
  }
  Tuple<int, T> last_true(int node, const BiChecker<i32, T> &pred) {
    auto s = s_nil;
    if (!pred(node, s)) {
      return Tuple<int, T>(-1, s);
    }
    while (true) {
      auto cand = adder(s, sum[node]);
      auto p = jump[node];
      if (pred(p, adder(cand, weight[p]))) {
        if (node == jump[node]) {
          return Tuple<int, T>(node, adder(cand, weight[node]));
        }
        s = cand;
        node = jump[node];
      } else {
        auto cand = adder(s, weight[node]);
        auto p = p[node];
        if (pred(p, adder(cand, weight[node]))) {
          s = cand;
          node = p;
        } else {
          return Tuple<int, T>(node, cand);
        }
      }
    }
  }
  int first_true_raw(int node, const Checker<int> &pred) {
    while (!pred(node)) {
      auto fa = jump[node];
      if (pred(fa)) {
        node = p[node];
      } else {
        if (node == fa) {
          return -1;
        }
        node = fa;
      }
    }
    return node;
  }
  int last_true_raw(int node, const Checker<int> &pred) {
    if (!pred(node)) {
      return -1;
    }
    while (true) {
      auto p = jump[node];
      if (pred(p)) {
        if (node == jump[node]) {
          return node;
        }
        node = jump[node];
      } else {
        auto p = p[node];
        if (pred(p)) {
          node = p;
        } else {
          return node;
        }
      }
    }
  }
  int kth_ancestor(i32 node, i32 k) {
    int target = depth[node] - k;
    return first_true_raw(node, [&](auto i) { return depth[i] <= target; });
  }
  // lowest common ancestor in O(log_2 n)
  i32 lca(int a, int b) {
    if (depth[a] > depth[b]) {
      a = kth_ancestor(a, depth[a] - depth[b]);
    } else {
      b = kth_ancestor(b, depth[b] - depth[a]);
    }
    while (a != b) {
      if (jump[a] == jump[b]) {
        a = p[a];
        b = p[b];
      } else {
        a = jump[a];
        b = jump[b];
      }
    }
    return a;
  }
};
} // namespace graph
} // namespace dalt
namespace dalt {
template <class T>
enable_if_t<is_integral_v<T>, Optional<T>> FirstTrue(
    T l, T r, const Checker<T> &checker) {
  if (!checker(r)) {
    return {};
  }
  while (l < r) {
    T m = DivFloor(l + r, 2);
    if (checker(m)) {
      r = m;
    } else {
      l = m + 1;
    }
  }
  return l;
}
template <class T>
enable_if_t<is_integral_v<T>, Optional<T>> LastTrue(T l, T r,
                                                    const Checker<T> &checker) {
  if (!checker(l)) {
    return {};
  }
  while (l < r) {
    T m = DivCeil(l + r, 2);
    if (checker(m)) {
      l = m;
    } else {
      r = m - 1;
    }
  }
  return l;
}
template <class T>
enable_if_t<is_floating_point_v<T>, Optional<T>> FirstTrue(
    T l, T r, const Checker<T> &checker, Function<bool()> stopper) {
  if (!checker(r)) {
    return {};
  }
  while (!stopper()) {
    T m = (l + r) / 2;
    if (checker(m)) {
      r = m;
    } else {
      l = m;
    }
  }
  return l;
}
template <class T>
enable_if_t<is_floating_point_v<T>, Optional<T>> FirstTrue(
    T l, T r, const Checker<T> &checker, i32 max_round) {
  return FirstTrue<T>(
      l, r, checker,[&]() { return max_round-- <= 0; });
}
}  // namespace dalt
namespace dalt {
namespace sbt {
template <class S, class U, i64 ID, class CID = Nil>
struct SelfBalanceTreeRegistry {
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
namespace dalt {
namespace sbt {
struct BinaryTree {
  struct Node {
    Array<Node *, 2> next;
    i64 size;
    Node *get_left() { return next[0]; }
    Node *get_right() { return next[1]; }
    const Node *get_left() const { return next[0]; }
    const Node *get_right() const { return next[1]; }
    Node *create_or_get(int i) {
      if (!next[i]) {
        next[i] = new Node();
      }
      return next[i];
    }
    i64 get_child_size(int i) const {
      if (!next[i]) {
        return 0;
      }
      return next[i]->size;
    }
    ~Node() {
      delete next[0];
      delete next[1];
    }
  };
  Node *root;
  i32 H;
  BinaryTree(u64 max_val) {
    root = new Node();
    H = Log2Floor(max_val);
  }
  void add(u64 x, i64 cnt) {
    auto dfs = [&](auto &dfs, int index, Node *root) {
      root->size += cnt;
      if (index < 0) {
        return;
      }
      int bit = KthBit(x, index);
      dfs(dfs, index - 1, root->create_or_get(bit));
    };
    dfs(dfs, H, root);
  }
  void remove(u64 x, i64 cnt) { add(x, -cnt); }
  i64 query_sum(u64 L, u64 R) const {
    if (L > R) {
      return 0;
    }
    auto dfs = [&](auto &dfs, Node *root, int l, int r) -> i64 {
      if (sbt::SegmentNoIntersection(L, R, l, r) || root == NULL) {
        return 0;
      }
      if (sbt::SegmentCover(L, R, l, r)) {
        return root->size;
      }
      int m = (l + r) / 2;
      return dfs(dfs, root->get_left(), l, m) +
             dfs(dfs, root->get_right(), m + 1, r);
    };
    return dfs(dfs, root, 0, (1 << (H + 1)) - 1);
  }
  i64 total() const { return root->size; }
  u64 kth_xor(u64 x, i64 k = 1) const {
    u64 ans = 0;
    auto dfs = [&](auto &dfs, Node *root, int index) -> void {
      if (index < 0) {
        return;
      }
      int prefer = KthBit(x, index);
      if (root->get_child_size(prefer) < k) {
        k -= root->get_child_size(prefer);
        prefer ^= 1;
      }
      ans |= u64(prefer) << index;
      dfs(dfs, root->create_or_get(prefer), index - 1);
    };
    dfs(dfs, root, H);
    return ans;
  }
  Vec<Pair<u64, i64>> to_vec() const {
    u64 trace = 0;
    Vec<Pair<u64, i64>> ans;
    auto dfs = [&](auto &dfs, Node *root, int index) {
      if (root == NULL) {
        return;
      }
      if (index < 0) {
        if (root->size != 0) {
          ans.emplace_back(trace, root->size);
        }
        return;
      }
      for (int i = 0; i < 2; i++) {
        trace ^= u64(i) << index;
        dfs(dfs, root->next[i], index - 1);
        trace ^= u64(i) << index;
      }
    };
    dfs(dfs, root, H);
    return ans;
  }
#ifdef DROP
  ~BinaryTree() { delete root; }
#endif
};
}  // namespace sbt
}  // namespace dalt
namespace dalt {
namespace graph {
template <class E>
IsBiGraph(E, Optional<Vec<bool>>) BipartiteColor(const Graph<E> &g) {
  int n = Size(g);
  Vec<bool> visited(n);
  Vec<bool> color(n);
  bool valid = true;
  auto dfs = [&](auto &dfs, int root, bool c) {
    if (visited[root]) {
      if (color[root] != c) {
        valid = false;
      }
      return;
    }
    visited[root] = true;
    for (auto &e : g[root]) {
      dfs(dfs, e.to, !c);
    }
  };
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(dfs, i, true);
    }
  }
  if (valid) {
    return color;
  }
  return {};
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
namespace graph {
// super fast, worst O(nm)
template <class E> IsBiGraph(E, Vec<int>) BipartiteMatch(const Graph<E> &g) {
  int n = Size(g);
  Vec<int> mate(n, -1);
  Vec<int> visit(n, 0);
  int time = 0;
  auto dfs = [&](auto &dfs, int root) -> bool {
    if (visit[root] == time) {
      return false;
    }
    visit[root] = time;
    for (auto &e : g[root]) {
      if (mate[e.to] == -1) {
        mate[root] = e.to;
        mate[e.to] = root;
        return true;
      }
      visit[e.to] = time;
      if (dfs(dfs, mate[e.to])) {
        mate[root] = e.to;
        mate[e.to] = root;
        return true;
      }
    }
    return false;
  };
  while (true) {
    bool find = false;
    time++;
    for (int i = 0; i < n; i++) {
      if (mate[i] == -1 && dfs(dfs, i)) {
        find = true;
      }
    }
    if (!find) {
      break;
    }
  }
  return mate;
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace graph {
// O(V+E)
template <class E>
IsBiGraph(E, Vec<bool>)
    BipartiteMinimumVertexCover(const Graph<E>& g, const Vec<int>& mates,
                                const Vec<bool>& bipartite_color) {
  int n = Size(g);
  Vec<bool> visited(n);
  auto dfs = [&](auto& dfs, int root) {
    if (visited[root]) {
      return;
    }
    visited[root] = true;
    for (auto& e : g[root]) {
      if (mates[e.to] == -1 || visited[e.to]) {
        continue;
      }
      visited[e.to] = true;
      dfs(dfs, mates[e.to]);
    }
  };
  for (int i = 0; i < n; i++) {
    if (bipartite_color[i] && mates[i] == -1) {
      dfs(dfs, i);
    }
  }
  Vec<bool> ans(n);
  for (int i = 0; i < n; i++) {
    if (bipartite_color[i]) {
      ans[i] = !visited[i];
    } else {
      ans[i] = visited[i];
    }
  }
  return ans;
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
namespace graph {
// credited to: http://longrm.com/2018/05/05/2018-05-05-KM/
// maximum weighted perfect matching
template <class V>
Tuple<V, Vec<i32>, Vec<i32>, Vec<V>, Vec<V>> BipartiteWeightMatchByKM(
    const Vec<Vec<V>> &table) {
  const static V INF = std::numeric_limits<V>::max() / 2;
  int n = Size(table);
  Vec<V> left_label(n, -INF);
  Vec<V> right_label(n);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (table[x][y] > left_label[x]) {
        left_label[x] = table[x][y];
      }
    }
  }
  Vec<i32> left_mate(n, -1);
  Vec<i32> right_mate(n, -1);
  auto bfs = [&](auto startX) {
    bool find = false;
    int end_y = -1;
    Vec<i32> y_pre(n, -1);   // 标识搜索路径上y点的前一个点
    Vec<bool> S(n), T(n);    // S集合，T集合
    Vec<V> slack_y(n, INF);  // Y点的松弛变量
    Vec<i32> queue(n);       // 队列
    int qs = 0, qe = 0;      // 队列开始结束索引
    queue[qe++] = startX;
    while (!find) {               // 循环直到找到匹配
      while (qs < qe && !find) {  // 队列不为空
        int x = queue[qs++];
        S[x] = true;
        for (int y = 0; y < n; y++) {
          if (T[y]) {
            continue;
          }
          V tmp = left_label[x] + right_label[y] - table[x][y];
          if (tmp == 0) {  // 相等子树中的边
            T[y] = true;
            y_pre[y] = x;
            if (right_mate[y] == -1) {
              end_y = y;
              find = true;
              break;
            } else {
              queue[qe++] = right_mate[y];
            }
          } else if (slack_y[y] >
                     tmp) {  // 不在相等子树中的边，看是否能够更新松弛变量
            slack_y[y] = tmp;
            y_pre[y] = x;
          }
        }
      }
      if (find) {
        break;
      }
      V a = INF;
      for (int y = 0; y < n; y++) {  // 找到最小的松弛值
        if (!T[y]) {
          a = Min(a, slack_y[y]);
        }
      }
      for (int i = 0; i < n; i++) {  // 根据a修改标号值
        if (S[i]) {
          left_label[i] -= a;
        }
        if (T[i]) {
          right_label[i] += a;
        }
      }
      qs = qe = 0;
      for (int y = 0; y < n; y++) {  // 重要！！！控制修改标号之后需要检查的x点
        if (!T[y] &&
            slack_y[y] ==
                a) {  // 查看那些y点新加入到T集合，注意，这些y点的前向x点都记录在了y_pre里面，所以这些x点不用再次入队
          T[y] = true;
          if (right_mate[y] == -1) {  // 新加入的y点没有匹配，那么就找到可扩路了
            end_y = y;
            find = true;
            break;
          } else {  // 新加入的y点已经有匹配了，将它匹配的x加到队列
            queue[qe++] = right_mate[y];
          }
        }
        slack_y[y] -=
            a;  // 所有松弛值减去a。(对于T集合中的松弛值已经没用了，对于不在T集合里面的y点，
      }  // 它们的松弛值是通过S集合中的x点求出的，S集合中的x点的标号值在上面都减去了a，所以这里松弛值也要减去a)
    }
    while (end_y != -1) {  // 找到可扩路最后的y点后，回溯并扩充
      int preX = y_pre[end_y], preY = left_mate[preX];
      left_mate[preX] = end_y;
      right_mate[end_y] = preX;
      end_y = preY;
    }
  };
  for (int x = 0; x < n; x++) {
    bfs(x);
  }
  V value = 0;
  for (int x = 0; x < n; x++) {
    value += table[x][left_mate[x]];
  }
  return {value, left_mate, right_mate, left_label, right_label};
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
struct BitSet {
private:
  Vec<u64> data;
  u64 tail_available;
  int capacity;
  int m;
  static const int SHIFT = 6;
  static const int LOW = 63;
  static const int BITS_FOR_EACH = 64;
  static const u64 ALL_ONE = ~u64(0);
  static const u64 ALL_ZERO = u64(0);
  static const int MAX_OFFSET = 63;
  static const int MIN_OFFSET = 0;
  static int word(int i) { return i >> SHIFT; }
  static int offset(int i) { return i & LOW; }
public:
  BitSet(int n) {
    capacity = n;
    this->m = (capacity + 64 - 1) / 64;
    data.resize(m);
    tail_available = IntervalOnes64(0, offset(capacity - 1));
  }
  BitSet interval(int l, int r) {
    if (r < l) {
      return BitSet(0);
    }
    return BitSet(*this, l, r);
  }
  BitSet(const BitSet &bs, int l, int r) { copyInterval(bs, l, r); }
  void copyInterval(const BitSet &bs, int l, int r) {
    capacity = r - l + 1;
    tail_available = IntervalOnes64(0, offset(capacity - 1));
    int req_length = word(r) - word(l) + 1;
    auto offset = bs.data.begin() + l;
    data = Vec<u64>(offset, offset + req_length);
    this->m = req_length;
    left_shift(this->offset(l));
    this->m = (capacity + 64 - 1) / 64;
    data[m - 1] &= tail_available;
    for (int i = m; i < req_length; i++) {
      data[i] = 0;
    }
  }
  int get(int i) const { return data[word(i)] & (u64(1) << offset(i)); }
  void set(int i) { data[word(i)] |= (u64(1) << offset(i)); }
  void set(int i, int val) {
    if (val) {
      set(i);
    } else {
      clear(i);
    }
  }
  void fill(bool val) {
    if (val) {
      set_range(0, get_capacity() - 1);
    } else {
      clear_range(0, get_capacity() - 1);
    }
  }
  void set_range(int l, int r) {
    if (r < l) {
      return;
    }
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      data[i] = ALL_ONE;
    }
    // lword
    if (left_word == right_word) {
      data[left_word] |= IntervalOnes64(offset(l), offset(r));
    } else {
      data[left_word] |= IntervalOnes64(offset(l), MAX_OFFSET);
      data[right_word] |= IntervalOnes64(0, offset(r));
    }
  }
  void clear(int i) { data[word(i)] &= ~(u64(1) << offset(i)); }
  void inverse(int i) { data[word(i)] ^= (u64(1) << offset(i)); }
  void clear_range(int l, int r) {
    if (r < l) {
      return;
    }
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      data[i] = ALL_ZERO;
    }
    // lword
    if (left_word == right_word) {
      data[left_word] &= ~IntervalOnes64(offset(l), offset(r));
    } else {
      data[left_word] &= ~IntervalOnes64(offset(l), MAX_OFFSET);
      data[right_word] &= ~IntervalOnes64(0, offset(r));
    }
  }
  void flip(int i) { data[word(i)] ^= (u64(1) << offset(i)); }
  void flip(int l, int r) {
    if (r < l) {
      return;
    }
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      data[i] ^= ALL_ONE;
    }
    // lword
    if (left_word == right_word) {
      data[left_word] ^= IntervalOnes64(offset(l), offset(r));
    } else {
      data[left_word] ^= IntervalOnes64(offset(l), MAX_OFFSET);
      data[right_word] ^= IntervalOnes64(0, offset(r));
    }
  }
  int get_capacity() const { return capacity; }
  bool empty() const { return next_set_bit(0) >= get_capacity(); }
  int size() const {
    int ans = 0;
    for (u64 x : data) {
      ans += CountBit(x);
    }
    return ans;
  }
  int size(int l, int r) const {
    if (r < l) {
      return 0;
    }
    int ans = 0;
    int left_word = l >> SHIFT;
    int right_word = r >> SHIFT;
    for (int i = left_word + 1; i < right_word; i++) {
      ans += CountBit(data[i]);
    }
    // lword
    if (left_word == right_word) {
      ans += CountBit(data[left_word] & IntervalOnes64(offset(l), offset(r)));
    } else {
      ans += CountBit(data[left_word] & IntervalOnes64(offset(l), MAX_OFFSET));
      ans += CountBit(data[right_word] & IntervalOnes64(0, offset(r)));
    }
    return ans;
  }
  void copy(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    data = bs.data;
  }
  void or_op(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    for (int i = 0; i < n; i++) {
      data[i] |= bs.data[i];
    }
  }
  void and_op(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    for (int i = 0; i < n; i++) {
      data[i] &= bs.data[i];
    }
  }
  void xor_op(const BitSet &bs) {
    int n = Min(this->m, bs.m);
    for (int i = 0; i < n; i++) {
      data[i] ^= bs.data[i];
    }
  }
  int next_set_bit(int start) const {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != 0) {
      u64 mask = IntervalOnes64(offset, MAX_OFFSET);
      if ((data[w] & mask) != 0) {
        return TrailingZeroNumber(data[w] & mask) + w * BITS_FOR_EACH;
      }
      w++;
    }
    while (w < m && data[w] == ALL_ZERO) {
      w++;
    }
    if (w >= m) {
      return get_capacity();
    }
    return TrailingZeroNumber(data[w]) + w * BITS_FOR_EACH;
  }
  int previous_set_bit(int start) const {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != MAX_OFFSET) {
      u64 mask = IntervalOnes64(0, offset);
      if ((data[w] & mask) != 0) {
        return MAX_OFFSET - LeadingZeroNumber(data[w] & mask) +
               w * BITS_FOR_EACH;
      }
      w--;
    }
    while (w >= 0 && data[w] == ALL_ZERO) {
      w--;
    }
    if (w < 0) {
      return -1;
    }
    return MAX_OFFSET - LeadingZeroNumber(data[w]) + w * BITS_FOR_EACH;
  }
  int next_clear_bit(int start) {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != 0) {
      u64 mask = IntervalOnes64(offset, MAX_OFFSET);
      if ((~data[w] & mask) != 0) {
        return TrailingZeroNumber(~data[w] & mask) + w * BITS_FOR_EACH;
      }
      w++;
    }
    while (w < m && data[w] == ALL_ONE) {
      w++;
    }
    if (w >= m) {
      return get_capacity();
    }
    return TrailingZeroNumber(~data[w]) + w * BITS_FOR_EACH;
  }
  int prev_clear_bit(int start) {
    int offset = this->offset(start);
    int w = word(start);
    if (offset != MAX_OFFSET) {
      u64 mask = IntervalOnes64(0, offset);
      if ((~data[w] & mask) != 0) {
        return MAX_OFFSET - LeadingZeroNumber(~data[w] & mask) +
               w * BITS_FOR_EACH;
      }
      w--;
    }
    while (w >= 0 && data[w] == ALL_ONE) {
      w--;
    }
    if (w < 0) {
      return -1;
    }
    return MAX_OFFSET - LeadingZeroNumber(~data[w]) + w * BITS_FOR_EACH;
  }
  void left_shift(int n) {
    int word_move = word(n);
    int offset_move = offset(n);
    int rshift = MAX_OFFSET - (offset_move - 1);
    if (offset_move != 0) {
      // slightly
      for (int i = 0; i < m; i++) {
        if (i > 0) {
          data[i - 1] |= data[i] << rshift;
        }
        data[i] >>= offset_move;
      }
    }
    if (word_move > 0) {
      for (int i = 0; i < m; i++) {
        if (i >= word_move) {
          data[i - word_move] = data[i];
        }
        data[i] = 0;
      }
    }
  }
  void right_shift(int n) {
    int word_move = word(n);
    int offset_move = offset(n);
    int lShift = MAX_OFFSET + 1 - offset_move;
    if (offset_move != 0) {
      // slightly
      for (int i = m - 1; i >= 0; i--) {
        if (i + 1 < m) {
          data[i + 1] |= data[i] >> lShift;
        }
        data[i] <<= offset_move;
      }
    }
    if (word_move > 0) {
      for (int i = m - 1; i >= 0; i--) {
        if (i + word_move < m) {
          data[i + word_move] = data[i];
        }
        data[i] = 0;
      }
    }
    data[m - 1] &= tail_available;
  }
  Vec<i32> to_vec() const {
    Vec<i32> ans;
    for (int i = 0; i < capacity; i++) {
      if (get(i)) {
        ans.push_back(i);
      }
    }
    return ans;
  }
  BitSet clone() const { return *this; }
  int operator[](int i) { return get(i); }
  friend bool operator==(const_ref(BitSet) a, const_ref(BitSet) b);
  friend bool operator<(const_ref(BitSet) a, const_ref(BitSet) b);
  BitSet &operator|=(const_ref(BitSet) b) {
    or_op(b);
    return *this;
  }
  BitSet &operator&=(const_ref(BitSet) b) {
    and_op(b);
    return *this;
  }
  BitSet &operator^=(const_ref(BitSet) b) {
    xor_op(b);
    return *this;
  }
  BitSet &operator>>=(int k) {
    right_shift(k);
    return *this;
  }
  BitSet &operator<<=(int k) {
    left_shift(k);
    return *this;
  }
  BitSet operator>>(int k) { return clone() >>= k; }
  BitSet operator<<(int k) { return clone() <<= k; }
  void swap(BitSet &b) {
    data.swap(b.data);
    Swap(tail_available, b.tail_available);
    Swap(capacity, b.capacity);
    Swap(m, b.m);
  }
};
inline bool operator==(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.capacity == b.capacity &&
         memcmp((void *)a.data.data(), (void *)b.data.data(), a.capacity) == 0;
}
inline bool operator!=(const_ref(BitSet) a, const_ref(BitSet) b) {
  return !(a == b);
}
inline bool operator<(const_ref(BitSet) a, const_ref(BitSet) b) {
  Assert(a.capacity == b.capacity);
  return memcmp((void *)a.data.data(), (void *)b.data.data(), a.capacity) < 0;
}
inline BitSet operator|(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.clone() |= b;
}
inline BitSet operator&(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.clone() &= b;
}
BitSet operator^(const_ref(BitSet) a, const_ref(BitSet) b) {
  return a.clone() ^= b;
}
} // namespace dalt
namespace dalt {
namespace poly {
template <class T>
Vec<T> CopyAndExtend(const Vec<T> &data, int n) {
  Vec<T> res;
  res.reserve(n);
  if (n <= Size(data)) {
    res.insert(res.begin(), data.begin(), data.begin() + n);
  } else {
    res.insert(res.begin(), All(data));
    res.resize(n);
  }
  return res;
}
template <class T>
void Normalize(Vec<T> &p) {
  while (!p.empty() && p.back() == T(0)) {
    p.pop_back();
  }
  if (p.empty()) {
    p.push_back(T(0));
  }
}
template <class T>
void Extend(Vec<T> &p, int cap) {
  while (Size(p) < cap) {
    p.push_back(T());
  }
}
template <class T>
Vec<T> DotMul(const Vec<T> &a, const Vec<T> &b) {
  int n = Min(Size(a), Size(b));
  Vec<T> ans(n);
  for (int i = 0; i < n; i++) {
    ans[i] = a[i] * b[i];
  }
  return ans;
}
template <class T>
void DotMulInplace(Vec<T> &a, const Vec<T> &b) {
  int n = Size(b);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i] = a[i] * b[i];
  }
}
template <class T>
void DotMulPlus(Vec<T> &a, const Vec<T> &b, Vec<T> &res) {
  int n = Min(Size(a), Size(b));
  for (int i = 0; i < n; i++) {
    res[i] = res[i] + a[i] * b[i];
  }
}
template <class T>
T Apply(const Vec<T> &a, T x) {
  T sum = 0;
  for (int i = Size(a) - 1; i >= 0; i--) {
    sum = sum * x + a[i];
  }
  return sum;
}
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace fwt {
// res[i] is how many superset of i occur in p
template <class T> struct And {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a + b, b}; }
};
// p[i] is the number of superset of i, ret[i] is the occurrence number of
// number i
template <class T> struct IAnd {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a - b, b}; }
};
// res[i] is how many subsets of i occur in p
template <class T> struct Or {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a, b + a}; }
};
// p[i] is the number of subset of i, ret[i] is the occurrence number of number
// i
template <class T> struct IOr {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a, b - a}; }
};
template <class T> struct Xor {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) { return {a + b, a - b}; }
};
template <class T> struct IXor {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) {
    return {(a + b) / T(2), (a - b) / T(2)};
  }
};
template <class T> struct IXorFast {
  using Type = T;
  static Array<T, 2> conv(const T &a, const T &b) {
    static const T div = T(1) / T(2);
    return {(a + b) * div, (a - b) * div};
  }
};
template <class Conv, class T = typename Conv::Type>
void BitwiseTransform(Vec<T> &data, int l, int r) {
  static_assert(is_same_v<typename Conv::Type, T>);
  if (l >= r) {
    return;
  }
  i32 m = (l + r) / 2;
  i32 step = r - m;
  BitwiseTransform<Conv>(data, l, m);
  BitwiseTransform<Conv>(data, m + 1, r);
  for (int i = l; i <= m; i++) {
    Array<T, 2> res = Conv::conv(data[i], data[i + step]);
    data[i] = res[0];
    data[i + step] = res[1];
  }
}
template <class Conv, class T = typename Conv::Type>
void BitwiseInverse(Vec<T> &data, int l, int r) {
  static_assert(is_same_v<typename Conv::Type, T>);
  if (l >= r) {
    return;
  }
  i32 m = (l + r) / 2;
  i32 step = r - m;
  for (int i = l; i <= m; i++) {
    Array<T, 2> res = Conv::conv(data[i], data[i + step]);
    data[i] = res[0];
    data[i + step] = res[1];
  }
  BitwiseInverse<Conv>(data, l, m);
  BitwiseInverse<Conv>(data, m + 1, r);
}
// ret[i] = \sum_{j \in i} a[j] * b[i ^ j]
// O(n(\log n)^2)
template <class T> Vec<T> SubsetConvolution(Vec<T> a, Vec<T> b) {
  Assert(Size(a) == Size(b));
  Assert(Size(a) == LowestOneBit(Size(a)));
  i32 n = Size(a);
  if (n == 0) {
    return Vec<T>();
  }
  i32 log = Log2Floor(n);
  Vec<Vec<T>> fwta = Vec<Vec<T>>(log + 1, Vec<T>(n));
  Vec<Vec<T>> fwtb = fwta;
  Vec<T> c(n);
  Vec<T> t(n);
  for (i32 i = 0; i < n; i++) {
    let bitcount = CountBit(i);
    fwta[bitcount][i] = a[i];
    fwtb[bitcount][i] = b[i];
  }
  for (i32 i = 0; i <= log; i++) {
    BitwiseTransform<Or<T>>(fwta[i], 0, Size(fwta[i]) - 1);
    BitwiseTransform<Or<T>>(fwtb[i], 0, Size(fwtb[i]) - 1);
  }
  for (i32 i = 0; i <= log; i++) {
    Fill(All(t), T(0));
    for (i32 j = 0; j <= i; j++) {
      let k = i - j;
      poly::DotMulPlus(fwta[j], fwtb[k], t);
    }
    BitwiseInverse<IOr<T>>(t, 0, Size(t) - 1);
    for (i32 j = 0; j < n; j++) {
      if (CountBit(j) == i) {
        c[j] = t[j];
      }
    }
  }
  return c;
}
} // namespace fwt
} // namespace dalt
namespace dalt {
static const u8 BitReverseTable[]{
    0,  128, 64, 192, 32, 160, 96,  224, 16, 144, 80, 208, 48, 176, 112, 240,
    8,  136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 120, 248,
    4,  132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 180, 116, 244,
    12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 60, 188, 124, 252,
    2,  130, 66, 194, 34, 162, 98,  226, 18, 146, 82, 210, 50, 178, 114, 242,
    10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 58, 186, 122, 250,
    6,  134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 54, 182, 118, 246,
    14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 62, 190, 126, 254,
    1,  129, 65, 193, 33, 161, 97,  225, 17, 145, 81, 209, 49, 177, 113, 241,
    9,  137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 121, 249,
    5,  133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 245,
    13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253,
    3,  131, 67, 195, 35, 163, 99,  227, 19, 147, 83, 211, 51, 179, 115, 243,
    11, 139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251,
    7,  135, 71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247,
    15, 143, 79, 207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255};
inline u8 ReverseBit(u8 x) { return BitReverseTable[x]; }
inline i8 ReverseBit(i8 x) { return ReverseBit((u8)x); }
#define DefineReverseBit(bit, low)                                             \
  inline u##bit ReverseBit(u##bit x) {                                         \
    static const u##bit mask = (u##bit(1) << low) - 1;                         \
    return ReverseBit(u##low(x >> low)) |                                      \
           (u##bit(ReverseBit(u##low(x & mask))) << low);                      \
  }                                                                            \
  inline i##bit ReverseBit(i##bit x) { return ReverseBit(u##bit(x)); }
DefineReverseBit(16, 8);
DefineReverseBit(32, 16);
DefineReverseBit(64, 32);
#undef DefineReverseBit
} // namespace dalt
namespace dalt {
namespace poly {
MakeAnnotation(convolution)
}
} // namespace dalt
namespace dalt {
struct uint128 {
  u64 high, low;
  uint128(u64 _low = 0, u64 _high = 0) : high(_high), low(_low) {}
  using Self = uint128;
  CastToAllScalar(low);
  friend Self operator+(const Self& a, const Self& b) {
    Self ans(a.low + b.low, a.high + b.high);
    if (ans.low < a.low) {
      ans.high++;
    }
    return ans;
  }
  friend Self operator-(const Self& a, const Self& b) {
    u64 h = a.high - b.high;
    u64 l = a.low - b.low;
    if(a.low < b.low) {
      l = -l;
      h--;
    }
    return Self(l, h);
  }
  friend Self operator*(const Self& a, const Self& b) {
    static u64 mask = ((u64(1) << 32) - 1);
    u64 all = a.low & mask;
    u64 bll = b.low & mask;
    u64 alh = a.low >> 32;
    u64 blh = b.low >> 32;
    Self ans(0, a.high * b.low + a.low * b.high + alh * blh + (all * blh >> 32) +
                 (alh * bll >> 32));
    ans += all * bll;
    ans += ((all * blh) & mask) << 32;
    ans += ((bll * alh) & mask) << 32;
    return ans;
  }
  Self& operator+=(const u64& rhs) {
    low += rhs;
    if (low < rhs) {
      high++;
    }
    return *this;
  }
  bool operator<(const Self& rhs) const {
    return MakePair(high, low) < MakePair(rhs.high, rhs.low);
  }
  ImplDefaultComparision(Self);
  //ImplArithmeticAssignOperation(Self);
  bool operator==(const Self& rhs) {
    return high == rhs.high && low == rhs.low;
  }
  bool operator!=(const Self& rhs) { return !(*this == rhs); }
  // x < 2 ^ 31
  u32 modular(u32 x) {
    static u64 max = std::numeric_limits<u64>::max();
    u64 ans = low < x ? low : low % x;
    if (high > 0) {
      ans = ans + (high >= x ? high % x : high) * (max % x + 1);
      ans %= x;
    }
    return ans;
  }
};
using u128 = uint128;
}  // namespace dalt
namespace dalt {
namespace poly {
template <class T>
struct BruteForceConv {
  using Type = T;
  template <class Arg = T>
  static enable_if_t<is_same_v<Arg, T> &&
                         !(is_modint_v<T> && is_same_v<typename T::Type, i32>),
                     Vec<T>>
  conv(const Vec<T> &a, const Vec<T> &b) {
    int rank = Size(a) + Size(b) - 2; 
    Vec<T> c(rank + 1);
    for (int i = 0; i < Size(a); i++) {
      for (int j = 0; j < Size(b); j++) {
        c[i + j] += a[i] * b[j];
      }
    }
    return c;
  }
  template <class Arg = T>
  static enable_if_t<is_same_v<Arg, T> && is_modint_v<T> &&
                         is_same_v<typename T::Type, i32>,
                     Vec<T>>
  conv(const Vec<T> &a, const Vec<T> &b) {
    int rank = Size(a) + Size(b) - 2;
    Vec<u128> data(rank + 1);
    for(int i = 0; i < Size(a); i++) {
      for(int j = 0; j < Size(b); j++) {
        data[i + j] += u64(a[i].value) * b[j].value;
      }
    }
    Vec<T> ans(rank + 1);
    i32 modulus = T::modulus();
    for(int i = 0; i <= rank; i++) {
      ans[i] = data[i].modular(modulus);
    } 
    return ans;
  }
  static Vec<T> conv2(const Vec<T> &a) { return conv(a, a); }
  static Vec<T> inverse(Vec<T> p, i32 n) {
    Extend(p, n);
    auto dfs = [&](auto &dfs, i32 m) -> Vec<T> {
      if (m == 1) {
        return Vec<T>{T(1) / p[0]};
      }
      i32 prev_mod = (m + 1) / 2;
      auto C = dfs(dfs, prev_mod);
      auto AC = conv(p, m, C, prev_mod);
      AC.resize(m);
      for (int i = 0; i < m; i++) {
        AC[i] = T(0) - AC[i];
      }
      AC[0] = AC[0] + T(2);
      auto res = conv(C, AC);
      res.resize(m);
      return res;
    };
    auto ans = dfs(dfs, n);
    ans.resize(n);
    return ans;
  }
  static Array<Vec<T>, 2> div_and_rem(Vec<T> a, Vec<T> b) {
    Reverse(All(b));
    auto inv_first = T(1) / b[0];
    i32 n = Size(a);
    i32 m = Size(b);
    if (n < m) {
      return {Vec<T>{T(0)}, Vec<T>{Move(a)}};
    }
    Vec<T> divisor(n - m + 1);
    for (int i = n - 1; i >= m - 1; i++) {
      if (a[i] == T(0)) {
        continue;
      }
      T factor = a[i] * inv_first;
      divisor[i - (m - 1)] = factor;
      for (int j = 0; j < m; j++) {
        a[i - j] = a[i - j] - b[j] * factor;
      }
    }
    return Array<Vec<T>, 2>{Move(divisor), Move(a)};
  }
};
template<class T>
struct is_convolution<BruteForceConv<T>> {
  static const bool value = true;
};
}  // namespace poly
}  // namespace dalt
namespace dalt {
struct CartesianTree {
  using Self = CartesianTree;
  Self *left;
  Self *right;
  int index;
  //create cartesian tree from 0..n, the smallest element becomes the root
  //return the root
  static CartesianTree *from(int n, const Comparator<int> &cmp) {
    Deque<Self *> deque;
    for (int i = 0; i < n; i++) {
      Self *self = new Self();
      self->left = self->right = NULL;
      self->index = i;
      while (!deque.empty() && cmp(self->index, deque.back()->index) > 0) {
        auto tail = deque.back();
        deque.pop_back();
        tail->right = self->left;
        self->left = tail;
      }
      deque.push_back(self);
    }
    while (Size(deque) > 1) {
      auto tail = deque.back();
      deque.pop_back();
      deque.back()->right = tail;
    }
    return deque.back();
  }
};
} // namespace dalt
namespace dalt {
template <class T, class F>
Vec<T> Cast(const Vec<F>& data) {
  int n = Size(data);
  Vec<T> ans;
  ans.reserve(n);
  for (int i = 0; i < n; i++) {
    ans.push_back(T(data[i]));
  }
  return ans;
}
template <class V, class C, class K>
V GetOrDefault(const C& data, const K& key, const V& def = V()) {
  auto res = data.find(key);
  if (res == data.end()) {
    return def;
  }
  return res->second;
}
template <class V, class C>
V PopFront(C& data) {
  V res = V(data.front());
  data.pop_front();
  return res;
}
template <class V, class C>
V PopBack(C& data) {
  V res = V(data.back());
  data.pop_back();
  return res;
}
}  // namespace dalt
namespace dalt {
namespace math {
template <class T>
struct Combination {
  static_assert(is_modint_v<T>);
  using Modular = typename T::Modular;
  Vec<T> fact;
  Vec<T> inv_fact;
  Combination(int cap) {
    cap += 1;
    fact.resize(cap);
    inv_fact.resize(cap);
    fact[0] = T(1);
    for (int i = 1; i < cap; i++) {
      T v = T(i);
      if (v != T(0)) {
        fact[i] = fact[i - 1] * v;
      } else {
        fact[i] = fact[i];
      }
    }
    T inv = T(1) / fact.back();
    for (int i = cap - 1; i >= 0; i--) {
      T v = T(i);
      inv_fact[i] = inv;
      if (v != T(0)) {
        inv = inv * T(i);
      }
    }
  }
  T inverse(int x) { return inv_fact[x] * fact[x - 1]; }
  T combination(int a, int b) {
    if (a < b || b < 0) {
      return T(0);
    }
    return fact[a] * inv_fact[b] * inv_fact[a - b];
  }
  template <class E>
  T combination_lucas(E a, E b) {
    if (a < b || b < 0) {
      return T(0);
    }
    if (a < Modular::modulus) {
      return fact[a] * inv_fact[b] * inv_fact[a - b];
    } else {
      return combination(a % Modular::modulus, b % Modular::modulus) *
             combination_lucas(a / Modular::modulus, b / Modular::modulus);
    }
  }
};
}  // namespace math
}  // namespace dalt
#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif
namespace dalt {
namespace geo2 {
template <class T>
struct Polygon {
  static_assert(is_near_value_v<T>);
  using Type = Point<T>;
  using Self = Polygon<T>;
  using Pt = Type;
  Vec<Pt> data;
  Polygon(Vec<Pt> _data) : data(Move(_data)) {}
  int size() const { return data.size(); }
  Pt& operator[](int index) { return data[index]; }
  const Pt& operator[](int index) const { return data[index]; }
  bool is_convex() const {
    bool has_pos = false;
    bool has_neg = false;
    for (int i = 0, n = Size(data); i < n; i++) {
      int o = Pt::orient(data[(i + 1) % n], data[(i + 2) % n], data[i]);
      if (o > 0) {
        has_pos = true;
      }
      if (o < 0) {
        has_neg = true;
      }
    }
    return !(has_pos && has_neg);
  }
  //判断某个顶点是否落在矩形内，1表示矩形内，2表示矩形边缘，0表示矩形外
  int in_polygon(const Pt& pt) const {
    int cross = 0;
    for (int i = 0, n = Size(data); i < n; i++) {
      auto& cur = data[i];
      auto& next = data[(i + 1) % n];
      if (Pt::on_segment(cur, next, pt)) {
        return 2;
      }
      if (Pt::cross_ray(pt, cur, next)) {
        cross++;
      }
    }
    return cross & 1;
  }
  T area_2() const {
    T sum = 0;
    for (int i = 0, n = Size(data); i < n; i++) {
      sum = sum + Pt::cross(data[i], data[(i + 1) % n]);
    }
    return sum.abs();
  }
  T area() const { return area_2() / T(2); }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<typename T::Type>, T>
  lattice_point_number_on_boundary() const {
    T sum = T(0);
    for (int i = 0, n = Size(data); i < n; i++) {
      auto& cur = data[i];
      auto& next = data[(i + 1) % n];
      sum = sum + Pt::lattice_point_number_on_segment(cur, next);
    }
    sum = sum - T(Size(data));
    return sum;
  }
  // pick theorem
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<typename T::Type>, T>
  lattice_point_number_inside() const {
    return (area_2() + T(2) - lattice_point_number_on_boundary()) / T(2);
  }
  template <class X = T>
  enable_if_t<is_same_v<X, T> && is_integral_v<typename T::Type>, T>
  lattice_point_number_inside_or_on_boundary() const {
    return (area_2() + T(2) + lattice_point_number_on_boundary()) / T(2);
  }
  Vec<Line<T>> to_line_polygon() const {
    int n = Size(data);
    Vec<Line<T>> ans(n);
    for(int i = 0; i < n; i++) {
      ans[i] = Line<T>::from_ends(data[i], data[(i + 1) % n]);
    }
    return ans;
  }
  static Self from_line_polygon(const Vec<Line<T>> &lines) {
    int n = Size(lines);
    Assert(n >= 3);
    Vec<Pt> data(n);
    for(int i = 0; i < n; i++) {
      data[i] = Line<T>::intersect(lines[i], lines[(i + 1) % n]);
    }
    return Self(Move(data));
  }
  Vec<Pt> to_vec() const {
    return data;
  }
};
}  // namespace geo2
}  // namespace dalt
namespace dalt {
namespace misc {
template <class T, class C = Less<T>, class I>
void QuickSort(I begin, I end, C comp = C()) {
  Shuffle(begin, end, std::mt19937(rng));
  auto dfs = [&](auto &dfs, auto begin, auto end) -> void {
    if (begin == end) {
      return;
    }
    auto l = begin;
    auto r = end;
    auto i = begin;
    for (++i; i < r; ++i) {
      if (comp(*i, *l)) {
        Swap(*i, *l);
        ++l;
      } else if (comp(*l, *i)) {
        --r;
        Swap(*r, *i);
        --i;
      }
    }
    dfs(dfs, begin, l);
    dfs(dfs, r, end);
  };
  dfs(dfs, begin, end);
}
}  // namespace misc
}  // namespace dalt
namespace dalt {
namespace geo2 {
// O(n\log_2n)
template <class T>
struct ConvexHull : public Polygon<T> {
  ConvexHull(Polygon<T> polygon, bool include_same_line = false,
             bool is_convex = false)
      : Polygon<T>(Move(polygon)) {
    using Pt = typename Polygon<T>::Pt;
    auto& data = Polygon<T>::data;
    if (is_convex) {
      return;
    }
    int n = data.size();
    if (n <= 1) {
      return;
    }
    for (int i = 1; i < n; i++) {
      if (data[i] >= data[0]) {
        continue;
      }
      Swap(data[0], data[i]);
    }
    auto first = data[0];
    SortByPolarAngleAround<T> sorter(first);
    Sort(data.begin() + 1, data.end(), [&](auto& a, auto& b) {
      int sign = sorter.compare(a, b);
      if (sign < 0 || sign == 0 && Pt::dist2(first, a) < Pt::dist2(first, b)) {
        return true;
      }
      return false;
    });
    if (!include_same_line) {
      i32 shrink_size = 2;
      int wpos = 1;
      for (int i = 1; i < n; i++) {
        int l = i;
        int r = i;
        Pt far = data[l];
        while (r + 1 < n && Pt::orient(first, data[l], data[r + 1]) == 0) {
          r++;
          if (Pt::dist2(first, far) < Pt::dist2(first, data[r])) {
            far = data[r];
          }
        }
        data[wpos++] = far;
        i = r;
      }
      data.resize(wpos);
    } else {
      int r = n - 1;
      int l = r;
      while (l - 1 > 0 && Pt::orient(first, data[l], data[l - 1]) == 0) {
        l--;
      }
      Reverse(data.begin() + l, data.begin() + r + 1);
    }
    // Debug(data);
    Deque<Pt> stack;
    stack.push_back(data[0]);
    for (int i = 1; i < n; i++) {
      while (Size(stack) >= 2) {
        auto last = PopBack<Pt>(stack);
        auto& second = stack.back();
        int sign = Pt::cross(second, data[i], last).sign();
        if (sign < 0 || include_same_line && sign == 0) {
          stack.push_back(last);
          break;
        }
      }
      stack.push_back(data[i]);
    }
    data.clear();
    data.insert(data.begin(), All(stack));
  }
};
}  // namespace geo2
}  // namespace dalt
namespace dalt {
template <class T, class I = Nil>
struct CHTLine {
  using Self = CHTLine;
  Nil id;
  T a;
  T b;
  mutable T l;
  mutable T r;
  T apply(T x) const { return a * x + b; }
  bool empty() const { return l >= r; }
  bool operator==(const Self &rhs) const { return l == rhs.l && r == rhs.r; }
  bool operator!=(const Self &rhs) const { return !(*this == rhs); }
};
template <class T, class I>
OStream &operator<<(OStream &os, const CHTLine<T, I> &line) {
  os << line.a << "x + " << line.b;
  return os;
}
template <class T, class I = Nil>
struct ConvexHullTrick {
  static_assert(is_floating_point_v<T> || is_integral_v<T>,
                "only integer and float are supported");
  using L = CHTLine<T, I>;
  struct SortLineByA {
    bool operator()(const L &a, const L &b) const { return a.a < b.a; }
  };
  struct SortLineByLeft {
    bool operator()(const L &a, const L &b) const { return a.l < b.l; }
  };
  using Self = ConvexHullTrick<T, I>;
  using SA = TreeSet<L, SortLineByA>;
  using SL = TreeSet<L, SortLineByLeft>;
  SA sort_by_a;
  SL sort_by_l;
  T constant;
 private:
  static T INF;
  T intersect(const L &x, const L &y) {
    Assert(y.a > x.a);
    return DivCeil(x.b - y.b, y.a - x.a);
  }
  void add(L line) {
    sort_by_a.insert(line);
    sort_by_l.insert(line);
  }
  Vec<L> to_vec_l() { return Vec<L>(sort_by_l.begin(), sort_by_l.end()); }
 public:
  ConvexHullTrick() : constant(0) {}
  // call this method for id only
  const L &best_line(T x) const {
    L q;
    q.l = x;
    auto iter = sort_by_l.lower_bound(q);
    if (iter == sort_by_l.end() || iter->l > x) {
      iter--;
    }
    return *iter;
  }
  // max_i Line[i](x)
  T query(T x) const { return best_line(x).apply(x) + constant; }
  void global_add(T x) { constant = constant + x; }
  void insert(T a, T b, I id = I()) {
    b = b - constant;
    L line{
        .id = id,
        .a = a,
        .b = b,
    };
    auto ceil_a = sort_by_a.lower_bound(line);
    auto ceil_l = ceil_a == sort_by_a.end() ? sort_by_l.end()
                                            : sort_by_l.lower_bound(*ceil_a);
    if (ceil_a != sort_by_a.end() && ceil_a->a == line.a) {
      if (ceil_a->b >= line.b) {
        return;
      }
      ceil_a = sort_by_a.erase(ceil_a);
      ceil_l = sort_by_l.erase(ceil_l);
    }
    while (true) {
      if (ceil_a == sort_by_a.end()) {
        line.r = INF;
        break;
      }
      T r = intersect(line, *ceil_a);
      if (r >= ceil_a->r) {
        ceil_a = sort_by_a.erase(ceil_a);
        ceil_l = sort_by_l.erase(ceil_l);
        continue;
      }
      ceil_l->l = ceil_a->l = Max(ceil_a->l, r);
      line.r = r;
      break;
    }
    while (true) {
      if (ceil_a == sort_by_a.begin()) {
        line.l = -INF;
        break;
      }
      ceil_a--;
      ceil_l--;
      T r = intersect(*ceil_a, line);
      if (r <= ceil_a->l) {
        ceil_a = sort_by_a.erase(ceil_a);
        ceil_l = sort_by_l.erase(ceil_l);
        continue;
      }
      ceil_a->r = ceil_l->r = Min(ceil_a->r, r);
      line.l = r;
      break;
    }
    if (!line.empty()) {
      add(line);
    }
    Assert(to_vec() == to_vec_l());
  }
  Vec<L> to_vec() const {
    auto ans = Vec<L>(sort_by_a.begin(), sort_by_a.end());
    for (auto &l : ans) {
      l.b = l.b + constant;
    }
    return ans;
  }
};
template <class T, class I>
T ConvexHullTrick<T, I>::INF = std::numeric_limits<T>::max() / 2;
}  // namespace dalt
namespace dalt {
namespace graph {
MakeTemplateAttribute(WithFlow, flow);
MakeAttribute(WithReal, bool, real);
template <class T>
struct FlowBaseEdge : BiBaseEdge, WithFlow<T>, WithReal {};
#define IsFlow(E, ret) enable_if_t<is_base_of_v<FlowBaseEdge<typename E::flow_type>, E>, ret>
template <class E>
IsFlow(E, void) PushFlow(Graph<E> &g, E &e, typename E::flow_type flow) {
  e.flow += flow;
  g[e.to][e.rev].flow -= flow;
}
template <class E>
IsFlow(E, void)
    AddFlowEdge(Graph<E> &g, int s, int t, typename E::flow_type flow) {
  if (s == t) {
    return;
  }
  AddBiEdge<E>(g, s, t);
  g[s].back().flow = 0;
  g[s].back().real = true;
  g[t].back().flow = flow;
  g[t].back().real = false;
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace graph {
MakeTemplateAttribute(WithCost, cost);
template <class T>
struct CostFlowBaseEdge : public FlowBaseEdge<T>, public WithCost<T> {};
#define IsCostFlow(E, ret)                                                  \
  enable_if_t<is_base_of_v<CostFlowBaseEdge<typename E::flow_type>, E>, ret>
template <class E>
IsCostFlow(E, void)
    AddCostFlowEdge(Graph<E> &g, int s, int t, typename E::flow_type flow,
                    typename E::cost_type cost) {
  if(s == t) {
      return;
  }
  AddFlowEdge<E>(g, s, t, flow);
  g[s].back().cost = cost;
  g[t].back().cost = -cost;
}
} // namespace graph
} // namespace dalt
namespace dalt {
template <class T, class C>
Indexer<T> MakeIndexer(const C &data) {
  return [&](auto i) -> T { return data[i]; };
}
template <class T, class C>
Indexer<T> MakeReverseIndexer(const C &data) {
  return [&](auto i) -> T { return data[Size(data) - 1 - i]; };
}
template <class T>
Vec<T> ExpandIndexer(int n, const Indexer<T> &indexer) {
  Vec<T> ans;
  ans.reserve(n);
  for (int i = 0; i < n; i++) {
    ans.push_back(indexer(i));
  }
  return ans;
}
Indexer<i32> SelfIndexer() {
  return [](auto i) { return i; };
}
template <class T>
Indexer<T> ConstantIndexer(const T &val) {
  return [=](auto i) { return val; };
}
template <class A, class B>
Mapper<A, B> ConstructorMapper() {
  return [&](auto a) { return B(a); };
}
template <class T>
Adder<T> NaturalAdder() {
  return [](auto a, auto b) { return a + b; };
}
template <class A, class B, class C>
constexpr Adder<A, B, C> EmptyAdder() {
  return [](auto a, auto b) { return C(); };
}
template <class A, class B = A>
constexpr Adder<A, B, A> ReturnLeftAdder() {
  return [](auto a, auto b) { return a; };
}
template <class A, class B = A>
constexpr Adder<A, B, B> ReturnRightAdder() {
  return [](auto a, auto b) { return b; };
}
template <class T>
Indexer<int> BinaryIndexer(const T& val) {
  return [=](int i) {return int((val >> i) & 1);};
}
template <class T>
Indexer<int> ReverseIndexer(int n, Indexer<T> indexer) {
  return [=](int i) {return indexer(n - 1 - i);};
}
}  // namespace dalt
namespace dalt {
// next() -> T
// has_next() -> bool
MakeAnnotation(iter);
template <class I, class F> struct MapperIter {
  static_assert(is_iter_v<I>);
  using Self = MapperIter<I, F>;
  using Type = typename I::Type;
  I &iter;
  Mapper<Type, F> mapper;
  MapperIter(I &_iter, const Mapper<Type, F> &_mapper)
      : iter(_iter), mapper(_mapper) {}
  bool has_next() const { return iter.has_next(); }
  F next() { return mapper(iter.next()); }
  template <class Z> MapperIter<Self, Z> map(const Mapper<F, Z> &f) {
    return MapperIter<Self, Z>(*this, f);
  }
  i32 size() const { return iter.size(); }
  Vec<F> to_vec() {
    Vec<F> res;
    res.reserve(size());
    while (has_next()) {
      res.push_back(next());
    }
    return res;
  }
};
template <class T> struct RangeIter {
  using Self = RangeIter<T>;
  using Type = T;
  T l;
  T r;
  T step;
  RangeIter(T _l, T _r, T _step) : l(_l), r(_r), step(_step) {}
  bool has_next() const { return l <= r; }
  T next() {
    T ans;
    if (step > T(0)) {
      ans = l;
      l = l + step;
    } else {
      ans = r;
      r = r - step;
    }
    return ans;
  }
  i32 size() const {
    if (l > r) {
      return 0;
    }
    T abs_step = Abs(step);
    return (r - l + abs_step) / abs_step;
  }
  Self step_by(T x) const { return Self(l, r, step * x); }
  Self reverse() const { return step_by(T(-1)); }
  template <class F> MapperIter<Self, F> map(const Mapper<T, F> &f) {
    return MapperIter<Self, F>(*this, f);
  }
  Vec<T> to_vec() {
    Vec<T> res;
    res.reserve(size());
    while (has_next()) {
      res.push_back(next());
    }
    return res;
  }
};
template <class T> struct is_iter<RangeIter<T>> {
  static const bool value = true;
};
template <class I, class F> struct is_iter<MapperIter<I, F>> {
  static const bool value = true;
};
template <class T> struct Range {
  T l;
  T r;
  Range(T _l, T _r) : l(_l), r(_r) {}
  T operator[](T index) const { return l + index; }
  RangeIter<T> iter() const { return RangeIter(l, r, T(1)); }
};
} // namespace dalt
namespace dalt {
namespace misc {
MakeAnnotation(factory);
template <class T>
struct Factory {
  Vec<T> data;
  const Indexer<T> &indexer;
  void ensure(int n) {
    if (Size(data) < n) {
      data.reserve(n);
      while (Size(data) < n) {
        data.push_back(indexer(Size(data)));
      }
    }
  }
  T get(int index) {
    ensure(index + 1);
    return data[index];
  }
  Factory(int cap, const Indexer<T> &_indexer) : indexer(_indexer) {
    ensure(cap);
  }
};
template <class T>
struct IndexerFactory {
  const Indexer<T> &indexer;
  IndexerFactory(const Indexer<T> &_indexer) : indexer(_indexer) {}
  void ensure(int n) {}
  T get(int i) { return indexer(i); }
};
template <class T>
struct is_factory<IndexerFactory<T>> {
  static const bool value = true;
};
}  // namespace misc
}  // namespace dalt
namespace dalt {
namespace math {
template <class T>
Vec<T> InverseBatch(Vec<T> batch) {
  int n = int(batch.size());
  Vec<T> origin = batch;
  T fact = 1;
  for (int i = 0; i < n; i++) {
    if (origin[i] == T(0)) {
      continue;
    }
    T val = batch[i];
    batch[i] = fact;
    fact = fact * val;
  }
  T inv_fact = T(1) / fact;
  for (int i = n - 1; i >= 0; i--) {
    if (origin[i] == T(0)) {
      continue;
    }
    batch[i] = batch[i] * inv_fact;
    inv_fact = inv_fact * origin[i];
  }
  return batch;
}
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace poly {
const static int POLY_FAST_MAGIC_THRESHOLD = 64;
MakeAnnotation(polynomial);
template <class Conv>
struct Polynomial {
  static_assert(is_convolution_v<Conv>);
  using T = typename Conv::Type;
  using Type = T;
  using Seq = Vec<T>;
  using Self = Polynomial<Conv>;
  Seq data;
  Polynomial(T v = T(0)): Polynomial(Vec<T>{v}) {}
  Polynomial(Vec<T> _data) : data(Move(_data)) { Normalize(data); }
  T operator()(T x) const { return Apply(data, x); }
  T apply(T x) const { return (*this)(x); }
  Self integral() const {
    let rank = this->rank();
    Vec<T> range(rank + 1);
    for (int i = 0; i <= rank; i++) {
      range[i] = i + 1;
    }
    let inv = math::InverseBatch(move(range));
    Vec<T> ans(rank + 2);
    for (int i = 0; i <= rank; i++) {
      ans[i + 1] = inv[i] * data[i];
    }
    return Self(ans);
  }
  Self differential() const {
    Vec<T> ans(rank());
    for (int i = 1; i <= Size(ans); i++) {
      ans[i - 1] = data[i] * T(i);
    }
    return Self(ans);
  }
  void self_modular(i32 n) {
    if(data.size() >= n) {
      data.resize(n);
      Normalize(data);
    }
  }
  Self modular(i32 n) const { return Self(CopyAndExtend(data, n)); }
  static Self of(T val) { return Self(Vec<T>{val}); }
  Self ln(i32 n) const {
    Assert(data[0] == T(1));
    let diff = differential().modular(n);
    let inv = inverse(n);
    return (diff * inv).integral().modular(n);
  }
  Self exp(i32 n) const {
    if (n == 0) {
      return Self::of(T(0));
    }
    auto dfs = [&](auto &dfs, i32 n) -> Self {
      if (n == 1) {
        return Self::of(T(1));
      }
      let ans = dfs(dfs, (n + 1) / 2);
      let ln = this->modular(n) - ans.ln(n);
      ln.data[0] = ln.data[0] + T(1);
      return (ans * ln).modular(n);
    };
    return dfs(dfs, n);
  }
  int rank() const { return Size(data) - 1; }
  Self operator*(const Self &rhs) const {
    const Self &lhs = *this;
    // if (Min(lhs.rank(), rhs.rank()) < POLY_FAST_MAGIC_THRESHOLD) {
    //   return Self(BruteForceConv<T>::conv(lhs.data, rhs.data));
    // }
    return Self(Conv::conv(lhs.data, rhs.data));
  }
  Self operator*(const T &rhs) const {
    Vec<T> res = data;
    for (int i = 0; i < Size(res); i++) {
      res[i] = res[i] * rhs;
    }
    return Self(res);
  }
  Self &operator*=(const T &rhs) {
    for (int i = 0; i < Size(data); i++) {
      data[i] = data[i] * rhs;
    }
    Normalize(data);
    return *this;
  }
  Self operator+(const T &rhs) const {
    Vec<T> res = data;
    res[0] = res[0] + rhs;
    return Self(res);
  }
  Self operator+=(const T &rhs) const {
    data[0] = data[0] + rhs;
    Normalize(data);
    return data;
  }
  Self operator-(const T &rhs) const {
    Vec<T> res = data;
    res[0] = res[0] - rhs;
    return Self(res);
  }
  Self operator-=(const T &rhs) const {
    data[0] = data[0] - rhs;
    Normalize(data);
    return data;
  }
  Self operator>>(i32 n) const {
    if (n < 0) {
      return *this << -n;
    }
    if (*this == Self::of(T(0))) {
      return Self::of(T(0));
    }
    Vec<T> res(Size(data) + n);
    for (int i = 0; i < Size(data); i++) {
      res[i + n] = data[i];
    }
    return Self(res);
  }
  Self operator<<(i32 n) const {
    if (n < 0) {
      return *this >> -n;
    }
    if (Size(data) < n) {
      return Self::of(T(0));
    }
    Vec<T> res(Size(data) - n);
    for (int i = 0; i < Size(res); i++) {
      res[i] = data[i + n];
    }
    return Self(res);
  }
  Self operator/(const Self &rhs) const {
    auto a = data;
    auto b = rhs.data;
    if (a.size() < b.size()) {
      return Self::of(T(0));
    }
    if (b.size() <= POLY_FAST_MAGIC_THRESHOLD) {
      return BruteForceConv<T>::div_and_rem(Move(a), Move(b))[0];
    }
    Reverse(All(a));
    Reverse(All(b));
    i32 c_rank = Size(a) - Size(b);
    i32 proper_len = 1 << Log2Ceil(c_rank * 2 + 1);
    a.resize(proper_len);
    b.resize(proper_len);
    Vec<T> c = Conv::inverse(move(b), c_rank + 1);
    Vec<T> prod = Conv::conv(move(a), move(c));
    prod.resize(c_rank + 1);
    Reverse(All(prod));
    return Self(prod);
  }
  Self operator%(const Self &rhs) const {
    if (Min(rank(), rhs.rank()) < POLY_FAST_MAGIC_THRESHOLD) {
      return BruteForceConv<T>::div_and_rem(data, rhs.data)[1];
    }
    return *this - (*this / rhs) * rhs;
  }
  Self operator+(const Self &rhs) const {
    const Self &lhs = *this;
    int n = Size(lhs.data);
    int m = Size(rhs.data);
    Vec<T> res(Max(n, m));
    for (int i = 0; i < n; i++) {
      res[i] = lhs.data[i];
    }
    for (int i = 0; i < m; i++) {
      res[i] = res[i] + rhs.data[i];
    }
    return Self(move(res));
  }
  Self operator-(const Self &rhs) const {
    const Self &lhs = *this;
    int n = Size(lhs.data);
    int m = Size(rhs.data);
    Vec<T> res(Max(n, m));
    for (int i = 0; i < n; i++) {
      res[i] = lhs.data[i];
    }
    for (int i = 0; i < m; i++) {
      res[i] = res[i] - rhs.data[i];
    }
    return Self(move(res));
  }
  T operator[](int index) const {
    return index < Size(data) ? data[index] : T(0);
  }
  T get(int index) const {
    if (index < Size(data)) {
      return data[index];
    }
    return T(0);
  }
  bool operator==(const_ref(Self) rhs) const { return data == rhs.data; }
  bool operator!=(const_ref(Self) rhs) const { return !(*this == rhs); }
  Vec<T> to_vec() const { return data; }
  Self inverse(int n) const { return Self(Conv::inverse(data, n)); }
  static Self mulmod(const Self &a, const Self &b, int mod) {
    return (a * b).modular(mod);
  }
  Self powmod_binary_lift(i64 n, i32 mod) const {
    if (n == 0) {
      return Self::of(T(1)).modular(mod);
    }
    Self res = powmod_binary_lift(n / 2, mod);
    res = (res * res).modular(mod);
    if (n % 2 == 1) {
      res = (res * *this).modular(mod);
    }
    return res;
  }
  enable_if_t<is_modint_v<T> && is_same_v<i32, typename T::Type>, Self>
  powmod_fast(i32 n_mod_modulus, i32 n_mod_phi, i64 estimate, i32 mod) const {
    if (estimate == 0) {
      return Self::of(T(1)).modular(mod);
    }
    if (*this == Self::of(T(0))) {
      return *this;
    }
    i32 k = 0;
    while (data[k] == T(0)) {
      k++;
    }
    if (MulLimit<i64>(k, estimate, mod) >= mod) {
      return Self::of(T(0));
    }
    auto expln = [&](const Self &p, i32 n_mod_modulus, i32 mod) -> Self {
      return (p.ln(mod) *= T(n_mod_modulus)).exp(mod);
    };
    auto expln_ext = [&](Self p, i32 n_mod_modulus, i32 n_mod_phi,
                         i32 mod) -> Self {
      T val = p[0];
      T inv = T(1) / p[0];
      p *= inv;
      Self res = expln(p, n_mod_modulus, mod);
      res *= PowBinaryLift(val, n_mod_phi);
      return res;
    };
    if (k == 0) {
      return expln_ext(*this, n_mod_modulus, n_mod_phi, mod);
    }
    Self trim = (*this) << k;
    Self res = expln_ext(Move(trim), n_mod_modulus, n_mod_phi, mod);
    return (res >> k * estimate).modular(mod);
  }
  static Self product(const Vec<Self> &data) {
    if (data.empty()) {
      return Self(Vec<T>{Type(1)});
    }
    auto dfs = [&](auto &dfs, int l, int r) {
      if (l == r) {
        return data[l];
      }
      int m = (l + r) / 2;
      return dfs(dfs, l, m) * dfs(dfs, m + 1, r);
    };
    return dfs(dfs, 0, Size(data) - 1);
  }
  //ret[i] = \sum_{j} this[i + j] * rhs[j]
  Self delta_convolution(const Self& rhs) const {
    Vec<T> lhs = data;
    Reverse(All(lhs));
    auto ans = Conv::conv(lhs, rhs.data);
    ans.resize(Size(lhs));
    Reverse(All(ans));
    return Self(Move(ans));
  }
};
AssignAnnotationTemplate(Polynomial, polynomial, class);
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace poly {
// reference: https://arxiv.org/pdf/1807.11597.pdf
// given |s| polynomial, F_i = x^{s_i}+1
// Find F = F_1 * F_2 * ... * F_|S| % x^{n}
// - constraint: s[i] > 0
// - time: O(|s| + n\log n)
template <class Conv, class T = typename Conv::Type>
Vec<T> CountSetsetSum(const Vec<i32> &s, i32 n) {
  static_assert(is_same_v<typename Conv::Type, T>);
  Vec<T> cnt(n);
  for (auto x : s) {
    if (x < n) {
      cnt[x] = cnt[x] + T(1);
    }
  }
  Vec<T> log(n);
  Vec<T> inv_buf(n);
  auto inv = math::InverseBatch(
      Range<i32>(0, n - 1).iter().map(ConstructorMapper<i32, T>()).to_vec());
  for (i32 i = 1; i < n; i++) {
    for (i32 j = 1, ij; (ij = i * j) <= n; j++) {
      T inv_j = inv[j];
      T contrib = inv_j * cnt[i];
      if ((j & 1) == 0) {
        contrib = T(0) - contrib;
      }
      log[ij] = log[ij] + contrib;
    }
  }
  using Poly = poly::Polynomial<Conv>;
  Poly exp = Poly(log).exp(n);
  auto ans = Move(exp.data);
  ans.resize(n);
  return ans;
}
}  // namespace conv
}  // namespace dalt
namespace dalt {
namespace math {
#define CID -202202141300
template <class T>
struct CRT {
  static_assert(is_integral_v<T>);
  T r, m;
  bool valid;
  CRT() {
    r = T(0);
    m = T(1);
    valid = true;
  }
  bool add(T _r, T _m) {
    if (!valid) {
      return false;
    }
    T m1 = m;
    T x1 = r;
    T m2 = _m;
    T x2 = _r % _m;
    auto gcd_res = ExtGcd(m1, m2);
    T g = gcd_res[2];
    T a = gcd_res[0];
    if ((x2 - x1) % g != 0) {
      return valid = false;
    }
    using MOD = DynamicModular<T, CID>;
    using Mi = ModInt<MOD>;
    m = m1 / g * m2;
    MOD::Register(m, -1);
    r = (Mi(a) * Mi((x2 - x1) / g) * Mi(m1) + Mi(x1)).value;
    return true;
  }
};
template <class T>
OStream& operator<<(OStream& os, const CRT<T>& crt) {
  os << "CRT{ ? % " << crt.m << " = " << crt.r << "}";
}
#undef CID
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Tuple<Vec<bool> COMMA Vec<bool> COMMA Vec<int>>)
    CutVertex(const Graph<E> &g) {
  int n = Size(g);
  Vec<int> depth(n);
  Vec<int> parent(n);
  Vec<bool> visit(n);
  auto dfs_tree = [&](auto &dfs, int root, int p) -> void {
    if (visit[root]) {
      return;
    }
    visit[root] = true;
    parent[root] = p;
    depth[root] = p == -1 ? 0 : depth[p] + 1;
    for (auto &e : g[root]) {
      dfs(dfs, e.to, root);
    }
  };
  for (int i = 0; i < n; i++) {
    dfs_tree(dfs_tree, i, -1);
  }
  visit = Vec<bool>(n);
  Vec<bool> cut(n);
  Vec<bool> be_cut(n);
  auto dfs_cut = [&](auto &dfs, int root) -> int {
    visit[root] = true;
    int min = depth[root];
    for (auto &e : g[root]) {
      if (parent[e.to] == root && !visit[e.to]) {
        int sub = dfs(dfs, e.to);
        if (sub >= depth[root]) {
          cut[root] = true;
          be_cut[e.to] = true;
        }
        min = Min(sub, min);
      } else {
        min = Min(depth[e.to], min);
      }
    }
    return min;
  };
  for (int i = 0; i < n; i++) {
    if (parent[i] != -1) {
      continue;
    }
    dfs_cut(dfs_cut, i);
    cut[i] = false;
    int last_child = -1;
    for (auto &e : g[i]) {
      if (parent[e.to] == i) {
        if (last_child == -1 || last_child == e.to) {
          last_child = e.to;
        } else {
          cut[i] = true;
        }
      }
    }
  }
  return {cut, be_cut, parent};
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
namespace graph {
template <class E>
enable_if_t<is_base_of_v<WithTo, E>, Optional<Deque<int>>>
CycleDetect(const Graph<E> &g) {
  int n = Size(g);
  Deque<int> dq;
  Vec<bool> visited(n);
  Vec<bool> instk(n);
  auto dfs = [&](auto &dfs, int root) -> bool {
    if (visited[root]) {
      if (instk[root]) {
        int front;
        while ((front = dq.front()) != root) {
          instk[front] = false;
          dq.pop_front();
        }
        return true;
      }
      return false;
    }
    visited[root] = instk[root] = true;
    dq.push_back(root);
    for (auto &e : g[root]) {
      if (dfs(dfs, e.to)) {
        return true;
      }
    }
    instk[root] = false;
    Assert(dq.back() == root);
    dq.pop_back();
    return false;
  };
  for (int i = 0; i < n; i++) {
    if (dfs(dfs, i)) {
      return dq;
    }
    Assert(dq.empty());
  }
  return {};
}
} // namespace graph
} // namespace dalt
namespace dalt {
struct DecompsePermutation {
  Vec<Vec<int>> groups;
  Vec<Array<int, 2>> ids;
  DecompsePermutation(Vec<int> perm) {
    int n = Size(perm);
    Vec<bool> visited(n);
    Vec<int> buf(n);
    ids.resize(n);
    auto add = [&](int x) {
      ids[x][0] = Size(groups);
      ids[x][1] = Size(buf);
      buf.push_back(x);
      visited[x] = true;
    };
    for (int i = 0; i < n; i++) {
      if (visited[i]) {
        continue;
      }
      buf.clear();
      int iter = i;
      while (!visited[iter]) {
        add(iter);
        iter = perm[iter];
      }
      groups.push_back(buf);
    }
  }
  Vec<Vec<int>> to_vec() const { return groups; }
  struct PowView {
    u64 k;
    const DecompsePermutation* ptr;
    int operator[](int i) const {
      auto &g = ptr->groups[ptr->ids[i][0]];
      return g[(i + k) % Size(g)];
    }
  };
  PowView pow(u64 k = 0) const {
    return PowView{
        .k = k,
        .ptr = this,
    };
  }
};
}  // namespace dalt
namespace dalt {
// credited to: https://judge.yosupo.jp/submission/63041
struct DominatorTree {
  std::vector<std::basic_string<int>> g, rg, bucket;
  std::basic_string<int> arr, par, rev, sdom, dom, dsu, label;
  int n, t;
  DominatorTree(int n)
      : g(n),
        rg(n),
        bucket(n),
        arr(n, -1),
        par(n, -1),
        rev(n, -1),
        sdom(n, -1),
        dom(n, -1),
        dsu(n, 0),
        label(n, 0),
        n(n),
        t(0) {}
  void add_edge(int u, int v) { g[u] += v; }
  void dfs(int u) {
    arr[u] = t;
    rev[t] = u;
    label[t] = sdom[t] = dsu[t] = t;
    t++;
    for (int w : g[u]) {
      if (arr[w] == -1) {
        dfs(w);
        par[arr[w]] = arr[u];
      }
      rg[arr[w]] += arr[u];
    }
  }
  int find(int u, int x = 0) {
    if (u == dsu[u]) return x ? -1 : u;
    int v = find(dsu[u], x + 1);
    if (v < 0) return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]]) label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
  }
  //ret[i] = father of node i or -1 for root and unreachable nodes
  std::vector<int> run(int root) {
    dfs(root);
    iota(dom.begin(), dom.end(), 0);
    for (int i = t - 1; i >= 0; i--) {
      for (int w : rg[i]) sdom[i] = std::min(sdom[i], sdom[find(w)]);
      if (i) bucket[sdom[i]] += i;
      for (int w : bucket[i]) {
        int v = find(w);
        if (sdom[v] == sdom[w])
          dom[w] = sdom[w];
        else
          dom[w] = v;
      }
      if (i > 1) dsu[i] = par[i];
    }
    for (int i = 1; i < t; i++) {
      if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
    }
    std::vector<int> outside_dom(n, -1);
    for (int i = 1; i < t; i++) outside_dom[rev[i]] = rev[dom[i]];
    return outside_dom;
  }
};
}
namespace dalt {
template <bool COMPRESS = true, class C = Nil, class P = Nil>
struct DSU {
  using Self = DSU<COMPRESS, C, P>;
  Vec<int> fa;
  Vec<int> size;
  Vec<C> sum_of_connected_commponent;
  Vec<P> sum_of_path_to_root;
 public:
  DSU(int n): DSU(Vec<C>(n)) {}
  DSU(Vec<C> weights): sum_of_connected_commponent(move(weights)) {
    int n = int(sum_of_connected_commponent.size());
    sum_of_path_to_root.resize(n);
    size.resize(n);
    fa.resize(n);
    for (int i = 0; i < n; i++) {
      fa[i] = i;
      size[i] = 1;
    }
  }
  IsBool(COMPRESS, int) find(int i) {
    if (fa[fa[i]] == fa[i]) {
      return fa[i];
    }
    int prev_fa = fa[i];
    fa[i] = find(prev_fa);
    sum_of_path_to_root[i] =
        sum_of_path_to_root[i] + sum_of_path_to_root[prev_fa];
    return fa[i];
  }
  IsBool(!COMPRESS, int) find(int i) const {
    while (fa[i] != i) {
      i = fa[i];
    }
    return i;
  }
  Pair<C, int> query_sum(int i) {
    auto root = find(i);
    return MakePair(sum_of_connected_commponent[root], root);
  }
  IsBool(COMPRESS, Pair<P COMMA int>) path_to_root(int i) {
    auto root = find(i);
    return MakePair(sum_of_path_to_root[i], root);
  }
  IsBool(!COMPRESS, Pair<P COMMA int>) path_to_root(int i) const {
    P sum = P();
    while (fa[i] != i) {
      sum = sum + sum_of_path_to_root[i];
      i = fa[i];
    }
    return MakePair(sum, i);
  }
  // a - b = delta
  // a - ra = x
  // b - rb = y
  // ra - rb = (a - x) - (b - y)
  void merge(int a, int b, P delta = P()) {
    auto pa = path_to_root(a);
    auto pb = path_to_root(b);
    delta = delta + pb.first - pa.first;
    a = pa.second;
    b = pb.second;
    if (a == b) {
      return;
    }
    if (size[a] < size[b]) {
      Swap(a, b);
    } else {
      delta = P() - delta;
    }
    sum_of_connected_commponent[a] =
        sum_of_connected_commponent[a] + sum_of_connected_commponent[b];
    size[a] = size[a] + size[b];
    fa[b] = a;
    sum_of_path_to_root[b] = delta;
  }
  Vec<i32> to_vec() {
    Vec<i32> res;
    int n = Size(fa);
    res.reserve(n);
    for (int i = 0; i < n; i++) {
      int root = fa[i];
      while (fa[root] != root) {
        root = fa[root];
      }
      res.push_back(root);
    }
    return res;
  }
};
}  // namespace dalt
namespace dalt {
namespace math {
  //for i <= k, ret[i] = {n \choose i}
  template<class C>
  enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>> 
  EnumerateCombination(i64 n, int k) {
    //[x^i](1+x)^n = {n\choose i}
    using P = poly::Polynomial<C>;
    using T = typename C::Type;
    auto modulus = C::modulus;
    auto phi = C::phi;
    auto res = P(Vec<T>{1, 1}).powmod_fast(n % modulus, n % phi, n, k + 1);
    auto vec = Move(res.data);
    vec.resize(k + 1);
    return vec;
  }
}
}  // namespace dalt
namespace dalt {
// Find all primes in [2, n] and consume them.
// The time complexity is O(n log log n) and the space complexity is O(sqrt(n))
void EratosthenesSieve(int n, const Consumer<int> &consumer) {
  if (n <= 1) {
    return;
  }
  int block = std::round(std::sqrt(n));
  Vec<bool> is_comp(block + 1);
  Vec<int> primes(block + 1);
  int prime_cnt = 0;
  for (int i = 2; i <= block; i++) {
    if (is_comp[i]) {
      continue;
    }
    primes[prime_cnt++] = i;
    for (int j = i + i; j <= block; j += i) {
      is_comp[j] = true;
    }
  }
  for (int i = 0; i < prime_cnt; i++) {
    int p = primes[i];
    consumer(p);
  }
  for (int l = block + 1; l <= n; l += block) {
    int r = Min(l + block - 1, n);
    Fill(All(is_comp), false);
    for (int i = 0; i < prime_cnt; i++) {
      int p = primes[i];
      if (r < p * p) {
        break;
      }
      int top = Max(0, l - p * p);
      int bot = p;
      for (int j = (top + bot - 1) / bot * p + p * p; j <= r; j += p) {
        is_comp[j - l] = true;
      }
    }
    for (int j = l; j <= r; j++) {
      if (!is_comp[j - l]) {
        consumer(j);
      }
    }
  }
}
} // namespace dalt
namespace dalt {
namespace math {
i64 EuclidLikeFloorAffineSum1(i64 n, i64 a, i64 b, i64 c);
i64 EuclidLikeFloorAffineSum1(i64 l, i64 r, i64 a, i64 b, i64 c);
i64 EuclidLikeFloorAffineSum2(i64 n, i64 a, i64 b, i64 c);
i64 EuclidLikeFloorAffineSquareSum(i64 n, i64 a, i64 b, i64 c);
i64 MinimumResidueOfLinearFunction(i64 a, i64 b, i64 m, i64 k);
 // c > 0
 // \sum_{i=0}^n \floor((ai+b)/c)
 // O(\log_2a+\log_2c)
i64 EuclidLikeFloorAffineSum1(i64 n, i64 a, i64 b, i64 c) {
  Assert(n >= 0);
  if (a == 0) {
    return (n + 1) * (b / c);
  }
  if (a >= c || b >= c) {
    return n * (n + 1) / 2 * (a / c) + (n + 1) * (b / c) +
           EuclidLikeFloorAffineSum1(n, a % c, b % c, c);
  }
  i64 m = (a * n + b) / c;
  if (m == 0) {
    return 0;
  }
  return n * m - EuclidLikeFloorAffineSum1(m - 1, c, c - b - 1, a);
}
i64 EuclidLikeFloorAffineSum1(i64 l, i64 r, i64 a, i64 b, i64 c) {
  if (l > r) {
    return 0;
  }
  i64 ans = EuclidLikeFloorAffineSum1(r, a, b, c);
  if (l > 0) {
    ans -= EuclidLikeFloorAffineSum1(l - 1, a, b, c);
  }
  return ans;
}
// \sum_{i=0}^n \floor((ai+b)/c) i
i64 EuclidLikeFloorAffineSum2(i64 n, i64 a, i64 b, i64 c) {
  Assert(n >= 0);
  if (a == 0) {
    return SumOfInterval<i64>(0, n) * (b / c);
  }
  if (n == 0) {
    return 0;
  }
  if (a >= c || b >= c) {
    return EuclidLikeFloorAffineSum2(n, a % c, b % c, c) +
           n * (n + 1) * (2 * n + 1) / 6 * (a / c) + n * (n + 1) / 2 * (b / c);
  }
  i64 m = (a * n + b) / c;
  if (m == 0) {
    return 0;
  }
  i64 ans = m * n * (n + 1) -
            EuclidLikeFloorAffineSum1(m - 1, c, -b + c - 1, a) -
            EuclidLikeFloorAffineSquareSum(m - 1, c, -b + c - 1, a);
  return ans / 2;
}
 // \sum_{i=0}^n \floor((ai+b)/c)^2
 // formula from https://blog.csdn.net/dreaming__ldx/article/details/86768953?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.control&dist_request_id=9f6059c1-08e6-4621-bac5-389e05276d86&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.control
i64 EuclidLikeFloorAffineSquareSum(i64 n, i64 a, i64 b, i64 c) {
  Assert(n >= 0);
  if (a == 0 || n == 0) {
    return (b / c) * (b / c) * (n + 1);
  }
  if (a >= c || b >= c) {
    return EuclidLikeFloorAffineSquareSum(n, a % c, b % c, c) +
           n * (n + 1) * (2 * n + 1) / 6 * Pow2(a / c) + (n + 1) * Pow2(b / c) +
           2 * (b / c) * EuclidLikeFloorAffineSum1(n, a % c, b % c, c) +
           2 * (a / c) * EuclidLikeFloorAffineSum2(n, a % c, b % c, c) +
           (a / c) * (b / c) * n * (n + 1);
  }
  i64 m = (a * n + b) / c;
  if (m == 0) {
    return 0;
  }
  return m * (m + 1) * n -
         2 * EuclidLikeFloorAffineSum2(m - 1, c, -b + c - 1, a) -
         2 * EuclidLikeFloorAffineSum1(m - 1, c, -b + c - 1, a) -
         EuclidLikeFloorAffineSum1(n, a, b, c);
}
/**
 * Find minimum non-negative x that L <= ax + b % m <= R
 * <p>
 * O(\log_2m)
 * <p>
 * https://codeforces.com/blog/entry/90690
 * <p>
 * The code only support 32bit integer, even though the parameter is i64
 * type
 * </p>
 *
 * @return -1 for no satisfied answer
 */
i64 FirstOccurResidue(i64 a, i64 b, i64 m, i64 L, i64 R) {
  L = Max<i64>(0, L);
  R = Min(m - 1, R);
  a = Modular(a, m);
  b = Modular(b, m);
  auto dfs = [&](auto& dfs, i64 a, i64 b, i64 m, i64 L, i64 R) -> i64 {
    if (L > R) {
      return -1;
    }
    i64 EuclidLikeFloorAffineSum2 = Gcd(a, m);
    if (EuclidLikeFloorAffineSum2 > 1) {
      return dfs(
          dfs, a / EuclidLikeFloorAffineSum2, b / EuclidLikeFloorAffineSum2,
          m / EuclidLikeFloorAffineSum2,
          DivCeil(L - b % EuclidLikeFloorAffineSum2, EuclidLikeFloorAffineSum2),
          DivFloor(R - b % EuclidLikeFloorAffineSum2,
                   EuclidLikeFloorAffineSum2));
    }
    i64 ia = PossibleModInverse(a, m);
    return MinimumResidueOfLinearFunction(ia, (L - b) * ia, m, R - L);
  };
  return dfs(dfs, a, b, m, L, R);
}
 // Find minimum value for ax+b % p where 0<=x<=k
 // O(\log_2m)
 // credited to: https://codeforces.com/blog/entry/90690
 // The code only support 32bit integer, even though the parameter is i64
i64 MinimumResidueOfLinearFunction(i64 a, i64 b, i64 m, i64 k) {
  Assert(k >= 0);
  auto stepRequire = [&](i64 ia, i64 b0, i64 m0, i64 val) {
    i64 res = ia * (val - b0) % m0;
    if (res < 0) {
      res += m0;
    }
    return res;
  };
  auto dfs = [&](auto& dfs, i64 a0, i64 b0, i64 m0, i64 k) -> i64 {
    i64 EuclidLikeFloorAffineSum2 = Gcd(a0, m0);
    if (EuclidLikeFloorAffineSum2 > 1) {
      return dfs(dfs, a0 / EuclidLikeFloorAffineSum2,
                 b0 / EuclidLikeFloorAffineSum2, m0 / EuclidLikeFloorAffineSum2,
                 k) *
                 EuclidLikeFloorAffineSum2 +
             b0 % EuclidLikeFloorAffineSum2;
    }
    i64 ia0 = PossibleModInverse(a0, m0);
    i64 b = b0;
    i64 a = a0;
    i64 m = m0;
    for (i64 s; a != 0; b = s) {
      if (a * 2 <= m) {
        s = b < a ? b : Modular(b - m, a);
        if (stepRequire(ia0, b0, m0, s) > k) {
          return b;
        }
        i64 tmp = m;
        m = a;
        a = Modular(-tmp, m);
      } else {
        i64 ma = m - a;
        s = b % ma;
        if (stepRequire(ia0, b0, m0, s) > k) {
          i64 lo = 0;
          i64 hi = b / ma - 1;
          while (lo < hi) {
            i64 mid = (lo + hi + 1) / 2;
            if (stepRequire(ia0, b0, m0, b - ma * mid) > k) {
              hi = mid - 1;
            } else {
              lo = mid;
            }
          }
          return b - ma * lo;
        }
        m = ma;
        a %= ma;
      }
    }
    return b;
  };
  return dfs(dfs, Modular(a, m), Modular(b, m), m, Min(k, m));
}
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace geo2 {
template <class T, class C>
//- time: O(Size(ch))
enable_if_t<is_base_of_v<ConvexHull<T>, C>, Pair<Point<T>, Point<T>>>
TheFarthestPoingPair(const C& ch) {
  using Pt = Point<T>;
  using F = typename T::FType;
  int n = Size(ch);
  if (n <= 2) {
    return {ch[0], ch[1 % n]};
  }
  Pt x = ch[0];
  Pt y = ch[1];
  for (int i = 0, j = 0; i < n; i++) {
    while (Pt::dist2(ch[i], ch[j % n]) < Pt::dist2(ch[i], ch[(j + 1) % n])) {
      j++;
    }
    if (Pt::dist2(x, y) < Pt::dist2(ch[i], ch[j % n])) {
      x = ch[i];
      y = ch[j % n];
    }
  }
  return {x, y};
}
}  // namespace geo2
}  // namespace dalt
namespace dalt {
namespace math {
template <class T>
struct FastPower2 {
  Vec<T> high;
  Vec<T> low;
  i32 mask;
  i32 shift;
  FastPower(const T& x, int n, const T& one = T(1)) {
    mask = 1;
    shift = 0;
    // n / mask <= mask
    // n <= mask * mask
    while (mask * mask < n) {
      mask *= 2;
      shift++;
    }
    high.resize(mask);
    low.resize(mask);
    mask--;
    low[0] = one;
    for (int i = 1; i <= mask; i++) {
      low[i] = low[i - 1] * x;
    }
    T y = low.back() * x;
    for (int i = 1; i <= mask; i++) {
      high[i] = high[i - 1] * y;
    }
  }
  T pow(int exp) const { return high[exp >> shift] * low[exp & mask]; }
};
}  // namespace math
}  // namespace dalt
namespace dalt {
template <class T>
struct FenwickTree2 {
 private:
  Vec<Vec<T>> data;
  int n;
  int m;
 public:
  // 创建大小A[1...n][1..,m]
  // O(nm)
  FenwickTree2(int _n, int _m) : n(_n), m(_m) {
    data = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
  }
  // O(nm)
  FenwickTree2(int _n, int _m, const Indexer2<T>& indexer)
      : FenwickTree2(_n, _m) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        data[i][j] = indexer(i - 1, j - 1);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int ni = i + (i & -i);
        int nj = j + (j & -j);
        if (ni <= n) {
          data[ni][j] = data[ni][j] + data[i][j];
        }
        if (nj <= m) {
          data[i][nj] = data[i][nj] + data[i][j];
        }
        if (ni <= n && nj <= m) {
          data[ni][nj] = data[ni][nj] - data[i][j];
        }
      }
    }
  }
  // 查询左上角为(1,1)，右下角为(x,y)的矩形和
  // O(\log n \log m)
  T query(int x, int y) const {
    x++;
    y++;
    T sum = T();
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        sum = sum + data[i][j];
      }
    }
    return sum;
  }
  // 查询左上角为(b,l)，右下角为(t,r)的矩形和
  // O(\log n \log m)
  T query(int b, int t, int l, int r) const {
    return query(t, r) - query(b - 1, r) - query(t, l - 1) +
           query(b - 1, l - 1);
  }
  // 将A[x][y] 更新为A[x][y]+mod
  // O(\log n \log m)
  void update(int x, int y, T mod) {
    x++;
    y++;
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        data[i][j] = data[i][j] + mod;
      }
    }
  }
  // 将A[x][y] 更新为mod
  // O(\log n \log m)
  void set(int r, int c, T mod) { update(r, c, mod - query(r, r, c, c)); }
  Vec<Vec<T>> to_vec() const {
    Vec<Vec<T>> res(n, Vec<T>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = query(i, i, j, j);
      }
    }
    return res;
  }
};
}  // namespace dalt
namespace dalt {
template <class T>
struct FenwickTree2Ext {
 private:
  Vec<Vec<T>> delta;
  Vec<Vec<T>> idelta;
  Vec<Vec<T>> jdelta;
  Vec<Vec<T>> ijdelta;
  int n;
  int m;
  void update(int x, int y, T mod) {
    x++;
    y++;
    T x1 = mod;
    T x2 = mod * x;
    T x3 = mod * y;
    T x4 = mod * x * y;
    for (int i = x; i <= n; i += i & -i) {
      for (int j = y; j <= m; j += j & -j) {
        delta[i][j] = delta[i][j] + x1;
        idelta[i][j] = idelta[i][j] + x2;
        jdelta[i][j] = jdelta[i][j] + x3;
        ijdelta[i][j] = ijdelta[i][j] + x4;
      }
    }
  }
 public:
 //O(nm)
  FenwickTree2Ext(int _n, int _m) : n(_n), m(_m) {
    delta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    idelta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    jdelta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    ijdelta = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
  }
  // O(nm)
  FenwickTree2Ext(int _n, int _m, const Indexer2<T>& indexer)
      : FenwickTree2Ext(_n, _m) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        delta[i][j] = indexer(i - 1, j - 1);
      }
    }
    for (int i = n; i > 0; i--) {
      for (int j = n; j > 0; j--) {
        delta[i][j] = delta[i][j] - delta[i - 1][j] - delta[i][j - 1] +
                      delta[i - 1][j - 1];
        idelta[i][j] = i * delta[i][j];
        jdelta[i][j] = j * delta[i][j];
        ijdelta[i][j] = j * idelta[i][j];
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int ni = i + (i & -i);
        int nj = j + (j & -j);
        if (ni <= n) {
          delta[ni][j] = delta[ni][j] + delta[i][j];
          idelta[ni][j] = idelta[ni][j] + idelta[i][j];
          jdelta[ni][j] = jdelta[ni][j] + jdelta[i][j];
          ijdelta[ni][j] = ijdelta[ni][j] + ijdelta[i][j];
        }
        if (nj <= m) {
          delta[i][nj] = delta[i][nj] + delta[i][j];
          idelta[i][nj] = idelta[i][nj] + idelta[i][j];
          jdelta[i][nj] = jdelta[i][nj] + jdelta[i][j];
          ijdelta[i][nj] = ijdelta[i][nj] + ijdelta[i][j];
        }
        if (ni <= n && nj <= m) {
          delta[ni][nj] = delta[ni][nj] - delta[i][j];
          idelta[ni][nj] = idelta[ni][nj] - idelta[i][j];
          jdelta[ni][nj] = jdelta[ni][nj] - jdelta[i][j];
          ijdelta[ni][nj] = ijdelta[ni][nj] - ijdelta[i][j];
        }
      }
    }
  }
  // O(\log n \log m)
  void update(int b, int t, int l, int r, T mod) {
    update(b, l, mod);
    update(t + 1, l, -mod);
    update(b, r + 1, -mod);
    update(t + 1, r + 1, mod);
  }
  // O(\log n \log m)
  T query(int x, int y) const {
    x++;
    y++;
    T ans1 = 0;
    T ans2 = 0;
    T ans3 = 0;
    T ans4 = 0;
    for (int i = x; i > 0; i -= i & -i) {
      for (int j = y; j > 0; j -= j & -j) {
        ans1 = ans1 + delta[i][j];
        ans2 = ans2 + idelta[i][j];
        ans3 = ans3 + jdelta[i][j];
        ans4 = ans4 + ijdelta[i][j];
      }
    }
    return ans1 * (x + 1) * (y + 1) - ans2 * (y + 1) - ans3 * (x + 1) + ans4;
  }
  // O(\log n \log m)
  T query(int b, int t, int l, int r) const {
    T ans = query(t, r);
    if (b > 0) {
      ans = ans - query(b - 1, r);
    }
    if (l > 0) {
      ans = ans - query(t, l - 1);
    }
    if (b > 0 && l > 0) {
      ans = ans + query(b - 1, l - 1);
    }
    return ans;
  }
  Vec<Vec<T>> to_vec() const {
    Vec<Vec<T>> res(n, Vec<T>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = query(i, i, j, j);
      }
    }
    return res;
  }
};
}  // namespace dalt
namespace dalt {
template <class T>
struct FenwickTreeExt {
 private:
  Vec<T> delta;
  Vec<T> idelta;
  int n;
  void update(int i, T x) {
    i++;
    T x1 = x;
    T x2 = x * i;
    for (; i <= n; i += i & -i) {
      delta[i] = delta[i] + x1;
      idelta[i] = idelta[i] + x2;
    }
  }
 public:
  FenwickTreeExt(int _n) : n(_n) {
    delta = Vec<T>(n + 1);
    idelta = Vec<T>(n + 1);
  }
  FenwickTreeExt(int _n, const Indexer<T>& indexer) : FenwickTreeExt(_n) {
    for (int i = 1; i <= n; i++) {
      delta[i] = indexer(i - 1);
    }
    for (int i = n; i > 0; i--) {
      delta[i] = delta[i] - delta[i - 1];
      idelta[i] = delta[i] * i;
    }
    for (int i = 1; i <= n; i++) {
      int to = i + (i & -i);
      if (to <= n) {
        delta[to] = delta[to] + delta[i];
        idelta[to] = idelta[to] + idelta[i];
      }
    }
  }
  void update(int l, int r, T x) {
    update(l, x);
    update(r + 1, -x);
  }
  // prefix sum
  T query(int x) const {
    x++;
    T ans1 = 0;
    T ans2 = 0;
    for (int i = x; i > 0; i -= (i & -i)) {
      ans1 = ans1 + delta[i];
      ans2 = ans2 + idelta[i];
    }
    return (x + 1) * ans1 - ans2;
  }
  T query(int l, int r) const { return query(r) - query(l - 1); }
  Vec<T> to_vec() const {
    Vec<T> res(n);
    for (int i = 0; i < n; i++) {
      res[i] = query(i, i);
    }
    return res;
  }
};
}  // namespace dalt
namespace dalt {
namespace poly {
template <class F>
enable_if_t<is_floating_point_v<F>> fft(Vec<Complex<F>> &p, bool inv) {
  static const F PI = std::asin((long double)1) * 2;
  using cpx = Complex<F>;
  static Vec<Vec<cpx>> multi_levels(30);
  int m = Log2Ceil(Size(p));
  int n = 1 << m;
  Assert((1 << m) == Size(p));
  int shift = 32 - TrailingZeroNumber(n);
  for (int i = 1; i < n; i++) {
    int j = ReverseBit(i << shift);
    if (i < j) {
      Swap(p[i], p[j]);
    }
  }
  for (int d = 0; d < m; d++) {
    int s = 1 << d;
    int s2 = s << 1;
    auto &level = multi_levels[d];
    if (level.empty()) {
      // init
      level.resize(1 << d);
      for (int j = 0, s = 1 << d; j < s; j++) {
        level[j] =
            cpx(Cos(F(PI) / s * j), Sin(F(PI) / s * j));
      }
    }
    for (int i = 0; i < n; i += s2) {
      for (int j = 0; j < s; j++) {
        auto a = i + j;
        auto b = a + s;
        auto t = level[j] * p[b];
        p[b] = p[a] - t;
        p[a] = p[a] + t;
      }
    }
  }
  if (inv) {
    int i = 0;
    int j = 0;
    F tn = n;
    while (i <= j) {
      auto pj = p[j];
      p[j] = p[i] / tn;
      if (i != j) {
        p[i] = pj / tn;
      }
      i += 1;
      j = n - i;
    }
  }
}
template <class M, class F = f80>
struct FFTConv {
  static_assert(is_modint_v<M>);
  using cpx = Complex<F>;
  using mi = M;
  using Type = mi;
  static_assert(is_same_v<i32, typename M::Type>);
  static Vec<mi> conv(const Vec<mi> &a, const Vec<mi> &b) {
    if(Size(a) <= 20 || Size(b) <= 20) {
      return BruteForceConv<M>::conv(a, b);
    }
    if (&a == &b) {
      return conv2(a);
    }
    return conv(a, Size(a), b, Size(b));
  }
  static Vec<mi> conv(const Vec<mi> &a, int na, const Vec<mi> &b, int nb) {
      let rank_a = na - 1;
      let rank_b = nb - 1;
      i32 step = 15;
      i32 mask = (1 << step) - 1;
      let n = 1 << Log2Ceil(rank_a + rank_b + 1);
      Vec<cpx> a_cpx(n);
      Vec<cpx> b_cpx(n);
      for (int i = 0; i < Size(a); i++) {
        let x = a[i].value;
        a_cpx[i] = cpx(x & mask, x >> step);
      }
      for (int i = 0; i < Size(b); i++) {
        let x = b[i].value;
        b_cpx[i] = cpx(x & mask, x >> step);
      }
      fft(a_cpx, false);
      fft(b_cpx, false);
      i32 i = 0;
      i32 j = 0;
      while (i <= j) {
        let ari = a_cpx[i].real();
        let aii = a_cpx[i].imag();
        let bri = b_cpx[i].real();
        let bii = b_cpx[i].imag();
        let arj = a_cpx[j].real();
        let aij = a_cpx[j].imag();
        let brj = b_cpx[j].real();
        let bij = b_cpx[j].imag();
        let a1r = (ari + arj) / 2;
        let a1i = (aii - aij) / 2;
        let a2r = (aii + aij) / 2;
        let a2i = (arj - ari) / 2;
        let b1r = (bri + brj) / 2;
        let b1i = (bii - bij) / 2;
        let b2r = (bii + bij) / 2;
        let b2i = (brj - bri) / 2;
        a_cpx[i] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                       a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
        b_cpx[i] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                       a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);
        if (i != j) {
          let a1r = (arj + ari) / 2;
          let a1i = (aij - aii) / 2;
          let a2r = (aij + aii) / 2;
          let a2i = (ari - arj) / 2;
          let b1r = (brj + bri) / 2;
          let b1i = (bij - bii) / 2;
          let b2r = (bij + bii) / 2;
          let b2i = (bri - brj) / 2;
          a_cpx[j] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                         a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
          b_cpx[j] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                         a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);
        }
        i += 1;
        j = n - i;
      }
      fft(a_cpx, true);
      fft(b_cpx, true);
      i64 modulus = M::modulus();
      Vec<mi> ans(n);
      for (int i = 0; i < n; i++) {
        i64 aa = Round(a_cpx[i].real());
        i64 bb = Round(b_cpx[i].real());
        i64 cc = Round(a_cpx[i].imag());
        ans[i] = (aa + (bb % modulus << 15) + (cc % modulus << 30)) % modulus;
      }
      return ans;
  }
  static Vec<mi> conv2(const Vec<mi> &p) {
    int na, nb;
    na = nb = Size(p);
    let rank_a = na - 1;
    let rank_b = nb - 1;
    i32 step = 15;
    i32 mask = (1 << step) - 1;
    let n = 1 << Log2Ceil(rank_a + rank_b + 1);
    Vec<cpx> a_cpx(n);
    for (int i = 0; i < na; i++) {
      let x = p[i].value;
      a_cpx[i] = cpx(x & mask, x >> step);
    }
    fft(a_cpx, false);
    auto b_cpx = a_cpx;
    i32 i = 0;
    i32 j = 0;
    while (i <= j) {
      let ari = a_cpx[i].real();
      let aii = a_cpx[i].imag();
      let bri = b_cpx[i].real();
      let bii = b_cpx[i].imag();
      let arj = a_cpx[j].real();
      let aij = a_cpx[j].imag();
      let brj = b_cpx[j].real();
      let bij = b_cpx[j].imag();
      let a1r = (ari + arj) / 2;
      let a1i = (aii - aij) / 2;
      let a2r = (aii + aij) / 2;
      let a2i = (arj - ari) / 2;
      let b1r = (bri + brj) / 2;
      let b1i = (bii - bij) / 2;
      let b2r = (bii + bij) / 2;
      let b2i = (brj - bri) / 2;
      a_cpx[i] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                     a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
      b_cpx[i] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                     a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);
      if (i != j) {
        let a1r = (arj + ari) / 2;
        let a1i = (aij - aii) / 2;
        let a2r = (aij + aii) / 2;
        let a2i = (ari - arj) / 2;
        let b1r = (brj + bri) / 2;
        let b1i = (bij - bii) / 2;
        let b2r = (bij + bii) / 2;
        let b2i = (bri - brj) / 2;
        a_cpx[j] = cpx(a1r * b1r - a1i * b1i - a2r * b2i - a2i * b2r,
                       a1r * b1i + a1i * b1r + a2r * b2r - a2i * b2i);
        b_cpx[j] = cpx(a1r * b2r - a1i * b2i + a2r * b1r - a2i * b1i,
                       a1r * b2i + a1i * b2r + a2r * b1i + a2i * b1r);
      }
      i += 1;
      j = n - i;
    }
    fft(a_cpx, true);
    fft(b_cpx, true);
    i64 modulus = M::modulus();
    Vec<mi> ans(n);
    for (int i = 0; i < n; i++) {
      i64 aa = Round(a_cpx[i].real());
      i64 bb = Round(b_cpx[i].real());
      i64 cc = Round(a_cpx[i].imag());
      ans[i] = (aa + (bb % modulus << 15) + (cc % modulus << 30)) % modulus;
    }
    return ans;
  }
  static Vec<mi> inverse(Vec<mi> p, i32 n) {
    Extend(p, n);
    auto dfs = [&](auto &dfs, i32 m) -> Vec<mi> {
      if (m == 1) {
        return Vec<mi>{mi(1) / p[0]};
      }
      i32 prev_mod = (m + 1) / 2;
      auto C = dfs(dfs, prev_mod);
      auto AC = conv(p, m, C, prev_mod);
      AC.resize(m);
      for (int i = 0; i < m; i++) {
        AC[i] = mi(0) - AC[i];
      }
      AC[0] = AC[0] + mi(2);
      auto res = conv(C, AC);
      res.resize(m);
      return res;
    };
    auto ans = dfs(dfs, n);
    ans.resize(n);
    return ans;
  }
};
template <class F, class M>
struct is_convolution<FFTConv<F, M>> {
  static const bool value = true;
};
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace graph {
// credited to: https://judge.yosupo.jp/submission/61234
template <class E>
IsBiGraph(E, Vec<i32>) GeneralGraphMatchByBlossom(const Graph<E> &graph) {
  int n = Size(graph), timer = -1;
  Vec<i32> mate(n, -1), label(n), parent(n), orig(n), aux(n, -1), q;
  auto lca = [&](int x, int y) {
    for (timer++;; Swap(x, y)) {
      if (x == -1)
        continue;
      if (aux[x] == timer)
        return x;
      aux[x] = timer;
      x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
    }
  };
  auto blossom = [&](int v, int w, int a) {
    while (orig[v] != a) {
      parent[v] = w;
      w = mate[v];
      if (label[w] == 1)
        label[w] = 0, q.push_back(w);
      orig[v] = orig[w] = a;
      v = parent[w];
    }
  };
  auto augment = [&](int v) {
    while (v != -1) {
      int pv = parent[v], nv = mate[pv];
      mate[v] = pv;
      mate[pv] = v;
      v = nv;
    }
  };
  auto bfs = [&](int root) {
    Fill(All(label), -1);
    std::iota(All(orig), 0);
    q.clear();
    label[root] = 0;
    q.push_back(root);
    for (int i = 0; i < (int)q.size(); ++i) {
      int v = q[i];
      for (auto &e : graph[v]) {
        int x = e.to;
        if (label[x] == -1) {
          label[x] = 1;
          parent[x] = v;
          if (mate[x] == -1)
            return augment(x), 1;
          label[mate[x]] = 0;
          q.push_back(mate[x]);
        } else if (label[x] == 0 && orig[v] != orig[x]) {
          int a = lca(orig[v], orig[x]);
          blossom(x, v, a);
          blossom(v, x, a);
        }
      }
    }
    return 0;
  };
  // Time halves if you start with (any) maximal matching.
  for (int i = 0; i < n; i++)
    if (mate[i] == -1)
      bfs(i);
  return mate;
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace graph {
// credited to: https://judge.yosupo.jp/submission/54445
// maximize weight, not necessary maximize cardinality
template <class T> struct GeneralWeightedMaxMatch {
private:
  struct Edge {
    int v, w;
    T weight;
    Edge() : v(0), w(0), weight(T()) {}
  };
  int V, VX, cardinality, curStamp;
  T INF, total_weight;
  Vec<int> mate, match, slack, st, par, S, stamp;
  Vec<T> lab;
  Vec<Vec<int>> flo, floFrom;
  Vec<Vec<Edge>> G;
  Queue<int> q;
  T eDelta(const Edge &e) {
    return lab[e.v] + lab[e.w] - G[e.v][e.w].weight * T(2);
  }
  void updateSlack(int v, int x) {
    if (!slack[x] || eDelta(G[v][x]) < eDelta(G[slack[x]][x]))
      slack[x] = v;
  }
  void setSlack(int x) {
    slack[x] = 0;
    for (int v = 1; v <= V; v++)
      if (G[v][x].weight > T() && st[v] != x && S[st[v]] == 0)
        updateSlack(v, x);
  }
  void qPush(int x) {
    if (x <= V)
      q.push(x);
    else
      for (int t : flo[x])
        qPush(t);
  }
  void setSt(int x, int b) {
    st[x] = b;
    if (x > V)
      for (int t : flo[x])
        setSt(t, b);
  }
  int getPr(int b, int xr) {
    int pr = find(flo[b].begin(), flo[b].end(), xr) - flo[b].begin();
    if (pr % 2) {
      reverse(flo[b].begin() + 1, flo[b].end());
      return int(flo[b].size()) - pr;
    }
    return pr;
  }
  void setMatch(int v, int w) {
    Edge &e = G[v][w];
    match[v] = e.w;
    if (v <= V)
      return;
    int xr = floFrom[v][e.v], pr = getPr(v, xr);
    for (int i = 0; i < pr; i++)
      setMatch(flo[v][i], flo[v][i ^ 1]);
    setMatch(xr, w);
    rotate(flo[v].begin(), flo[v].begin() + pr, flo[v].end());
  }
  void augment(int v, int w) {
    while (true) {
      int xnw = st[match[v]];
      setMatch(v, w);
      if (!xnw)
        return;
      setMatch(xnw, v = st[par[w = xnw]]);
    }
  }
  int lca(int v, int w) {
    for (curStamp++; v || w; Swap(v, w)) {
      if (!v)
        continue;
      if (stamp[v] == curStamp)
        return v;
      stamp[v] = curStamp;
      v = st[match[v]];
      if (v)
        v = st[par[v]];
    }
    return 0;
  }
  void addBlossom(int v, int anc, int w) {
    int b = V + 1;
    while (b <= VX && st[b])
      b++;
    if (b > VX)
      VX++;
    lab[b] = T();
    S[b] = 0;
    match[b] = match[anc];
    flo[b] = Vec<int>{anc};
    auto blossom = [&](int x) {
      for (int y; x != anc; x = st[par[y]]) {
        flo[b].push_back(x);
        flo[b].push_back(y = st[match[x]]);
        qPush(y);
      }
    };
    blossom(v);
    reverse(flo[b].begin() + 1, flo[b].end());
    blossom(w);
    setSt(b, b);
    for (int x = 1; x <= VX; x++)
      G[b][x].weight = G[x][b].weight = T();
    for (int x = 1; x <= V; x++)
      floFrom[b][x] = 0;
    for (int xs : flo[b]) {
      for (int x = 1; x <= VX; x++)
        if (G[b][x].weight == T(0) || eDelta(G[xs][x]) < eDelta(G[b][x])) {
          G[b][x] = G[xs][x];
          G[x][b] = G[x][xs];
        }
      for (int x = 1; x <= V; x++)
        if (floFrom[xs][x])
          floFrom[b][x] = xs;
    }
    setSlack(b);
  }
  void expandBlossom(int b) {
    for (int t : flo[b])
      setSt(t, t);
    int xr = floFrom[b][G[b][par[b]].v], pr = getPr(b, xr);
    for (int i = 0; i < pr; i += 2) {
      int xs = flo[b][i], xns = flo[b][i + 1];
      par[xs] = G[xns][xs].v;
      S[xs] = 1;
      S[xns] = slack[xs] = slack[xns] = 0;
      qPush(xns);
    }
    S[xr] = 1;
    par[xr] = par[b];
    for (int i = pr + 1; i < int(flo[b].size()); i++) {
      int xs = flo[b][i];
      S[xs] = -1;
      setSlack(xs);
    }
    st[b] = 0;
  }
  bool onFoundEdge(const Edge &e) {
    int v = st[e.v], w = st[e.w];
    if (S[w] == -1) {
      par[w] = e.v;
      S[w] = 1;
      slack[w] = 0;
      int nv = st[match[w]];
      S[nv] = slack[nv] = 0;
      qPush(nv);
    } else if (S[w] == 0) {
      int anc = lca(v, w);
      if (!anc) {
        augment(v, w);
        augment(w, v);
        return true;
      }
      addBlossom(v, anc, w);
    }
    return false;
  }
  bool matching() {
    q = Queue<int>();
    for (int x = 1; x <= VX; x++) {
      S[x] = -1;
      slack[x] = 0;
      if (st[x] == x && !match[x]) {
        par[x] = S[x] = 0;
        qPush(x);
      }
    }
    if (q.empty())
      return false;
    while (true) {
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (S[st[v]] == 1)
          continue;
        for (int w = 1; w <= V; w++)
          if (G[v][w].weight > T() && st[v] != st[w]) {
            if (eDelta(G[v][w]) == T()) {
              if (onFoundEdge(G[v][w]))
                return true;
            } else
              updateSlack(v, st[w]);
          }
      }
      T d = INF;
      for (int b = V + 1; b <= VX; b++)
        if (st[b] == b && S[b] == 1)
          d = Min(d, lab[b] / T(2));
      for (int x = 1; x <= VX; x++)
        if (st[x] == x && slack[x]) {
          if (S[x] == -1)
            d = Min(d, eDelta(G[slack[x]][x]));
          else if (S[x] == 0)
            d = Min(d, eDelta(G[slack[x]][x]) / T(2));
        }
      for (int v = 1; v <= V; v++) {
        if (S[st[v]] == 0) {
          if (lab[v] <= d)
            return false;
          lab[v] -= d;
        } else if (S[st[v]] == 1)
          lab[v] += d;
      }
      for (int b = V + 1; b <= VX; b++)
        if (st[b] == b && S[b] != -1) {
          if (S[b] == 0)
            lab[b] += d * T(2);
          else
            lab[b] -= d * T(2);
        }
      q = Queue<int>();
      for (int x = 1; x <= VX; x++)
        if (st[x] == x && slack[x] && st[slack[x]] != x &&
            eDelta(G[slack[x]][x]) == T() && onFoundEdge(G[slack[x]][x]))
          return true;
      for (int b = V + 1; b <= VX; b++)
        if (st[b] == b && S[b] == 1 && lab[b] == T())
          expandBlossom(b);
    }
    return false;
  }
public:
  int get_cardinality() const { return cardinality; }
  T get_total_weight() const { return total_weight; }
  const Vec<int> &get_mate() const { return mate; }
  GeneralWeightedMaxMatch(const Vec<Vec<T>> &matrix,
                          T INF = std::numeric_limits<T>::max())
      : V(matrix.size()), VX(V), cardinality(0), curStamp(0), INF(INF),
        total_weight(T()), mate(V, -1), match(V * 2 + 1, 0),
        slack(V * 2 + 1, 0), st(V * 2 + 1, 0), par(V * 2 + 1, 0),
        S(V * 2 + 1, 0), stamp(V * 2 + 1, 0), lab(V * 2 + 1, T()),
        flo(V * 2 + 1), floFrom(V * 2 + 1, Vec<int>(V + 1, 0)),
        G(V * 2 + 1, Vec<Edge>(V * 2 + 1)) {
    std::iota(st.begin(), st.begin() + V + 1, 0);
    T mx = T();
    for (int v = 1; v <= V; v++)
      for (int w = 1; w <= V; w++) {
        G[v][w].v = v;
        G[v][w].w = w;
        floFrom[v][w] = (v == w ? v : 0);
        Assert(G[v][w].weight >= T());
        mx = Max(mx, G[v][w].weight = matrix[v - 1][w - 1]);
      }
    Fill(lab.begin() + 1, lab.begin() + V + 1, mx);
    while (matching())
      cardinality++;
    for (int v = 1; v <= V; v++)
      if (match[v] && match[v] < v) {
        mate[mate[v - 1] = G[v][match[v]].w - 1] = v - 1;
        total_weight += G[v][match[v]].weight;
      }
  }
};
} // namespace graph
} // namespace dalt
namespace dalt {
template <class T = int>
struct GridView {
  using A3 = Array<T, 3>;
  using Mat3 = Array<A3, 3>;
  using A2 = Array<T, 2>;
 private:
  int n;
  int m;
  Mat3 mat;
  Mat3 inv_mat;
  static Mat3 mul(const Mat3 &a, const Mat3 &b) {
#define MAT3_MUL(i, j) a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j]
    return Mat3{A3{MAT3_MUL(0, 0), MAT3_MUL(0, 1), MAT3_MUL(0, 2)},
                A3{MAT3_MUL(1, 0), MAT3_MUL(1, 1), MAT3_MUL(1, 2)},
                A3{MAT3_MUL(2, 0), MAT3_MUL(2, 1), MAT3_MUL(2, 2)}};
#undef MAT3_MUL
  }
  static A3 mul(const Mat3 &a, const A3 &b) {
#define MAT3_MUL(i) a[i][0] * b[0] + a[i][1] * b[1] + a[i][2] * b[2]
    return A3{MAT3_MUL(0), MAT3_MUL(1), MAT3_MUL(2)};
#undef MAT3_MUL
  }
  static int mul(const A3 &a, const A3 &b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  }
  void add_right(const Mat3 &x, const Mat3 &inv_x) {
    mat = mul(mat, x);
    inv_mat = mul(inv_x, inv_mat);
  }
  void add_left(const Mat3 &x, const Mat3 &inv_x) {
    mat = mul(x, mat);
    inv_mat = mul(inv_mat, inv_x);
  }
  void add_right(const Mat3 &x) { add_right(x, x); }
  void add_left(const Mat3 &x) { add_left(x, x); }
 public:
  GridView(int _n, int _m)
      : n(_n),
        m(_m),
        mat(Mat3{A3{1, 0, 0}, A3{0, 1, 0}, A3{0, 0, 1}}),
        inv_mat(Mat3{A3{1, 0, 0}, A3{0, 1, 0}, A3{0, 0, 1}}) {}
  int width() const { return m; }
  int height() const { return n; }
  GridView clone() const { return *this; }
  GridView &flip_x() {
    add_left(Mat3{A3{-1, 0, n - 1}, A3{0, 1, 0}, A3{0, 0, 1}});
    return *this;
  }
  GridView &flip_y() {
    add_left(Mat3{A3{1, 0, 0}, A3{0, -1, m - 1}, A3{0, 0, 1}});
    return *this;
  }
  GridView &swap_x_y() {
    Swap(n, m);
    add_left(Mat3{A3{0, 1, 0}, A3{1, 0, 0}, A3{0, 0, 1}});
    return *this;
  }
  A2 global_to_view(const A2 &xy) const {
    auto ans = mul(mat, A3{xy[0], xy[1], 1});
    return A2{ans[0], ans[1]};
  }
  A2 view_to_global(const A2 &xy) const {
    auto ans = mul(inv_mat, A3{xy[0], xy[1], 1});
    return A2{ans[0], ans[1]};
  }
  GridView &rect(T xl, T xr, T yl, T yr) {
    Assert(xr - xl + 1 <= n);
    Assert(yr - yl + 1 <= m);
    add_left(Mat3{A3{1, 0, -xl}, A3{0, 1, -yl}, {0, 0, 1}},
             Mat3{A3{1, 0, xl}, A3{0, 1, yl}, {0, 0, 1}});
    n = xr - xl + 1;
    m = yr - yl + 1;
    return *this;
  }
};
}  // namespace dalt
namespace dalt {
template <class T>
struct GuassElimination {
 private:
  Vec<Vec<T>> data;
  Vec<T> inv;
  int n;
  int rank;
  void sub(Vec<T>& x, const Vec<T>& row, T f) {
    for (int i = 0; i < n; i++) {
      x[i] -= row[i] * f;
    }
  }
 public:
  GuassElimination(int _n) : data(_n + 1), inv(_n + 1), n(_n + 1), rank(0) {}
  int add(Vec<T> e) {
    Assert(Size(e) == n);
    for (int i = 0; i < n; i++) {
      if (data[i].empty() || e[i] == T(0)) {
        continue;
      }
      sub(e, data[i], e[i] * inv[i]);
    }
    int index = -1;
    for (int i = 0; i < n; i++) {
      if (e[i] != T(0)) {
        index = i;
        break;
      }
    }
    if (index != -1) {
      data[index] = e;
      inv[index] = T(1) / e[index];
      rank++;
    }
    return index;
  }
  int get_rank() const { return rank - int(Size(data[n - 1]) > 0); }
  bool has_solution() const { return Size(data[n - 1]) == 0; }
  Optional<Vec<T>> any_solution() const {
    if (!has_solution()) {
      return {};
    }
    Vec<T> ans(n - 1, T(0));
    for (int i = n - 2; i >= 0; i--) {
      if (data[i].empty()) {
        continue;
      }
      T sum = data[i][n - 1];
      for (int j = n - 2; j > i; j--) {
        sum -= data[i][j] * ans[j];
      }
      ans[i] = sum * inv[i];
    }
    return ans;
  }
  Vec<Vec<T>> to_vec() const { return data; }
};
}  // namespace dalt
namespace dalt {
namespace geo2 {
template <class T>
enable_if_t<is_near_value_v<T>, Optional<Vec<Line<T>>>> HalfPlaneIntersection(
    Vec<Line<T>> lines, bool close = true, bool is_anticlockwise_sort = false) {
  using L = Line<T>;
  using Pt = Point<T>;
  if (Size(lines) < 2) {
    return {};
  }
  SortByPolarAngleAround<T> sorter;
  if (!is_anticlockwise_sort) {
    Sort(All(lines), [&](const Line<T>& a, const Line<T> &b) { return sorter(a.vec, b.vec); });
  }
  int n = Size(lines);
  Deque<L> deque;
  auto insert = [&](const L& line) -> bool {
    //Debug(line);
    while (Size(deque) >= 2) {
      L tail = deque.back();
      deque.pop_back();
      auto pt = L::intersect(tail, deque.back());
      if (pt.is_none()) {
        continue;
      }
      int side = line.side(pt.value());
      if (side > 0 || (close && side == 0)) {
        deque.push_back(tail);
        break;
      }
      if (Pt::orient(line.vec, deque.back().vec) !=
          Pt::orient(tail.vec, deque.back().vec)) {
        return false;
      }
    }
    while (Size(deque) >= 2) {
      L front = deque.front();
      deque.pop_front();
      auto pt = L::intersect(front, deque.front());
      if (pt.is_none()) {
        continue;
      }
      int side = line.side(pt.value());
      if (side > 0 || (close && side == 0)) {
        deque.push_front(front);
        break;
      }
      if (Pt::orient(line.vec, deque.front().vec) !=
          Pt::orient(front.vec, deque.front().vec)) {
        return false;
      }
    }
    if (Size(deque) == 1 && Pt::orient(line.vec, deque.back().vec) == 0) {
      int side = deque.back().side(line);
      if (!(side > 0 || (close && side == 0))) {
        return false;
      }
    }
    deque.push_back(line);
    return true;
  };
  for (int i = 0; i < n; i++) {
    L& line = lines[i];
    while (i + 1 < n && sorter.compare(line.vec, lines[i + 1].vec) == 0) {
      i++;
      if (line.side(lines[i]) > 0) {
        line = lines[i];
      }
    }
    if (!insert(line)) {
      return {};
    }
    // Debug(line);
    // Debug(deque);
  }
  auto first = deque.front();
   Debug(deque);
  deque.pop_front();
  if (!insert(first)) {
    return {};
  }
   Debug(deque);
  Vec<Line<T>> res;
  res.insert(res.end(), All(deque));
  return res;
}
}  // namespace geo2
}  // namespace dalt
/**
 * Description: Hash Map with the same API as unordered\_map, but \tilde 3x
 * faster. Initial capacity must be a power of 2 if provided. Source: KACTL
 * Usage: ht<int,int> h({},{},{},{},{1<<16});
 */
 /*
namespace dalt {
namespace hash {
struct chash {  /// use most bits rather than just the lowest ones
  i64 operator()(i64 x) const { return hash::Shuffle(x); }
};
template <class K, class V>
using HashMap_um = std::unordered_map<K, V, chash>;
template <class K, class V>
using HashMap_ht = __gnu_pbds::gp_hash_table<K, V, chash>;
template <class K, class V>
OStream &operator<<(OStream &os, const HashMap_ht<K, V> &hv) {
  HashMap_um<K, V> hm;
  for (auto iter = hv.begin(); iter != hv.end(); iter++) {
    hm[iter->first] = iter->second;
  }
  os << hm;
  return os;
}
}  // namespace hash
}  // namespace dalt
*/
namespace dalt {
namespace hash {
struct HashBase {
  using Modular = MOD_BIG;
  using Mi = ModInt<Modular>;
  static Mi x;
  static Mi inv_x;
  static Vec<Mi> xp;
  static Vec<Mi> inv_xp;
  HashBase() {
    int cap = 1e6 + 10;
    x = Mi(random_choice<i64>(1, Modular::modulus - 1));
    inv_x = Mi(1) / x;
    xp.clear();
    inv_xp.clear();
    xp.reserve(cap);
    inv_xp.reserve(cap);
    xp.push_back(Mi(1));
    inv_xp.push_back(Mi(1));
  }
  static void ensure(i32 n) {
    Assert(x != Mi(0));
    while (Size(xp) < n) {
      xp.push_back(xp.back() * x);
      inv_xp.push_back(inv_xp.back() * inv_x);
    }
  }
  static Mi pow(i32 n) {
    Assert(x != Mi(0));
    ensure(Abs(n) + 1);
    if (n >= 0) {
      return xp[n];
    } else {
      return inv_xp[-n];
    }
  }
  static Mi verbose(Mi hash, i32 size) {
    Assert(x != Mi(0));
    ensure(size + 1);
    return hash + xp[size];
  }
} __HASH_BASE__;
decltype(HashBase::x) HashBase::x;
decltype(HashBase::inv_x) HashBase::inv_x;
decltype(HashBase::xp) HashBase::xp;
decltype(HashBase::inv_xp) HashBase::inv_xp;
}  // namespace hash
}  // namespace dalt
namespace dalt {
namespace hash {
template <class T>
struct HashRange {
  using Self = HashRange;
  using Mi = HashBase::Mi;
  Vec<Mi> data;
  HashRange(int n, const Indexer<T>& s) {
    static_assert(is_integral_v<T>);
    HashBase::ensure(n + 2);
    data.resize(n + 1);
    for (int i = 1; i <= n; i++) {
      data[i] = Mi(s(i - 1)) * HashBase::xp[i] + data[i - 1];
    }
  }
  struct Range {
    Vec<Mi>& data;
    Mi sum;
    i32 size;
    Range& append(int l, int r) {
      if (l > r) {
        return *this;
      }
      sum = sum + (data[r + 1] - data[l]) * HashBase::pow(size - (l + 1));
      size += r - l + 1;
      return *this;
    }
    i64 hash() const { return sum.value; }
    i64 hash_verbose() const { return HashBase::verbose(sum, size).value; }
  };
  Range range() {
    return Range{
        .data = data,
        .sum = Mi(0),
        .size = 0,
    };
  }
  i64 hash(int l, int r) {
    if (l > r) {
      return 0;
    }
    return ((data[r + 1] - data[l]) * HashBase::inv_xp[l + 1]).value;
  }
  i64 hash_verbose(int l, int r) {
    if (l > r) {
      return 0;
    }
    return HashBase::verbose(((data[r + 1] - data[l]) * HashBase::inv_xp[l + 1]), r - l + 1).value;
  }
};
};  // namespace hash
}  // namespace dalt
namespace dalt {
namespace hash {
template <class T>
struct HashRangeFenwickTree {
  static_assert(is_integral_v<T>);
  using Mi = HashBase::Mi;
  FenwickTree<Mi> ft;
  HashRangeFenwickTree(const Indexer<T>& data, i32 n) {
    HashBase::ensure(n + 1);
    ft = decltype(ft)([&](auto i) { return Mi(data(i)); }, n);
  }
  HashRangeFenwickTree(i32 n) : ft(n) { HashBase::ensure(n + 1); }
  //- time: O(\log n)
  void set(int index, T val) { ft.set(index, Mi(val) * HashBase::xp[index]); }
  //- time: O(\log n)
  i64 hash(int l, int r) const {
    return (ft.query(l, r) * HashBase::inv_xp[l]).value;
  }
  //- time: O(\log n)
  i64 hash_verbose(int l, int r) const {
    return ((ft.query(l, r) + HashBase::xp[r + 1]) * HashBase::inv_xp[l]).value;
  }
};
}  // namespace hash
}  // namespace dalt
namespace dalt {
namespace hash {
template <class T>
struct MultiHashBase {
  using Modular = MOD_BIG;
  using Mi = ModInt<Modular>;
  static HashMap<T, Mi> mem;
  static Mi get(T key) {
    Mi ans = mem[key];
    if (ans == Mi(0)) {
      ans = mem[key] = random();
    }
    return ans;
  }
  static Mi random() { return Mi(random_choice<i64>(1, Modular::modulus - 1)); }
};
template <class T>
HashMap<T, typename MultiHashBase<T>::Mi> MultiHashBase<T>::mem;
}  // namespace hash
}  // namespace dalt
namespace dalt {
namespace hash {
// ret[i] = the hash value of the whole tree if we regard i-th node as the root
// of the tree
//- time: O(n)
//- space: O(n)
template <class E>
Vec<i64> HashTreeAllRoot(const graph::Graph<E>& g) {
  static_assert(is_base_of_v<graph::BiBaseEdge, E>);
  using Mi = ModInt<MOD_BIG>;
  int n = Size(g);
  Vec<Mi> subtree_hash(n);
  auto down_up = [&](auto& down_up, i32 root, i32 rev) -> void {
    i32 m = Size(g[root]);
    Mi sum = Mi(0);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        continue;
      }
      auto& e = g[root][i];
      down_up(down_up, e.to, e.rev);
      sum = sum + subtree_hash[e.to];
    }
    subtree_hash[root] = MultiHashBase<Mi>::get(sum);
  };
  down_up(down_up, 0, -1);
  auto up_down = [&](auto& up_down, i32 root, i32 rev, Mi fa_hash) -> void {
    i32 m = Size(g[root]);
    Mi sum = Mi(0);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        sum = sum + fa_hash;
        continue;
      }
      auto& e = g[root][i];
      sum = sum + subtree_hash[e.to];
    }
    subtree_hash[root] = MultiHashBase<Mi>::get(sum);
    for (int i = 0; i < m; i++) {
      if (i == rev) {
        continue;
      }
      auto& e = g[root][i];
      auto truncated = MultiHashBase<Mi>::get(sum - subtree_hash[e.to]);
      up_down(up_down, e.to, e.rev, truncated);
    }
  };
  up_down(up_down, 0, -1, Mi(0));
  Vec<i64> ans = Cast<i64>(subtree_hash);
  return ans;
}
}  // namespace hash
}  // namespace dalt
namespace dalt {
  template<class FORWARD, class T, class METADATA = Nil>
  struct RWElement {
    using Self = RWElement<FORWARD, T, METADATA>;
    FORWARD *forward;
    METADATA metadata;
    RWElement(FORWARD *_forward, const METADATA& _metadata): forward(_forward), metadata(_metadata) {
    }
    operator T() {
      return forward->read(metadata);
    }
    Self &operator=(const T& val) {
      forward->write(metadata, val);
      return *this;
    }
  };
}
namespace dalt {
namespace hash {
template <class T>
struct HashWhole {
  static_assert(is_integral_v<T>);
  using Self = HashWhole<T>;
  using Mi = HashBase::Mi;
  Vec<T> data;
  Mi sum;
  HashWhole(i32 n) : data(n), sum(0) { HashBase::ensure(n + 1); }
  void write(i32 index, const T& x) {
    sum = sum + (Mi(x) - Mi(data[index])) * HashBase::xp[index];
    data[index] = x;
  }
  const T& read(i32 index) const {
    return data[index];
  }
  RWElement<Self, T, int> operator[](i32 index) {
    return RWElement<Self, T, int>(this, index);
  }
  const T& operator[](i32 index) const { return read(index); }
  i64 hash() const { return sum.value; }
  i64 hash_verbose() const { return HashBase::verbose(sum, Size(data)).value; }
  Vec<T> to_vec() const {
    return data;
  }
};
}  // namespace hash
}  // namespace dalt
namespace dalt {
namespace hash {
template <class T>
struct HashWholeDeque {
  static_assert(is_integral_v<T>);
  using Mi = HashBase::Mi;
  Deque<T> dq;
  Mi sum;
  void push_back(T x) {
    sum = sum + HashBase::pow(Size(dq)) * Mi(x);
    dq.push_back(x);
  }
  void push_front(T x) {
    sum = sum * HashBase::x + x;
    dq.push_front(x);
  }
  void clear() {
    dq.clear();
    sum = Mi();
  }
  bool empty() const { return dq.empty(); }
  int size() const { return dq.size(); }
  const T& front() const { return dq.front(); }
  const T& back() const { return dq.back(); }
  void pop_back() {
    sum = sum - HashBase::pow(Size(dq) - 1) * Mi(dq.back());
    dq.pop_back();
  }
  void pop_front() {
    sum = (sum - Mi(dq.front())) * HashBase::inv_x;
    dq.pop_front();
  }
  i64 hash() const { return sum.value; }
  i64 hash_verbose() const { return HashBase::verbose(sum, Size(dq)).value; }
};
}  // namespace hash
}  // namespace dalt
namespace dalt {
String ReadAll(IStream &in, int cap = 10 << 20) {
  in >> std::noskipws;
  String s;
  s.reserve(cap);
  char c;
  while (in >> c) {
    s.push_back(c);
  }
  in >> std::skipws;
  return s;
}
} // namespace dalt
namespace dalt {
namespace poly {
template <class T> struct GravityLargrangeInterpolation {
  hash::HashMap<T, T> points;
  Vec<T> xs;
  Vec<T> ys;
  Vec<T> lx;
  Vec<T> inv_w;
  GravityLargrangeInterpolation(i32 cap) {
    xs.reserve(cap);
    ys.reserve(cap);
    lx = Vec<T>{T(1)};
    inv_w.reserve(cap);
  }
  void add(T x, T y) {
    if (points.find(x) != points.end()) {
      return;
    }
    points[x] = y;
    i32 n = Size(xs);
    xs.push_back(x);
    ys.push_back(y);
    lx = BruteForceConv<T>::conv(Vec<T>{T(0) - x, T(1)}, lx);
    inv_w.push_back(T(1));
    for (int i = 0; i < n; i++) {
      inv_w[i] = inv_w[i] * (xs[i] - x);
      inv_w[n] = inv_w[n] * (x - xs[i]);
    }
  }
  T estimate_point(T x) const {
    auto iter = points.find(x);
    if (iter != points.end()) {
      return iter->second;
    }
    T y = Apply(lx, x);
    T sum = T(0);
    for (int i = 0; i < Size(xs); i++) {
      T val = ys[i] / (inv_w[i] * (x - xs[i]));
      sum = sum + val;
    }
    return y * sum;
  }
  template <class Conv = BruteForceConv<T>>
  enable_if_t<is_convolution_v<Conv>, Polynomial<Conv>> interpolate() const {
    i32 n = Size(xs);
    Vec<T> ans(n);
    for (int i = 0; i < n; i++) {
      T c = ys[i] / inv_w[i];
      T div = BruteForceConv<T>::div_and_rem(lx, Vec<T>{T(0) - xs[i], T(1)})[0];
      for (int j = 0; j < Size(div); j++) {
        ans[j] = ans[j] + div[j] * c;
      }
    }
    return Polynomial<Conv>(ans);
  }
};
} // namespace poly
} // namespace dalt
namespace dalt {
template <class T>
struct IntervalMap {
  static_assert(is_arithmetic_v<T>);
  using Self = IntervalMap<T>;
  //[l, r), left close, right open
  TreeMap<T, T> map;
  Function<void(T, T)> add_callback;
  Function<void(T, T)> del_callback;
 private:
  void add0(T l, T r) {
    if(l >= r) {
      return;
    }
    add_callback(l, r);
    map[l] = r;
  }
  decltype(map.begin()) del0(decltype(map.begin())& iter) {
    del_callback(iter->first, iter->second);
    return map.erase(iter);
  }
public:
  IntervalMap(
      const Function<void(T, T)>& _add_callback = [](T a, T b) {},
      const Function<void(T, T)>& _del_callback = [](T a, T b) {})
      : add_callback(_add_callback), del_callback(_del_callback) {}
  //[begin, end)
  void add(T begin, T end) {
    auto iter = map.upper_bound(begin);
    if(iter != map.begin()) {
      --iter;
      if(iter->second < begin) {
        ++iter;
      }
    }
    while(iter != map.end() && !(iter->second < begin || iter->first > end)) {
      begin = Min(begin, iter->first);
      end = Max(end, iter->second);
      iter = del0(iter);
    }
    add0(begin, end);
  }
  void remove(T begin, T end) {
    auto iter = map.upper_bound(begin);
    if (iter != map.begin()) {
      --iter;
      if (iter->second < begin) {
        ++iter;
      }
    }
    while (iter != map.end() && !(iter->second < begin || iter->first > end)) {
      T l = iter->first;
      T r = iter->second;
      iter = del0(iter);
      add0(l, begin);
      add0(end, r);
    }
  }
  Optional<Pair<T, T>> cover_line(T pt) {
    auto iter = map.upper_bound(pt);
    if(iter == map.begin()) {
      return {};
    }
    --iter;
    if(iter->second <= pt) {
      return {};
    }
    return MakePair(iter->first, iter->second);
  }
  Vec<Pair<T, T>> to_vec() const {
    Vec<Pair<T, T>> res;
    res.insert(res.begin(), All(map));
    return res;
  }
};
}  // namespace dalt
namespace dalt {
namespace seq {
template <class T>
struct KMP {
  Vec<T> data;
  Vec<int> fail;
  KMP(int cap = 0) {
    cap += 1;
    data.reserve(cap);
    data.resize(1);
    fail.reserve(cap);
    fail.push_back(-1);
  }
  int size() const { return data.size() - 1; }
  void build(T c) {
    fail.push_back(visit(c, fail.back()) + 1);
    data.push_back(c);
  }
  // length of longest suffix(not whole) which is also a prefix
  int max_border(int i) const { return fail[i + 1]; }
  struct Matcher {
    int match_length;
    KMP &kmp;
    bool match_fully() const { return match_length == kmp.size(); }
    void match(T c) { 
      if(match_fully()) {
        match_length = kmp.fail[match_length];
      }
      match_length = kmp.visit(c, match_length) + 1; }
    int get_match_length() const { return match_length; }
  };
  Matcher matcher() {
    return Matcher{
        .match_length = 0,
        .kmp = *this,
    };
  }
 private:
  int visit(T c, int trace) const {
    while (trace >= 0 && data[trace + 1] != c) {
      trace = fail[trace];
    }
    return trace;
  }
};
}  // namespace seq
}  // namespace dalt
namespace dalt {
namespace math {
// credited to: https://judge.yosupo.jp/submission/5940
// return a^{1/p} (mod p) or -1 if not exists
i64 KthRootModPrime(i64 a, i64 k, i64 p) {
  auto pow = [](i64 a, i64 n, i64 p) -> i64 {
    i64 r = 1;
    for (; n > 0; n >>= 1, a = a * a % p)
      if (n % 2 == 1) r = r * a % p;
    return r;
  };
  auto inv = [](i64 a, i64 p) -> i64 {
    a %= p;
    i64 u = 1, v = 0;
    i64 b = p;
    while (b > 0) {
      i64 q = a / b;
      a %= b;
      u -= v * q % p;
      u = (u % p + p) % p;
      Swap(u, v);
      Swap(a, b);
    }
    return u < 0 ? u + p : u;
  };
  auto peth_root = [&](i64 a, i64 p, int e,
                       i64 mod) -> i64 {
    i64 q = mod - 1;
    int s = 0;
    while (q % p == 0) {
      q /= p;
      ++s;
    }
    i64 pe = pow(p, e, mod);
    i64 ans = pow(a, ((pe - 1) * inv(q, pe) % pe * q + 1) / pe, mod);
    i64 c = 2;
    while (pow(c, (mod - 1) / p, mod) == 1) ++c;
    c = pow(c, q, mod);
    i64 add = 1;
    int v = (int)std::sqrt((double)(s - e) * p) + 1;
    hash::HashMap<i64, int> map(v + 1);
    i64 mul = pow(c, v * pow(p, s - 1, mod - 1) % (mod - 1), mod);
    for (int i = 0; i <= v; ++i) {
      map[add] = i;
      add = add * mul % mod;
    }
    mul = inv(pow(c, pow(p, s - 1, mod - 1), mod), mod);
    for (int i = e; i < s; ++i) {
      i64 err = inv(pow(ans, pe, mod), mod) * a % mod;
      i64 target = pow(err, pow(p, s - 1 - i, mod - 1), mod);
      for (int j = 0; j <= v; ++j) {
        if (map.find(target) != map.end()) {
          int x = map[target];
          ans = ans *
                pow(c, (j + v * x) * pow(p, i - e, mod - 1) % (mod - 1), mod) %
                mod;
          break;
        }
        target = target * mul % mod;
        assert(j != v);
      }
    }
    return ans;
  };
  if (k > 0 && a == 0) return 0;
  k %= p - 1;
  i64 g = Gcd(k, p - 1);
  if (pow(a, (p - 1) / g, p) != 1) return -1;
  a = pow(a, inv(k / g, (p - 1) / g), p);
  for (i64 div = 2; div * div <= g; ++div) {
    int sz = 0;
    while (g % div == 0) {
      g /= div;
      ++sz;
    }
    if (sz > 0) {
      i64 b = peth_root(a, div, sz, p);
      a = b;
    }
  }
  if (g > 1) a = peth_root(a, g, 1, p);
  return a;
}
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace poly {
// [x^k] P/Q 
// time complexity: O(M(Poly) n) where M(Poly) is the time taken to perform polynomial mutiplication
// consider from last bit to first bit
template <class Poly>
typename Poly::Type KthTermOfInversePolynomial(int n,
                                               const Indexer<int> &bit_indexer,
                                               const Poly &P, const Poly &Q) {
  static_assert(is_polynomial_v<Poly>);
  using T = typename Poly::Type;
  if (n == 0) { return P[0] / Q[0]; }
  auto bit = bit_indexer(n - 1);
  //assert(P.rank() <= 1 && Q.rank() <= 1);
  Vec<T> neg_Q_data = Q.data;
  for (int i = 1; i < Size(neg_Q_data); i += 2) {
    neg_Q_data[i] = T(0) - neg_Q_data[i];
  }
  Poly neg_Q(Move(neg_Q_data));
  let AB = P * neg_Q;
  let QQ = Q * neg_Q;
  Vec<T> A;
  Vec<T> C;
  A.reserve((AB.rank() + 1 + 1) / 2);
  C.reserve((QQ.rank() + 1 + 1) / 2);
  for (int i = bit; i <= AB.rank(); i += 2) {
    A.push_back(AB[i]);
  }
  for (int i = 0; i <= QQ.rank(); i += 2) {
    C.push_back(QQ[i]);
  }
  return KthTermOfInversePolynomial(n - 1, bit_indexer, Poly(Move(A)),
                                    Poly(Move(C)));
}
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace poly {
template <class M>
enable_if_t<is_modular_v<M>> NumberTheoryTransform(Vec<ModInt<M>> &p,
                                                   bool inv) {
  using mi = ModInt<M>;
  auto modulus = mi::modulus();
  mi g = mi(mi::primitive_root());
  i32 m = Log2Ceil(Size(p));
  i32 n = 1 << m;
  Assert(n == Size(p));
  auto shift = 32 - TrailingZeroNumber(n);
  for (int i = 1; i < n; i++) {
    auto j = ReverseBit(u32(i << shift));
    if (i < j) {
      Swap(p[i], p[j]);
    }
  }
  Vec<mi> ws(n / 2);
  Assert((modulus - 1) % n == 0);
  auto unit = PowBinaryLift(g, (modulus - 1) / n);
  if (Size(ws) >= 1) {
    ws[0] = 1;
  }
  for (int i = 1; i < Size(ws); i++) {
    ws[i] = ws[i - 1] * unit;
  }
  for (int d = 0; d < m; d++) {
    auto s = 1 << d;
    auto s2 = s << 1;
    auto right = n >> (1 + d);
    for (int i = 0; i < n; i += s2) {
      for (int j = 0; j < s; j++) {
        auto a = i + j;
        auto b = a + s;
        auto t = ws[j * right] * p[b];
        p[b] = p[a] - t;
        p[a] = p[a] + t;
      }
    }
  }
  if (inv) {
    auto inv_n = mi(1) / mi(n);
    auto i = 0;
    auto j = 0;
    while (i <= j) {
      auto a = p[j];
      p[j] = p[i] * inv_n;
      if (i != j) {
        p[i] = a * inv_n;
      }
      i += 1;
      j = n - i;
    }
  }
}
template <class M>
struct NTTConv {
  static_assert(is_modint_v<M>);
  using mi = M;
  using Type = mi;
  using P = Vec<mi>;
  static P conv(const P &a, const P &b) {
    if (Size(a) <= 20 || Size(b) <= 20) {
      return BruteForceConv<Type>::conv(a, b);
    }
    if (&a == &b) {
      return conv2(a);
    }
    int n = Size(a) + Size(b);
    int conv_len = 1 << Log2Ceil(n);
    auto pa = CopyAndExtend(a, conv_len);
    auto pb = CopyAndExtend(b, conv_len);
    NumberTheoryTransform(pa, false);
    NumberTheoryTransform(pb, false);
    DotMulInplace(pa, pb);
    NumberTheoryTransform(pa, true);
    return pa;
  }
  static P conv2(const P &a) {
    int n = Size(a) + Size(a) - 1;
    int conv_len = 1 << Log2Ceil(n);
    auto pa = CopyAndExtend(a, conv_len);
    NumberTheoryTransform(pa, false);
    DotMulInplace(pa, pa);
    NumberTheoryTransform(pa, true);
    return pa;
  }
  static P inverse(P p, i32 n) {
    Extend(p, n);
    auto dfs = [&](auto &dfs, i32 m) {
      if (m == 1) {
        return P{mi(1) / mi(p[0])};
      }
      i32 prev_len = (m + 1) / 2;
      auto ans = dfs(dfs, prev_len);
      i32 n = (prev_len - 1) * 2 + m;
      auto proper_len = 1 << Log2Ceil(n);
      ans.resize(proper_len);
      P prefix;
      prefix.reserve(proper_len);
      prefix.insert(prefix.begin(), p.begin(), p.begin() + m);
      prefix.resize(proper_len);
      NumberTheoryTransform(prefix, false);
      NumberTheoryTransform(ans, false);
      for (int i = 0; i < proper_len; i++) {
        ans[i] = ans[i] * (mi(2) - prefix[i] * ans[i]);
      }
      NumberTheoryTransform(ans, true);
      ans.resize(m);
      return ans;
    };
    return dfs(dfs, n);
  }
};
template <class M>
struct is_convolution<NTTConv<M>> {
  static const bool value = true;
};
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace poly {
template <class T, int B = 20>
struct LargeConvolution {
  const static int batch_size = 1 << B;
  const static int batch_size_2 = batch_size * 2;
  using Type = T;
  static Vec<Vec<T>> split(const Vec<T> &a) {
    Vec<Vec<T>> data((Size(a) + batch_size - 1) / batch_size,
                     Vec<T>(batch_size * 2));
    for (int i = 0; i < Size(a); i++) {
      data[i >> B][i & (batch_size - 1)] = a[i];
    }
    Timer ntt("ntt");
    for (auto &chunk : data) {
      NumberTheoryTransform(chunk, false);
    }
    ntt.stop();
    return data;
  }
  // template <class Arg = T>
  // static enable_if_t<is_same_v<Arg, T> &&
  //                        !(is_modint_v<T> && is_same_v<typename T::Type, i32>),
  //                    Vec<T>>
   static   Vec<T> conv(const Vec<T> &a, const Vec<T> &b) {
    auto a_data = split(a);
    auto b_data = split(b);
    Vec<Vec<T>> c_data(Size(a_data) + Size(b_data) - 1, Vec<T>(batch_size * 2));
    Timer dmp("DotMulPlus");
    for (int i = 0; i < Size(a_data); i++) {
      for (int j = 0; j < Size(b_data); j++) {
        DotMulPlus(a_data[i], b_data[j], c_data[i + j]);
      }
    }
    dmp.stop();
    Timer ntt("ntt");
    for (int i = 0; i < Size(c_data); i++) {
      NumberTheoryTransform(c_data[i], true);
    }
    ntt.stop();
    Vec<T> res(Size(a) + Size(b) - 1);
    for (int i = 0; i < Size(c_data); i++) {
      auto &chunk = c_data[i];
      for (int j = 0, to = i * batch_size; j < Size(chunk) && to < Size(res);
           j++, to++) {
        res[to] += chunk[j];
      }
    }
    return res;
  }
  // template <class Arg = T>
  // static enable_if_t<is_same_v<Arg, T> && is_modint_v<T> &&
  //                        is_same_v<typename T::Type, i32>,
  //                    Vec<T>>
  // conv(const Vec<T> &a, const Vec<T> &b) {
  //   auto a_data = split(a);
  //   auto b_data = split(b);
  //   Vec<u128> aggregate(batch_size * 2);
  //   Vec<T> res(Size(a) + Size(b) - 1);
  //   i32 modulus = T::modulus();
  //   for (int i = 0; i < Size(a_data) + Size(b_data); i++) {
  //     //Timer plus("plus");
  //     Fill(All(aggregate), u128());
  //     for (int j = Max(0, i - Size(b_data) + 1); j < Size(a_data) && j <= i;
  //          j++) {
  //       int k = i - j;
  //       auto &a_ref = a_data[j];
  //       auto &b_ref = b_data[k];
  //       for (int t = 0; t < batch_size_2; t++) {
  //         aggregate[t] += u64(a_ref[t].value) * u64(b_ref[t].value);
  //       }
  //     }
  //     //plus.stop();
  //     Vec<T> chunk(batch_size * 2);
  //     for (int j = 0; j < batch_size * 2; j++) {
  //       chunk[j] = aggregate[j].modular(modulus);
  //     }
  //     NumberTheoryTransform(chunk, true);
  //     for (int j = 0, to = i * batch_size; j < Size(chunk) && to < Size(res);
  //          j++, to++) {
  //       res[to] += chunk[j];
  //     }
  //   }
  //   return res;
  // }
};
}  // namespace poly
}  // namespace dalt
namespace dalt {
#define CLASS_ID -202206092222
template <class T, class C = Less<T>, i64 ID = 0, i64 CID = 0>
struct LeftistTree {
  using Self = LeftistTree<T, C, ID, CID>;
  Self *left;
  Self *right;
  int dist;
  static Self *NIL;
  static C comp;
  T key;
 public:
  LeftistTree(T _key) : key(_key) {
    dist = 0;
    left = right = NIL;
  }
  static void Register(C comp = C(), T nil = T()) {
    if (NIL) {
      delete NIL;
    }
    NIL = new Self(nil);
    NIL->left = NIL->right = NIL;
    NIL->dist = -1;
    NIL->key = nil;
  }
  static Self* Merge(Self* a, Self *b) {
    if (a == NIL) {
      return b;
    } else if (b == NIL) {
      return a;
    }
    if (comp(b->key, a->key)) {
      Swap(a, b);
    }
    a->right = Merge(a->right, b);
    if (a->left->dist < a->right->dist) {
      Swap(a->left, a->right);
    }
    a->dist = a->right->dist + 1;
    return a;
  }
  bool empty() const {
    return this == NIL;
  }
  Self *pop() {
    auto ans = Merge(left, right);
    left = right = NIL;
    return ans;
  }
  T peek() const {
    return key;
  }
  Vec<T> to_vec() const {
    Vec<T> ans;
    auto dfs = [&](auto& rec, const Self *root) {
      if(root == NIL) {
        return;
      }
      ans.push_back(root->key);
      rec(rec, root->left);
      rec(rec, root->right);
    };
    dfs(dfs, this);
    //Sort(All(ans), comp);
    return ans;
  }
};
template <class T, class C, i64 ID, i64 CID>
LeftistTree<T, C, ID, CID> *LeftistTree<T, C, ID, CID>::NIL = NULL;
template <class T, class C, i64 ID, i64 CID>
C LeftistTree<T, C, ID, CID>::comp;
#undef CLASS_ID
}
namespace dalt {
namespace sbt {
template <class T> struct LichaoSegTree {
  static_assert(is_floating_point_v<T> || is_integral_v<T>,
                "only integer and float are supported");
  struct Line {
    using Self = Line;
    T a;
    T b;
    T apply(T x) const { return a * x + b; }
  };
  struct LCNode {
    using L = Line;
    using Self = LCNode;
    L line;
    Self *left;
    Self *right;
    LCNode() : left(NULL), right(NULL) {}
  };
  using Self = LichaoSegTree<T>;
  using Node = LCNode;
  using Ln = typename Node::L;
  Node *tree;
  Vec<T> sorted;
  const static T INF = std::numeric_limits<T>::max() / 2;
private:
  Node *make_tree(int l, int r) {
    Node *root = new Node();
    root->line = Ln{
        .a = 0,
        .b = -INF,
    };
    if (l == r) {
      return root;
    } else {
      int m = (l + r) / 2;
      root->left = make_tree(l, m);
      root->right = make_tree(m + 1, r);
    }
    return root;
  }
  T intersect(const Ln &a, const Ln &b) {
    Assert(a.a < b.a);
    return DivFloor(a.b - b.b, b.a - a.a);
  }
  void update(Node *root, int L, int R, int l, int r, Ln small_line) {
    if (SegmentNoIntersection(L, R, l, r)) {
      return;
    } else if (l == r) {
      if (root->line.apply(sorted[l]) < small_line.apply(sorted[l])) {
        root->line = small_line;
      }
      return;
    }
    int m = (l + r) / 2;
    if (SegmentCover(L, R, l, r)) {
      if (root->line.a == small_line.a) {
        root->line.b = max(root->line.b, small_line.b);
        return;
      }
      Ln large_line = root->line;
      if (small_line.a > large_line.a) {
        swap(small_line, large_line);
      }
      auto intersect_at = intersect(small_line, large_line);
      if (intersect_at <= sorted[m]) {
        root->line = large_line;
        if (l < r) {
          update(root->left, L, R, l, m, small_line);
        }
      } else {
        root->line = small_line;
        if (l < r) {
          update(root->right, L, R, m + 1, r, large_line);
        }
      }
      return;
    }
    update(root->left, L, R, l, m, small_line);
    update(root->right, L, R, m + 1, r, small_line);
  }
  T query(const Node *root, int l, int r, int x) const {
    T best = root->line.apply(sorted[x]);
    if (l == r) {
      return best;
    }
    int m = (l + r) / 2;
    if (x <= m) {
      best = max(best, query(root->left, l, m, x));
    } else {
      best = max(best, query(root->right, m + 1, r, x));
    }
    return best;
  }
public:
  LichaoSegTree(const Vec<T> &_sorted) : sorted(_sorted) {
    if (sorted.empty()) {
      sorted.push_back(0);
    }
    sort(All(sorted));
    Unique(sorted);
    tree = make_tree(0, Size(sorted) - 1);
  }
  void update(T _L, T _R, T a, T b) {
    int L = LowerBound(All(sorted), _L) - sorted.begin();
    int R = UpperBound(All(sorted), _R) - sorted.begin();
    R--;
    update(tree, L, R, 0, Size(sorted) - 1,
           Ln{
               .a = a,
               .b = b,
           });
  }
  T query(T x) const {
    auto iter = LowerBound(All(sorted), x);
    Assert(iter != sorted.end() && *iter == x);
    return query(tree, 0, Size(sorted) - 1, iter - sorted.begin());
  }
  Vec<T> to_vec() const {
    Vec<T> res;
    for (auto x : sorted) {
      res.push_back(query(x));
    }
    return res;
  }
};
} 
} // namespace dalt
namespace dalt {
template <class T, T MAX = std::numeric_limits<T>::max()>
struct LimitValue {
  static_assert(is_integral_v<T>);
  using Self = LimitValue<T, MAX>;
  T value;
  LimitValue(T _value = T(0)) : value(_value) {}
  bool is_max() const { return value == MAX; }
  Self operator*(const Self& rhs) const {
    return Self(MulLimit(value, rhs.value, MAX));
  }
  Self operator+(const Self& rhs) const {
    return Self(AddLimit(value, rhs.value, MAX));
  }
  bool operator<(const Self& rhs) const {
    return value < rhs.value;
  }
  ImplDefaultComparision(Self);
  ImplArithmeticAssignOperation(Self);
  Self operator==(const Self& rhs) const { return value == rhs.value; }
  Self operator!=(const Self& rhs) const { return !(*this == rhs); }
  template <class E>
  static enable_if_t<is_integral_v<E>, Self> from(const E& e) {
    return e >= MAX ? Self(MAX) : Self(T(e));
  }
  template <class E>
  enable_if_t<is_integral_v<E>, Self> pow(E exp) {
    if (value == T(0)) {
      return exp == E(0) ? T(1) : T(0);
    }
    if (value == T(1)) {
      return value;
    }
    if (exp >= sizeof(T) || value == MAX) {
      return MAX;
    }
    return PowBinaryLift(*this, exp);
  }
};
template <class T, T MAX>
OStream& operator<<(OStream& os, const LimitValue<T, MAX>& lv) {
  os << lv.value;
  return os;
}
}  // namespace dalt
namespace dalt {
namespace math {
template <int B>
struct LinearBasis {
  using Type = std::bitset<B>;
  Type map[B];
  int expires[B];
  Type source[B];
  Type set;
  int size() const { return set.count(); }
  const Type& get_set() const { return set; }
  Optional<Type> representation(Type x) const {
    Type ans;
    for (int i = B - 1; i >= 0; i--) {
      if (!x[i] || !set[i]) {
        continue;
      }
      x ^= map[i];
      ans.flip(i);
    }
    if (x == Type()) {
      return ans;
    }
    return {};
  }
  Optional<Type> representation_original(Type x) const {
    Type ans;
    for (int i = B - 1; i >= 0; i--) {
      if (!x[i] || !set[i]) {
        continue;
      }
      x ^= map[i];
      ans ^= source[i];
    }
    if (x == Type()) {
      return ans;
    }
    return {};
  }
  int get_expiry(int i) const { return expires[i]; }
  int min_expiry(Type x) const {
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < B; i++) {
      if (x[i]) {
        ans = Min(ans, expires[i]);
      }
    }
    return ans;
  }
  int max_expiry(Type x) const {
    int ans = std::numeric_limits<int>::min();
    for (int i = 0; i < B; i++) {
      if (x[i]) {
        ans = Max(ans, expires[i]);
      }
    }
    return ans;
  }
  Vec<Type> to_vec() const {
    Vec<Type> ans;
    ans.reserve(size());
    for (int i = B - 1; i >= 0; i--) {
      if (set[i]) {
        ans.push_back(map[i]);
      }
    }
    return ans;
  }
  int add(Type val, int expiry = std::numeric_limits<int>::max()) {
    Type state;
    for (int i = B - 1; i >= 0; i--) {
      if (!val[i] || !set[i]) {
        continue;
      }
      val ^= map[i];
      state ^= source[i];
    }
    if (val != Type()) {
      int log = B - 1;
      while (!val[log]) {
        log--;
      }
      set[log] = true;
      map[log] = val;
      source[log] = state;
      source[log].set(log);
      expires[log] = expiry;
      upward(log);
      return log;
    }
    int min_index = -1;
    int min_expiry = std::numeric_limits<int>::max();
    for (int i = 0; i < B; i++) {
      if (!state[i]) {
        continue;
      }
      if (expires[i] < min_expiry) {
        min_expiry = expires[i];
        min_index = i;
      }
    }
    if (min_expiry < expiry) {
      Type xor_val = state;
      xor_val[min_index] = false;
      for (int i = 0; i < B; i++) {
        if (source[i][min_index]) {
          source[i] ^= xor_val;
        }
      }
      expires[min_index] = expiry;
      return min_index;
    }
    return -1;
  }
  bool contain(Type val) const {
    for (int i = B - 1; i >= 0; i--) {
      if (val[i]) {
        if (!set[i]) {
          return false;
        }
        val ^= map[i];
      }
    }
    return val == Type();
  }
  i64 xor_number_count() const { return i64(1) << size(); }
  Type the_kth(Type k) const {
    int id = 0;
    Type num;
    for (int i = 0; i < B; i++) {
      if (!set[i]) {
        continue;
      }
      if (k[id]) {
        num ^= map[i];
      }
      id++;
    }
    return num;
  }
  Type the_rank(Type n) const {
    int index = size() - 1;
    Type rank;
    for (int i = B - 1; i >= 0; i--) {
      if (!set[i]) {
        continue;
      }
      if (n[i]) {
        rank.set(index);
        n ^= map[i];
      }
      index--;
    }
    return rank;
  }
  Type the_max_xor(Type x) const {
    for (int i = B - 1; i >= 0; i--) {
      if (!set[i]) {
        continue;
      }
      if (!x[i]) {
        x ^= map[i];
      }
    }
    return x;
  }
  Type the_min_xor(Type x) const {
    for (int i = B - 1; i >= 0; i--) {
      if (!map[i]) {
        continue;
      }
      if (x[i]) {
        x ^= map[i];
      }
    }
    return x;
  }
 private:
  void upward(int row) {
    Assert(map[row][row]);
    for (int i = row + 1; i < B; i++) {
      if (map[i][row]) {
        map[i] ^= map[row];
        source[i] ^= source[row];
      }
    }
  }
};
}  // namespace math
}  // namespace dalt
namespace dalt {
/**
 * Linear program class.
 * <br>
 * N constraints and M variables.
 * <br>
 * The target is to find an assignment for each variable to make target
 * expression as large as possible. <br> <pre> Maximize t0+t1*x1+...+tm*xm where
 * following constraint satisfied: c11*x1+...+c1m*xm <= c10
 *   ...
 *   cn1*x1+...+cnm*xm <= cn0
 *   x1, x2, ..., xm >= 0
 * </pre>
 */
struct LinearProgramming {
  double prec;
  Vec<Vec<double>> mat;
  Vec<int> basicVariables;
  Vec<int> basicVariable2RowIndex;
  bool unbound;
  bool infeasible;
  int n;
  int m;
 private:
  void normalize() {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        if (mat[i][j] >= -prec && mat[i][j] <= prec) {
          mat[i][j] = 0;
        }
      }
    }
  }
  void pivot(int variableId, int row) {
    int basicVariableId = basicVariables[row];
    mat[row][basicVariableId] = -1;
    for (int i = 0; i <= m; i++) {
      if (i == variableId) {
        continue;
      }
      mat[row][i] /= -mat[row][variableId];
    }
    mat[row][variableId] = -1;
    basicVariables[row] = variableId;
    basicVariable2RowIndex[basicVariableId] = -1;
    basicVariable2RowIndex[variableId] = row;
    for (int i = 0; i <= n; i++) {
      if (i == row || mat[i][variableId] == 0) {
        continue;
      }
      double c = mat[i][variableId];
      for (int j = 0; j <= m; j++) {
        if (j == variableId) {
          mat[i][j] = 0;
          continue;
        }
        mat[i][j] += mat[row][j] * c;
      }
    }
    normalize();
  }
  bool simplex() {
    int firstPositiveVariableId = -1;
    for (int i = 1; i <= m && firstPositiveVariableId == -1; i++) {
      if (mat[0][i] > 0) {
        firstPositiveVariableId = i;
      }
    }
    if (firstPositiveVariableId == -1) {
      return false;
    }
    double maxConstraint = 1e50;
    int maxConstraintRow = -1;
    for (int i = 1; i <= n; i++) {
      if (mat[i][firstPositiveVariableId] >= 0) {
        continue;
      }
      double constraint = mat[i][0] / (-mat[i][firstPositiveVariableId]);
      if (maxConstraint > constraint) {
        maxConstraint = constraint;
        maxConstraintRow = i;
      }
    }
    if (maxConstraintRow == -1) {
      unbound = true;
      return false;
    }
    pivot(firstPositiveVariableId, maxConstraintRow);
    return true;
  }
 public:
  /**
   *
   * @param n constraint number
   * @param m variable number
   * @param prec precision
   */
  LinearProgramming(int _n, int _m, double _prec) {
    prec = _prec;
    n = _n;
    m = _m + _n;
    unbound = false;
    infeasible = false;
    mat = Vec<Vec<double>>(_n + 1, Vec<double>(m + 2));
    basicVariables = Vec<int>(m + 2);
    basicVariable2RowIndex = Vec<int>(m + 2);
    for (int i = 1; i <= m; i++) {
      if (i <= _m) {
        basicVariable2RowIndex[i] = -1;
      } else {
        basicVariable2RowIndex[i] = i - _m;
        basicVariables[i - _m] = i;
      }
    }
  }
  /**
   * both constraintId and variableId start with 1
   * @param constraintId
   * @param noMoreThan
   */
  void setConstraintConstant(int constraintId, double noMoreThan) {
    mat[constraintId][0] = noMoreThan;
  }
  /**
   * both constraintId and variableId start with 1
   * @param constraintId
   * @param variableId
   * @param c
   */
  void setConstraintCoefficient(int constraintId, int variableId, double c) {
    mat[constraintId][variableId] = -c;
  }
  void setTargetConstant(double c) { mat[0][0] = c; }
  void setTargetCoefficient(int variableId, double c) {
    mat[0][variableId] = c;
  }
  double maxSolution() { return mat[0][0]; }
  bool isInfeasible() { return infeasible; }
  bool isUnbound() { return unbound; }
  double getAssignmentValueForVariable(int i) {
    if (basicVariable2RowIndex[i] == -1) {
      return 0;
    } else {
      return mat[basicVariable2RowIndex[i]][0];
    }
  }
  bool initSimplex() {
    if (n == 0) {
      return true;
    }
    int minConstantRow = 1;
    for (int i = 2; i <= n; i++) {
      if (mat[i][0] < mat[minConstantRow][0]) {
        minConstantRow = i;
      }
    }
    if (mat[minConstantRow][0] >= 0) {
      return true;
    }
    auto originalTargetExpression = mat[0];
    m++;
    mat[0] = Vec<double>(m + 1);
    mat[0][m] = -1;
    basicVariable2RowIndex[m] = -1;
    for (int i = 1; i <= n; i++) {
      mat[i][m] = 1;
    }
    pivot(m, minConstantRow);
    while (simplex())
      ;
    if (mat[0][0] != 0 || unbound) {
      infeasible = true;
      unbound = false;
      return false;
    }
    if (basicVariable2RowIndex[m] != -1) {
      int row = basicVariable2RowIndex[m];
      int firstNegativeVariable = -1;
      for (int i = 1; i <= m && firstNegativeVariable == -1; i++) {
        if (mat[row][i] != 0) {
          firstNegativeVariable = i;
        }
      }
      pivot(firstNegativeVariable, row);
    }
    // restore
    m--;
    mat[0] = originalTargetExpression;
    for (int i = 1; i <= m; i++) {
      if (basicVariable2RowIndex[i] == -1) {
        continue;
      }
      int row = basicVariable2RowIndex[i];
      double c = mat[0][i];
      for (int j = 0; j <= m; j++) {
        if (j == i) {
          mat[0][j] = 0;
          continue;
        }
        mat[0][j] += mat[row][j] * c;
      }
    }
    normalize();
    return true;
  }
  void solve() {
    if (!initSimplex()) {
      return;
    }
    while (simplex())
      ;
  }
};
/**
 * <br>
 * N constraints and M variables.
 * <br>
 * The target is to find an assignment for each variable to make target
 * expression as large as possible. <br> <pre> Minimize t0+t1*x1+...+tm*xm where
 * following constraint satisfied: c11*x1+...+c1m*xm >= c10
 *   ...
 *   cn1*x1+...+cnm*xm >= cn0
 *   x1, x2, ..., xm >= 0
 * </pre>
 */
struct DualLinearProgramming {
  LinearProgramming lp;
  int n;
  int m;
  DualLinearProgramming(int _n, int _m, double prec) : lp(_m, _n, prec) {
    n = _n;
    m = _m;
  }
  void setConstraintConstant(int constraintId, double noMoreThan) {
    lp.setTargetCoefficient(constraintId, noMoreThan);
  }
  void setConstraintCoefficient(int constraintId, int variableId, double c) {
    lp.setConstraintCoefficient(variableId, constraintId, c);
  }
  void setTargetConstant(double c) { lp.setTargetConstant(c); }
  void setTargetCoefficient(int variableId, double c) {
    lp.setConstraintConstant(variableId, c);
  }
  void solve() { lp.solve(); }
  double minSolution() { return lp.maxSolution(); }
  bool isInfeasible() { return lp.isUnbound(); }
  bool isUnbound() { return lp.isInfeasible(); }
  double getAssignmentValueForVariable(int i) {
    if (i + n <= lp.m) {
      return -lp.mat[0][i + n];
    } else {
      return 0;
    }
  }
};
}  // namespace dalt
namespace dalt {
namespace poly {
// lr = {1, -c1, -c2, ...}
// consider from last bit to first bit
template <class Poly, class T>
T KthTermOfLinearRecurrence(int n, const Indexer<int>& indexer, Vec<T> lr,
                            Vec<T> prefix) {
  static_assert(is_polynomial_v<Poly>);
  static_assert(is_same_v<T, typename Poly::Type>);
  let rank = Size(lr) - 1;
  Poly Q(Move(lr));
  Poly F(Move(prefix));
  Poly P = (Q * F).modular(rank);
  return KthTermOfInversePolynomial<Poly>(n, indexer, P, Q);
}
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace ds {
template <class T>
struct LinkedNode {
  using Self = LinkedNode<T>;
  using Node = Self;
  T data;
  Node *next;
  Node *prev;
  LinkedNode(T _data = T()) : data(_data) { next = prev = this; }
  void append(Node *b) {
    Assert(b->is_single());
    Node *a = this;
    b.next = a.next;
    b.next.prev = b;
    a.next = b;
    b.prev = a;
  }
  void detach(Node *a) {
    a.prev.next = a.next;
    a.next.prev = a.prev;
    a.prev = a.next = a;
  }
  bool is_single() const { return next == this; }
};
template <class T>
struct LinkedList {
  using Self = LinkedList<T>;
  using Node = LinkedNode<T>;
  Node *head;
  int size;
  LinkedList(T nil = T()) {
    size = 0;
    head = new Node(nil);
  }
  void push_back(Node *node) {
    size++;
    head->prev->append(node);
  }
  void push_front(Node *node) {
    size++;
    head->next->append(node);
  }
  void append(Node *a, Node *b) {
    a->append(b);
    size++;
  }
  void detach(Node *node) {
    node->detach();
    size--;
  }
  int get_size() const { return size; }
  bool empty() const { return size == 0; }
  Node *front() { return head->next; }
  Node *back() { return head->prev; }
  Node *guard() { return head; }
  const Node *front() const { return head->next; }
  const Node *back() const { return head->prev; }
  void pop_front() {
    head->next->detach();
    size--;
  }
  void pop_back() {
    head->prev->detach();
    size--;
  }
};
}  // namespace ds
}  // namespace dalt
namespace dalt {
namespace misc {
template <class T, bool E>
struct OptionalField {};
template <class T>
struct OptionalField<T, true> {
  T value;
  T& operator->() { return value; }
  const T& operator->() const { return value; }
  T& operator*() { return value; }
  const T& operator*() const { return value; }
};
}  // namespace misc
}  // namespace dalt
namespace dalt {
namespace sbt {
template <class S, class U, bool EXIST, class REG>
struct SbtReverse {
  static_assert(is_sbt_registry_v<REG>);
  using Self = SbtReverse<S, U, EXIST, REG>;
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
namespace dalt {
namespace sbt {
template <class SBT, class S, class U, bool DIR = false, i64 ID = 0>
struct LCTNode
    : protected SbtReverse<S, U, DIR, SBT> {
  static_assert(is_sbt_registry_v<SBT>);
  using Self = LCTNode<SBT, S, U, DIR, ID>;
  static Self *NIL;
  Self *left;
  Self *right;
  Self *father;
  Self *tree_father;
  S sum;
  S weight;
  U upd;
  bool rev;
  i32 id;
  int tree_size;
  int vtree_size;
  i8 tree_weight;
  LCTNode(int _id = 0, const S &_weight = SBT::s_nil,
          const U &_upd = SBT::u_nil, i8 _tree_weight = 1) {
    init(_id, _weight, _upd, _tree_weight);
  }
  void init(int _id = 0, const S &_weight = SBT::s_nil,
            const U &_upd = SBT::u_nil, i8 _tree_weight = 1) {
    id = _id;
    left = right = father = tree_father = NIL;
    rev = false;
    tree_size = vtree_size = 0;
    sum = weight = _weight;
    upd = _upd;
    tree_weight = _tree_weight;
    this->init_sum_rev(_weight);
  }
  static void Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
                       const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    if (NIL != NULL) {
      delete NIL;
    }
    NIL = new LCTNode(-1, _s_nil, _u_nil, 0);
    NIL->left = NIL->right = NIL->father = NIL->tree_father = NIL;
    SBT::Register(_s_nil, _u_nil, _s_s, _s_u,  _u_u);
  }
  void reverse() {
    rev = !rev;
    this->swap_sum_rev(sum);
  }
  void set_left(Self *x) {
    left = x;
    x->father = this;
  }
  void set_right(Self *x) {
    right = x;
    x->father = this;
  }
  void change_child(Self *y, Self *x) {
    if (left == y) {
      set_left(x);
    } else {
      set_right(x);
    }
  }
  static void zig(Self *x) {
    Self *y = x->father;
    Self *z = y->father;
    Self *b = x->right;
    y->set_left(b);
    x->set_right(y);
    z->change_child(y, x);
    y->push_up();
  }
  static void zag(Self *x) {
    Self *y = x->father;
    Self *z = y->father;
    Self *b = x->left;
    y->set_right(b);
    x->set_left(y);
    z->change_child(y, x);
    y->push_up();
  }
  void modify(const U &upd) {
    Self *x = this;
    if (x == NIL) {
      return;
    }
    x->sum = SBT::s_u(x->sum, upd);
    x->weight = SBT::s_u(x->weight, upd);
    x->upd = SBT::u_u(x->upd, upd);
    this->apply_sum_rev(upd);
  }
  static void access(Self *x) {
    Self *last = NIL;
    while (x != NIL) {
      splay(x);
      x->right->father = NIL;
      x->right->tree_father = x;
      x->vtree_size += x->right->tree_size;
      x->set_right(last);
      x->vtree_size -= last->tree_size;
      x->push_up();
      last = x;
      x = x->tree_father;
    }
  }
  static void make_root(Self *x) {
    access(x);
    splay(x);
    x->reverse();
  }
  static void cut(Self *y, Self *x) {
    make_root(y);
    access(x);
    splay(y);
    y->right->tree_father = NIL;
    y->right->father = NIL;
    y->set_right(NIL);
    y->push_up();
  }
  static void join(Self *y, Self *x) {
    make_root(x);
    make_root(y);
    x->tree_father = y;
    y->vtree_size += x->tree_size;
    y->push_up();
  }
  static void find_path(Self *x, Self *y) {
    make_root(x);
    access(y);
  }
  static void splay(Self *x) {
    if (x == NIL) {
      return;
    }
    Self *y, *z;
    while ((y = x->father) != NIL) {
      if ((z = y->father) == NIL) {
        y->push_down();
        x->push_down();
        if (x == y->left) {
          zig(x);
        } else {
          zag(x);
        }
      } else {
        z->push_down();
        y->push_down();
        x->push_down();
        if (x == y->left) {
          if (y == z->left) {
            zig(y);
            zig(x);
          } else {
            zig(x);
            zag(x);
          }
        } else {
          if (y == z->left) {
            zag(x);
            zig(x);
          } else {
            zag(y);
            zag(x);
          }
        }
      }
    }
    x->push_down();
    x->push_up();
  }
  Vec<Pair<int, S>> to_vec_sub_tree() const {
    Vec<Pair<int, S>> data;
    travel([&](auto a, auto b) { data.push_back({a, b}); });
    return data;
  }
  Vec<Pair<int, S>> to_vec_tree() const {
    const Self *root = this;
    while (root->father != NIL) {
      root = root->father;
    }
    return root->to_vec_sub_tree();
  }
  static Self *find_root(Self *x) {
    splay(x);
    x->push_down();
    while (x->left != NIL) {
      x = x->left;
      x->push_down();
    }
    splay(x);
    return x;
  }
  static const Self *find_root_slow(const Self *x) {
    while (x->father != NIL) {
      x = x->father;
    }
    return x;
  }
  void travel(const BiConsumer<int, S> &consumer, bool rev = false,
              const U &upd = SBT::u_nil) const {
    const Self *root = this;
    if (root == NIL) {
      return;
    }
    if (root->rev) {
      rev = !rev;
    }
    U new_upd = SBT::u_u(root->upd, upd);
    (rev ? root->right : root->left)->travel(consumer, rev, new_upd);
    consumer(root->id, SBT::s_u(root->weight, upd));
    (rev ? root->left : root->right)->travel(consumer, rev, new_upd);
  }
  void push_down() {
    Self *root = this;
    if (root == NIL) {
      return;
    }
    if (root->rev) {
      root->rev = false;
      Self *tmpNode = root->left;
      root->left = root->right;
      root->right = tmpNode;
      root->left->reverse();
      root->right->reverse();
    }
    root->left->tree_father = root->tree_father;
    root->right->tree_father = root->tree_father;
    if (root->upd != NIL->upd) {
      root->left->modify(root->upd);
      root->right->modify(root->upd);
      root->upd = NIL->upd;
    }
  }
  void push_up() {
    Self *root = this;
    if (root == NIL) {
      return;
    }
    root->sum =
        SBT::s_s(SBT::s_s(root->left->sum, root->weight), root->right->sum);
    this->push_up_sum_rev(*(root->left), *(root->right));
    root->tree_size = root->left->tree_size + root->right->tree_size +
                      root->vtree_size + root->tree_weight;
  }
  static Self *lca(Self *a, Self *b) {
    if (a == b) {
      return a;
    }
    access(a);
    splay(a);
    access(b);
    splay(b);
    if (a->tree_father != NIL) {
      return a->tree_father;
    }
    if (a->father != NIL) {
      // in same splay
      return a;
    }
    return NIL;
  }
  static bool connected(Self *a, Self *b) {
    return lca(a, b) != NIL;
    //        makeRoot(a);
    //        access(b);
    //        splay(b);
    //        return findRoot(b) == a;
  }
};
template <class SBT, class S, class U, bool DIR, i64 ID>
LCTNode<SBT, S, U, DIR, ID> *LCTNode<SBT, S, U, DIR, ID>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
namespace dalt {
namespace graph {
// O(V)
Vec<bool> MaximumIndependentSetFromMinimumVertexCover(Vec<bool> minimum_vertex_cover) {
  for (int i = 0; i < Size(minimum_vertex_cover); i++) {
    minimum_vertex_cover[i] = !minimum_vertex_cover[i];
  }
  return minimum_vertex_cover;
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Vec<bool>) LongestAntiChain(const Graph<E>& g) {
  int n = Size(g);
  Graph<BiBaseEdge> bg(n * 2);
  Vec<bool> visit(n);
  for (int i = 0; i < n; i++) {
    Deque<int> dq;
    Fill(All(visit), false);
    visit[i] = true;
    dq.push_back(i);
    while (!dq.empty()) {
      int head = dq.front();
      dq.pop_front();
      for (auto& e : g[head]) {
        if (!visit[e.to]) {
          visit[e.to] = true;
          dq.push_back(e.to);
        }
      }
    }
    for (int j = 0; j < n; j++) {
      if (j != i && visit[j]) {
        AddBiEdge(bg, i, j + n);
      }
    }
  }
  auto mates = BipartiteMatch(bg);
  Vec<bool> color(n * 2);
  for (int i = 0; i < n; i++) {
    color[i] = true;
  }
  Vec<bool> min_vertex_cover = BipartiteMinimumVertexCover(bg, mates, color);
  Vec<bool> max_independent_set =
      MaximumIndependentSetFromMinimumVertexCover(Move(min_vertex_cover));
  Vec<bool> longest_antichain(n);
  for (int i = 0; i < n; i++) {
    if (max_independent_set[i] && max_independent_set[i + n]) {
      longest_antichain[i] = true;
    }
  }
  return longest_antichain;
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
namespace seq {
template <class T = char>
struct SuffixAutomaton {
  struct Node {
    TreeMap<T, Node*> next;
    Node* fail;
    i32 maxlen;
    i32 id;
    i32 get_max_length() { return maxlen; }
    i32 get_min_length() { return fail == NULL ? 0 : fail->maxlen + 1; }
    Node() : fail(NULL), maxlen(0) {}
  };
  struct Right {
    i32 cnt;
    i32 leftest_right;
    i32 rightest_right;
    Right()
        : leftest_right(std::numeric_limits<i32>::max()),
          rightest_right(std::numeric_limits<i32>::min()) {}
  };
  struct Matcher {
    SuffixAutomaton* sa;
    Node* match_last;
    i32 match_length;
    void match(T c) {
      T index = c;
      auto candidate = GetOrDefault<Node*>(match_last->next, index, NULL);
      if (candidate != NULL) {
        match_last = candidate;
        match_length = match_length + 1;
        return;
      }
      while (match_last != NULL &&
             (candidate = GetOrDefault<Node*>(match_last->next, index, NULL)) ==
                 NULL) {
        match_last = match_last->fail;
      }
      if (match_last == NULL) {
        match_last = sa->root;
        match_length = 0;
      } else {
        match_length = match_last->maxlen + 1;
        match_last = candidate;
      }
    }
  };
  Matcher matcher() {
    return Matcher{
        .sa = this,
        .match_last = root,
        .match_length = 0,
    };
  }
  Node* build_last;
  Vec<Node*> all;
 private:
  Node* root;
  i64 distinct_substr;
  bool sorted;
  Node* add_node(Node* node) {
    all.push_back(node);
    all.back()->id = Size(all) - 1;
    return node;
  }
  Node* alloc() { return add_node(new Node()); }
  Node* clone(Node* id) { return add_node(new Node(*id)); }
 public:
  void enable_distinct_substr() {
    if (distinct_substr == -1) {
      distinct_substr = 0;
    }
  }
  decltype(distinct_substr) get_distinct_substr() const {
    return distinct_substr;
  }
  SuffixAutomaton(i32 cap) : distinct_substr(-1) {
    all.reserve(cap + 1);
    build_last = root = alloc();
  }
  Node* visit(T index, Node* trace, Node* target, Node* replacement) {
    while (trace != NULL &&
           GetOrDefault<Node*>(trace->next, index, NULL) == target) {
      trace->next[index] = replacement;
      trace = trace->fail;
    }
    return trace;
  } 
  void build_next() { build_last = root; }
  void build(T c) {
    sorted = false;
    T index = c;
    Node* candidate = build_last->next[c];
    //generic sam
    if (candidate != NULL && build_last->maxlen == candidate->maxlen + 1) {
      build_last = candidate;
      return;
    }
    auto now = alloc();
    now->maxlen = build_last->maxlen + 1;
    Node* p = visit(index, build_last, NULL, now);
    build_last = now;
    if (p == NULL) {
      now->fail = root;
    } else {
      auto q = p->next[index];
      if (q->maxlen == p->maxlen + 1) {
        now->fail = q;
      } else {
        auto clone = this->clone(q);
        clone->maxlen = p->maxlen + 1;
        now->fail = q->fail = clone;
        if (distinct_substr != -1) {
          distinct_substr -= q->maxlen - clone->fail->maxlen;
          distinct_substr += q->maxlen - q->fail->maxlen;
          distinct_substr += clone->maxlen - clone->fail->maxlen;
        }
        visit(index, p, q, clone);
        //generic sam
        if (p->maxlen + 1 == now->maxlen) {
          build_last = clone;
        }
      }
    }
    if (distinct_substr != -1) {
      distinct_substr += now->maxlen - now->fail->maxlen;
    }
  }
  Vec<Node*>& topo_sort() {
    if (sorted) {
      return all;
    }
    sorted = true;
    Vec<i32> indeg(Size(all));
    Deque<Node*> dq;
    for (auto node : all) {
      if (node->fail != NULL) {
        indeg[node->fail->id]++;
      }
    }
    for (auto node : all) {
      if (indeg[node->id] == 0) {
        dq.push_back(node);
      }
    }
    all.clear();
    while (!dq.empty()) {
      auto head = dq.front();
      dq.pop_front();
      all.push_back(head);
      if (head->fail != NULL) {
        indeg[head->fail->id]--;
        if (indeg[head->fail->id] == 0) {
          dq.push_back(head->fail);
        }
      }
    }
    return all;
  }
  Vec<Right> calculate_right(const Indexer<T>& s, int n) {
    topo_sort();
    Vec<Right> res(n);
    Matcher matcher = this->matcher();
    for (int i = 0; i < n; i++) {
      matcher.match(s(i));
      i32 id = matcher.match_last->id;
      res[id].cnt++;
      res[id].leftest_right = Min(res[id].leftest_right, i);
      res[id].rightest_right = Max(res[id].rightest_right, i);
    }
    for (auto node : all) {
      if (node->fail != NULL) {
        i32 id = node->id;
        i32 fid = node->fail->id;
        res[fid].cnt += res[id].cnt;
        res[fid].leftest_right =
            Min(res[fid].leftest_right, res[id].leftest_right);
        res[fid].rightest_right =
            Max(res[fid].rightest_right, res[id].rightest_right);
      }
    }
    return res;
  }
};
}  // namespace seq
}  // namespace dalt
namespace dalt {
namespace seq {
template <class T = String, class C = char>
i32 LongestCommonSubstr(const Vec<T> &ss) {
  i32 min_index =
      std::min_element(All(ss),
                       [&](auto &a, auto &b) { return Size(a) < Size(b); }) -
      ss.begin();
  SuffixAutomaton<C> sa(Size(ss[min_index]));
  for (char c : ss[min_index]) {
    sa.build(c);
  }
  auto &topo = sa.topo_sort();
  Vec<i32> global_min_match(Size(topo));
  Vec<i32> cur_match(Size(topo));
  for (auto &node : topo) {
    global_min_match[node->id] = node->get_max_length();
  }
  for (int i = 0; i < Size(ss); i++) {
    if (i == min_index) {
      continue;
    }
    auto &s = ss[i];
    auto matcher = sa.matcher();
    Fill(All(cur_match), 0);
    for (char c : s) {
      matcher.match(c);
      i32 id = matcher.match_last->id;
      cur_match[id] = Max(cur_match[id], matcher.match_length);
    }
    for (auto &node : topo) {
      i32 id = node->id;
      if (node->fail) {
        i32 fid = node->fail->id;
        cur_match[fid] = Max(cur_match[fid], cur_match[id]);
      }
      global_min_match[id] = Min(global_min_match[id], cur_match[id]);
    }
  }
  auto ans = *MaxElement(All(global_min_match));
  return ans;
}
}  // namespace seq
}  // namespace dalt
namespace dalt {
namespace graph {
// credited to:
// https://github.com/indy256/codelibrary/blob/master/java/graphs/lca/LcaSchieberVishkin.java
template <class E>
struct LowestCommonAncestorBySchieberVishkin {
  static_assert(is_base_of_v<BiBaseEdge, E>);
 private:
  Vec<int> parent;
  Vec<int> pre_order;
  Vec<int> i;
  Vec<int> head;
  Vec<int> a;
  int time;
  const Graph<E> &tree;
  void dfs1(int u, int p) {
    parent[u] = p;
    i[u] = pre_order[u] = time++;
    for (auto &e : tree[u]) {
      int v = e.to;
      if (v == p) continue;
      dfs1(v, u);
      if (LowestOneBit(i[u]) < LowestOneBit(i[v])) {
        i[u] = i[v];
      }
    }
    head[i[u]] = u;
  }
  void dfs2(int u, int p, int up) {
    a[u] = up | LowestOneBit(i[u]);
    for (auto &e : tree[u]) {
      int v = e.to;
      if (v == p) continue;
      dfs2(v, u, a[u]);
    }
  }
  int enter_into_strip(int x, int hz) {
    if (LowestOneBit(i[x]) == hz) return x;
    int hw = 1 << Log2Floor(u32(a[x] & (hz - 1)));
    return parent[head[i[x] & -hw | hw]];
  }
 public:
  LowestCommonAncestorBySchieberVishkin(const Graph<E> &_tree,
                                        const Checker<int> &is_root)
      : tree(_tree) {
    int n = Size(tree);
    pre_order = Vec<int>(n);
    i = Vec<int>(n);
    head = Vec<int>(n);
    a = Vec<int>(n);
    parent = Vec<int>(n);
    time = 0;
    for (int i = 0; i < n; i++) {
      if (is_root(i)) {
        dfs1(i, -1);
        dfs2(i, -1, 0);
      }
    }
  }
  int lca(int x, int y) {
    int hb =
        i[x] == i[y] ? LowestOneBit(i[x]) : (1 << Log2Floor(u32(i[x] ^ i[y])));
    int hz = LowestOneBit(a[x] & a[y] & -hb);
    int ex = enter_into_strip(x, hz);
    int ey = enter_into_strip(y, hz);
    return pre_order[ex] < pre_order[ey] ? ex : ey;
  }
};
}  // namespace graph
}  // namespace dalt
namespace dalt {
template <class T> struct LinearFeedbackShiftRegister {
  Vec<T> cm;
  i32 m;
  T dm;
  Vec<T> cn;
  Vec<T> seq;
  LinearFeedbackShiftRegister(i32 cap) {
    seq.reserve(cap + 1);
    m = -1;
    cn.push_back(T(1));
  }
  void push(T x) {
    let n = Size(seq);
    seq.push_back(x);
    let dn = estimate_delta();
    if(dn == T(0)) {
      return;
    }
    if(m == -1) {
      cm = cn;
      dm = dn;
      m = n;
      cn.resize(n + 2, T(0));
      return;
    }
    let ln = Size(cn) - 1;
    let len = Max(ln, n + 1 - ln);
    let buf = Vec<T>(len + 1);
    for(int i = 0; i < Size(cn); i++) {
      buf[i] = cn[i];
    }
    T factor = dn / dm;
    for(int i = n - m, R = n - m + Size(cm); i < R; i++) {
      buf[i] = buf[i] - factor * cm[i - (n - m)];
    }
    if(Size(cn) < Size(buf)) {
      cn.swap(cm);
      m = n;
      dm = dn;
    }
    cn = buf;
  }
  //[1, -c1, -c2, ...]
  const Vec<T>& to_vec() const {
    return cn;
  }
private:
  T estimate_delta() const {
    T ans = T(0);
    i32 n = Size(seq) - 1;
    for (int i = 0; i < Size(cn); i++) {
      ans = ans + cn[i] * seq[n - i];
    }
    return ans;
  }
};
} // namespace dalt
namespace dalt {
namespace seq {
template <class T>
// ret[0][i] * 2     = the longest palindrom centered at i - 1 and i with even length
// ret[1][i] * 2 - 1 = the longest palindrom centered at i with odd length
//- time: O(n)
Array<Vec<i32>, 2> Manacher(const Indexer<T> &s, int n) {
  Array<Vec<i32>, 2> res;
  {
    Vec<i32> ans(n);
    int c = -1;
    int mx = -1;
    ans[0] = 0;
    for (int i = 1; i < n; i++) {
      int len = 0;
      if (mx >= i) {
        int mirror = c - (i - c);
        len = Min(ans[mirror], mx - (i - 1));
      }
      while (i - (len + 1) >= 0 && i - 1 + (len + 1) < n &&
             s(i - (len + 1)) == s(i - 1 + (len + 1))) {
        len++;
      }
      ans[i] = len;
      if (mx < i - 1 + len) {
        mx = i - 1 + len;
        c = i;
      }
    }
    res[0] = Move(ans);
  }
  {
    Vec<i32> ans(n);
    int c = -1;
    int mx = -1;
    for (int i = 0; i < n; i++) {
      int len = 0;
      if (mx > i) {
        int mirror = c - (i - c);
        len = Min(ans[mirror] - 1, mx - i);
      }
      while (i - (len + 1) >= 0 && i + (len + 1) < n &&
             s(i - (len + 1)) == s(i + (len + 1))) {
        len++;
      }
      ans[i] = len + 1;
      if (mx < i + len) {
        mx = i + len;
        c = i;
      }
    }
    res[1] = Move(ans);
  }
  return res;
}
}  // namespace seq
}  // namespace dalt
namespace dalt {
template <class Modular> struct ModIntSum {
  static_assert(is_modular_v<Modular>);
  using Type = typename Modular::Type;
  static_assert(is_same_v<i32, Type>);
  void add(i64 x) {
    if (x >= 0) {
      if (sum + x < sum) {
        sum %= Modular::modulus;
      }
      sum += x;
    } else {
      if (sum + x > sum) {
        sum %= Modular::modulus;
      }
      sum += x;
    }
  }
  ModInt<Modular> get() {
    normalize();
    return ModInt<Modular>(sum);
  }
  ModIntSum() : sum(0) {}
private:
  i64 sum;
  void normalize() {
    if (sum < -Modular::modulus || sum >= Modular::modulus) {
      sum %= Modular::modulus;
    }
    if (sum < 0) {
      sum += Modular::modulus;
    }
  }
};
} // namespace dalt
namespace dalt {
namespace math {
template <class T>
struct Matrix {
  using Self = Matrix<T>;
  Vec<T> data;
  int m;
  Matrix(int _m, Vec<T> _data) : m(_m), data(Move(_data)) {}
  Matrix(int _n, int _m) : data(_n * _m), m(_m) {}
  Matrix() : Matrix(0, 0) {}
  static Self mul_identity(int n) {
    Self res(n, n);
    for (int i = 0; i < n; i++) {
      res[i][i] = T(1);
    }
    return res;
  }
  T *operator[](int i) { return data.data() + i * m; }
  const T *operator[](int i) const { return data.data() + i * m; }
  Array<i32, 2> shape() const { return {Size(data) / m, m}; }
  i32 row_num() const { return Size(data) / m; }
  i32 col_num() const { return m; }
  bool square() const { return row_num() == col_num(); }
  Self operator+(const Self &rhs) const {
    const Self &lhs = *this;
    Assert(lhs.shape() == rhs.shape());
    int n = Size(lhs.data);
    Self res(lhs.row_num(), lhs.col_num());
    for (int i = 0; i < n; i++) {
      res[i][0] = lhs[i][0] + rhs[i][0];
    }
    return res;
  }
  Self operator-(const Self &rhs) const {
    const Self &lhs = *this;
    Assert(lhs.shape() == rhs.shape());
    int n = Size(lhs.data);
    Self res(lhs.row_num(), lhs.col_num());
    for (int i = 0; i < n; i++) {
      res[i][0] = lhs[i][0] - rhs[i][0];
    }
    return res;
  }
  Self operator/(const Self &rhs) const {
    return *this * (*rhs.possible_inv());
  }
  template <class V = T>
  enable_if_t<is_same_v<V, T> &&
                  !(is_modint_v<T> && is_same_v<i32, typename T::Type>),
              Self>
  operator*(const Self &rhs) const {
    const Self &lhs = *this;
    Assert(lhs.col_num() == rhs.row_num());
    int n = lhs.row_num();
    int mid = lhs.col_num();
    int m = rhs.col_num();
    Self res(n, m);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < mid; k++) {
        for (int j = 0; j < m; j++) {
          res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
        }
      }
    }
    return res;
  }
  // fast way to achievc matrix mutiplication, reduce the number of modular
  // operation
  template <class V = T>
  enable_if_t<is_same_v<V, T> &&
                  (is_modint_v<T> && is_same_v<i32, typename T::Type>),
              Self>
  operator*(const Self &rhs) const {
    using Modular = typename T::Modular;
    const Self &lhs = *this;
    Assert(lhs.col_num() == rhs.row_num());
    int n = lhs.row_num();
    int mid = lhs.col_num();
    int m = rhs.col_num();
    Vec<u128> accummulate(n * m);
    u64 threshold = std::numeric_limits<u64>::max() -
                    u64(Modular::modulus - 1) * u64(Modular::modulus - 1);
    Self res(n, m);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < mid; k++) {
        for (int j = 0; j < m; j++) {
          i32 ij = i * m + j;
          accummulate[ij] += u64(lhs[i][k].value) * rhs[k][j].value;
        }
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        res[i][j] = accummulate[i * m + j].modular(Modular::modulus);
      }
    }
    return res;
  }
  bool operator==(const Self &rhs) const {
    return col_num() == rhs.col_num() && data == rhs.data;
  }
  bool operator!=(const Self &rhs) const {
    return !(*this == rhs);
  }
  T determinant() const {
    Assert(row_num() == col_num());
    Self self = *this;
    let n = m;
    let ans = T(1);
    for (int i = 0; i < n; i++) {
      let max_row = i;
      for (int j = i; j < n; j++) {
        if (self[j][i] != T(0)) {
          max_row = j;
          break;
        }
      }
      if (self[max_row][i] == T(0)) {
        return T(0);
      }
      if (i != max_row) {
        self.row_swap(i, max_row);
        ans = T(0) - ans;
      }
      ans = ans * self[i][i];
      self.row_mul(i, T(1) / self[i][i]);
      for (int j = i + 1; j < n; j++) {
        if (self[j][i] == T(0)) {
          continue;
        }
        let f = T(0) - self[j][i];
        self.row_add(j, i, f);
      }
    }
    return ans;
  }
  Optional<Self> possible_inv() const {
    if (row_num() != col_num()) {
      return {};
    }
    let n = row_num();
    Self l = *this;
    Self r = mul_identity(n);
    for (int i = 0; i < n; i++) {
      let max_row = i;
      for (int j = i; j < n; j++) {
        if (l[j][i] != T(0)) {
          max_row = j;
          break;
        }
      }
      if (l[max_row][i] == T(0)) {
        return {};
      }
      l.row_swap(i, max_row);
      r.row_swap(i, max_row);
      let inv = T(1) / l[i][i];
      r.row_mul(i, inv);
      l.row_mul(i, inv);
      for (int j = 0; j < n; j++) {
        if (i == j) {
          continue;
        }
        if (l[j][i] == T(0)) {
          continue;
        }
        r.row_add(j, i, T(0) - l[j][i]);
        l.row_add(j, i, T(0) - l[j][i]);
      }
    }
    return {r};
  }
  template <class E>
  enable_if_t<is_integral_v<E>, Self> pow(E exp) {
    if (exp == 0) {
      return Self::mul_identity(col_num());
    }
    auto res = pow(exp / 2);
    res = res * res;
    if (exp % 2 == 1) {
      res = res * (*this);
    }
    return res;
  }
 private:
  void row_swap(int i, int j) {
    T *offset_i = (*this)[i];
    T *offset_j = (*this)[j];
    for (int k = 0; k < m; k++) {
      Swap(offset_i[k], offset_j[k]);
    }
  }
  void row_mul(int r, T x) {
    T *ptr = (*this)[r];
    for (int k = 0; k < m; k++) {
      ptr[k] = ptr[k] * x;
    }
  }
  void row_add(int r, T x) {
    T *ptr = (*this)[r];
    for (int k = 0; k < m; k++) {
      ptr[k] = ptr[k] + x;
    }
  }
  void row_add(int a, int b, T f) {
    T *ptr_a = (*this)[a];
    T *ptr_b = (*this)[b];
    for (int i = 0; i < m; i++) {
      ptr_a[i] = ptr_a[i] + ptr_b[i] * f;
    }
  }
public:
  Vec<Vec<T>> to_vec() const {
    Vec<Vec<T>> res(row_num(), Vec<T>(col_num()));
    for (int i = 0; i < row_num(); i++) {
      for (int j = 0; j < col_num(); j++) {
        res[i][j] = (*this)[i][j];
      }
    }
    return res;
  }
  ImplArithmeticAssignOperation(Self);
};
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace graph {
template <class T, class E>
IsFlow(E, Tuple<Vec<int> COMMA Vec<int>>)
AugmentPathBfs(const Graph<E> &g, int t, int inf) {
  int n = Size(g);
  Vec<int> dist(n, inf);
  Vec<int> prev(n, -1);
  Deque<int> dq;
  dq.push_back(t);
  dist[t] = 0;
  while (!dq.empty()) {
    int head = dq.front();
    dq.pop_front();
    for (auto &e : g[head]) {
      if (e.flow == 0) {
        continue;
      }
      if (dist[e.to] > dist[head] + 1) {
        dist[e.to] = dist[head] + 1;
        prev[e.to] = head;
        dq.push_back(e.to);
      }
    }
  }
  return Tuple<Vec<int>, Vec<int>>(dist, prev);
}
template <class E>
IsFlow(E, typename E::flow_type)
    MaxFlowDinic(Graph<E> &g, int s, int t, typename E::flow_type send) {
  using T = typename E::flow_type;
  T remain = send;
  int n = Size(g);
  Vec<int> iters(n);
  Vec<int> dist;
  auto dfs = [&](auto &dfs, int root, T flow) {
    if (root == t) {
      return flow;
    }
    T snapshot = flow;
    while (iters[root] >= 0 && flow != 0) {
      auto &e = g[root][iters[root]];
      auto &rev_e = g[e.to][e.rev];
      if (dist[e.to] + 1 == dist[root] && rev_e.flow > 0) {
        T sent = dfs(dfs, e.to, Min(rev_e.flow, flow));
        if (sent != 0) {
          flow -= sent;
          PushFlow(g, e, sent);
          continue;
        }
      }
      iters[root]--;
    }
    return snapshot - flow;
  };
  int inf = (int)1e9;
  while (remain > 0) {
    dist = std::get<0>(AugmentPathBfs<T, E>(g, t, inf));
    if (dist[s] == inf) {
      break;
    }
    for (int i = 0; i < n; i++) {
      iters[i] = Size(g[i]) - 1;
    }
    remain -= dfs(dfs, s, remain);
  }
  return send - remain;
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace graph {
template <class T, class E>
enable_if_t<is_base_of_v<DiBaseEdge, E>, Tuple<T, Vec<bool>>>
MaxIndependentSet(const Graph<E> &g, const Vec<T> &weights) {
  int n = Size(weights);
  Assert(n <= 60);
  Vec<Vec<bool>> edges(n, Vec<bool>(n));
  for(int i = 0; i < n; i++) {
    for(auto &e : g[i]) {
      edges[e.to][i] = edges[i][e.to] = true;
    }
  }
  Vec<u64> adj(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        continue;
      }
      if (edges[i][j] || edges[j][i]) {
        adj[i] = SetBit(adj[i], j);
      }
    }
  }
  int left_half = (n + 1) / 2;
  int right_half = n - left_half;
  Vec<int> subsets(1 << left_half);
  Vec<T> left_sum(1 << left_half);
  int log = 0;
  for (int i = 1; i < 1 << left_half; i++) {
    while((1 << (log + 1)) <= i) {
        log++;
    }
    int highest = 1 << log;
    left_sum[i] = left_sum[i - highest] + weights[log];
    subsets[i] = subsets[i - highest];
    int possible = subsets[(int)((i - highest) & (~adj[log]))];
    if (left_sum[subsets[i]] < left_sum[possible] + weights[log]) {
      subsets[i] = possible | highest;
    }
  }
  int mask = (1 << left_half) - 1;
  Vec<T> right_sum(1 << right_half);
  Vec<u64> nearby(1 << right_half);
  u64 solution = subsets[mask];
  T ans = left_sum[subsets[mask]];
  T inf = std::numeric_limits<T>::max() / 2;
  log = 0;
  for (int i = 1; i < 1 << right_half; i++) {
        while((1 << (log + 1)) <= i) {
        log++;
    }
    int highest = 1 << log;
    right_sum[i] = KthBit(nearby[i - highest], left_half + log) == 1
                       ? -inf
                       : (right_sum[i - highest] + weights[left_half + log]);
    nearby[i] = nearby[i - highest] | adj[left_half + log];
    int leftSubset = subsets[(int)(mask & (~nearby[i]))];
    T cand = right_sum[i] + left_sum[leftSubset];
    if (cand > ans) {
      ans = cand;
      solution = ((u64)i << left_half) | leftSubset;
    }
  }
  Vec<bool> selections(n);
  for (int i = 0; i < n; i++) {
    selections[i] = KthBit(solution, i) == 1;
  }
  return {ans, selections};
}
}
} // namespace dalt
namespace dalt {
  #define CLASS_ID -202206092234
  template<class T, class C = Less<T>, i64 ID = 0> 
  struct MergeableHeap{
    using LT = LeftistTree<T, C, ID, CLASS_ID>;
    using Self = MergeableHeap<T, C, ID>;
    LT *root;
    int size;
    static void Register(C comp = C(), T nil = T()) {
      LT::Register(comp, nil);
    }
    MergeableHeap() {
      root = LT::NIL;
      size = 0;
    }
    void add(T item) {
      root = LT::Merge(root, new LT(item));
      size++;
    }
    int get_size() const {
      return size;
    }
    T peek() const {
      return root->key;
    }
    T pop() {
      T ans = peek();
      root = root->pop();
      size--;
      return ans;
    }
    void absorb(Self &data) {
      root = LT::Merge(root, data.root);
      size += data.size;
      data.root = LT::NIL;
      data.size = 0;
    }
    Vec<T> to_vec() const {
      return root->to_vec();
    }
  };
  #undef CLASS_ID
}
namespace dalt {
namespace graph {
  //g should be max flow (it means there is no augment path from s to t)
  //time complexity: O(V+E)
  template<class E>
  IsFlow(E, Vec<bool>) FindSetST(const Graph<E> &g, int s, int t) {
    int n = Size(g);
    Vec<bool> res(n);
    Deque<int> dq;
    dq.push_back(s);
    res[s] = true;
    while(!dq.empty()) {
      int head = dq.front();
      dq.pop_front();
      for (auto &e : g[head]) {
        if(g[e.to][e.rev].flow > 0 && !res[e.to]) {
          res[e.to] = true;
          dq.push_back(e.to);
        }
      }
    }
    Assert(!res[t]);
    return res;
  } 
}
}  // namespace dalt
namespace dalt {
namespace graph {
template <class E>
IsCostFlow(E, Tuple<Vec<typename E::flow_type> COMMA Vec<int>>)
    AugmentPathSpfa(Graph<E> &g, int s, typename E::flow_type inf) {
  Timer timer("AugmentPathSpfa");
  using T = typename E::flow_type;
  int n = Size(g);
  Deque<int> dq;
  Vec<T> dist(n, inf);
  Vec<int> prev(n, -1);
  Vec<bool> inq(n, false);
  dist[s] = 0;
  dq.push_back(s);
  inq[s] = true;
  i64 threshold = i64(n) * n;
  while (!dq.empty()) {
    int root = dq.front();
    dq.pop_front();
    inq[root] = false;
    Assert(threshold-- >= 0);
    for (auto &e : g[root]) {
      if (g[e.to][e.rev].flow == 0 || dist[e.to] <= dist[root] + e.cost) {
        continue;
      }
      dist[e.to] = dist[root] + e.cost;
      prev[e.to] = root;
      if (!inq[e.to]) {
        inq[e.to] = true;
        dq.push_back(e.to);
      }
    }
  }
  return {dist, prev};
}
//return {flow, cost}
template <class E>
IsCostFlow(E, Array<typename E::flow_type COMMA 2>) MinCostFlowDijkstra(
    Graph<E> &g, int s, int t, typename E::flow_type send, bool use_pq = true,
    const Function<bool(typename E::flow_type, typename E::flow_type)>
        &call_back = [](auto x, auto y) { return true; },
    Vec<typename E::flow_type> last_dist = Vec<typename E::flow_type>()) {
  using T = typename E::flow_type;
  int n = Size(g);
  T inf = std::numeric_limits<T>::max() / 2;
  if(last_dist.empty()) {
    last_dist = std::get<0>(AugmentPathSpfa(g, s, inf));
  }
  Vec<E *> prev(n, NULL);
  Vec<T> cur_dist(n, inf);
  auto fix_dist = [&]() {
    for (int i = 0; i < n; i++) {
      last_dist[i] = Min(cur_dist[i] + last_dist[i], inf);
    }
  };
  Function<void()> elogv = [&]() {
    TreeSet<int, Comparator<i32>> set([&](auto a, auto b) {
      return Tuple<T, i32>(cur_dist[a], a) < Tuple<T, i32>(cur_dist[b], b);
    });
    Fill(All(cur_dist), inf);
    Fill(All(prev), (E *)NULL);
    cur_dist[s] = 0;
    set.insert(s);
    while (!set.empty()) {
      auto top = set.begin();
      i32 root = *top;
      Debug(root);
      set.erase(top);
      for (auto &e : g[root]) {
        if (g[e.to][e.rev].flow == 0) {
          continue;
        }
        T dist = cur_dist[root] + e.cost - last_dist[e.to] + last_dist[root];
        Assert(dist >= cur_dist[root]);
        if (dist < cur_dist[e.to]) {
          set.erase(e.to);
          cur_dist[e.to] = dist;
          prev[e.to] = &g[e.to][e.rev];
          set.insert(e.to);
        }
      }
    }
  };
  Function<void()> v2 = [&]() {
    Vec<bool> visited(n, false);
    Fill(All(cur_dist), inf);
    Fill(All(prev), (E *)NULL);
    cur_dist[s] = 0;
    for (int round = 0; round < n; round++) {
      int root = -1;
      for (int i = 0; i < n; i++) {
        if (!visited[i] && (root == -1 || cur_dist[root] > cur_dist[i])) {
          root = i;
        }
      }
      if (cur_dist[root] >= inf) {
        break;
      }
      visited[root] = true;
      for (auto &e : g[root]) {
        if (g[e.to][e.rev].flow == 0) {
          continue;
        }
        T dist = cur_dist[root] + e.cost - last_dist[e.to] + last_dist[root];
        if (dist < cur_dist[e.to]) {
          cur_dist[e.to] = dist;
          prev[e.to] = &g[e.to][e.rev];
        }
      }
    }
  };
  auto &algo = use_pq ? elogv : v2;
  T remain = send;
  T cost = 0;
  while (remain > 0) {
    Timer one_batch_push_flow("push flow");
    algo();
    fix_dist();
    if (prev[t] == NULL) {
      break;
    }
    T max = remain;
    T sum = 0;
    for (int trace = t; trace != s; trace = prev[trace]->to) {
      max = Min(max, prev[trace]->flow);
      sum -= prev[trace]->cost;
    }
    if (!call_back(max, sum)) {
      break;
    }
    for (int trace = t; trace != s; trace = prev[trace]->to) {
      PushFlow(g, *prev[trace], -max);
    }
    Assert(max > 0);
    cost += sum * max;
    remain -= max;
  }
  return {send - remain, cost};
}
}  // namespace graph
}  // namespace dalt
namespace dalt {
// verified by:
//  - https://www.luogu.com.cn/problem/P1886
template <class T, class COMPARER = Less<T>, bool SUPPORT_MAX = false>
struct MinQueue {
 private:
  // maintain incremental sequence
  Deque<T> data;
  Deque<T> inc;
  Deque<T> dec;
  COMPARER comparer;
  IsBool(SUPPORT_MAX, void) push_max(const T& x) {
    while (!dec.empty() && comparer(dec.back(), x)) {
      dec.pop_back();
    }
    dec.push_back(x);
  }
  IsBool(!SUPPORT_MAX, void) push_max(const T& x) {}
  IsBool(SUPPORT_MAX, void) pop_max(const T& x) {
    // dec.front() >= x
    if (!comparer(x, dec.front())) {
      dec.pop_front();
    }
  }
  IsBool(!SUPPORT_MAX, void) pop_max(const T& x) {}
 public:
  MinQueue(COMPARER _comparer = COMPARER()) : comparer(_comparer) {}
  void push_back(T x) {
    data.push_back(x);
    while (!inc.empty() && comparer(x, inc.back())) {
      inc.pop_back();
    }
    inc.push_back(x);
    push_max(x);
    // Debug(inc);
    // Debug(dec);
  }
  const T& front() const { return data.front(); }
  T& front() { return data.front(); }
  void pop_front() {
    T ans = data.front();
    data.pop_front();
    // inc.front() >= ans
    if (!comparer(inc.front(), ans)) {
      inc.pop_front();
    }
    pop_max(ans);
  }
  bool empty() const { return data.empty(); }
  decltype(data.size()) size() const { return data.size(); }
  const T& min() const { return inc.front(); }
  IsBool(SUPPORT_MAX, const T&) max() const { return dec.front(); }
};
}  // namespace dalt
namespace dalt {
namespace math {
template <class T, bool SWAP = false>
Vec<T> MonoidSpanningSet(int n, const Indexer<T>& indexer, T zero = T()) {
  Vec<T> data;
  data.reserve(n + 1);
  auto try_add = [&](const T& ele) {
    for (auto& v : data) {
      if (v == ele) {
        return;
      }
    }
    data.push_back(ele);
  };
  for (int i = 0; i < n; i++) {
    try_add(indexer(i));
  }
  for (int i = 0; i < Size(data); i++) {
    for (int j = 0; j <= i; j++) {
      try_add(data[i] + data[j]);
      if (!SWAP && i < j) {
        try_add(data[j] + data[i]);
      }
    }
  }
  try_add(zero);
  return data;
}
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace geo2 {
// credited to:
// https://github.com/bqi343/USACO/blob/58968ef3ea1e18247292ffb5ec399668c791515a/Implementations/content/geometry%20(13)/Misc/ClosestPair%20(13.2).h
// verified by: https://cses.fi/problemset/task/2194/
template <class T, class POLYGON = Polygon<T>>
enable_if_t<is_base_of_v<Polygon<T>, POLYGON>, Pair<Point<T>, Point<T>>>
TheNearestPointPair(POLYGON polygon) {
  using P = Point<T>;
  using Type = typename P::Type;
  using FType = typename P::FType;
  static_assert(is_same_v<FType, f80>);
  Vec<P> v(Move(polygon.data));
  Pair<FType, Pair<P, P>> bes = {(v[0] - v[1]).abs(), {v[0], v[1]}};
  T INF = T::max() / T(2);
  TreeSet<P> S;
  int ind = 0;
  Sort(All(v));
  for (int i = 0; i < Size(v); i++) {
    if (i && v[i] == v[i - 1]) {
      Debug("same");
      return {v[i], v[i]};
    }
    for (; FType(v[i].x - v[ind].x) >= bes.first; ++ind)
      S.erase(P{v[ind].y, v[ind].x});
    for (auto it = S.upper_bound(P{std::floor(FType(v[i].y) - bes.first), INF});
         it != S.end() && FType(it->x - v[i].y) < bes.first; ++it) {
      P t = {it->y, it->x};
      bes = std::min(bes, {(t - v[i]).abs(), {t, v[i]}});
    }
    S.insert(P{v[i].y, v[i].x});
  }
  return bes.second;
}
}  // namespace geo2
}  // namespace dalt
namespace dalt {
namespace seq {
// verified by: 
//  - https://loj.ac/p/141
template <int C = 26>
struct PalindromeAutomaton {
  struct Node {
    Array<Node *, C> next;
    Node* fail;
    int len;
    int depth;
  };
  Node *odd;
  Node *even;
  Vec<i32> data;
  int zero;
  int front_size;
  int back_size;
  Node *front_build_last;
  Node *back_build_last;
  Vec<Node *> all;
  i64 palindrome_substring_cnt;
  Node *newNode() {
    auto ans = new Node();
    all.push_back(ans);
    return ans;
  }
  PalindromeAutomaton(int front_addition, int back_addition = 0)
      : palindrome_substring_cnt(0) {
    int cap = front_addition + back_addition;
    all.resize(2 + cap);
    data.resize(cap);
    zero = front_addition;
    front_size = zero - 1;
    back_size = zero;
    odd = newNode();
    odd->len = -1;
    odd->depth = 0;
    even = newNode();
    even->fail = odd;
    even->len = 0;
    even->depth = 0;
    all.clear();
    back_build_last = front_build_last = odd;
  }
  void push_front(i32 c) {
    data[front_size--] = c;
    int index = c;
    auto trace = front_build_last;
    while (front_size + 2 + trace->len >= back_size) {
      trace = trace->fail;
    }
    while (data[front_size + trace->len + 2] != c) {
      trace = trace->fail;
    }
    if (trace->next[index] != NULL) {
      front_build_last = trace->next[index];
    } else {
      auto now = newNode();
      now->len = trace->len + 2;
      trace->next[index] = now;
      if (now->len == 1) {
        now->fail = even;
      } else {
        trace = trace->fail;
        while (data[front_size + trace->len + 2] != c) {
          trace = trace->fail;
        }
        now->fail = trace->next[index];
      }
      now->depth = now->fail->depth + 1;
      front_build_last = now;
    }
    if (front_build_last->len == back_size - front_size - 1) {
      back_build_last = front_build_last;
    }
    palindrome_substring_cnt += front_build_last->depth;
  }
  void push_back(i32 c) {
    data[back_size++] = c;
    int index = c;
    auto trace = back_build_last;
    while (back_size - 2 - trace->len <= front_size) {
      trace = trace->fail;
    }
    while (data[back_size - trace->len - 2] != c) {
      trace = trace->fail;
    }
    if (trace->next[index] != NULL) {
      back_build_last = trace->next[index];
    } else {
      auto now = newNode();
      now->len = trace->len + 2;
      trace->next[index] = now;
      if (now->len == 1) {
        now->fail = even;
      } else {
        trace = trace->fail;
        while (data[back_size - trace->len - 2] != c) {
          trace = trace->fail;
        }
        now->fail = trace->next[index];
      }
      now->depth = now->fail->depth + 1;
      back_build_last = now;
    }
    if (back_build_last->len == back_size - front_size - 1) {
      front_build_last = back_build_last;
    }
    palindrome_substring_cnt += back_build_last->depth;
  }
  void visit(Consumer<Node *> consumer) {
    for (int i = Size(all) - 1; i >= 0; i--) {
      consumer(all[i]);
    }
  }
  i64 get_palindrome_substring_cnt() const { return palindrome_substring_cnt; }
  int get_distinct_palindrome_substring() const { return Size(all); }
};
}  // namespace seq
}  // namespace dalt
namespace dalt {
namespace math {
//O(n)
template <class T>
Vec<T> PentagonalNumber(int n) {
  Vec<T> data(n);
  if (n == 0) {
    return data;
  }
  T one = T(1);
  T neg = T(-1);
  data[0] = one;
  for (int k = 1; k * (3 * k + 1) / 2 < n; k++) {
    T val = k % 2 == 1 ? neg : one;
    data[k * (3 * k + 1) / 2] += val;
  }
  for (int k = 1; k * (3 * k - 1) / 2 < n; k++) {
    T val = k % 2 == 1 ? neg : one;
    data[k * (3 * k - 1) / 2] += val;
  }
  return data;
}
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace math {
// verified by: https://judge.yosupo.jp/problem/partition_function
// ret[j] = way of (a1,...,an) where \sum_i i*ai = j
// time complexity: O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>> PartitionNumber(
    int n) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  auto inv = Poly(PentagonalNumber<T>(n + 1)).inverse(n + 1);
  auto vec = Move(inv.data);
  vec.resize(n + 1);
  return vec;
}
}  // namespace math
}  // namespace dalt
namespace dalt {
struct Permutation : public Vec<int> {
  using Self = Permutation;
  Permutation(int n = 0) : Permutation(Vec<int>(n)) {}
  Permutation(Vec<int> data) : Vec<int>(Move(data)) {}
  friend Self operator+(const Self &a, const Self &b) {
    int n = Size(a);
    Self res(n);
    for (int i = 0; i < n; i++) {
      res[i] = b[a[i]];
    }
    return res;
  }
  friend Self operator*(const Self& a, const Self& b) {
    return a + b;
  }
  friend bool operator<(const Self &a, const Self &b) {
    if(Size(a) != Size(b)) {
      return Size(a) < Size(b);
    }
    for (int i = 0; i < Size(a); i++) {
      if (a[i] < b[i]) {
        return true;
      }
      if (a[i] > b[i]) {
        return false;
      }
    }
    return false;
  }
  ImplDefaultComparision(Self);
  Vec<int> to_vec() const { return Vec<int>(*this); }
  template<class E>
  Vec<E> apply(const Vec<E>& data) const {
    Vec<E> res(Size(data));
    for(int i = 0; i < Size(data); i++) {
      res[i] = data[(*this)[i]];
    }
    return res;
  }
};
}
namespace dalt {
namespace poly {
// internal usage
template <class P>
struct PolynomialTree {
  static_assert(is_polynomial_v<P>);
  using T = typename P::Type;
  PolynomialTree* left;
  PolynomialTree* right;
  P p;
  PolynomialTree() : left(NULL), right(NULL) {}
  PolynomialTree(const Vec<T>& x, int l, int r) : PolynomialTree() {
    if (l == r) {
      p = P(Vec<T>{T(0) - x[l], T(1)});
    } else {
      int m = (l + r) / 2;
      left = new PolynomialTree(x, l, m);
      right = new PolynomialTree(x, m + 1, r);
      p = left->p * right->p;
    }
  }
  void multi_apply(const P& p, const Vec<T>& x, Vec<T>& y, int l, int r) {
    if (r - l + 1 <= POLY_FAST_MAGIC_THRESHOLD) {
      for (int i = l; i <= r; i++) {
        y[i] = p.apply(x[i]);
      }
      return;
    }
    auto rem = p % this->p;
    int m = (l + r) / 2;
    left->multi_apply(rem, x, y, l, m);
    right->multi_apply(rem, x, y, m + 1, r);
  }
#ifdef DROP
  ~PolynomialTree() {
    delete left;
    delete right;
  }
#endif
};
//- time: O(|p|\log |p| + |x|(log |x|)^2)
template <class P, class T = typename P::Type>
enable_if_t<is_polynomial_v<P> && is_same_v<T, typename P::Type>, Vec<T>>
MultiApplyFast(const P& p, const Vec<T>& x) {
  int n = Size(x);
  Vec<T> y(n);
  auto tree = new PolynomialTree<P>(x, 0, n - 1);
  tree->multi_apply(p, x, y, 0, n - 1);
  delete tree;
  return y;
}
//- time: O(|p|\log |p| + |x|(log |x|)^2)
template <class P, class T = typename P::Type>
enable_if_t<is_polynomial_v<P> && is_same_v<T, typename P::Type>, P>
InterpolationFast(const Vec<T>& xs, const Vec<T>& ys) {
  Assert(Size(xs) == Size(ys));
  i32 n = Size(xs);
  auto tree = new PolynomialTree<P>(xs, 0, n - 1);
  auto diff_m = tree->p.differential();
  Vec<T> v(Size(xs));
  tree->multi_apply(diff_m, xs, v, 0, n - 1);
  Vec<T> inv = math::InverseBatch<T>(v);
  for (int i = 0; i < n; i++) {
    v[i] = ys[i] * inv[i];
  }
  auto interpolate = [&](auto& interpolate, int l, int r,
                         PolynomialTree<P>* tree) -> P {
    if (l == r) {
      return P::of(v[l]);
    }
    int m = (l + r) / 2;
    auto f0 = interpolate(interpolate, l, m, tree->left);
    auto f1 = interpolate(interpolate, m + 1, r, tree->right);
    auto a = f0 * tree->right->p;
    auto b = f1 * tree->left->p;
    return a + b;
  };
  auto ans = interpolate(interpolate, 0, n - 1, tree);
  delete tree;
  return ans;
}
}  // namespace poly
}  // namespace dalt
namespace dalt {
namespace math {
#define CID -202202162000
template <class I, bool CACHE>
I TotientEval(I n) {
  static auto f = [](auto x, auto xp) { return xp - xp / x; };
  if (!CACHE) {
    return BigMultiplicativeFunctionEval<I, I>(n, f);
  } else {
    return BigMultiplicativeFunctionEval<I, I, CID>(n, f);
  }
}
#undef CID
}  // namespace math
}  // namespace dalt
namespace dalt {
namespace math {
#define CID -202202162049
//(\log mod)^2
template <class E>
struct PowerChain {
  static_assert(is_integral_v<E>);
  Vec<E> data;
  Vec<int> next;
  PowerChain(Vec<E> _data) : data(Move(_data)) {
    int n = Size(data);
    next.resize(n);
    int last = n;
    for (int i = n - 1; i >= 0; i--) {
      if (data[i] != E(0)) {
        last = i;
      }
      next[i] = last;
    }
  }
  template <class T>
  T query(int l, int r, T mod) const {
    static_assert(is_integral_v<T>);
    using Lv = LimitValue<T>;
    auto dfs = [&](auto& dfs, int index, T mod) -> Pair<T, Lv> {
      if (mod == T(1)) {
        int to = index;
        while (to + 1 <= r && to - index + 1 <= 5 && data[to] >= E(2)) {
          to++;
        }
        Lv estimate = Lv::from(1);
        if (data[to] == E(0)) {
          // hard case
          int zero = Min(r + 1, next[to]) - to;
          to--;
          if (zero % 2 == 1) {
            estimate = Lv::from(0);
          }
        }
        for (int i = to; i >= index; i--) {
          estimate = Lv::from(data[i]).pow(estimate.value);
        }
        return MakePair(T(0), estimate);
      }
      E val = data[index];
      T mod_val = Modular(val, mod);
      if (index == r) {
        return MakePair(mod_val, Lv::from(val));
      }
      T totient = TotientEval<T, true>(mod);
      auto res = dfs(dfs, index + 1, totient);
      T exp = res.second.value >= totient ? (totient + res.first) : (res.first);
      T ans = PowMod<T, E>(mod_val, exp, mod);
      auto lv_ans = Lv::from(val).pow(res.second.value);
      Debug(index);
      Debug(lv_ans);
      return MakePair(ans, lv_ans);
    };
    return dfs(dfs, l, mod).first;
  }
};
#undef CID
}  // namespace math
}  // namespace dalt
namespace dalt {
template <class T> struct PrefixSum {
private:
  Vec<T> sum;
  int n;
public:
  using Self = PrefixSum<T>;
  PrefixSum(Vec<T> data = Vec<T>()) : sum(move(data)) {
    if (sum.empty()) {
      sum.push_back(T());
    }
    n = int(sum.size());
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + sum[i];
    }
  }
  PrefixSum(int n, const Indexer<T> &indexer): PrefixSum(ExpandIndexer(n, indexer)) {}
  T prefix(int i) const {
    if (i < 0) {
      return T();
    }
    i = Min(i, n - 1);
    return sum[i];
  }
  T suffix(int i) const { return sum.back() - prefix(i - 1); }
  T query(int l, int r) const {
    if (l > r) {
      return 0;
    }
    return prefix(r) - prefix(l - 1);
  }
  Vec<T> to_vec() const {
    return sum;
  }
};
} // namespace dalt
namespace dalt {
template <class T>
struct PrefixSum2 {
 private:
  Vec<Vec<T>> data;
 public:
  PrefixSum2(int n, int m, const Indexer2<T> &indexer) {
    data = Vec<Vec<T>>(n + 1, Vec<T>(m + 1));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        data[i][j] = data[i][j - 1] + indexer(i - 1, j - 1);
      }
      for (int j = 1; j <= m; j++) {
        data[i][j] = data[i][j] + data[i - 1][j];
      }
    }
  }
  T query(int b, int t, int l, int r) const {
    r++;
    t++;
    return data[t][r] - data[t][l] - data[b][r] + data[b][l];
  }
  Vec<Vec<T>> to_vec() const { return data; }
};
}  // namespace dalt
namespace dalt {
// verified by:
//  - https://www.luogu.com.cn/problem/P1177
template <class F, class T, i32 BIT_8 = 1>
enable_if_t<is_integral_v<T>, void> RadixSortMapper(
    F* begin, i32 n, const Mapper<F, T>& mapper) {
  static_assert(BIT_8 >= 1 && BIT_8 <= 2);
  static const i32 BUF_SIZE = 1 << 8 * BIT_8;
  static const i32 BUF_MASK = BUF_SIZE - 1;
  static i32 CNT[BUF_SIZE];
  static Vec<F> BUF;
  BUF.resize(n);
  auto sort = [&](auto data, auto output, i32 shift, i32 n) {
    memset(CNT, 0, sizeof(CNT));
    for (int i = 0; i < n; i++) {
      CNT[(mapper(data[i]) >> shift) & BUF_MASK]++;
    }
    for (int i = 1; i < BUF_SIZE; i++) {
      CNT[i] += CNT[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      output[--CNT[(mapper(data[i]) >> shift) & BUF_MASK]] = data[i];
    }
  };
  i32 round = sizeof(T) / BIT_8 / 2;
  if (round == 0) {
    sort(begin, BUF.data(), 0, n);
    std::memcpy(begin, BUF.data(), n);
    return;
  }
  for (int i = 0; i < round; i++) {
    sort(begin, BUF.data(), i * 2 * BIT_8 * 8, n);
    sort(BUF.data(), begin, (i * 2 + 1) * BIT_8 * 8, n);
  }
}
template <class T, i32 BIT_8 = 1>
enable_if_t<is_integral_v<T>, void> RadixSort(T* begin, i32 n) {
  static_assert(BIT_8 >= 1 && BIT_8 <= 2);
  static const i32 BUF_SIZE = 1 << 8 * BIT_8;
  static const i32 BUF_MASK = BUF_SIZE - 1;
  static i32 CNT[BUF_SIZE];
  static Vec<T> BUF;
  BUF.resize(n);
  auto sort = [&](auto data, auto output, i32 shift, i32 n) {
    memset(CNT, 0, sizeof(CNT));
    for (int i = 0; i < n; i++) {
      CNT[(data[i] >> shift) & BUF_MASK]++;
    }
    for (int i = 1; i < BUF_SIZE; i++) {
      CNT[i] += CNT[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      output[--CNT[(data[i] >> shift) & BUF_MASK]] = data[i];
    }
  };
  i32 round = sizeof(T) / BIT_8 / 2;
  if (round == 0) {
    sort(begin, BUF.data(), 0, n);
    std::memcpy(begin, BUF.data(), n);
    return;
  }
  for (int i = 0; i < round; i++) {
    sort(begin, BUF.data(), i * 2 * BIT_8 * 8, n);
    sort(BUF.data(), begin, (i * 2 + 1) * BIT_8 * 8, n);
  }
}
template <class F, class T>
enable_if_t<is_integral_v<T>, void> RadixSortMapperAdjust(
    F* begin, i32 n, const Mapper<F, T>& mapper) {
  if (sizeof(T) == 1) {
    RadixSortMapper<F, T, 1>(begin, n, mapper);
    return;
  }
  i32 round1 = sizeof(T);
  i32 round2 = sizeof(T) / 2;
  if ((i64)round1 * (n + (1 << 8)) <= (i64)round2 * (n + (1 << 16))) {
    RadixSortMapper<F, T, 1>(begin, n, mapper);
  } else {
    RadixSortMapper<F, T, 2>(begin, n, mapper);
  }
}
template <class T>
enable_if_t<is_integral_v<T>, void> RadixSortAdjust(T* begin, i32 n) {
  if (sizeof(T) == 1) {
    RadixSort<T, 1>(begin, n);
    return;
  }
  i32 round1 = sizeof(T);
  i32 round2 = sizeof(T) / 2;
  if ((i64)round1 * (n + (1 << 8)) <= (i64)round2 * (n + (1 << 16))) {
    RadixSort<T, 1>(begin, n);
  } else {
    RadixSort<T, 2>(begin, n);
  }
}
}  // namespace dalt
namespace dalt {
namespace sbt {
#define CLASS_ID -202202131500
template <class SBT, class S, class U, bool P = false, bool SPARSE = false, i64 ID = 0>
struct SegTree {
  static_assert(is_sbt_registry_v<SBT>);
  static_assert(int(P) + int(SPARSE) <= 1);
  struct Node {
    using Self = Node;
    Self *left;
    Self *right;
    S sum;
    U upd;
#ifdef DROP
    ~Node() {
      if (this == NIL) {
        return;
      }
      delete left;
      delete right;
    }
#endif
    Self* clone() {
      if (SPARSE) {
        if (this == NIL) {
          return new Node(*NIL);
        }
        return this;
      } else if (P) {
        return new Node(*this);
      } else {
        return this;
      }
    }
    void push_up() { sum = SBT::s_s(left->sum, right->sum); }
    void push_down() {
      left = left->clone();
      right = right->clone();
      if (upd != SBT::u_nil) {
        left->modify(upd);
        right->modify(upd);
        upd = SBT::u_nil;
      }
    }
    void modify(const U &u) {
      sum = SBT::s_u(sum, u);
      upd = SBT::u_u(upd, u);
    }
  };
  using Self = SegTree<SBT, S, U, P, SPARSE, ID>;
  static Node *NIL;
  Node *tree;
  int n;
 private:
  Node *make_node() {
    Node *ans = new Node{
        .left = NIL,
        .right = NIL,
        .sum = SBT::s_nil,
        .upd = SBT::u_nil,
    };
    return ans;
  }
  IsBool(P, Node *) make_tree() {
    Node *root = make_node();
    root->left = root->right = root;
    return root;
  }
  IsBool(!P, Node *) make_tree() {
    Node *root = make_node();
    return root;
  }
 public:
  IsBoolStatic(SPARSE, void)
      Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
               const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    SBT::Register(_s_nil, _u_nil, _s_s,
                                                      _s_u, _u_u);
    NIL = new Node();
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->upd = _u_nil;
    NIL->sum = _s_nil;
  }
  IsBoolStatic(!SPARSE, void)
      Register(S _s_nil, U _u_nil, const Adder<S, S> &_s_s,
               const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    SBT::Register(_s_nil, _u_nil, _s_s,
                                                      _s_u, _u_u);
  }
  Self clone() const {
    Self ans = *this;
    ans.tree = ans.tree->clone();
    return ans;
  }
  SegTree(
      int _n = 0,
      const Indexer<S> &indexer = [](int index) { return SBT::s_nil; })
      : n(_n) {
    auto dfs = [&](auto &dfs, int l, int r) -> Node * {
      Node *root = make_tree();
      root->upd = SBT::u_nil;
      if (l == r) {
        root->sum = indexer(l);
      } else {
        int m = (l + r) / 2;
        root->left = dfs(dfs, l, m);
        root->right = dfs(dfs, m + 1, r);
        root->push_up();
      }
      return root;
    };
    tree = dfs(dfs, 0, n - 1);
  }
  IsBoolStatic(SPARSE, Self) MakeSparseTree(int n) {
    Self res(1);
    res.n = n;
    return res;
  }
  IsBoolStatic(P, Self) MakePersistentTree(int n) {
    Self res(1);
    res.n = n;
    return res;
  }
  S query(int L, int R) {
    auto dfs = [&](auto &dfs, Node *root, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SBT::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return root->sum;
      }
      root->push_down();
      int m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m);
      auto rsum = dfs(dfs, root->right, m + 1, r);
      return SBT::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1);
  }
  S query_const(int L, int R) const {
    auto dfs = [&](auto &dfs, Node *root, int l, int r, const U &upd) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SBT::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return SBT::s_u(root->sum, upd);
      }
      U new_upd = SBT::u_u(root->upd, upd);
      int m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m, new_upd);
      auto rsum = dfs(dfs, root->right, m + 1, r, new_upd);
      return SBT::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1, SBT::u_nil);
  }
  void update(int L, int R, const U &upd) {
    auto dfs = [&](auto &dfs, Node *root, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        root->modify(upd);
        return;
      }
      root->push_down();
      int m = (l + r) / 2;
      dfs(dfs, root->left, l, m);
      dfs(dfs, root->right, m + 1, r);
      root->push_up();
    };
    dfs(dfs, tree, 0, n - 1);
  }
  void travel(const Consumer<S> &consumer) const {
    auto dfs = [&](auto &dfs, Node *root, const U &upd, int l, int r) {
      // is leaf
      if (l == r) {
        consumer(SBT::s_u(root->sum, upd));
        return;
      }
      int m = (l + r) / 2;
      U new_upd = SBT::u_u(root->upd, upd);
      dfs(dfs, root->left, new_upd, l, m);
      dfs(dfs, root->right, new_upd, m + 1, r);
    };
    dfs(dfs, tree, SBT::u_nil, 0, n - 1);
  }
  Vec<S> to_vec() const {
    Vec<S> res;
    res.reserve(n);
    travel([&](auto x) { res.push_back(x); });
    return res;
  }
  Optional<Tuple<int, S>> first_true(int L, int R, const Checker<S> &checker) {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, int l, int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, root->sum);
        if (!checker(new_sum)) {
          sum = new_sum;
          return {};
        }
        if (l == r) {
          // leaf
          sum = new_sum;
          return l;
        }
      }
      root->push_down();
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    Mapper<int, Tuple<int, S>> mapper = [&](const int &x) -> Tuple<int, S> {
      return Tuple<int, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<int, S>> last_true(int L, int R, const Checker<S> &checker) {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, int l, int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, root->sum);
        if (checker(new_sum)) {
          sum = new_sum;
          return r;
        }
        if (l == r) {
          return {};
        }
      }
      root->push_down();
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if ((lres.is_some() && lres.value() == m) || m < L) {
        auto rres = dfs(dfs, root->right, m + 1, r);
        if (rres.is_some()) {
          return rres;
        }
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    Mapper<int, Tuple<int, S>> mapper = [&](const int &x) -> Tuple<int, S> {
      return Tuple<int, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<int, S>> first_true_const(int L, int R,
                                           const Checker<S> &checker) const {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, const U &upd, int l,
                   int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, SBT::s_u(root->sum, upd));
        if (!checker(new_sum)) {
          sum = new_sum;
          return {};
        }
        if (l == r) {
          // leaf
          sum = new_sum;
          return l;
        }
      }
      U new_upd = SBT::u_u(root->upd, upd);
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, new_upd, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SBT::u_nil, 0, n - 1);
    Mapper<int, Tuple<int, S>> mapper = [&](const int &x) -> Tuple<int, S> {
      return Tuple<int, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<int, S>> last_true_const(int L, int R,
                                          const Checker<S> &checker) const {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, const U &upd, int l,
                   int r) -> Optional<int> {
      if (SegmentNoIntersection(L, R, l, r)) {
        return {};
      }
      if (SegmentCover(L, R, l, r)) {
        S new_sum = SBT::s_s(sum, SBT::s_u(root->sum, upd));
        if (checker(new_sum)) {
          sum = new_sum;
          return r;
        }
        if (l == r) {
          // leaf
          return {};
        }
      }
      U new_upd = SBT::u_u(root->upd, upd);
      int m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if ((lres.is_some() && lres.value() == m) || m < L) {
        auto rres = dfs(dfs, root->right, new_upd, m + 1, r);
        if (rres.is_some()) {
          return rres;
        }
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SBT::u_nil, 0, n - 1);
    Mapper<int, Tuple<int, S>> mapper = [&](const int &x) -> Tuple<int, S> {
      return Tuple<int, S>(x, sum);
    };
    return res.map(mapper);
  }
  IsBool(!(P || SPARSE), void) destroy() { delete tree; }
  IsBool(P || SPARSE, void) destroy() {}
  // to support merge, only support single point update
  IsBoolStatic(SPARSE, Self) merge(Self a, Self b, const Adder<S, S> &adder) {
    assert(a.n == b.n);
    auto dfs = [&](auto &dfs, Node *a, Node *b, int l, int r) -> Node * {
      if (a == NIL) {
        return b;
      }
      if (b == NIL) {
        return a;
      }
      if (l == r) {
        a->sum = adder(a->sum, b->sum);
        return a;
      }
      int m = (l + r) / 2;
      // a->push_down();
      // b->push_down();
      a->left = dfs(dfs, a->left, b->left, l, m);
      a->right = dfs(dfs, a->right, b->right, m + 1, r);
      a->push_up();
      return a;
    };
    a.tree = dfs(dfs, a.tree, b.tree, 0, a.n - 1);
    return a;
  }
#ifdef DROP
  ~SegTree() { destroy(); }
#endif
};
#undef CLASS_ID
template <class SBT, class S, class U, bool P, bool SPARSE, i64 ID>
typename SegTree<SBT, S, U, P, SPARSE, ID>::Node
    *SegTree<SBT, S, U, P, SPARSE, ID>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
namespace dalt {
namespace sbt {
template <class T>
struct RangeAffineRangeSum {
  using Self = RangeAffineRangeSum<T>;
 private:
  using A = Array<T, 2>;
  using ST = SegTree<SelfBalanceTreeRegistry<A, A, 0, Self>, A, A, false, false, 0>;
  ST st;
  struct InitJob {
    InitJob() {
      ST::Register(
          A{0, 0}, A{1, 0},
          [&](auto a, auto b) {
            return A{a[0] + b[0], a[1] + b[1]};
          },
          [&](auto a, auto b) {
            return A{a[0] * b[0] + a[1] * b[1], a[1]};
          },
          [&](auto a, auto b) {
            return A{a[0] * b[0], b[0] * a[1] + b[1]};
          });
    }
  };
  static InitJob init_job;
 public:
  RangeAffineRangeSum(int n, const Indexer<T> &indexer)
      : st(n, [&](auto i) -> A {
          return A{indexer(i), 1};
        }) {}
  T query(int L, int R) { return st.query_const(L, R)[0]; }
  void update(int L, int R, T a, T b) { return st.update(L, R, {a, b}); }
  Vec<T> to_vec() {
    auto data = st.to_vec();
    Vec<T> res;
    res.reserve(data.size());
    for (auto x : data) {
      res.push_back(x[0]);
    }
    return res;
  }
};
template <class T>
typename RangeAffineRangeSum<T>::InitJob RangeAffineRangeSum<T>::init_job;
}  // namespace sbt
}  // namespace dalt
namespace dalt {
// like treeset
// - time: O(\log_64 n)
// - memory: O(n/8)
struct RangeTree {
private:
  Vec<Vec<u64>> data;
  static const int BIT_SHIFT = 6;
  static const int BIT_SHIFT_VALUE = 1 << BIT_SHIFT;
  static const int BIT_SHIFT_VALUE_MASK = BIT_SHIFT_VALUE - 1;
  int size;
  int n;
  int calc_level(int n) {
    int level = 0;
    while (n > 64) {
      level++;
      n = (n + 63) / 64;
    }
    level++;
    return level;
  }
  bool check(int i) const { return i >= 0 && i < n; }
  int last_set(int i, int x) const {
    Assert(i < 0 || data[i][x] != 0);
    for (; i >= 0; i--) {
      int offset = HighestOneBitOffset(data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }
  int first_set(int i, int x) const {
    Assert(i < 0 || data[i][x] != 0);
    for (; i >= 0; i--) {
      int offset = LowestOneBitOffset(data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }
  int last_clear(int i, int x) const {
    Assert(i < 0 || data[i][x] != -1);
    for (; i >= 0; i--) {
      int offset = HighestOneBitOffset(~data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }
  int first_clear(int i, int x) const {
    Assert(i < 0 || data[i][x] != -1);
    for (; i >= 0; i--) {
      int offset = LowestOneBitOffset(~data[i][x]);
      x = (x << BIT_SHIFT) | offset;
    }
    return x;
  }
public:
  RangeTree(int _n) : n(_n), size(0) {
    int level = calc_level(n);
    data.resize(level);
    for (int i = 0, m = (n + 63) / 64; i < level; i++, m = (m + 63) / 64) {
      data[i] = Vec<u64>(m);
    }
  }
  bool contains(int x) const {
    return ((data[0][x >> BIT_SHIFT] >> (x & BIT_SHIFT_VALUE_MASK)) & 1) == 1;
  }
  int get_size() const { return size; }
  void add(int x) {
    if (contains(x)) {
      return;
    }
    size++;
    for (int i = 0; i < Size(data); i++) {
      int offset = x & BIT_SHIFT_VALUE_MASK;
      x >>= BIT_SHIFT;
      data[i][x] = SetBit(data[i][x], offset);
    }
  }
  void remove(int x) {
    if (!contains(x)) {
      return;
    }
    size--;
    u64 last_value = 0;
    for (int i = 0; i < Size(data) && last_value == 0; i++) {
      int offset = x & BIT_SHIFT_VALUE_MASK;
      x >>= BIT_SHIFT;
      last_value = data[i][x] = ClearBit(data[i][x], offset);
    }
  }
  int floor(int x) const {
    if (x < 0) {
      return -1;
    }
    if (contains(x)) {
      return x;
    }
    for (int i = 0, y = x; i < Size(data); i++) {
      int offset = y & BIT_SHIFT_VALUE_MASK;
      y = y >> BIT_SHIFT;
      u64 head_mask = LowestKOnes64(offset);
      if ((data[i][y] & head_mask) != 0) {
        return last_set(i - 1, (y << BIT_SHIFT) |
                                   HighestOneBitOffset(data[i][y] & head_mask));
      }
    }
    return -1;
  }
  int ceil(int x) const {
    if (x >= n) {
      return -1;
    }
    if (contains(x)) {
      return x;
    }
    for (int i = 0, y = x; i < Size(data); i++) {
      int offset = y & BIT_SHIFT_VALUE_MASK;
      y = y >> BIT_SHIFT;
      u64 tail_mask = HighestKOnes64(63 - offset);
      if ((data[i][y] & tail_mask) != 0) {
        return first_set(i - 1, (y << BIT_SHIFT) |
                                    LowestOneBitOffset(data[i][y] & tail_mask));
      }
    }
    return -1;
  }
  int first() const {
    if (size == 0) {
      return -1;
    }
    return first_set(Size(data) - 1, 0);
  }
  int last() const {
    if (size == 0) {
      return -1;
    }
    return last_set(Size(data) - 1, 0);
  }
  Vec<i32> to_vec() const {
    Vec<i32> ans;
    ans.reserve(size);
    for (int i = first(); i != -1; i = ceil(i + 1)) {
      ans.push_back(i);
    }
    return ans;
  }
  void clear() {
    size = 0;
    for (int i = 0; i < Size(data); i++) {
      Fill(All(data[i]), 0);
    }
  }
};
} // namespace dalt
namespace dalt {
namespace graph {
Vec<i32> DepthOnTree(const Vec<i32> &fa) {
  int n = Size(fa);
  Vec<i32> depth(n, -1);
  auto dfs = [&](auto &dfs, auto root) -> i32 {
    if (root == -1) {
      return -1;
    }
    if (depth[root] == -1) {
      depth[root] = dfs(dfs, fa[root]) + 1;
    }
    return depth[root];
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  return depth;
}
template <class E>
IsBiGraph(E, Vec<i32>)
    DepthOnTree(const Graph<E> &g, const Checker<int> &is_root) {
  int n = Size(g);
  Vec<i32> depth(n);
  auto dfs = [&](auto &dfs, int root, int rev) -> void {
    int n = Size(g[root]);
    for (int i = 0; i < n; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      depth[e.to] = depth[root] + 1;
      dfs(dfs, e.to, e.rev);
    }
  };
  for (int i = 0; i < n; i++) {
    if (is_root(i)) {
      dfs(dfs, i, -1);
    }
  }
  return depth;
}
template <class T, class E>
enable_if_t<is_base_of_v<BiBaseEdge, E> && is_base_of_v<WithWeight<T>, E>,
            Vec<T>>
DepthOnTreeWeight(const Graph<E> &g, const Checker<int> &is_root) {
  int n = Size(g);
  Vec<T> depth(n);
  auto dfs = [&](auto &dfs, int root, int rev) -> void {
    int n = Size(g[root]);
    for (int i = 0; i < n; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      depth[e.to] = depth[root] + e.weight;
      dfs(dfs, e.to, e.rev);
    }
  };
  for (int i = 0; i < n; i++) {
    if (is_root(i)) {
      dfs(dfs, i, -1);
    }
  }
  return depth;
}
template <class E>
IsBiGraph(E, Vec<i32>)
    FatherOnTree(const Graph<E> &g, const Checker<i32> &is_root) {
  int n = Size(g);
  Vec<i32> father(n, -1);
  auto dfs = [&](auto &dfs, int root, int rev) -> void {
    int n = Size(g[root]);
    for (int i = 0; i < n; i++) {
      if (i == rev) {
        continue;
      }
      auto &e = g[root][i];
      father[e.to] = root;
      dfs(dfs, e.to, e.rev);
    }
  };
  for (int i = 0; i < n; i++) {
    if (is_root(i)) {
      dfs(dfs, i, -1);
    }
  }
  return father;
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace sbt {
// verify by: https://cses.fi/problemset/task/2416
template <class T>
struct SegTreeBeat {
  using Self = SegTreeBeat<T>;
  static_assert(is_arithmetic_v<T>);
  struct Node {
    using Self = Node;
    const static T INF = std::numeric_limits<T>::max() / 2;
    Node *left;
    Node *right;
    T first;
    T second;
    int first_cnt;
    T sum;
    Node(i32 l, i32 r, const Indexer<T> &indexer) {
      left = right = NULL;
      if (l < r) {
        int m = (l + r) / 2;
        left = new Self(l, m, indexer);
        right = new Self(m + 1, r, indexer);
        push_up();
      } else {
        sum = first = indexer(l);
        second = -INF;
        first_cnt = 1;
      }
    }
    void push_up() {
      first = Max(left->first, right->first);
      second = Max(left->first == first ? left->second : left->first,
                   right->first == first ? right->second : right->first);
      first_cnt = (left->first == first ? left->first_cnt : 0) +
                  (right->first == first ? right->first_cnt : 0);
      sum = left->sum + right->sum;
    }
    void push_down() {
      left->set_min(first);
      right->set_min(first);
    }
    void set_min(const T &x) {
      if (first <= x) {
        return;
      }
      sum -= (first - x) * first_cnt;
      first = x;
    }
    void update_min(int L, int R, int l, int r, const T &x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        if (first <= x) {
          return;
        }
        if (second < x) {
          set_min(x);
          return;
        }
      }
      push_down();
      int m = (l + r) / 2;
      left->update_min(L, R, l, m, x);
      right->update_min(L, R, m + 1, r, x);
      push_up();
    }
    T query_sum(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return 0;
      }
      if (SegmentCover(L, R, l, r)) {
        return sum;
      }
      push_down();
      int m = (l + r) / 2;
      return left->query_sum(L, R, l, m) + right->query_sum(L, R, m + 1, r);
    }
    T query_max(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return -INF;
      }
      if (SegmentCover(L, R, l, r)) {
        return first;
      }
      push_down();
      int m = (l + r) / 2;
      return Max(left->query_max(L, R, l, m), right->query_max(L, R, m + 1, r));
    }
    void travel(const Consumer<T> &consumer, T min_val) const {
      min_val = Min(min_val, first);
      if (left == NULL) {
        consumer(min_val);
        return;
      }
      left->travel(consumer, min_val);
      right->travel(consumer, min_val);
    }
    ~Node() {
      delete left;
      delete right;
    }
  };
 private:
  Node *tree;
  int n;
 public:
  SegTreeBeat(int _n, const Indexer<T> &indexer) : n(_n) {
    tree = new Node(0, n - 1, indexer);
  }
  inline void update_min(int L, int R, const T &min_val) {
    tree->update_min(L, R, 0, n - 1, min_val);
  }
  inline T query_max(int L, int R) { return tree->query_max(L, R, 0, n - 1); }
  inline T query_sum(int L, int R) { return tree->query_sum(L, R, 0, n - 1); }
  void travel(const Consumer<T> &consumer) const {
    tree->travel(consumer, Node::INF);
  }
  Vec<T> to_vec() const {
    Vec<T> res;
    res.reserve(n);
    travel([&](auto x) { res.push_back(x); });
    return res;
  }
#ifdef DROP
  ~SegTreeBeat() { delete tree; }
#endif
};
} 
}  // namespace dalt
// verify by: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
namespace dalt {
namespace sbt {
#define ASSERTION_STUB                     \
  Assert(first_largest >= second_largest); \
  Assert(first_smallest <= second_smallest);
template <class T>
struct SegTreeBeatExt {
  static_assert(is_arithmetic_v<T>);
 private:
  struct Node {
    static const T INF = std::numeric_limits<T>::max() / 2;
    using Self = Node;
    Self *left;
    Self *right;
    T first_largest;
    T second_largest;
    int first_largest_cnt;
    T first_smallest;
    T second_smallest;
    int first_smallest_cnt;
    T dirty;
    int size;
    T sum;
    void set_min(T x) {
      if (first_largest <= x) {
        return;
      }
      sum -= (first_largest - x) * first_largest_cnt;
      first_largest = x;
      if (first_smallest >= x) {
        first_smallest = x;
      }
      second_smallest = Min(second_smallest, x);
      if (second_smallest == first_smallest) {
        second_smallest = INF;
      }
      ASSERTION_STUB
    }
    void set_max(T x) {
      if (first_smallest >= x) {
        return;
      }
      sum += (x - first_smallest) * first_smallest_cnt;
      first_smallest = x;
      if (first_largest <= x) {
        first_largest = x;
      }
      second_largest = Max(second_largest, x);
      if (second_largest == first_largest) {
        second_largest = -INF;
      }
      ASSERTION_STUB
    }
    void modify(T x) {
      dirty += x;
      sum += x * size;
      first_smallest += x;
      first_largest += x;
      second_smallest += x;
      second_largest += x;
      ASSERTION_STUB
    }
    void push_up() {
      first_largest = Max(left->first_largest, right->first_largest);
      second_largest =
          Max(left->first_largest == first_largest ? left->second_largest
                                                   : left->first_largest,
              right->first_largest == first_largest ? right->second_largest
                                                    : right->first_largest);
      first_largest_cnt =
          (left->first_largest == first_largest ? left->first_largest_cnt : 0) +
          (right->first_largest == first_largest ? right->first_largest_cnt
                                                 : 0);
      first_smallest = Min(left->first_smallest, right->first_smallest);
      second_smallest =
          Min(left->first_smallest == first_smallest ? left->second_smallest
                                                     : left->first_smallest,
              right->first_smallest == first_smallest ? right->second_smallest
                                                      : right->first_smallest);
      first_smallest_cnt =
          (left->first_smallest == first_smallest ? left->first_smallest_cnt
                                                  : 0) +
          (right->first_smallest == first_smallest ? right->first_smallest_cnt
                                                   : 0);
      sum = left->sum + right->sum;
      size = left->size + right->size;
      ASSERTION_STUB
    }
    void push_down() {
      if (dirty != 0) {
        left->modify(dirty);
        right->modify(dirty);
        dirty = 0;
      }
      left->set_min(first_largest);
      right->set_min(first_largest);
      left->set_max(first_smallest);
      right->set_max(first_smallest);
    }
    Node(int l, int r, const Indexer<T> &indexer) : left(NULL), right(NULL) {
      if (l < r) {
        int m = (l + r) / 2;
        left = new Self(l, m, indexer);
        right = new Self(m + 1, r, indexer);
        push_up();
      } else {
        sum = first_smallest = first_largest = indexer(l);
        first_smallest_cnt = first_largest_cnt = 1;
        second_smallest = INF;
        second_largest = -INF;
        size = 1;
        ASSERTION_STUB
      }
    }
    void update_min(int L, int R, int l, int r, T x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        if (first_largest <= x) {
          return;
        }
        if (second_largest < x) {
          set_min(x);
          return;
        }
      }
      push_down();
      int m = (l + r) / 2;
      left->update_min(L, R, l, m, x);
      right->update_min(L, R, m + 1, r, x);
      push_up();
    }
    void update_max(int L, int R, int l, int r, T x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        if (first_smallest >= x) {
          return;
        }
        if (second_smallest > x) {
          set_max(x);
          return;
        }
      }
      push_down();
      int m = (l + r) / 2;
      left->update_max(L, R, l, m, x);
      right->update_max(L, R, m + 1, r, x);
      push_up();
    }
    void update(int L, int R, int l, int r, T x) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        modify(x);
        return;
      }
      push_down();
      int m = (l + r) / 2;
      left->update(L, R, l, m, x);
      right->update(L, R, m + 1, r, x);
      push_up();
    }
    T query_sum(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return 0;
      }
      if (SegmentCover(L, R, l, r)) {
        return sum;
      }
      push_down();
      int m = (l + r) / 2;
      return left->query_sum(L, R, l, m) + right->query_sum(L, R, m + 1, r);
    }
    T query_max(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return -INF;
      }
      if (SegmentCover(L, R, l, r)) {
        return first_largest;
      }
      push_down();
      int m = (l + r) / 2;
      return Max(left->query_max(L, R, l, m), right->query_max(L, R, m + 1, r));
    }
    T query_min(int L, int R, int l, int r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return -INF;
      }
      if (SegmentCover(L, R, l, r)) {
        return first_smallest;
      }
      push_down();
      int m = (l + r) / 2;
      return Max(left->query_min(L, R, l, m), right->query_min(L, R, m + 1, r));
    }
    void travel(T max_val, T min_val, T mod, Consumer<T> &consumer) const {
      if (left == NULL) {
        T ans = sum + mod;
        ans = Min(ans, max_val);
        ans = Max(ans, min_val);
        consumer(ans);
        return;
      }
      T new_mod = dirty + mod;
      T new_max_val = Min(max_val, first_largest + mod);
      T new_min_val = Max(min_val, first_smallest + mod);
      left->travel(new_max_val, new_min_val, new_mod, consumer);
      right->travel(new_max_val, new_min_val, new_mod, consumer);
    }
#ifdef DROP
    ~Node() {
      delete left;
      delete right;
    }
#endif
  };
  Node *tree;
  int n;
 public:
  using Self = SegTreeBeatExt<T>;
  SegTreeBeatExt(int _n, const Indexer<T> &indexer) : n(_n) {
    tree = new Node(0, n - 1, indexer);
  }
  inline void update_min(int L, int R, T x) {
    tree->update_min(L, R, 0, n - 1, x);
  }
  inline void update_max(int L, int R, T x) {
    tree->update_max(L, R, 0, n - 1, x);
  }
  inline void update(int L, int R, T x) { tree->update(L, R, 0, n - 1, x); }
  inline T query_sum(int L, int R) { return tree->query_sum(L, R, 0, n - 1); }
  inline T query_max(int L, int R) { return tree->query_max(L, R, 0, n - 1); }
  inline T query_min(int L, int R) { return tree->query_min(L, R, 0, n - 1); }
  void travel(Consumer<T> &consumer) const {
    tree->travel(Node::INF, -Node::INF, 0, consumer);
  }
  Vec<T> to_vec() const {
    Vec<T> res;
    res.reserve(n);
    Consumer<T> consumer = [&](auto x) { res.push_back(x); };
    travel(consumer);
    return res;
  }
#ifdef DROP
  ~SegTreeBeatExt() { delete tree; }
#endif
};
#undef ASSERTION_STUB
}  // namespace sbt
}  // namespace dalt
namespace dalt {
namespace graph {
template <class T, class E,
          class = enable_if_t<is_base_of_v<WithTo, E> &&
                              is_base_of_v<WithWeight<T>, E>>>
Tuple<Vec<T>, Vec<int>> ShortestPathWeightElogE(const Graph<E> &g,
                                                const Checker<int> &is_source,
                                                T inf) {
  using State = Tuple<T, int, int>;
  int n = Size(g);
  MinHeap<State> heap;
  Vec<T> dist(n, inf);
  Vec<int> prev(n, -1);
  for (int i = 0; i < n; i++) {
    if (is_source(i)) {
      heap.push(State(0, i, -1));
    }
  }
  while (!heap.empty()) {
    auto state = heap.top();
    heap.pop();
    int root = std::get<1>(state);
    T d = std::get<0>(state);
    if (dist[root] <= d) {
      continue;
    }
    dist[root] = d;
    prev[root] = std::get<2>(state);
    for (auto &e : g[root]) {
      heap.push(State(d + e.weight, e.to, root));
    }
  }
  return Tuple<Vec<T>, Vec<int>>(dist, prev);
}
template <class T, class E,
          class = enable_if_t<is_base_of_v<WithTo, E> &&
                              is_base_of_v<WithWeight<T>, E>>>
Tuple<Vec<T>, Vec<int>> ShortestPathWeightElogV(const Graph<E> &g,
                                                const Checker<int> &is_source,
                                                T inf) {
  int n = Size(g);
  Vec<T> dist(n, inf);
  Vec<int> prev(n, -1);
  TreeSet<i32, Comparator<i32>> set([&](auto a, auto b) {
    return Tuple<T, i32>(dist[a], a) < Tuple<T, i32>(dist[b], b);
  });
  for (int i = 0; i < n; i++) {
    if (is_source(i)) {
      dist[i] = 0;
      set.insert(i);
    }
  }
  while (!set.empty()) {
    auto top = set.begin();
    int root = *top;
    set.erase(top);
    for (auto &e : g[root]) {
      if (dist[e.to] > dist[root] + e.weight) {
        set.erase(e.to);
        dist[e.to] = dist[root] + e.weight;
        prev[e.to] = root;
        set.insert(e.to);
      }
    }
  }
  return Tuple<Vec<T>, Vec<int>>(dist, prev);
}
} // namespace graph
} // namespace dalt
namespace dalt {
template <class T> struct SparseTable {
private:
  Vec<Vec<T>> table;
  Reducer<T> reducer;
public:
  using Self = SparseTable<T>;
  SparseTable(int n, const Indexer<T> &data, Reducer<T> f) : reducer(f) {
    i32 m = Log2Floor(u32(n));
    table = Vec<Vec<T>>(m + 1, Vec<T>(n));
    for(int i = 0; i < n; i++){
      table[0][i] = data(i);
    }
    for (i32 i = 0; i < m; i++) {
      i32 step = 1 << i;
      for (i32 j = 0; j < n; j++) {
        if (j + step < n) {
          table[i + 1][j] = reducer(table[i][j], table[i][j + step]);
        } else {
          table[i + 1][j] = table[i][j];
        }
      }
    }
  }
  T query(i32 l, i32 r) const {
    int len = r - l + 1;
    int log_floor = Log2Floor(u32(len));
    return reducer(table[log_floor][l],
                   table[log_floor][r + 1 - (1 << log_floor)]);
  }
};
} // namespace dalt
namespace dalt {
// verified by: https://codeforces.com/contest/713/problem/D
template <class T>
struct SparseTable2 {
 private:
  Vec<Vec<Vec<Vec<T>>>> data;
  Reducer<T> reducer;
 public:
  //O(nm\log n\log m)
  SparseTable2(int n, int m, const Indexer2<T> &indexer,
               const Reducer<T> &_reducer)
      : reducer(_reducer) {
    int logn = Log2Floor(n);
    int logm = Log2Floor(m);
    data = Vec<Vec<Vec<Vec<T>>>>(
        logn + 1, Vec<Vec<Vec<T>>>(n, Vec<Vec<T>>(logm + 1, Vec<T>(m))));
    for (int i = 0; i <= logn; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k <= logm; k++) {
          for (int t = 0; t < m; t++) {
            if (i == 0 && k == 0) {
              data[i][j][k][t] = indexer(j, t);
            } else if (i == 0) {
              data[i][j][k][t] =
                  reducer(data[i][j][k - 1][t],
                          data[i][j][k - 1][Min(t + (1 << k - 1), m - 1)]);
            } else if (k == 0) {
              data[i][j][k][t] =
                  reducer(data[i - 1][j][k][t],
                          data[i - 1][Min(j + (1 << i - 1), n - 1)][k][t]);
            } else {
              T ans = reducer(data[i - 1][j][k][t],
                              data[i - 1][Min(j + (1 << i - 1), n - 1)][k][t]);
              ans = reducer(data[i - 1][j][k - 1][Min(t + (1 << k - 1), m - 1)],
                            ans);
              ans = reducer(data[i - 1][Min(j + (1 << i - 1), n - 1)][k - 1]
                                [Min(t + (1 << k - 1), m - 1)],
                            ans);
              data[i][j][k][t] = ans;
            }
          }
        }
      }
    }
  }
  //O(1)
  T query(int b, int t, int l, int r) const {
    int h = t - b + 1;
    int w = r - l + 1;
    int logh = Log2Floor(h);
    int logw = Log2Floor(w);
    T ans = reducer(data[logh][b][logw][l],
                    data[logh][t + 1 - (1 << logh)][logw][l]);
    ans = reducer(data[logh][b][logw][r + 1 - (1 << logw)], ans);
    ans = reducer(data[logh][t + 1 - (1 << logh)][logw][r + 1 - (1 << logw)],
                  ans);
    return ans;
  }
};
}  // namespace dalt
namespace dalt {
namespace misc {
template <class T, class C = Less<T>>
struct StaticRectQuery {
  using Self = StaticRectQuery<T>;
  using PST = sbt::SegTree<sbt::SelfBalanceTreeRegistry<i32, i32, 0, Self>, i32, i32, true, false, 0>;
  using Node = typename PST::Node;
 private:
  Vec<PST> psts;
  Vec<T> sorted_input;
  C comp;
  struct InitJob {
    InitJob() {
      PST::Register(
          0, 0, [](auto a, auto b) { return a + b; },
          [](auto a, auto b) { return a + b; },
          [](auto a, auto b) { return a + b; });
    }
  };
  static InitJob _init_job;
 public:
  StaticRectQuery(int n, const Indexer<T> &indexer, C _comp = C())
      : comp(_comp) {
    sorted_input = ExpandIndexer(n, indexer);
    Sort(All(sorted_input), comp);
    MakeUnique(sorted_input);
    psts.reserve(n + 1);
    psts.push_back(PST::MakePersistentTree(Size(sorted_input)));
    // debug(psts.back().to_vec());
    for (int i = 0; i < n; i++) {
      int val = LowerBound(All(sorted_input), indexer(i), comp) -
                sorted_input.begin();
      psts.push_back(psts.back().clone());
      psts.back().update(val, val, 1);
      // debug(psts.back().to_vec());
    }
  }
  int count_rect_point(int L, int R, T below, T top) {
    int below_value =
        LowerBound(All(sorted_input), below, comp) - sorted_input.begin();
    int top_value =
        (UpperBound(All(sorted_input), top, comp) - sorted_input.begin()) - 1;
    int plus = psts[R + 1].query_const(below_value, top_value);
    int sub = psts[L].query_const(below_value, top_value);
    return plus - sub;
  }
  Optional<T> kth_lowest_point(int L, int R, int k) {
    auto dfs = [&](auto &dfs, Node *a, Node *b, int l, int r,
                   int k) -> Optional<i32> {
      if (l == r) {
        if (k <= b->sum - a->sum) {
          return l;
        } else {
          return {};
        }
      }
      int m = (l + r) / 2;
      int left_cnt = b->left->sum - a->left->sum;
      if (left_cnt >= k) {
        return dfs(dfs, a->left, b->left, l, m, k);
      } else {
        return dfs(dfs, a->right, b->right, m + 1, r, k - left_cnt);
      }
    };
    // debug(psts[L].to_vec());
    // debug(psts[R + 1].to_vec());
    Optional<i32> offset =
        dfs(dfs, psts[L].tree, psts[R + 1].tree, 0, Size(sorted_input) - 1, k);
    return offset.map<T>([&](int i) { return sorted_input[i]; });
    // return res;
  }
};
template <class T, class C>
typename StaticRectQuery<T, C>::InitJob StaticRectQuery<T, C>::_init_job;
}  // namespace dalt
}
namespace dalt {
const i32 SHIFT = 5;
const i32 BLOCK_SIZE = 1 << SHIFT;
const i32 AND_MASK = BLOCK_SIZE - 1;
struct StaticRMQ {
private:
  Vec<i32> to_left;
  Comparator<i32> comparator;
  SparseTable<i32> *st;
  i32 minor(i32 a, i32 b) { return comparator(a, b) <= 0 ? a : b; }
public:
  using Self = StaticRMQ;
  StaticRMQ(int n, Comparator<i32> arg_comparator)
      : comparator(arg_comparator) {
    int consider_part = ((n - 1) >> SHIFT) + 1;
    Vec<i32> min_indices = Vec<i32>(consider_part, -1);
    to_left = Vec<i32>(n);
    for (int i = 0; i < n; i++) {
      int to = i >> SHIFT;
      if (min_indices[to] == -1 || comparator(i, min_indices[to])) {
        min_indices[to] = i;
      }
    }
    st = new SparseTable<i32>(consider_part, MakeIndexer<i32>(min_indices),
                              comparator);
    int mask = 0;
    for (int i = 0; i < n; i++) {
      if ((i & AND_MASK) == 0) {
        mask = 0;
      }
      int b = i >> SHIFT;
      while (mask != 0) {
        int head = HighestOneBitOffset(mask);
        if (!comparator((b << SHIFT) | head, i)) {
          mask = ClearBit(mask, head);
        } else {
          break;
        }
      }
      mask = SetBit(mask, i & AND_MASK);
      to_left[i] = mask;
    }
  }
  i32 query(int l, int r) {
    Assert(l <= r);
    int bl = l >> SHIFT;
    int br = r >> SHIFT;
    int tl = l & AND_MASK;
    //        int tr = r & AND_MASK;
    if (bl == br) {
      return TrailingZeroNumber(to_left[r] & HighestKOnes32(32 - tl)) |
             (bl << SHIFT);
    }
    int res1 = TrailingZeroNumber(to_left[(bl << SHIFT) | AND_MASK] &
                                  HighestKOnes32(32 - tl)) |
               (bl << SHIFT);
    int res2 = TrailingZeroNumber(to_left[r]) | (br << SHIFT);
    int best = minor(res1, res2);
    if (bl + 1 < br) {
      best = minor(best, st->query(bl + 1, br - 1));
    }
    return best;
  }
#ifdef DROP
  ~StaticRMQ() { delete st; }
#endif
};
} // namespace dalt
namespace dalt {
namespace math {
template <class T>
struct FirstKindStirlingNumberResult {
  Vec<T> data;
  int n;
  // c(n, i) = ways to split n elements into k loops
  T get_unsign(int i) const { return data[i]; }
  T get_sign(int i) const {
    if ((n - i) & 1) {
      return -data[i];
    }
    return data[i];
  }
};
//O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>,
            FirstKindStirlingNumberResult<typename C::Type>>
FirstKindStirlingNumber(int n) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  Combination<T> comb(n + 1);
  auto dfs = [&](auto &dfs, int n) -> Poly {
    if (n == 0) {
      return Poly(T(1));
    }
    if (n & 1) {
      Vec<T> ans = dfs(dfs, n - 1).data;
      ans.resize(n + 1);
      for (int i = n; i >= 0; i--) {
        ans[i] *= T(n - 1);
        if (i >= 1) {
          ans[i] += ans[i - 1];
        }
      }
      return Poly(Move(ans));
    } else {
      int half = n / 2;
      auto ans = dfs(dfs, half);
      Vec<T> A(half + 1);
      Vec<T> B(half + 1);
      T ni = T(1);
      for (int i = 0; i <= half; i++) {
        A[i] = ans[i] * comb.fact[i];
        B[i] = ni * comb.inv_fact[i];
        ni *= T(half);
      }
      auto delta = Poly(Move(A)).delta_convolution(Poly(Move(B)));
      for (int i = 0; i <= delta.rank() && i <= half; i++) {
        delta.data[i] *= comb.inv_fact[i];
      }
      // Debug(n);
      // Debug((delta * ans).to_vec());
      return delta * ans;
    }
  };
  auto ans = dfs(dfs, n).data;
  ans.resize(n + 1);
  return FirstKindStirlingNumberResult<T>{
      .data = Move(ans),
      .n = n,
  };
}
//ret[i] = ways to split n number into i subset
//time complexity: O(n\log n)
template <class C>
enable_if_t<poly::is_convolution_v<C>, Vec<typename C::Type>>
SecondKindStirlingNumber(int n) {
  using T = typename C::Type;
  using Poly = poly::Polynomial<C>;
  Combination<T> comb(n);
  Vec<T> a(n + 1);
  Vec<T> b(n + 1);
  auto pow = EulerSieve::powmod<T>(n + 1, n);
  for (int i = 0; i <= n; i++) {
    a[i] = comb.inv_fact[i];
    if (i & 1) {
      a[i] = -a[i];
    }
    b[i] = comb.inv_fact[i] * pow[i];
  }
  auto c = (Poly(Move(a)) * Poly(Move(b))).data;
  c.resize(n + 1);
  return c;
}
}  // namespace math
}  // namespace dalt
#ifndef ATCODER_STRING_HPP
#define ATCODER_STRING_HPP 1
#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>
namespace atcoder {
namespace internal {
std::vector<int> sa_naive(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r) return false;
        while (l < n && r < n) {
            if (s[l] != s[r]) return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}
std::vector<int> sa_doubling(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}
// SA-IS, linear-time suffix array construction
// Reference:
// G. Nong, S. Zhang, and W. H. Chan,
// Two Efficient Algorithms for Linear Time Suffix Array Construction
template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }
    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }
    auto induce = [&](const std::vector<int>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };
    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }
    induce(lms);
    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1) sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }
        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);
        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}
}  // namespace internal
std::vector<int> suffix_array(const std::vector<int>& s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = internal::sa_is(s, upper);
    return sa;
}
template <class T> std::vector<int> suffix_array(const std::vector<T>& s) {
    int n = int(s.size());
    std::vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int l, int r) { return s[l] < s[r]; });
    std::vector<int> s2(n);
    int now = 0;
    for (int i = 0; i < n; i++) {
        if (i && s[idx[i - 1]] != s[idx[i]]) now++;
        s2[idx[i]] = now;
    }
    return internal::sa_is(s2, now);
}
std::vector<int> suffix_array(const std::string& s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return internal::sa_is(s2, 255);
}
// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
template <class T>
std::vector<int> lcp_array(const std::vector<T>& s,
                           const std::vector<int>& sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}
std::vector<int> lcp_array(const std::string& s, const std::vector<int>& sa) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return lcp_array(s2, sa);
}
// Reference:
// D. Gusfield,
// Algorithms on Strings, Trees, and Sequences: Computer Science and
// Computational Biology
template <class T> std::vector<int> z_algorithm(const std::vector<T>& s) {
    int n = int(s.size());
    if (n == 0) return {};
    std::vector<int> z(n);
    z[0] = 0;
    for (int i = 1, j = 0; i < n; i++) {
        int& k = z[i];
        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
}
std::vector<int> z_algorithm(const std::string& s) {
    int n = int(s.size());
    std::vector<int> s2(n);
    for (int i = 0; i < n; i++) {
        s2[i] = s[i];
    }
    return z_algorithm(s2);
}
}  // namespace atcoder
#endif  // ATCODER_STRING_HPP
FunctionAlias(atcoder::suffix_array, SuffixArray);
FunctionAlias(atcoder::lcp_array, LongestCommonPrefixArray);
namespace dalt {
namespace graph {
template <class E>
IsDiGraph(E, Optional<Vec<int>>) TopoSort(const Graph<E> &g) {
  int n = Size(g);
  Vec<bool> visited(n);
  Vec<bool> instk(n);
  bool ok = true;
  Vec<int> res;
  res.reserve(n);
  auto dfs = [&](auto &dfs, int root) {
    if (visited[root]) {
      if(instk[root]) {
        ok = false;
      }
      return;
    }
    visited[root] = true;
    instk[root] = true;
    for (auto &e : g[root]) {
      dfs(dfs, e.to);
    }
    res.push_back(root);
    instk[root] = false;
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  if(!ok) {
    return {};
  }
  return res;
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace sbt {
template <class SBT, class S, class U, i64 ID = 0, bool P = false, bool DIR = false>
struct Treap : protected SbtReverse<S, U, DIR, SBT> {
 static_assert(is_sbt_registry_v<SBT>);
 private:
  using Self = Treap<SBT, S, U, ID, P, DIR>;
  using AT2 = Array<Self *, 2>;
  AT2 split_by_weight_first_true(const Checker<S> &checker, bool &find) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (checker(weight)) {
      res = left->split_by_weight_first_true(checker, find);
      if (!find) {
        res[1] = right;
        right = NULL;
        res->left = res[0];
        res[0] = this;
        find = true;
      } else {
        left = res[1];
        res[1] = this;
      }
    } else {
      res = right->split_by_weight_first_true(checker, find);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  IsBool(!P,void) do_perm() {}
  IsBool(P, void) do_perm() {
    left = left->clone();
    right = right->clone();
  }
  Treap(bool x) {}
  void travel(const U &u, const bool &rev_upd,
              const Consumer<S> &consumer) const {
    if (this == NIL) {
      return;
    }
    U new_upd = SBT::u_u(upd, u);
    bool new_rev_upd = rev_upd != rev;
    (new_rev_upd ? right : left)->travel(new_upd, new_rev_upd, consumer);
    consumer(SBT::s_u(weight, u));
    (new_rev_upd ? left : right)->travel(new_upd, new_rev_upd, consumer);
  }
 public:
  static Self *NIL;
  static void Register(S s_nil, U u_nil, const Adder<S, S> &_s_s,
                       const Adder<S, U> &_s_u, const Adder<U, U> &_u_u) {
    if (NIL != NULL) {
      delete NIL;
    }
    NIL = new Self(true);
    NIL->sum = s_nil;
    NIL->upd = u_nil;
    NIL->weight = s_nil;
    NIL->size = 0;
    NIL->id = -1;
    NIL->rev = false;
    NIL->left = NIL->right = NIL;
    SBT::Register(s_nil, u_nil, _s_s, _s_u,
                                                 _u_u);
  }
  Treap(int _id = 0, S _sum = S())
      : sum(_sum),
        weight(_sum),
        id(_id),
        size(1),
        upd(NIL->upd),
        left(NIL),
        right(NIL),
        rev(false) {
    this->init_sum_rev(SBT::s_nil);
  }
  S sum;
  U upd;
  S weight;
  int size;
  int id;
  Self *left;
  Self *right;
  bool rev;
  void reverse() {
    rev = !rev;
    this->swap_sum_rev(sum);
  }
  Self *clone() {
    if (this == NIL) {
      return this;
    }
    return new Self(*this);
  }
  void push_up() {
    if (this == NIL) {
      return;
    }
    sum = SBT::s_s(SBT::s_s(left->sum, weight), right->sum);
    this->push_up_sum_rev(*left, *right);
    size = left->size + 1 + right->size;
  }
  void modify(const U &u) {
    if (this == NIL) {
      return;
    }
    sum = SBT::s_u(sum, u);
    upd = SBT::u_u(upd, u);
    weight = SBT::s_u(weight, u);
    this->apply_sum_rev(u);
  }
  void push_down() {
    if (this == NIL) {
      return;
    }
    do_perm();
    if (rev) {
      Swap(left, right);
      left->reverse();
      right->reverse();
      rev = false;
    }
    if (upd != NIL->upd) {
      left->modify(upd);
      right->modify(upd);
      upd = NIL->upd;
    }
  }
  AT2 split_by_rank(int k) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (left->size >= k) {
      res = left->split_by_rank(k);
      left = res[1];
      res[1] = this;
    } else {
      res = right->split_by_rank(k - 1 - left->size);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  AT2 split_by_weight_first_true(const Checker<S> &checker) {
    bool find = false;
    return split_by_weight_first_true(checker, find);
  }
  AT2 split_by_weight_last_true(const Checker<S> &checker) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    if (!checker(weight)) {
      res = left->split_by_weight_last_true(checker);
      left = res[1];
      res[1] = this;
    } else {
      res = right->split_by_weight_last_true(checker);
      right = res[0];
      res[0] = this;
    }
    push_up();
    return res;
  }
  AT2 split_by_sum_first_true(const Checker<S> &checker, S &s) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    S s_1 = s_s(s, left->sum);
    if (checker(s_1)) {
      res = left->split_by_weight_first_true(checker, s);
      left = res[1];
      res[1] = this;
    } else {
      s = s_1;
      S s_2 = s_s(s, weight);
      if (checker(s_2)) {
        res[1] = right;
        right = NULL;
      } else {
        s = s_2;
        res = right->split_by_sum_first_true(checker, s);
        right = res[0];
        res[0] = this;
      }
    }
    push_up();
    return res;
  }
  AT2 split_by_sum_last_true(const Checker<S> &checker, S &s) {
    if (this == NIL) {
      return AT2{NIL, NIL};
    }
    push_down();
    AT2 res;
    S s_1 = s_s(s_s(s, left->sum), weight);
    if (checker(s_1)) {
      s = s_1;
      res = right->split_by_sum_last_true(checker, s);
      right = res[0];
      res[0] = this;
    } else {
      res = left->split_by_sum_last_true(checker, s);
      left = res[1];
      res[1] = this;
    }
    push_up();
    return res;
  }
  static Self *merge(AT2 ab) { return merge(ab[0], ab[1]); }
  static Self *merge(Self *a, Self *b) {
    if (a == NIL) {
      return b;
    }
    if (b == NIL) {
      return a;
    }
    if (random_choice(1, a->size + b->size) <= a->size) {
      a->push_down();
      a->right = merge(a->right, b);
      a->push_up();
      return a;
    } else {
      b->push_down();
      b->left = merge(a, b->left);
      b->push_up();
      return b;
    }
  }
  void travel(const Consumer<S> &consumer) const {
    bool rev_upd = false;
    travel(NIL->upd, rev_upd, consumer);
  }
  Vec<S> to_vec() const {
    Vec<S> res;
    travel(NIL->upd, false, [&](auto x) { res.push_back(x); });
    return res;
  }
};
template <class SBT, class S, class U, i64 ID, bool P, bool DIR>
Treap<SBT, S, U, ID, P, DIR> *Treap<SBT, S, U, ID, P, DIR>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
namespace dalt {
namespace graph {
template <class E>
enable_if_t<is_base_of_v<BiBaseEdge, E>, Tuple<i32, i32, i32>>
TreeDiameter(const Graph<E> &g) {
  auto depth0 = DepthOnTree(g, [&](i32 i) { return i == 0; });
  int a = *std::max_element(All(depth0));
  auto depth1 = DepthOnTree(g, [&](i32 i) { return i == a; });
  int b = *std::max_element(All(depth1));
  return Tuple<i32, i32, i32>(depth1[b], a, b);
}
template <class T, class E>
enable_if_t<is_base_of_v<BiBaseEdge, E> && is_base_of_v<WithWeight<T>, E>,
            Tuple<T, i32, i32>>
TreeDiameterWeight(const Graph<E> &g) {
  auto depth0 = DepthOnTreeWeight<T>(g, [&](auto i) { return i == 0; });
  int a = std::max_element(All(depth0)) - depth0.begin();
  auto depth1 = DepthOnTreeWeight<T>(g, [&](auto i) { return i == a; });
  int b = std::max_element(All(depth1)) - depth1.begin();
  return Tuple<T, i32, i32>(depth1[b], a, b);
}
template <class E>
enable_if_t<is_base_of_v<BiBaseEdge, E>, Tuple<i32, i32, i32>>
ForestDiameter(const Graph<E> &g) {
  int n = Size(g);
  DSU dsu(n);
  for (int i = 0; i < n; i++) {
    for (auto &e : g[i]) {
      dsu.merge(i, e.to);
    }
  }
  auto depth0 = DepthOnTree(g, [&](auto i) { return dsu.find(i) == i; });
  Vec<i32> roots(n, -1);
  for (int i = 0; i < n; i++) {
    int p = dsu.find(i);
    if (roots[p] == -1 || depth0[roots[p]] < depth0[i]) {
      roots[p] = i;
    }
  }
  auto depth1 = DepthOnTree(g, [&](auto i) { return roots[dsu.find(i)] == i; });
  int b = *std::max_element(All(depth1));
  return Tuple<i32, i32, i32>(depth1[b], roots[dsu.find(b)], b);
}
template <class T, class E>
enable_if_t<is_base_of_v<WithWeight<T>, E> && is_base_of_v<BiBaseEdge, E>,
            Tuple<T, i32, i32>>
ForestDiameter(const Graph<E> &g) {
  int n = Size(g);
  DSU dsu(n);
  for (int i = 0; i < n; i++) {
    for (auto &e : g[i]) {
      dsu.merge(i, e.to);
    }
  }
  auto depth0 = DepthOnTree(g, [&](auto i) { return dsu.find(i) == i; });
  Vec<i32> roots(n, -1);
  for (int i = 0; i < n; i++) {
    int p = dsu.find(i);
    if (roots[p] == -1 || depth0[roots[p]] < depth0[i]) {
      roots[p] = i;
    }
  }
  auto depth1 = DepthOnTree(g, [&](auto i) { return roots[dsu.find(i)] == i; });
  int b = *std::max_element(All(depth1));
  return Tuple<T, i32, i32>(depth1[b], roots[dsu.find(b)], b);
}
} // namespace graph
} // namespace dalt
namespace dalt {
namespace trie {
template <class S = Nil, int C = 26, i64 ID = 0> struct Trie {
  using Self = Trie<S, C, ID>;
  static S s_nil;
  static void Register(S _s_nil) { s_nil = _s_nil; }
  S sum;
  Self *next[C];
  Trie() : sum(s_nil) { memset(next, 0, sizeof(Self *) * C); }
  Self *get_or_create(int index) {
    if (next[index] == NULL) {
      next[index] = new Self();
    }
    return next[index];
  }
  Optional<Self *> get(int index) {
    if (next[index] == NULL) {
      return {};
    } else {
      return next[index];
    }
  }
  bool exist(int index) { return next[index] != NULL; }
  Self *operator[](int index) { return get_or_create(index); }
};
template <class S, int C, i64 ID> S Trie<S, C, ID>::s_nil = S();
} // namespace trie
using trie::Trie;
} // namespace dalt
namespace dalt {
template <class T>
struct VersionArray {
  using Self = VersionArray<T>;
  Vec<T> data;
  Vec<int> version;
  int timestamp = 0;
  T def;
  VersionArray(int n, T _def = T()) : def(_def) {
    data = Vec<T>(n);
    version = Vec<int>(n);
    timestamp = 1;
  }
  void access(int i) {
    if (version[i] < timestamp) {
      version[i] = timestamp;
      data[i] = def;
    }
  }
  T& operator[](int i) {
    access(i);
    return data[i];
  }
  const T& operator[](int i) const {
    access(i);
    return data[i];
  }
  int size() { return Size(data); }
  void clear() {
    timestamp++;
  }
  void clear(int _def) {
    def = _def;
    clear();
  }
};
}  // namespace dalt
namespace dalt {
template <class T>
struct XorValue {
  using Self = XorValue<T>;
  static_assert(is_integral_v<T>);
  T value;
  XorValue(T _value) : value(_value) {}
  bool operator==(const Self& rhs) { return value == rhs.value; }
  bool operator!=(const Self& rhs) { return value != rhs.value; }
  Self operator+(const Self& rhs) { return value ^ rhs.value; }
  Self operator-(const Self& rhs) { return value ^ rhs.value; }
};
template <class T>
OStream& operator<<(OStream& os, const XorValue<T>& rhs) {
  os << rhs.value;
  return os;
}
}  // namespace dalt
namespace dalt {
namespace seq {
//Z[i] = longest common prefix of s and s[i..]
template <class T>
Vec<i32> ZAlgorithm(int n, const Indexer<T> &s) {
  if (n == 0) {
    return Vec<i32>();
  }
  int l = 0;
  int r = -1;
  Vec<i32> z(n);
  z[0] = n;
  for (int i = 1; i < n; i++) {
    if (r < i) {
      l = r = i;
    } else {
      int t = i - l;
      int k = r - i + 1;
      if (z[t] < k) {
        z[i] = z[t];
        continue;
      }
      l = i;
      r++;
    }
    while (r < n && s(r - l) == s(r)) {
      r++;
    }
    r--;
    z[i] = r - l + 1;
  }
  return z;
}
}  // namespace seq
}  // namespace dalt
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
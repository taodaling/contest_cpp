//Timestamp: 2023-05-08 14:39:19
#define DROP
#ifdef ONLINE
#undef LOCAL
#endif
#ifndef LOCAL
#undef _GLIBCXX_DEBUG
#undef _DEBUG
#endif
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
#define DebugPoint int _x_ = 0; _x_++;
#else
#define Debug(...) 42
#define DebugFmtln(...) 42
#define Assert(x) 42
#define DebugRun(X)
#define DebugPoint
#endif
#define Trace(x) DebugFmtln("Line %d: %s", __LINE__, #x)
template<class T>
inline T DebugRet(T x) {
    Debug(x);
    return x;
}
#define const_ref(T) const T &
#define mut_ref(T) T &
#define let auto
#define var auto
#define MEMSET0(X) std::memset(&X, 0, sizeof(X)) 
#define Size(T) int((T).size())
#define All(data) data.begin(), data.end()
#define MakeUnique(data) data.resize(std::unique(All(data)) - data.begin())
#define MakeUniqueAndSort(data) Sort(All(data)); MakeUnique(data) 
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
FunctionAlias(std::acos, Acos);
FunctionAlias(std::tan, Tan);
FunctionAlias(std::atan, Atan);
FunctionAlias(std::sort, Sort);
FunctionAlias(std::fill, Fill);
FunctionAlias(std::move, Move);
FunctionAlias(std::reverse, Reverse);
FunctionAlias(std::max_element, MaxElement);
FunctionAlias(std::min_element, MinElement);
FunctionAlias(std::make_tuple, MakeTuple);
FunctionAlias(std::make_pair, MakePair);
FunctionAlias(std::clamp, Clamp);
FunctionAlias(std::shuffle, Shuffle);
FunctionAlias(std::to_string, ToString);
FunctionAlias(std::tie, Tie);
template <typename _Signature>
using Function = std::function<_Signature>;
template <typename _Signature>
using Func = Function<_Signature>;
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
using Reducer = Func<T(const T &, const T &)>;
template <class T>
using Comparator = Func<bool(const T &, const T &)>;
template <class T>
using Indexer = Func<T(i32)>;
template <class T>
using Indexer2 = Func<T(i32, i32)>;
template <class A, class B = A, class C = A>
using Adder = Func<C(const A &, const B &)>;
template <class I>
using Checker = Func<bool(const I &)>;
template <class A, class B>
using BiChecker = Func<bool(const A &, const B &)>;
template <class T>
using Consumer = Func<void(const T &)>;
template<class T>
using Supplier = Func<T()>;
template <class FIRST, class SECOND>
using BiConsumer = Func<void(const FIRST &, const SECOND &)>;
template <class F, class T = F>
using Mapper = Func<T(const F &)>;
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
template <class T>
bool operator<(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) < 0;
}
template <class T>
bool operator>(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) > 0;
}
template <class T>
bool operator<=(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) <= 0;
}
template <class T>
bool operator>=(const Vec<T>& lhs, const Vec<T>& rhs) {
  return Compare(lhs, rhs) >= 0;
}
}  // namespace dalt
//#include "array_adder.cpp"
using namespace dalt;
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
  static bool initialized;
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
bool SelfBalanceTreeRegistry<S, U, ID, CID>::initialized = false;
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
template<class T = i32>
inline bool SegmentNoIntersection(T L, T R, T l, T r) {
  return R < l || r < L;
}
template <class T = i32>
inline bool SegmentCover(T L, T R, T l, T r) {
  return L <= l && r <= R;
}
}  // namespace sbt
}  // namespace dalt
namespace dalt {
namespace sbt {
#define CLASS_ID -202202131500
template <class SBT, bool P = false, bool SPARSE = false, i64 ID = 0>
struct SegTree {
  static_assert(is_sbt_registry_v<SBT>);
  static_assert(i64(P) + i64(SPARSE) <= 1);
  using S = typename SBT::TypeS;
  using U = typename SBT::TypeU;
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
  using Self = SegTree<SBT, P, SPARSE, ID>;
  static Node *NIL;
  Node *tree;
  i64 n;
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
      i64 _n = 0,
      const Indexer<S> &indexer = [](i64 index) { return SBT::s_nil; })
      : n(_n) {
    auto dfs = [&](auto &dfs, i64 l, i64 r) -> Node * {
      Node *root = make_tree();
      root->upd = SBT::u_nil;
      if (l == r) {
        root->sum = indexer(l);
      } else {
        i64 m = (l + r) / 2;
        root->left = dfs(dfs, l, m);
        root->right = dfs(dfs, m + 1, r);
        root->push_up();
      }
      return root;
    };
    if(n <= 0) {
      tree = make_tree();
    } else {
      tree = dfs(dfs, 0, n - 1);
    }
  }
  IsBoolStatic(SPARSE, Self) MakeSparseTree(i64 n) {
    Self res(1);
    res.n = n;
    return res;
  }
  IsBoolStatic(P, Self) MakePersistentTree(i64 n) {
    Self res(1);
    res.n = n;
    return res;
  }
  S query(i64 L, i64 R) {
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SBT::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return root->sum;
      }
      root->push_down();
      i64 m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m);
      auto rsum = dfs(dfs, root->right, m + 1, r);
      return SBT::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1);
  }
  S query_const(i64 L, i64 R) const {
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r, const U &upd) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return SBT::s_nil;
      }
      if (SegmentCover(L, R, l, r)) {
        return SBT::s_u(root->sum, upd);
      }
      U new_upd = SBT::u_u(root->upd, upd);
      i64 m = (l + r) / 2;
      auto lsum = dfs(dfs, root->left, l, m, new_upd);
      auto rsum = dfs(dfs, root->right, m + 1, r, new_upd);
      return SBT::s_s(lsum, rsum);
    };
    return dfs(dfs, tree, 0, n - 1, SBT::u_nil);
  }
  void update(i64 L, i64 R, const U &upd) {
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) {
      if (SegmentNoIntersection(L, R, l, r)) {
        return;
      }
      if (SegmentCover(L, R, l, r)) {
        root->modify(upd);
        return;
      }
      root->push_down();
      i64 m = (l + r) / 2;
      dfs(dfs, root->left, l, m);
      dfs(dfs, root->right, m + 1, r);
      root->push_up();
    };
    dfs(dfs, tree, 0, n - 1);
  }
  void travel(const Consumer<S> &consumer) const {
    auto dfs = [&](auto &dfs, Node *root, const U &upd, i64 l, i64 r) {
      // is leaf
      if (l == r) {
        consumer(SBT::s_u(root->sum, upd));
        return;
      }
      i64 m = (l + r) / 2;
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
  Optional<Tuple<i64, S>> first_true(i64 L, i64 R, const Checker<S> &checker) {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) -> Optional<i64> {
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
      i64 m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, 0, n - 1);
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<i64, S>> last_true(i64 L, i64 R, const Checker<S> &checker) {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, i64 l, i64 r) -> Optional<i64> {
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
      i64 m = (l + r) / 2;
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
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<i64, S>> first_true_const(i64 L, i64 R,
                                           const Checker<S> &checker,
                                           const S& init_sum = SBT::s_nil) const {
    S sum = init_sum;
    auto dfs = [&](auto &dfs, Node *root, const U &upd, i64 l,
                   i64 r) -> Optional<i64> {
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
      i64 m = (l + r) / 2;
      auto lres = dfs(dfs, root->left, new_upd, l, m);
      if (lres.is_none()) {
        return dfs(dfs, root->right, new_upd, m + 1, r);
      }
      return lres;
    };
    auto res = dfs(dfs, tree, SBT::u_nil, 0, n - 1);
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  Optional<Tuple<i64, S>> last_true_const(i64 L, i64 R,
                                          const Checker<S> &checker) const {
    S sum = SBT::s_nil;
    auto dfs = [&](auto &dfs, Node *root, const U &upd, i64 l,
                   i64 r) -> Optional<i64> {
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
      i64 m = (l + r) / 2;
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
    Mapper<i64, Tuple<i64, S>> mapper = [&](const i64 &x) -> Tuple<i64, S> {
      return Tuple<i64, S>(x, sum);
    };
    return res.map(mapper);
  }
  IsBool(!(P || SPARSE), void) destroy() { delete tree; }
  IsBool(P || SPARSE, void) destroy() {}
  // to support merge, only support single poi64 update
  IsBoolStatic(SPARSE, Self) merge(Self a, Self b, const Adder<S, S> &adder) {
    assert(a.n == b.n);
    auto dfs = [&](auto &dfs, Node *a, Node *b, i64 l, i64 r) -> Node * {
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
      i64 m = (l + r) / 2;
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
template <class SBT, bool P, bool SPARSE, i64 ID>
typename SegTree<SBT, P, SPARSE, ID>::Node
    *SegTree<SBT, P, SPARSE, ID>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
  using A6 = Array<i64, 3 * 3 * 3>;
  using A3 = Array<i64, 3>;
  struct Item {
    A6 T;
    A3 C;
  };
  OStream& operator<<(OStream& os, const Item &item) {
    return os << item.C;
  }
void SolveOne(int test_id, IStream &in, OStream &out) {
  int N, Q;
  in >> N >> Q;
  Vec<int> A(N);
  in >> A;
  Debug(A);
  Vec<Vec<int>> Trans(3 * 3 * 3, Vec<int>(3 * 3 * 3));
  Vec<A3> decompose(3 * 3 * 3);
  Trace(decompose);
  var to_index = [&](A3 x) {
    return x[0] + x[1] * 3 + x[2] * 9;
  };
  for(int i = 0; i < 3 * 3 * 3; i++) {
    decompose[i] = A3 {i % 3, i / 3 % 3, i / 9};
  }
  var mul = [&](A3 a, A3 b) {
    return A3 {a[b[0]], a[b[1]], a[b[2]]};
  };
  Trace(Trans);
  for(int i = 0; i < 3 * 3 * 3; i++) {
    for(int j = 0; j < 3 * 3 * 3; j++) {
      //DebugFmtln("Make trans (%d, %d)", i, j);
      Trans[i][j] = to_index(mul(decompose[i], decompose[j]));
    }
  }
  Trace(sbt);
  using SBT = sbt::SelfBalanceTreeRegistry<Item, int>;
  using ST = sbt::SegTree<SBT>;
  Item nil;
  MEMSET0(nil);
  int zero_transform = to_index(A3{0, 1, 2});
  ST::Register(
    nil,
    zero_transform,
    [&](var &a, var &b) {
      Item ans = nil;
      for(int i = 0; i < 3 * 3 * 3; i++) {
        ans.T[i] = a.T[i] + b.T[i];
        var C1 = mul(a.C, decompose[i]);
        var C2 = mul(b.C, decompose[i]);
        C1[1] += C1[2];
        C1[0] += C1[1];
        ans.T[i] += C1[2] * C2[1] + C1[1] * C2[0];
      }
      for(int i = 0; i < 3; i++) {
        ans.C[i] = a.C[i] + b.C[i];
      }
      return ans;
    },
    [&](var &a, var &b) {
      Item ans = nil;
      ans.C = mul(a.C, decompose[b]);
      for(int i = 0; i < 3 * 3 * 3; i++) {
        ans.T[i] += a.T[Trans[i][b]];
      }
      return ans;
    },
    [&](var &a, var &b) {
      return Trans[a][b];
    }
  );
  ST st(N, [&](int i) {
    //DebugFmtln("make item %d", i);
    Item ans = nil;
    ans.C[A[i]]++;
    return ans;
  });
  for(int i = 0; i < Q; i++) {
    Debug(i);
    Debug(st.to_vec());
    int t, L, R;
    in >> t >> L >> R;
    L--;
    R--;
    if(t == 1) {
      var ans = st.query(L, R);
      out << ans.T[zero_transform] << '\n';
    } else {
      int a, b, c;
      in >> a >> b >> c;
      st.update(L, R, a + b * 3 + c * 9);
    }
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
//Timestamp: 2022-08-25 17:46:16
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
template <class SBT, bool DIR = false, i64 ID = 0>
struct LCTNode {
  static_assert(is_sbt_registry_v<SBT>);
  using S = typename SBT::TypeS;
  using U = typename SBT::TypeU;
  using Self = LCTNode<SBT, DIR, ID>;
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
template <class SBT, bool DIR, i64 ID>
LCTNode<SBT, DIR, ID> *LCTNode<SBT, DIR, ID>::NIL = NULL;
}  // namespace sbt
}  // namespace dalt
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
using namespace sbt;
struct Sum {
  int add;
  int sub;
  int add_visited;
};
using LCTReg = SelfBalanceTreeRegistry<Sum, Sum, 0>;
using LCT = LCTNode<LCTReg>;
namespace dalt {
namespace seq {
template <class T = char>
struct SuffixAutomaton {
  struct Node {
    TreeMap<T, Node*> next;
    Node* fail;
    i32 maxlen;
    i32 id;
    LCT* lct;
    i32 leftist;
    i32 get_max_length() { return maxlen; }
    i32 get_min_length() { return fail == NULL ? 0 : fail->maxlen + 1; }
    Node() : fail(NULL), maxlen(0), leftist(-1) {}
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
    node->lct = new LCT();
    all.push_back(node);
    all.back()->id = Size(all) - 1;
    return node;
  }
  Node* alloc() { return add_node(new Node()); }
  Node* clone(Node* id) { 
    var ans = new Node(*id);
    return add_node(ans); }
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
  void set_fail(Node *node, Node *fail) {
    if(node->fail) {
      LCT::cut(node->lct, node->fail->lct);
    }
    node->fail = fail;
    LCT::join(node->lct, node->fail->lct);
  }
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
      set_fail(now, root);
    } else {
      auto q = p->next[index];
      if (q->maxlen == p->maxlen + 1) {
        set_fail(now, q);
      } else {
        auto clone = this->clone(q);
        clone->fail = NULL;
        set_fail(clone, q->fail);
        clone->maxlen = p->maxlen + 1;
        now->fail = q->fail = clone;
        set_fail(now, clone);
        set_fail(q, clone);
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
void SolveOne(int test_id, IStream &in, OStream &out) {
  int n;
  in >> n;
  using SA = seq::SuffixAutomaton<>;
  using SANode = SA::Node;
  seq::SuffixAutomaton<> sa(3e5);
  int last_processed = 1;
  MinHeap<Tuple<int, int, SANode *>> heap;
  var add_to_heap = [&]() {
    while(last_processed < sa.all.size()) {
      var node = sa.all[last_processed++];
      heap.emplace(node->get_min_length(), node->leftist, node);
    }
  };
  Str first_str;
  int total_add = 0;
  for(int i = 0; i < n; i++) {
    Str s;
    in >> s;
    bool add = s[s.size() - 1] == '+';
    if(add) {
      s.pop_back();
    }
    if(i == 0) {
      first_str = s;
    }
    if(add) {
      total_add++;
    }
    int index = 0;
    int j = 0;
    Sum mod;
    mod.add = add;
    mod.sub = !add;
    mod.add_visited = 1;
    for(var c : s) {
      sa.build(c);
      if(i == 0) {
        sa.build_last->leftist = j++; 
      }
      add_to_heap();
      //process last
      LCT::find_path(sa.all[0]->lct, sa.build_last->lct);
      LCT::splay(sa.build_last->lct);
      sa.build_last->lct->modify(mod);
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
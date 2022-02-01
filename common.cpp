#pragma once
#define DROP
#include "internal/std_include.cpp"
//#include "internal/compiler_hint.cpp"
#include "internal/constant.cpp"
#include "internal/debug.cpp"
#include "internal/macros.cpp"
#include "internal/random.cpp"
#include "internal/timer.cpp"

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usize = size_t;
using f32 = float;
using f64 = double;
// 16 exp, 64 precision
using f80 = long double;

#define LowerBound std::lower_bound;
#define UpperBond std::upper_bound;
#define Unique std::unique
#define Swap std::swap
#define Min std::min
#define Max std::max
#define Abs std::abs
#define Sort std::sort
#define Get(x, i) std::get<i>(x)
#define Fill std::fill
#define Move std::move
#define Reverse std::reverse
template <typename _Signature> using Function = std::function<_Signature>;
using String = std::string;
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
using std::is_same;
using std::is_same_v;
#define Stderr std::cerr
#define Stdin std::cin
#define Stdout std::cout
template <typename _Key, typename _Tp, typename _Compare = std::less<_Key>>
using TreeMap = std::map<_Key, _Tp, _Compare>;
template <typename _Key, typename _Compare = std::less<_Key>>
using TreeSet = std::set<_Key, _Compare>;
template <class T> using Deque = std::deque<T>;
template <class T> using Queue = std::queue<T>;
template <class T> using Vec = std::vector<T>;
template <class T> using Reducer = Function<T(const T &, const T &)>;
template <class T> using Comparator = Function<bool(const T &, const T &)>;
template <class T> using Indexer = Function<T(i32)>;
template <class A, class B = A, class C = A>
using Adder = Function<C(const A &, const B &)>;
template <class I> using Checker = Function<bool(const I &)>;
template <class A, class B>
using BiChecker = Function<bool(const A &, const B &)>;
template <class T> using Consumer = Function<void(const T &)>;
template <class E> using Graph = Vec<Vec<E>>;
template <class T> using Greater = std::greater<T>;
template <class T> using Less = std::less<T>;
template <class F, class T = F> using Mapper = Function<T(const F &)>;
template <class T> using MinHeap = std::priority_queue<T, Vec<T>, Greater<T>>;
template <class T> using MaxHeap = std::priority_queue<T, Vec<T>, Less<T>>;
template <class T, usize S> using Array = std::array<T, S>;
template <typename... _Elements> using Tuple = std::tuple<_Elements...>;
template <class T, class = enable_if_t<is_floating_point_v<T>>>
using Complex = std::complex<T>;
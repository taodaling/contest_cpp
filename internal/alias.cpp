#pragma once
#include "macros.cpp"
#include "std_include.cpp"
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
FunctionAlias(std::get<0>, Get0);
FunctionAlias(std::get<1>, Get1);
FunctionAlias(std::get<2>, Get2);
FunctionAlias(std::get<3>, Get3);
FunctionAlias(std::get<4>, Get4);
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
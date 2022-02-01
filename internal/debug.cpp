#pragma once
#ifdef LOCAL
#include "debug_impl.cpp"
#define Assert(x) assert(x)
#else
#define Debug(...) 42
#define DebugFmtln(...) 42
#define Assert(x) 42
#endif
template<class T>
inline T DebugRet(T x) {
    Debug(x);
    return x;
}
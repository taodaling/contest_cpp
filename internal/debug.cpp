#pragma once
#ifdef LOCAL
#include "debug_impl.cpp"
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
#pragma once
#ifdef LOCAL
#include "debug_impl.cpp"
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
#define Line(x) DebugFmtln("Line %d: %s", __LINE__, #x)
template<class T>
inline T DebugRet(T x) {
    Debug(x);
    return x;
}
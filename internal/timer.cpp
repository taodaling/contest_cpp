#pragma once
#ifndef LOCAL
struct Timer {explicit Timer(const char* m) {}void stop() const {}};
#else
#include "timer_impl.cpp"
#endif
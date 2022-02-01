#pragma once
#include "std_include.cpp"

#ifndef LOCAL
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
#else
std::mt19937 rng(0);
#endif
template <class T> T random_choice(T l, T r, std::mt19937 &gen = rng) {
  std::uniform_int_distribution<T> random(l, r);
  return random(gen);
}
#pragma once
#include "debug.cpp"
#include "std_include.cpp"
// copied from: https://judge.yosupo.jp/submission/75039
struct Timer {
  const char* msg;
  std::chrono::high_resolution_clock::time_point start;
  bool done;

  explicit Timer(const char* m)
      : msg(m), start(std::chrono::high_resolution_clock::now()), done(false) {}
  void stop() {
    done = true;
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    DebugFmtln(
        "%s: %llu ms", msg,
        std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count());
  }
  ~Timer() {
    if (!done) {
      stop();
    }
  }
};
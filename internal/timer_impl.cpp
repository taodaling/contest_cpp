#pragma once
#include "std_include.cpp"
#include "debug.cpp"
//copied from: https://judge.yosupo.jp/submission/75039
namespace dalt {
struct Timer {
    const char* msg;
    std::chrono::high_resolution_clock::time_point start;

    explicit Timer(const char* m) : msg(m), start(std::chrono::high_resolution_clock::now()) {}
    void stop() const {
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        DebugFmtln("%s: %llu ms", msg, std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count());
    }
};
}
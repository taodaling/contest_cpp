#pragma once
#include "common.cpp"
namespace dalt {
  template<class T>
  T ReturnWithExecuteOnce(const_ref(T) ret, const_ref(Func<void(void)>) task) {
    task();
    return ret;
  }
  template <class T>
  T ReturnWithExecuteOnce(const_ref(T) ret, bool &done,
                          const_ref(Func<void(void)>) task) {
    if(!done) {
      done = true;
      task();
    }
    return ret;
  }
}
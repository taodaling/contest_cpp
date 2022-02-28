#pragma once
#include "point2.cpp"
namespace dalt{
  namespace geo2{
    template<class T>
    struct Line {
      using Pt = Point<T>;
    };
  }
}
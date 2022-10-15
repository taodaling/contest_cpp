#include "common.cpp"

namespace dalt {
String ReadAll(IStream &in, int cap = 0) {
  in >> std::noskipws;
  String s;
  s.reserve(cap);
  char c;
  while (in >> c) {
    s.push_back(c);
  }
  in >> std::skipws;
  return s;
}
} // namespace dalt
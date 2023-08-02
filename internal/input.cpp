#include "common.cpp"

namespace dalt {
String ReadAll(IStream& in, int cap = 0) {
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
String ReadLine(IStream& in) {
  String s;
  while (s.empty()) {
    if (!std::getline(in, s)) {
      exit(1);
    }
  }
  return s;
}
}  // namespace dalt
#include "../common.cpp"

namespace dalt {
String ReadAll(IStream &in, int cap = 10 << 20) {
  String s, token;
  s.reserve(cap);
  token.reserve(cap);
  while (in >> token) {
    s.append(token);
    s.push_back('\n');
  }
  return s;
}
} // namespace dalt
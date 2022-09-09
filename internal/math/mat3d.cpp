#pragma once
#include "common.cpp"
namespace dalt {
namespace math {
template <class T>
using Vec3 = Array<T, 3>;
template <class T>
using Mat3 = Array<Vec3<T>, 3>;
template <class T>
Vec3<T> operator+(const Vec3<T> &a, const Vec3<T> &b) {
  return Vec3<T>{a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}
template <class T>
Vec3<T> operator-(const Vec3<T> &a, const Vec3<T> &b) {
  return Vec3<T>{a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}
template <class T>
Vec3<T> operator*(const Vec3<T> &a, const Vec3<T> &b) {
  return Vec3<T>{a[0] * b[0], a[1] * b[1], a[2] * b[2]};
}
#define ROW_OP(i, op) \
  Vec3<T>{ a[i][0] op b[i][0], a[i][1] op b[i][1], a[i][2] op b[i][2] }
#define MULTI_ROW_OP(op) ROW_OP(0, op), ROW_OP(1, op), ROW_OP(2, op)
template <class T>
Mat3<T> operator+(const Mat3<T> &a, const Mat3<T> &b) {
  return Mat3<T>{MULTI_ROW_OP(+)};
}
template <class T>
Mat3<T> operator-(const Mat3<T> &a, const Mat3<T> &b) {
  return Mat3<T>{MULTI_ROW_OP(-)};
}
#undef ROW_OP
#undef MULTI_ROW_OP
template <class T>
Mat3<T> operator*(const Mat3<T> &a, const Mat3<T> &b) {
#define CONV(i, j) a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j]
#define CONV3(i) \
  Vec3<T> { CONV(i, 0), CONV(i, 1), CONV(i, 2) }
  return Mat3<T>{CONV3(0), CONV3(1), CONV3(2)};
#undef CONV
#undef CONV3
}
template <class T>
Vec3<T> operator*(const Mat3<T> &a, const Vec3<T> &b) {
#define CONV(i) a[i][0] * b[0] + a[i][1] * b[1] + a[i][2] * b[2]
  return Vec3<T>{CONV(0), CONV(1), CONV(2)};
#undef CONV
}
template <class T>
Vec3<T> operator*(const Vec3<T> &a, const Mat3<T> &b) {
#define CONV(i) b[0] * a[0][i] * +b[1] * a[1][i] + b[2] * a[2][i]
  return Vec3<T>{CONV(0), CONV(1), CONV(2)};
#undef CONV
}
}  // namespace math
}  // namespace dalt
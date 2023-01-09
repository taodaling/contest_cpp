#pragma once
#include "gcd.cpp"
#include "math.cpp"
#include "modular.cpp"
#include "number.cpp"
namespace dalt {
namespace math {
i64 EuclidLikeFloorAffineSum1(i64 n, i64 a, i64 b, i64 c);
i64 EuclidLikeFloorAffineSum1(i64 l, i64 r, i64 a, i64 b, i64 c);
i64 EuclidLikeFloorAffineSum2(i64 n, i64 a, i64 b, i64 c);
i64 EuclidLikeFloorAffineSquareSum(i64 n, i64 a, i64 b, i64 c);
i64 MinimumResidueOfLinearFunction(i64 a, i64 b, i64 m, i64 k);

 // c > 0
 // \sum_{i=0}^n \floor((ai+b)/c)
 // O(\log_2a+\log_2c)
i64 EuclidLikeFloorAffineSum1(i64 n, i64 a, i64 b, i64 c) {
  if(n < 0) {
    return 0;
  }
  if (a == 0) {
    return (n + 1) * (b / c);
  }
  if (a >= c || b >= c) {
    return n * (n + 1) / 2 * (a / c) + (n + 1) * (b / c) +
           EuclidLikeFloorAffineSum1(n, a % c, b % c, c);
  }
  i64 m = (a * n + b) / c;
  if (m == 0) {
    return 0;
  }
  return n * m - EuclidLikeFloorAffineSum1(m - 1, c, c - b - 1, a);
}

i64 EuclidLikeFloorAffineSum1(i64 l, i64 r, i64 a, i64 b, i64 c) {
  if (l > r) {
    return 0;
  }
  i64 ans = EuclidLikeFloorAffineSum1(r, a, b, c);
  if (l > 0) {
    ans -= EuclidLikeFloorAffineSum1(l - 1, a, b, c);
  }
  return ans;
}

// \sum_{i=0}^n \floor((ai+b)/c) i
i64 EuclidLikeFloorAffineSum2(i64 n, i64 a, i64 b, i64 c) {
  Assert(n >= 0);
  if (a == 0) {
    return SumOfInterval<i64>(0, n) * (b / c);
  }
  if (n == 0) {
    return 0;
  }
  if (a >= c || b >= c) {
    return EuclidLikeFloorAffineSum2(n, a % c, b % c, c) +
           n * (n + 1) * (2 * n + 1) / 6 * (a / c) + n * (n + 1) / 2 * (b / c);
  }
  i64 m = (a * n + b) / c;
  if (m == 0) {
    return 0;
  }
  i64 ans = m * n * (n + 1) -
            EuclidLikeFloorAffineSum1(m - 1, c, -b + c - 1, a) -
            EuclidLikeFloorAffineSquareSum(m - 1, c, -b + c - 1, a);
  return ans / 2;
}

 // \sum_{i=0}^n \floor((ai+b)/c)^2
 // formula from https://blog.csdn.net/dreaming__ldx/article/details/86768953?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.control&dist_request_id=9f6059c1-08e6-4621-bac5-389e05276d86&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-3.control
i64 EuclidLikeFloorAffineSquareSum(i64 n, i64 a, i64 b, i64 c) {
  Assert(n >= 0);
  if (a == 0 || n == 0) {
    return (b / c) * (b / c) * (n + 1);
  }
  if (a >= c || b >= c) {
    return EuclidLikeFloorAffineSquareSum(n, a % c, b % c, c) +
           n * (n + 1) * (2 * n + 1) / 6 * Pow2(a / c) + (n + 1) * Pow2(b / c) +
           2 * (b / c) * EuclidLikeFloorAffineSum1(n, a % c, b % c, c) +
           2 * (a / c) * EuclidLikeFloorAffineSum2(n, a % c, b % c, c) +
           (a / c) * (b / c) * n * (n + 1);
  }
  i64 m = (a * n + b) / c;
  if (m == 0) {
    return 0;
  }
  return m * (m + 1) * n -
         2 * EuclidLikeFloorAffineSum2(m - 1, c, -b + c - 1, a) -
         2 * EuclidLikeFloorAffineSum1(m - 1, c, -b + c - 1, a) -
         EuclidLikeFloorAffineSum1(n, a, b, c);
}

/**
 * Find minimum non-negative x that L <= ax + b % m <= R
 * <p>
 * O(\log_2m)
 * <p>
 * https://codeforces.com/blog/entry/90690
 * <p>
 * The code only support 32bit integer, even though the parameter is i64
 * type
 * </p>
 *
 * @return -1 for no satisfied answer
 */

i64 FirstOccurResidue(i64 a, i64 b, i64 m, i64 L, i64 R) {
  L = Max<i64>(0, L);
  R = Min(m - 1, R);
  a = Modular(a, m);
  b = Modular(b, m);
  auto dfs = [&](auto& dfs, i64 a, i64 b, i64 m, i64 L, i64 R) -> i64 {
    if (L > R) {
      return -1;
    }
    i64 EuclidLikeFloorAffineSum2 = Gcd(a, m);
    if (EuclidLikeFloorAffineSum2 > 1) {
      return dfs(
          dfs, a / EuclidLikeFloorAffineSum2, b / EuclidLikeFloorAffineSum2,
          m / EuclidLikeFloorAffineSum2,
          DivCeil(L - b % EuclidLikeFloorAffineSum2, EuclidLikeFloorAffineSum2),
          DivFloor(R - b % EuclidLikeFloorAffineSum2,
                   EuclidLikeFloorAffineSum2));
    }
    i64 ia = PossibleModInverse(a, m);
    return MinimumResidueOfLinearFunction(ia, (L - b) * ia, m, R - L);
  };
  return dfs(dfs, a, b, m, L, R);
}

 // Find minimum value for ax+b % m where 0<=x<=k
 // O(\log_2m)
 // credited to: https://codeforces.com/blog/entry/90690
 // The code only support 32bit integer, even though the parameter is i64
i64 MinimumResidueOfLinearFunction(i64 a, i64 b, i64 m, i64 k) {
  Assert(k >= 0);
  auto stepRequire = [&](i64 ia, i64 b0, i64 m0, i64 val) {
    i64 res = ia * (val - b0) % m0;
    if (res < 0) {
      res += m0;
    }
    return res;
  };
  auto dfs = [&](auto& dfs, i64 a0, i64 b0, i64 m0, i64 k) -> i64 {
    i64 EuclidLikeFloorAffineSum2 = Gcd(a0, m0);
    if (EuclidLikeFloorAffineSum2 > 1) {
      return dfs(dfs, a0 / EuclidLikeFloorAffineSum2,
                 b0 / EuclidLikeFloorAffineSum2, m0 / EuclidLikeFloorAffineSum2,
                 k) *
                 EuclidLikeFloorAffineSum2 +
             b0 % EuclidLikeFloorAffineSum2;
    }
    i64 ia0 = PossibleModInverse(a0, m0);
    i64 b = b0;
    i64 a = a0;
    i64 m = m0;
    for (i64 s; a != 0; b = s) {
      if (a * 2 <= m) {
        s = b < a ? b : Modular(b - m, a);
        if (stepRequire(ia0, b0, m0, s) > k) {
          return b;
        }
        i64 tmp = m;
        m = a;
        a = Modular(-tmp, m);
      } else {
        i64 ma = m - a;
        s = b % ma;
        if (stepRequire(ia0, b0, m0, s) > k) {
          i64 lo = 0;
          i64 hi = b / ma - 1;
          while (lo < hi) {
            i64 mid = (lo + hi + 1) / 2;
            if (stepRequire(ia0, b0, m0, b - ma * mid) > k) {
              hi = mid - 1;
            } else {
              lo = mid;
            }
          }
          return b - ma * lo;
        }
        m = ma;
        a %= ma;
      }
    }
    return b;
  };
  return dfs(dfs, Modular(a, m), Modular(b, m), m, Min(k, m));
}
}  // namespace math
}  // namespace dalt
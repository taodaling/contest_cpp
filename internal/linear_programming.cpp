#pragma once
#include "common.cpp"
namespace dalt {
/**
 * Linear program class.
 * <br>
 * N constraints and M variables.
 * <br>
 * The target is to find an assignment for each variable to make target
 * expression as large as possible. <br> <pre> Maximize t0+t1*x1+...+tm*xm where
 * following constraint satisfied: c11*x1+...+c1m*xm <= c10
 *   ...
 *   cn1*x1+...+cnm*xm <= cn0
 *   x1, x2, ..., xm >= 0
 * </pre>
 */

struct LinearProgramming {
  double prec;
  Vec<Vec<double>> mat;
  Vec<int> basicVariables;
  Vec<int> basicVariable2RowIndex;
  bool unbound;
  bool infeasible;
  int n;
  int m;

 private:
  void normalize() {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= m; j++) {
        if (mat[i][j] >= -prec && mat[i][j] <= prec) {
          mat[i][j] = 0;
        }
      }
    }
  }

  void pivot(int variableId, int row) {
    int basicVariableId = basicVariables[row];
    mat[row][basicVariableId] = -1;
    for (int i = 0; i <= m; i++) {
      if (i == variableId) {
        continue;
      }
      mat[row][i] /= -mat[row][variableId];
    }
    mat[row][variableId] = -1;
    basicVariables[row] = variableId;
    basicVariable2RowIndex[basicVariableId] = -1;
    basicVariable2RowIndex[variableId] = row;
    for (int i = 0; i <= n; i++) {
      if (i == row || mat[i][variableId] == 0) {
        continue;
      }
      double c = mat[i][variableId];
      for (int j = 0; j <= m; j++) {
        if (j == variableId) {
          mat[i][j] = 0;
          continue;
        }
        mat[i][j] += mat[row][j] * c;
      }
    }
    normalize();
  }

  bool simplex() {
    int firstPositiveVariableId = -1;
    for (int i = 1; i <= m && firstPositiveVariableId == -1; i++) {
      if (mat[0][i] > 0) {
        firstPositiveVariableId = i;
      }
    }
    if (firstPositiveVariableId == -1) {
      return false;
    }
    double maxConstraint = 1e50;
    int maxConstraintRow = -1;
    for (int i = 1; i <= n; i++) {
      if (mat[i][firstPositiveVariableId] >= 0) {
        continue;
      }
      double constraint = mat[i][0] / (-mat[i][firstPositiveVariableId]);
      if (maxConstraint > constraint) {
        maxConstraint = constraint;
        maxConstraintRow = i;
      }
    }
    if (maxConstraintRow == -1) {
      unbound = true;
      return false;
    }
    pivot(firstPositiveVariableId, maxConstraintRow);
    return true;
  }

 public:
  /**
   *
   * @param n constraint number
   * @param m variable number
   * @param prec precision
   */

  LinearProgramming(int _n, int _m, double _prec) {
    prec = _prec;
    n = _n;
    m = _m + _n;
    unbound = false;
    infeasible = false;
    mat = Vec<Vec<double>>(_n + 1, Vec<double>(m + 2));
    basicVariables = Vec<int>(m + 2);
    basicVariable2RowIndex = Vec<int>(m + 2);
    for (int i = 1; i <= m; i++) {
      if (i <= _m) {
        basicVariable2RowIndex[i] = -1;
      } else {
        basicVariable2RowIndex[i] = i - _m;
        basicVariables[i - _m] = i;
      }
    }
  }

  /**
   * both constraintId and variableId start with 1
   * @param constraintId
   * @param noMoreThan
   */

  void setConstraintConstant(int constraintId, double noMoreThan) {
    mat[constraintId][0] = noMoreThan;
  }

  /**
   * both constraintId and variableId start with 1
   * @param constraintId
   * @param variableId
   * @param c
   */

  void setConstraintCoefficient(int constraintId, int variableId, double c) {
    mat[constraintId][variableId] = -c;
  }

  void setTargetConstant(double c) { mat[0][0] = c; }

  void setTargetCoefficient(int variableId, double c) {
    mat[0][variableId] = c;
  }

  double maxSolution() { return mat[0][0]; }

  bool isInfeasible() { return infeasible; }

  bool isUnbound() { return unbound; }

  double getAssignmentValueForVariable(int i) {
    if (basicVariable2RowIndex[i] == -1) {
      return 0;
    } else {
      return mat[basicVariable2RowIndex[i]][0];
    }
  }

  bool initSimplex() {
    if (n == 0) {
      return true;
    }
    int minConstantRow = 1;
    for (int i = 2; i <= n; i++) {
      if (mat[i][0] < mat[minConstantRow][0]) {
        minConstantRow = i;
      }
    }
    if (mat[minConstantRow][0] >= 0) {
      return true;
    }
    auto originalTargetExpression = mat[0];
    m++;
    mat[0] = Vec<double>(m + 1);
    mat[0][m] = -1;
    basicVariable2RowIndex[m] = -1;
    for (int i = 1; i <= n; i++) {
      mat[i][m] = 1;
    }
    pivot(m, minConstantRow);
    while (simplex())
      ;
    if (mat[0][0] != 0 || unbound) {
      infeasible = true;
      unbound = false;
      return false;
    }
    if (basicVariable2RowIndex[m] != -1) {
      int row = basicVariable2RowIndex[m];
      int firstNegativeVariable = -1;
      for (int i = 1; i <= m && firstNegativeVariable == -1; i++) {
        if (mat[row][i] != 0) {
          firstNegativeVariable = i;
        }
      }
      pivot(firstNegativeVariable, row);
    }

    // restore
    m--;
    mat[0] = originalTargetExpression;
    for (int i = 1; i <= m; i++) {
      if (basicVariable2RowIndex[i] == -1) {
        continue;
      }
      int row = basicVariable2RowIndex[i];
      double c = mat[0][i];
      for (int j = 0; j <= m; j++) {
        if (j == i) {
          mat[0][j] = 0;
          continue;
        }
        mat[0][j] += mat[row][j] * c;
      }
    }
    normalize();
    return true;
  }

  void solve() {
    if (!initSimplex()) {
      return;
    }
    while (simplex())
      ;
  }
};

/**
 * <br>
 * N constraints and M variables.
 * <br>
 * The target is to find an assignment for each variable to make target
 * expression as large as possible. <br> <pre> Minimize t0+t1*x1+...+tm*xm where
 * following constraint satisfied: c11*x1+...+c1m*xm >= c10
 *   ...
 *   cn1*x1+...+cnm*xm >= cn0
 *   x1, x2, ..., xm >= 0
 * </pre>
 */

struct DualLinearProgramming {
  LinearProgramming lp;
  int n;
  int m;

  DualLinearProgramming(int _n, int _m, double prec) : lp(_m, _n, prec) {
    n = _n;
    m = _m;
  }

  void setConstraintConstant(int constraintId, double noMoreThan) {
    lp.setTargetCoefficient(constraintId, noMoreThan);
  }

  void setConstraintCoefficient(int constraintId, int variableId, double c) {
    lp.setConstraintCoefficient(variableId, constraintId, c);
  }

  void setTargetConstant(double c) { lp.setTargetConstant(c); }

  void setTargetCoefficient(int variableId, double c) {
    lp.setConstraintConstant(variableId, c);
  }

  void solve() { lp.solve(); }

  double minSolution() { return lp.maxSolution(); }

  bool isInfeasible() { return lp.isUnbound(); }

  bool isUnbound() { return lp.isInfeasible(); }

  double getAssignmentValueForVariable(int i) {
    if (i + n <= lp.m) {
      return -lp.mat[0][i + n];
    } else {
      return 0;
    }
  }
};
}  // namespace dalt
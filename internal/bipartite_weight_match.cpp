#include "../common.cpp"

namespace dalt {
namespace graph {
// credited to: http://longrm.com/2018/05/05/2018-05-05-KM/
// maximum weighted perfect matching
template <class V>
Tuple<V, Vec<i32>, Vec<i32>, Vec<V>, Vec<V>>
BipartiteWeightMatchByKM(const Vec<Vec<V>> &table) {
  const static V INF = std::numeric_limits<V>::max() / 2;
  int n = Size(table);
  Vec<V> left_label(n, -INF);
  Vec<V> right_label(n);
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < n; y++) {
      if (table[x][y] > left_label[x]) {
        left_label[x] = table[x][y];
      }
    }
  }
  Vec<i32> left_mate(n, -1);
  Vec<i32> right_mate(n, -1);
  auto bfs = [&](auto startX) {
    bool find = false;
    int end_y = -1;
    Vec<i32> y_pre(n, -1);  // 标识搜索路径上y点的前一个点
    Vec<bool> S(n), T(n);   // S集合，T集合
    Vec<V> slack_y(n, INF); // Y点的松弛变量
    Vec<i32> queue(n);      // 队列
    int qs = 0, qe = 0;     // 队列开始结束索引
    queue[qe++] = startX;
    while (!find) {              // 循环直到找到匹配
      while (qs < qe && !find) { // 队列不为空
        int x = queue[qs++];
        S[x] = true;
        for (int y = 0; y < n; y++) {
          if (T[y]) {
            continue;
          }
          V tmp = left_label[x] + right_label[y] - table[x][y];
          if (tmp == 0) { // 相等子树中的边
            T[y] = true;
            y_pre[y] = x;
            if (right_mate[y] == -1) {
              end_y = y;
              find = true;
              break;
            } else {
              queue[qe++] = right_mate[y];
            }
          } else if (slack_y[y] >
                     tmp) { // 不在相等子树中的边，看是否能够更新松弛变量
            slack_y[y] = tmp;
            y_pre[y] = x;
          }
        }
      }
      if (find) {
        break;
      }
      V a = INF;
      for (int y = 0; y < n; y++) { // 找到最小的松弛值
        if (!T[y]) {
          a = Min(a, slack_y[y]);
        }
      }
      for (int i = 0; i < n; i++) { // 根据a修改标号值
        if (S[i]) {
          left_label[i] -= a;
        }
        if (T[i]) {
          right_label[i] += a;
        }
      }
      qs = qe = 0;
      for (int y = 0; y < n; y++) { // 重要！！！控制修改标号之后需要检查的x点
        if (!T[y] &&
            slack_y[y] ==
                a) { // 查看那些y点新加入到T集合，注意，这些y点的前向x点都记录在了y_pre里面，所以这些x点不用再次入队
          T[y] = true;
          if (right_mate[y] == -1) { // 新加入的y点没有匹配，那么就找到可扩路了
            end_y = y;
            find = true;
            break;
          } else { // 新加入的y点已经有匹配了，将它匹配的x加到队列
            queue[qe++] = right_mate[y];
          }
        }
        slack_y[y] -=
            a; // 所有松弛值减去a。(对于T集合中的松弛值已经没用了，对于不在T集合里面的y点，
      } // 它们的松弛值是通过S集合中的x点求出的，S集合中的x点的标号值在上面都减去了a，所以这里松弛值也要减去a)
    }
    while (end_y != -1) { // 找到可扩路最后的y点后，回溯并扩充
      int preX = y_pre[end_y], preY = left_mate[preX];
      left_mate[preX] = end_y;
      right_mate[end_y] = preX;
      end_y = preY;
    }
  };
  for (int x = 0; x < n; x++) {
    bfs(x);
  }
  V value = 0;
  for (int x = 0; x < n; x++) {
    value += table[x][left_mate[x]];
  }
  return {value, left_mate, right_mate, left_label, right_label};
}
} // namespace graph
} // namespace dalt
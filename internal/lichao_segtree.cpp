#include "common.cpp"
#include "number.cpp"
#include "segtree_common.cpp"
namespace dalt {
namespace sbt {
template <class T> struct LichaoSegTree {
  static_assert(is_floating_point_v<T> || is_integral_v<T>,
                "only integer and float are supported");
  struct Line {
    using Self = Line;
    T a;
    T b;
    T apply(T x) const { return a * x + b; }
  };
  struct LCNode {
    using L = Line;
    using Self = LCNode;
    L line;
    Self *left;
    Self *right;
    LCNode() : left(NULL), right(NULL) {}
  };

  using Self = LichaoSegTree<T>;
  using Node = LCNode;
  using Ln = typename Node::L;
  Node *tree;
  Vec<T> sorted;
  const static T INF = std::numeric_limits<T>::max() / 2;

private:
  Node *make_tree(int l, int r) {
    Node *root = new Node();
    root->line = Ln{
        .a = 0,
        .b = -INF,
    };
    if (l == r) {
      return root;
    } else {
      int m = (l + r) / 2;
      root->left = make_tree(l, m);
      root->right = make_tree(m + 1, r);
    }
    return root;
  }
  T intersect(const Ln &a, const Ln &b) {
    Assert(a.a < b.a);
    return DivFloor(a.b - b.b, b.a - a.a);
  }

  void update(Node *root, int L, int R, int l, int r, Ln small_line) {
    if (SegmentNoIntersection(L, R, l, r)) {
      return;
    } else if (l == r) {
      if (root->line.apply(sorted[l]) < small_line.apply(sorted[l])) {
        root->line = small_line;
      }
      return;
    }
    int m = (l + r) / 2;
    if (SegmentCover(L, R, l, r)) {
      if (root->line.a == small_line.a) {
        root->line.b = max(root->line.b, small_line.b);
        return;
      }
      Ln large_line = root->line;
      if (small_line.a > large_line.a) {
        swap(small_line, large_line);
      }
      auto intersect_at = intersect(small_line, large_line);
      if (intersect_at <= sorted[m]) {
        root->line = large_line;
        if (l < r) {
          update(root->left, L, R, l, m, small_line);
        }
      } else {
        root->line = small_line;
        if (l < r) {
          update(root->right, L, R, m + 1, r, large_line);
        }
      }
      return;
    }
    update(root->left, L, R, l, m, small_line);
    update(root->right, L, R, m + 1, r, small_line);
  }

  T query(const Node *root, int l, int r, int x) const {
    T best = root->line.apply(sorted[x]);
    if (l == r) {
      return best;
    }
    int m = (l + r) / 2;
    if (x <= m) {
      best = max(best, query(root->left, l, m, x));
    } else {
      best = max(best, query(root->right, m + 1, r, x));
    }
    return best;
  }

public:
  LichaoSegTree(const Vec<T> &_sorted) : sorted(_sorted) {
    if (sorted.empty()) {
      sorted.push_back(0);
    }
    Sort(All(sorted));
    Unique(sorted);
    tree = make_tree(0, Size(sorted) - 1);
  }
  void update(T _L, T _R, T a, T b) {
    int L = LowerBound(All(sorted), _L) - sorted.begin();
    int R = UpperBound(All(sorted), _R) - sorted.begin();
    R--;
    update(tree, L, R, 0, Size(sorted) - 1,
           Ln{
               .a = a,
               .b = b,
           });
  }

  T query(T x) const {
    auto iter = LowerBound(All(sorted), x);
    Assert(iter != sorted.end() && *iter == x);
    return query(tree, 0, Size(sorted) - 1, iter - sorted.begin());
  }

  Vec<T> to_vec() const {
    Vec<T> res;
    for (auto x : sorted) {
      res.push_back(query(x));
    }
    return res;
  }
};
} 
} // namespace dalt
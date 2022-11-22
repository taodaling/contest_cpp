#pragma once
#include "common.cpp"
#include "hashmap.cpp"
namespace dalt {
namespace seq {
// verified by:
//  - https://loj.ac/p/141
struct Eertree {
  struct Node {
    int id;
    Node *fail;
    int len;
    int depth;
    Vec<Node *> children;
  };
  Node *odd;
  Node *even;
  hash::HashMap<u64, Node *> hm;
  Vec<i32> data;
  int zero;
  int front_size;
  int back_size;
  Node *front_build_last;
  Node *back_build_last;
  Vec<Node *> all;

  i64 palindrome_substring_cnt;

  Node *newNode() {
    auto ans = new Node();
    ans->id = Size(all);
    all.push_back(ans);
    return ans;
  }

  Node *GetChild(Node *node, int index) {
    var iter = hm.find(IdOf(node, index));
    return iter == hm.end() ? NULL : iter->second;
  }
  void SetChild(Node *node, int index, Node *item) {
    hm[IdOf(node, index)] = item;
  }
  u64 IdOf(Node *node, int index) { return u64(node->id) << 32 | index; }
  Eertree(int back_addition, int front_addition = 0)
      : palindrome_substring_cnt(0) {
    int cap = front_addition + back_addition;
    all.reserve(2 + cap);
    data.resize(cap);
    zero = front_addition;
    front_size = zero - 1;
    back_size = zero;

    odd = newNode();
    odd->len = -1;
    odd->depth = 0;
    odd->id = -1;

    even = newNode();
    even->fail = odd;
    even->len = 0;
    even->depth = 0;
    even->id = -2;

    all.clear();
    back_build_last = front_build_last = odd;

    hm = decltype(hm)(cap);
  }

  void push_front(i32 c) {
    data[front_size--] = c;

    int index = c;

    auto trace = front_build_last;
    while (front_size + 2 + trace->len >= back_size) {
      trace = trace->fail;
    }

    while (data[front_size + trace->len + 2] != c) {
      trace = trace->fail;
    }

    var next_index_iter = hm.find(IdOf(trace, index));
    if (next_index_iter != hm.end()) {
      front_build_last = next_index_iter->second;
    } else {
      auto now = newNode();
      now->len = trace->len + 2;
      hm[IdOf(trace, index)] = now;

      if (now->len == 1) {
        now->fail = even;
      } else {
        trace = trace->fail;
        while (data[front_size + trace->len + 2] != c) {
          trace = trace->fail;
        }
        now->fail = hm[IdOf(trace, index)];
      }
      now->depth = now->fail->depth + 1;
      front_build_last = now;
    }
    if (front_build_last->len == back_size - front_size - 1) {
      back_build_last = front_build_last;
    }
    palindrome_substring_cnt += front_build_last->depth;
  }

  void push_back(i32 c) {
    data[back_size++] = c;

    int index = c;

    auto trace = back_build_last;
    while (back_size - 2 - trace->len <= front_size) {
      trace = trace->fail;
    }

    while (data[back_size - trace->len - 2] != c) {
      trace = trace->fail;
    }
    var next_index_iter = hm.find(IdOf(trace, index));
    if (next_index_iter != hm.end()) {
      back_build_last = next_index_iter->second;
    } else {
      auto now = newNode();
      now->len = trace->len + 2;
      hm[IdOf(trace, index)] = now;

      if (now->len == 1) {
        now->fail = even;
      } else {
        trace = trace->fail;
        while (data[back_size - trace->len - 2] != c) {
          trace = trace->fail;
        }
        now->fail = hm[IdOf(trace, index)];
      }
      now->depth = now->fail->depth + 1;
      back_build_last = now;
    }
    if (back_build_last->len == back_size - front_size - 1) {
      front_build_last = back_build_last;
    }
    palindrome_substring_cnt += back_build_last->depth;
  }

  void visit(Consumer<Node *> consumer) {
    for (int i = Size(all) - 1; i >= 0; i--) {
      consumer(all[i]);
    }
  }

  i64 get_palindrome_substring_cnt() const { return palindrome_substring_cnt; }

  int get_distinct_palindrome_substring() const { return Size(all); }

#ifdef DROP
  ~Eertree() {
    delete odd;
    delete even;
    for (var item : all) {
      delete item;
    }
  }
#endif
};
}  // namespace seq
}  // namespace dalt
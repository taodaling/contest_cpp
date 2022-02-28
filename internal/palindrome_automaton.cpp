#pragma once
#include "common.cpp"
namespace dalt {
namespace seq {
// verified by: 
//  - https://loj.ac/p/141
template <int C = 26>
struct PalindromeAutomaton {
  struct Node {
    Array<Node *, C> next;
    Node* fail;
    int len;
    int depth;
  };
  Node *odd;
  Node *even;

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
    all.push_back(ans);
    return ans;
  }

  PalindromeAutomaton(int front_addition, int back_addition = 0)
      : palindrome_substring_cnt(0) {
    int cap = front_addition + back_addition;
    all.resize(2 + cap);
    data.resize(cap);
    zero = front_addition;
    front_size = zero - 1;
    back_size = zero;

    odd = newNode();
    odd->len = -1;
    odd->depth = 0;

    even = newNode();
    even->fail = odd;
    even->len = 0;
    even->depth = 0;

    all.clear();
    back_build_last = front_build_last = odd;
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

    if (trace->next[index] != NULL) {
      front_build_last = trace->next[index];
    } else {
      auto now = newNode();
      now->len = trace->len + 2;
      trace->next[index] = now;

      if (now->len == 1) {
        now->fail = even;
      } else {
        trace = trace->fail;
        while (data[front_size + trace->len + 2] != c) {
          trace = trace->fail;
        }
        now->fail = trace->next[index];
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

    if (trace->next[index] != NULL) {
      back_build_last = trace->next[index];
    } else {
      auto now = newNode();
      now->len = trace->len + 2;
      trace->next[index] = now;

      if (now->len == 1) {
        now->fail = even;
      } else {
        trace = trace->fail;
        while (data[back_size - trace->len - 2] != c) {
          trace = trace->fail;
        }
        now->fail = trace->next[index];
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
};
}  // namespace seq
}  // namespace dalt
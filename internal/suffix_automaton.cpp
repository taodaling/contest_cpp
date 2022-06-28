#pragma once
#include "common.cpp"
#include "collection.cpp"
#include "nil.cpp"
namespace dalt {
namespace seq {
template <class T = char>
struct SuffixAutomaton {
  struct Node {
    TreeMap<T, Node*> next;
    Node* fail;
    i32 maxlen;
    i32 id;
    i32 get_max_length() { return maxlen; }
    i32 get_min_length() { return fail == NULL ? 0 : fail->maxlen + 1; }
    Node() : fail(NULL), maxlen(0) {}
  };
  struct Right {
    i32 cnt;
    i32 leftest_right;
    i32 rightest_right;
    Right()
        : leftest_right(std::numeric_limits<i32>::max()),
          rightest_right(std::numeric_limits<i32>::min()) {}
  };
  struct Matcher {
    SuffixAutomaton* sa;
    Node* match_last;
    i32 match_length;
    void match(T c) {
      T index = c;
      auto candidate = GetOrDefault<Node*>(match_last->next, index, NULL);
      if (candidate != NULL) {
        match_last = candidate;
        match_length = match_length + 1;
        return;
      }
      while (match_last != NULL &&
             (candidate = GetOrDefault<Node*>(match_last->next, index, NULL)) ==
                 NULL) {
        match_last = match_last->fail;
      }
      if (match_last == NULL) {
        match_last = sa->root;
        match_length = 0;
      } else {
        match_length = match_last->maxlen + 1;
        match_last = candidate;
      }
    }
  };
  Matcher matcher() {
    return Matcher{
        .sa = this,
        .match_last = root,
        .match_length = 0,
    };
  }
  Node* build_last;
  Vec<Node*> all;

 private:
  Node* root;
  i64 distinct_substr;
  bool sorted;

  Node* add_node(Node* node) {
    all.push_back(node);
    all.back()->id = Size(all) - 1;
    return node;
  }
  Node* alloc() { return add_node(new Node()); }
  Node* clone(Node* id) { return add_node(new Node(*id)); }

 public:
  void enable_distinct_substr() {
    if (distinct_substr == -1) {
      distinct_substr = 0;
    }
  }
  decltype(distinct_substr) get_distinct_substr() const {
    return distinct_substr;
  }
  SuffixAutomaton(i32 cap) : distinct_substr(-1) {
    all.reserve(cap + 1);
    build_last = root = alloc();
  }

  Node* visit(T index, Node* trace, Node* target, Node* replacement) {
    while (trace != NULL &&
           GetOrDefault<Node*>(trace->next, index, NULL) == target) {
      trace->next[index] = replacement;
      trace = trace->fail;
    }
    return trace;
  } 
  void build_next() { build_last = root; }
  void build(T c) {
    sorted = false;
    T index = c;
    Node* candidate = build_last->next[c];
    //generic sam
    if (candidate != NULL && build_last->maxlen == candidate->maxlen + 1) {
      build_last = candidate;
      return;
    }
    auto now = alloc();
    now->maxlen = build_last->maxlen + 1;
    Node* p = visit(index, build_last, NULL, now);
    build_last = now;
    if (p == NULL) {
      now->fail = root;
    } else {
      auto q = p->next[index];
      if (q->maxlen == p->maxlen + 1) {
        now->fail = q;
      } else {
        auto clone = this->clone(q);
        clone->maxlen = p->maxlen + 1;
        now->fail = q->fail = clone;
        if (distinct_substr != -1) {
          distinct_substr -= q->maxlen - clone->fail->maxlen;
          distinct_substr += q->maxlen - q->fail->maxlen;
          distinct_substr += clone->maxlen - clone->fail->maxlen;
        }
        visit(index, p, q, clone);
        //generic sam
        if (p->maxlen + 1 == now->maxlen) {
          build_last = clone;
        }
      }
    }
    if (distinct_substr != -1) {
      distinct_substr += now->maxlen - now->fail->maxlen;
    }
  }
  Vec<Node*>& topo_sort() {
    if (sorted) {
      return all;
    }
    sorted = true;
    Vec<i32> indeg(Size(all));
    Deque<Node*> dq;
    for (auto node : all) {
      if (node->fail != NULL) {
        indeg[node->fail->id]++;
      }
    }
    for (auto node : all) {
      if (indeg[node->id] == 0) {
        dq.push_back(node);
      }
    }
    all.clear();
    while (!dq.empty()) {
      auto head = dq.front();
      dq.pop_front();
      all.push_back(head);
      if (head->fail != NULL) {
        indeg[head->fail->id]--;
        if (indeg[head->fail->id] == 0) {
          dq.push_back(head->fail);
        }
      }
    }
    return all;
  }
  Vec<Right> calculate_right(const Indexer<T>& s, int n) {
    topo_sort();
    Vec<Right> res(n);
    Matcher matcher = this->matcher();
    for (int i = 0; i < n; i++) {
      matcher.match(s(i));
      i32 id = matcher.match_last->id;
      res[id].cnt++;
      res[id].leftest_right = Min(res[id].leftest_right, i);
      res[id].rightest_right = Max(res[id].rightest_right, i);
    }
    for (auto node : all) {
      if (node->fail != NULL) {
        i32 id = node->id;
        i32 fid = node->fail->id;
        res[fid].cnt += res[id].cnt;
        res[fid].leftest_right =
            Min(res[fid].leftest_right, res[id].leftest_right);
        res[fid].rightest_right =
            Max(res[fid].rightest_right, res[id].rightest_right);
      }
    }
    return res;
  }
};
}  // namespace seq
}  // namespace dalt
#pragma once
#include "common.cpp"
namespace dalt {
namespace ds {
template <class T>
struct LinkedNode {
  using Self = LinkedNode<T>;
  using Node = Self;
  T data;
  Node *next;
  Node *prev;

  LinkedNode(T _data = T()) : data(_data) { next = prev = this; }
  void append(Node *b) {
    Assert(b->is_single());
    Node *a = this;
    b.next = a.next;
    b.next.prev = b;
    a.next = b;
    b.prev = a;
  }
  void detach(Node *a) {
    a.prev.next = a.next;
    a.next.prev = a.prev;
    a.prev = a.next = a;
  }
  bool is_single() const { return next == this; }
};
template <class T>
struct LinkedList {
  using Self = LinkedList<T>;
  using Node = LinkedNode<T>;
  Node *head;
  int size;
  LinkedList(T nil = T()) {
    size = 0;
    head = new Node(nil);
  }

  void push_back(Node *node) {
    size++;
    head->prev->append(node);
  }
  void push_front(Node *node) {
    size++;
    head->next->append(node);
  }
  void append(Node *a, Node *b) {
    a->append(b);
    size++;
  }
  void detach(Node *node) {
    node->detach();
    size--;
  }
  int get_size() const { return size; }
  bool empty() const { return size == 0; }
  Node *front() { return head->next; }
  Node *back() { return head->prev; }
  const Node *front() const { return head->next; }
  const Node *back() const { return head->prev; }
  void pop_front() {
    head->next->detach();
    size--;
  }
  void pop_back() {
    head->prev->detach();
    size--;
  }
};
}  // namespace ds
}  // namespace dalt
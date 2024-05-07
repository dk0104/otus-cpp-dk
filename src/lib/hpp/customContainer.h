#pragma once
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>

template <typename T> struct Node {
  T value;
  Node<T> *next;
  Node(const T &v) : value(v), next(nullptr){};

  friend std::ostream &operator<<(std::ostream &out, const Node<T> &node) {
    out << " current node value : " << node.value;
    return out;
  };
};

template <typename T, typename Allocator = std::allocator<T>>
class CustomContainer {
public:
  static const size_t MemAllocSize = 1;
  using node_at =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node<T>>;
  using ptr = typename std::allocator_traits<node_at>::pointer;

  node_at mNode;
  ptr mHead;
  ptr mTail;

  explicit CustomContainer(const Allocator &a = Allocator{})
      : mHead(nullptr), mTail(nullptr), mNode(node_at{a}) {}

  ~CustomContainer() {
    for (auto it = this->begin(); it != this->end(); ++it) {
      mNode.deallocate(&(*it), MemAllocSize);
    }
  }

  void push(T &value) { push(std::move(value)); }

  void push(T &&value) {
    auto _node = mNode.allocate(MemAllocSize);

    if (mHead == nullptr) {
      mHead = _node;
      mTail = mHead;
    } else {
      mTail->next = _node;
      mTail = _node;
    }
  }

  class iterator : public std::iterator<std::forward_iterator_tag, Node<T>> {

  public:
    iterator() : mVT(nullptr){};

    explicit iterator(Node<T> *vt) : mVT(vt){};

    iterator &operator++() {
      mVT = mVT->next;
      return *this;
    }

    typename std::iterator_traits<iterator>::reference operator*(void) {
      return *mVT;
    }

    bool operator!=(const iterator &other) { return this->mVT != other.mVT; }

  private:
    Node<T> *mVT;
  };
  iterator begin(void) { return iterator(mHead); }

  iterator end(void) { return iterator(); }
};

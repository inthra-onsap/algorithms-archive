#ifndef ALGORITHMS_ARCHIVE_BINARY_HEAP_H_
#define ALGORITHMS_ARCHIVE_BINARY_HEAP_H_

#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class BinaryHeap {
 public:
  BinaryHeap(uint64_t capacity_ = 50) : capacity{capacity_}, size{0} {
    tree.resize(capacity_);
  }

  BinaryHeap(std::vector<Comparable> &items) : capacity{items.capacity()}, size{items.size()} {
    tree.resize(items.capacity());
    for (uint64_t i = 0; i < items.size(); ++i) {
      tree[i + 1] = items[i];
    }
    BuildHeap();
  }

  ~BinaryHeap() {}

  bool IsEmpty() {
    return (size == 0);
  }

  void Empty() {
    size = 0;
  }

  void Insert(const Comparable &value) {
    if (size == (tree.size() - 1)) {
      tree.resize(tree.size() * 2);
    }
    tree[++size] = value;
    SiftUp(size);
  }

  void Insert(const Comparable &&value) {
    if (size == (tree.size() - 1)) {
      tree.resize(tree.size() * 2);
    }
    tree[++size] = std::move(value);
    SiftUp(size);
  }

  const Comparable &FindMin() {
    return tree[1];
  }

  void DeleteMin() {
    if (size == 0) {
      return;
    }
    tree[1] = tree[size--];
    SiftDown(1);
  }

 private:
  uint64_t capacity;
  uint64_t size;
  std::vector<Comparable> tree;

  void BuildHeap() {
    for (uint64_t i = size / 2; i > 0; --i) {
      SiftDown(i);
    }
  }

  uint64_t Parent(uint64_t index) {
    return index / 2;
  }

  uint64_t LeftChild(uint64_t index) {
    return index * 2;
  }

  uint64_t RightChild(uint64_t index) {
    return index * 2 + 1;
  }

  void SiftUp(uint64_t pos) {
    while (Parent(pos) > 0 && tree[pos] < tree[Parent(pos)]) {
      std::swap(tree[Parent(pos)], tree[pos]);
      pos /= 2;
    }
  }

  void SiftDown(uint64_t pos) {
    while ((LeftChild(pos) <= size && tree[pos] > tree[LeftChild(pos)]) ||
        (RightChild(pos) <= size && tree[pos] > tree[RightChild(pos)])) {
      if (RightChild(pos) > size || tree[LeftChild(pos)] < tree[RightChild(pos)]) {
        std::swap(tree[LeftChild(pos)], tree[pos]);
        pos = LeftChild(pos);
      } else {
        std::swap(tree[RightChild(pos)], tree[pos]);
        pos = RightChild(pos);
      }
    }
  }

// [ONLY] Test Purposes
#ifdef UNIT_TESTS_
  friend class BinaryHeapTest_ExpectInsertElementsExceedTheSizeSuccess_Test;
#endif // UNIT_TESTS_
};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_BINARY_HEAP_H_

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

  void SiftUp(uint64_t pos) {
    while ((pos / 2) > 0 && tree[pos] < tree[pos / 2]) {
      std::swap(tree[pos / 2], tree[pos]);
      pos /= 2;
    }
  }

  void SiftDown(uint64_t pos) {
    while ((2 * pos <= size && tree[pos] > tree[2 * pos]) ||
        (2 * pos + 1 <= size && tree[pos] > tree[2 * pos + 1])) {
      if (tree[2 * pos] < tree[2 * pos + 1]) {
        std::swap(tree[2 * pos], tree[pos]);
        pos *= 2;
      } else {
        std::swap(tree[2 * pos + 1], tree[pos]);
        pos = 2 * pos + 1;
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

#ifndef ALGORITHMS_ARCHIVE_BINARY_HEAP_H_
#define ALGORITHMS_ARCHIVE_BINARY_HEAP_H_

#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class BinaryHeap {
 public:
  BinaryHeap(int capacity_ = 50) : capacity{capacity_}, size{0} {
    tree = new Comparable[capacity_];
  }

  BinaryHeap(std::vector<Comparable> &items) : capacity{items.capacity()}, size{items.size()} {
    for (int i = 0; i < items.size(); ++i) {
      tree[i + 1] = items[i];
    }
    BuildHeap();
  }

  ~BinaryHeap() {
    delete tree;
  }

  bool IsEmpty() {
    return (size == 0);
  }

  void Empty() {
    size = 0;
  }

  void Insert(const Comparable &value) {
    if (size == (tree->size() - 1)) {
      tree->resize(tree->size() * 2);
    }
    tree[++size] = value;
    SiftUp(size);
  }

  void Insert(const Comparable &&value) {}

  const Comparable &FindMin() {
    return tree[0];
  }

  void DeleteMin() {
    if (size == 0) {
      return;
    }
    tree[1] = tree[size--];
    SiftDown(1);
  }

 private:
  int capacity;
  int size;
  std::vector<Comparable> *tree;

  void BuildHeap() {
    for (int i = size / 2; i > 0; --i) {
      SiftDown(i);
    }
  }

  void SiftUp(int pos) {
    while ((pos / 2) > 0 && tree[pos] < tree[pos / 2]) {
      std::swap(tree[pos / 2], tree[pos]);
      pos /= 2;
    }
  }

  void SiftDown(int pos) {
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
};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_BINARY_HEAP_H_

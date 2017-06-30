#ifndef ALGORITHMS_ARCHIVE_DIJSTRA_MIN_HEAP_H
#define ALGORITHMS_ARCHIVE_DIJSTRA_MIN_HEAP_H

#include <utility>
#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace graphs {
template<typename VertexType>
class GraphMinHeap {
 public:
  GraphMinHeap() : size{0} {
    heap.resize(1);
  }

  void Insert(std::pair<VertexType, int> vertex) {
    if (heap.size() <= size) {
      heap.resize(heap.size() * 2);
    }
    heap[size] = vertex;
    SiftUp(size++);
  }

  std::pair<VertexType, int> GetMin() {
    return heap[0];
  }

  void DeleteMin() {
    std::swap(heap[0], heap[--size]);
    SiftDown(0);
  }

  void UpdateWeight(int vertex, int new_weight) {
    int i;
    for (i = 0; i < size; ++i) {
      if (heap[i].first == vertex) {
        heap[i].second = new_weight;
        break;
      }
    }

    if (Parent(i) > 0 && heap[i].second < heap[Parent(i)].second) {
      SiftUp(i);
    } else {
      SiftDown(i);
    }
  }

  bool Empty() {
    return (size == 0);
  }

 private:
  int size;
  std::vector<std::pair<VertexType, int>> heap;

  int Parent(int index) {
    return (index - 1) / 2;
  }

  int LeftChild(int index) {
    return index * 2 + 1;
  }

  int RightChild(int index) {
    return index * 2 + 2;
  }

  void SiftUp(int index) {
    while (Parent(index) >= 0 && heap[Parent(index)].second > heap[index].second) {
      std::swap(heap[Parent(index)], heap[index]);
      index = Parent(index);
    }
  }

  void SiftDown(int index) {
    while ((LeftChild(index) < size && heap[LeftChild(index)].second < heap[index].second) ||
        (RightChild(index) < size && heap[RightChild(index)].second < heap[index].second)) {

      if (RightChild(index) >= size || heap[LeftChild(index)].second < heap[RightChild(index)].second) {
        std::swap(heap[LeftChild(index)], heap[index]);
        index = LeftChild(index);
      } else {
        std::swap(heap[RightChild(index)], heap[index]);
        index = RightChild(index);
      }
    }
  }
};
} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_DIJSTRA_MIN_HEAP_H

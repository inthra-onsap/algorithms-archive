#ifndef ALGORITHMS_ARCHIVE_DIJSTRA_MIN_HEAP_H
#define ALGORITHMS_ARCHIVE_DIJSTRA_MIN_HEAP_H

#include <utility>
#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace graphs {
class DijkstraMinHeap {
 public:
  DijkstraMinHeap() : size{0} {
    heap.resize(1);
  }

  void Insert(std::pair<int, int> vertex);

  std::pair<int, int> GetMin();

  void DeleteMin();

  void UpdateWeight(int vertex, int new_weight);

  bool Empty();

 private:
  int size;
  std::vector<std::pair<int, int>> heap;

  int Parent(int index);

  int LeftChild(int index);

  int RightChild(int index);

  void SiftUp(int index);

  void SiftDown(int index);
};
} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_DIJSTRA_MIN_HEAP_H

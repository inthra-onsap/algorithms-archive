#ifndef ALGORITHMS_ARCHIVE_HEAP_SORT_H_
#define ALGORITHMS_ARCHIVE_HEAP_SORT_H_

#include <vector>
#include <algorithm>

/**
 * Internal used function
 * @param int parent
 * @return int
 */
int LeftChildIndex(int parent) {
  return 2 * parent + 1;
}

/**
 * Internal used function
 * @tparam Comparable
 */
template<typename Comparable>
void SiftDown(std::vector<Comparable> &container, int parent, int size) {
  int child = LeftChildIndex(parent);
  Comparable tmp = std::move(container[parent]);
  while (child < size) {
    if ((child + 1) < size && container[child] < container[child + 1]) {
      ++child;
    }
    if (tmp < container[child]) {
      container[parent] = std::move(container[child]);
    } else {
      break;
    }
    parent = child;
    child = LeftChildIndex(child);
  }
  container[parent] = std::move(tmp);
}

template<typename Comparable>
void HeapSort(std::vector<Comparable> &container) {
  for (int i = (container.size() / 2) - 1; i >= 0; --i) {
    SiftDown(container, i, container.size());
  }
  for (int i = container.size() - 1; i > 0; --i) {
    std::swap(container[0], container[i]);
    SiftDown(container, 0, i);
  }
}

#endif //ALGORITHMS_ARCHIVE_HEAP_SORT_H_

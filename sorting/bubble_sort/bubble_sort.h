#ifndef ALGORITHMS_ARCHIVE_BUBBLE_SORT_H_
#define ALGORITHMS_ARCHIVE_BUBBLE_SORT_H_
#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace sorting {
template<typename Comparable>
void BubbleSort(std::vector<Comparable> &container) {
  for (int i = 1; i < container.size(); ++i) {
    for (int j = 0; j < container.size() - i; ++j) {
      if (container[j] > container[j + 1]) {
        std::swap(container[j], container[j + 1]);
      }
    }
  }
}
}
}
#endif //ALGORITHMS_ARCHIVE_BUBBLE_SORT_H_

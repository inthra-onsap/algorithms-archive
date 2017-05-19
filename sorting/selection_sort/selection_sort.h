#ifndef ALGORITHMS_ARCHIVE_SELECTION_SORT_H_
#define ALGORITHMS_ARCHIVE_SELECTION_SORT_H_
#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace sorting {
template<typename Comparable>
void SelectionSort(std::vector<Comparable> &container) {
  for (int i = 0; i < container.size(); ++i) {
    int min_index = i;
    int j = i + 1;
    while (j < container.size()) {
      if (container[min_index] > container[j]) {
        min_index = j;
      }
      ++j;
    }
    if (i != min_index) {
      std::swap(container[i], container[min_index]);
    }
  }
}
} // namespace sorting
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_SELECTION_SORT_H_

#ifndef ALGORITHMS_ARCHIVE_INSERTION_SORT_H_
#define ALGORITHMS_ARCHIVE_INSERTION_SORT_H_

#include <vector>
#include <utility>

namespace algorithms_archive {
namespace sorting {
template<typename Comparable>
void InsertionSort(std::vector<Comparable> &container) {
  for (int i = 1; i < container.size(); ++i) {
    Comparable tmp = std::move(container[i]);
    int j = i;
    while (j > 0 && tmp < container[j - 1]) {
      container[j] = std::move(container[j - 1]);
      --j;
    }
    container[j] = std::move(tmp);
  }
}
} // namespace sorting
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_INSERTION_SORT_H_

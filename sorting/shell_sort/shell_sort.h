#ifndef ALGORITHMS_ARCHIVE_SHELL_SORT_H_
#define ALGORITHMS_ARCHIVE_SHELL_SORT_H_

#include <vector>
#include <utility>

namespace algorithms_archive {
namespace sorting {
template<typename Comparable>
void ShellSort(std::vector<Comparable> &container) {
  for (int gap = container.size() / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < container.size(); ++i) {
      Comparable tmp = std::move(container[i]);
      int j = i;
      while (j >= gap && tmp < container[j - gap]) {
        container[j] = std::move(container[j - gap]);
        j -= gap;
      }
      container[j] = std::move(tmp);
    }
  }
}
} // namespace sorting
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_SHELL_SORT_H_

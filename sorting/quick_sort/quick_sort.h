#ifndef ALGORITHMS_ARCHIVE_QUICK_SORT_H_
#define ALGORITHMS_ARCHIVE_QUICK_SORT_H_

#include <vector>
#include <cstdlib>

namespace algorithms_archive {
namespace sorting {
/**
 * Internal function
 * @tparam Comparable
 * @param container
 * @param left
 * @param right
 */
template<typename Comparable>
void QuickSortInternal(std::vector<Comparable> &container, int left, int right) {
  int len = (right - left) + 1;
  if (len <= 1) {
    return;
  }
  const Comparable pivot = container[std::rand() % len + left];
  int lt_pos = left;
  int curr_pos = left;
  int gt_pos = right;
  while (curr_pos <= gt_pos) {
    if (pivot < container[curr_pos]) {
      std::swap(container[curr_pos], container[gt_pos--]);
    } else if (pivot > container[curr_pos]) {
      std::swap(container[curr_pos++], container[lt_pos++]);
    } else {
      ++curr_pos;
    }
  }
  QuickSortInternal(container, left, lt_pos);
  QuickSortInternal(container, gt_pos + 1, right);
}

template<typename Comparable>
void QuickSort(std::vector<Comparable> &container) {
  QuickSortInternal(container, 0, container.size() - 1);
}
} // namespace sorting
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_QUICK_SORT_H_

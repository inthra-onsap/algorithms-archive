#ifndef ALGORITHMS_ARCHIVE_QUICK_SORT_H_
#define ALGORITHMS_ARCHIVE_QUICK_SORT_H_

#include <vector>

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
const Comparable &MedianInternal(std::vector<Comparable> &container, int left, int right) {
  int center = (left + right) / 2;
  if (container[center] < container[left]) {
    std::swap(container[center], container[left]);
  }
  if (container[right] < container[left]) {
    std::swap(container[right], container[left]);
  }
  if (container[center] > container[right]) {
    std::swap(container[center], container[right]);
  }
  return container[center];
}

/**
 * Internal function
 * @tparam Comparable
 * @param container
 * @param left
 * @param right
 */
template<typename Comparable>
void QuickSortInternal(std::vector<Comparable> &container, int left, int right) {
  if ((right - left) <= 1) {
    return;
  }
  const Comparable &pivot = MedianInternal(container, left, right);
  int lt_pos = left + 1;
  int curr_pos = left + 1;
  int gt_pos = right - 1;
  while (curr_pos <= gt_pos) {
    if (pivot > container[curr_pos]) {
      std::swap(container[curr_pos++], container[gt_pos--]);
    } else if (pivot < container[curr_pos]) {
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

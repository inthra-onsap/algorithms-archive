#ifndef ALGORITHMS_ARCHIVE_MERGE_SORT_H_
#define ALGORITHMS_ARCHIVE_MERGE_SORT_H_
#include <vector>
#include <utility>

namespace algorithms_archive {
namespace sorting {
/**
 * Internal function
 * @tparam Comparable
 * @param container
 * @param tmp
 * @param left
 * @param right
 */
template<typename Comparable>
void MergeSortInternal(std::vector<Comparable> &container,
                       std::vector<Comparable> &tmp,
                       int left,
                       int right) {
  if ((right - left) <= 1) {
    return;
  }
  int center = (left + right) / 2;
  MergeSortInternal(container, tmp, left, center);
  MergeSortInternal(container, tmp, center, right);
  // Merge Operation
  int left_index = left;
  int tmp_index = left;
  int right_index = center;
  int first_arr_end = center;
  int second_arr_end = right;
  while (left_index < first_arr_end && right_index < second_arr_end) {
    if (container[left_index] <= container[right_index]) {
      tmp[tmp_index++] = std::move(container[left_index++]);
    } else {
      tmp[tmp_index++] = std::move(container[right_index++]);
    }
  }
  while (left_index < first_arr_end) {
    tmp[tmp_index++] = std::move(container[left_index++]);
  }
  while (right_index < second_arr_end) {
    tmp[tmp_index++] = std::move(container[right_index++]);
  }
  for (int i = left; i < right; ++i) {
    container[i] = std::move(tmp[i]);
  }
};

template<typename Comparable>
void MergeSort(std::vector<Comparable> &container) {
  std::vector<Comparable> tmp(container.size());
  MergeSortInternal<Comparable>(container, tmp, 0, container.size());
}
} // namespace sorting
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_MERGE_SORT_H_

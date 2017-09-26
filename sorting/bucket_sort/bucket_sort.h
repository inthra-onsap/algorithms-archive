#ifndef ALGORITHMS_ARCHIVE_BUCKET_SORT_H_
#define ALGORITHMS_ARCHIVE_BUCKET_SORT_H_
#include <vector>
#include <cmath>

namespace algorithms_archive {
namespace sorting {
/**
 * Internal function
 * @tparam Comparable
 * @param chunk
 */
template<typename Comparable>
void InsertionSortInternal(std::vector<Comparable> &chunk) {
  for (int i = 1; i < chunk.size(); ++i) {
    Comparable tmp = std::move(chunk[i]);
    int j = i;
    while (j > 0 && tmp < chunk[j - 1]) {
      chunk[j] = std::move(chunk[j - 1]);
      --j;
    }
    chunk[j] = std::move(tmp);
  }
}

/**
 * @tparam Comparable
 * @param container
 */
template<typename Comparable>
void BucketSort(std::vector<Comparable> &container) {
  int num_buckets = 10;
  int pos;
  Comparable max = *std::max_element(container.begin(), container.end());
  std::vector<std::vector<Comparable>> bucket(num_buckets, std::vector<Comparable>());
  int divider = std::ceil(float((max + 1.0) / num_buckets));

  for (int i = 0; i < container.size(); ++i) {
    pos = std::floor(container[i] / divider);
    bucket[pos].push_back(container[i]);
  }
  for (int i = 0; i < bucket.size(); ++i) {
    InsertionSortInternal(bucket[i]);
  }

  pos = 0;
  for (int i = 0; i < bucket.size(); ++i) {
    for (int j = 0; j < bucket[i].size(); ++j) {
      container[pos++] = bucket[i][j];
    }
  }
}
} // namespace sorting
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_BUCKET_SORT_H_

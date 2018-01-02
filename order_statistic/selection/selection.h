#ifndef ALGORITHMS_ARCHIVE_ITH_SMALLEST_ELEMENT_H_
#define ALGORITHMS_ARCHIVE_ITH_SMALLEST_ELEMENT_H_

#include <vector>
#include <random>
#include <utility>

namespace algorithms_archive {
namespace order_statistic {

template<typename Comparable>
class Selection {
 public:
  Comparable randomizedSelect(std::vector<Comparable> &data, int left, int right, int ith) {
    if (left == right)
      return data[left];

    int mid = randomizedPartition(data, left, right);
    int kth = mid - left + 1;

    if (ith == kth) {
      return data[mid];
    } else if (ith > kth) {
      return randomizedSelect(data, mid + 1, right, ith - kth);
    } else {
      return randomizedSelect(data, left, mid - 1, ith);
    }
  }

 private:
  int randomizedPartition(std::vector<Comparable> &data, int left, int right) {
    int len = right - left + 1;
    int pivot = left + (rand() % len);
    int i = left;
    int j = right - 1;

    std::swap(data[pivot], data[right]);
    while (i <= j) {
      if (data[i] > data[pivot])
        std::swap(data[j--], data[i]);
      else
        ++i;
    }
    std::swap(data[i], data[right]);
    return i;
  }
};

} // namespace order_statistic
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_ITH_SMALLEST_ELEMENT_H_

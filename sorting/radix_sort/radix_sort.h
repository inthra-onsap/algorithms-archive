#ifndef ALGORITHMS_ARCHIVE_RADIX_SORT_H_
#define ALGORITHMS_ARCHIVE_RADIX_SORT_H_
#include <vector>
#include <string>

template<typename Comparable>
void RadixSort(std::vector<Comparable> &container, int string_len) {
  std::vector<std::vector<std::string>> buckets(256);
  for (int pos = string_len - 1; pos >= 0; --pos) {
    for (std::string &str: container) {
      buckets[str[pos]].emplace_back(str);
    }
    int idx = 0;
    for (auto &bucket: buckets) {
      for (std::string &str: bucket) {
        container[idx++] = std::move(str);
      }
      bucket.clear();
    }
  }
}
#endif //ALGORITHMS_ARCHIVE_RADIX_SORT_H_

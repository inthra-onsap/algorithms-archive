#ifndef ALGORITHMS_ARCHIVE_SUFFIX_ARRAY_H_
#define ALGORITHMS_ARCHIVE_SUFFIX_ARRAY_H_

#include <string>
#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace string {

class SuffixArray {
 public:
  SuffixArray(std::string text_) : text{text_} {
    suffix_arr.resize(text.length(), -1);
    lcp.resize(text.length(), 0);
    BuildSuffixArray();
  }

  std::vector<int> NumberOccurrence() {
    return lcp;
  }

  std::vector<int> GetSuffixArray() {
    return suffix_arr;
  }

  bool Contains(const std::string &pattern);

 private:
  std::string text;
  std::vector<int> suffix_arr;
  std::vector<int> lcp;

  int ComputeLcp(const std::string &s1, const std::string &s2);

  void BuildSuffixArray();

  int Matches(const int &left, const int &right, const char *cstr, const std::string &pattern);
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_SUFFIX_ARRAY_H_

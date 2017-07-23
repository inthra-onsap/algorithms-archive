#ifndef ALGORITHMS_ARCHIVE_SUFFIX_ARRAY_H_
#define ALGORITHMS_ARCHIVE_SUFFIX_ARRAY_H_

#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

class SuffixArray {
 public:
  SuffixArray(std::string text_) : text{text_} {
    suffix_arr.resize(text.length(), -1);
    lcp.resize(text.length(), 0);
    BuildSuffixArray();
  }

  bool Contains(const std::string &pattern) {
    return (Matches(0, suffix_arr.size() - 1, text.c_str(), pattern) != -1);
  }

  std::vector<int> NumberOccurrence() {
    return lcp;
  }

  std::vector<int> GetSuffixArray() {
    return suffix_arr;
  }

 private:
  std::string text;
  std::vector<int> suffix_arr;
  std::vector<int> lcp;

  int ComputeLcp(const std::string &s1, const std::string &s2) {
    int match_count = 0;
    while (match_count < s1.length() && match_count < s2.length() && s1[match_count] == s2[match_count])
      ++match_count;
    return match_count;
  }

  void BuildSuffixArray() {
    const char *cstr = text.c_str();
    std::vector<const char *> suffices(text.length());

    for (int i = 0; i < text.length(); ++i)
      suffices[i] = cstr + i;
    std::sort(suffices.begin(), suffices.end(), [](const char *s1, const char *s2) { return strcmp(s1, s2) < 0; });
    for (int i = 0; i < text.length(); ++i)
      suffix_arr[i] = suffices[i] - cstr;
    for (int i = 1; i < text.length(); ++i)
      lcp[i] = ComputeLcp(suffices[i - 1], suffices[i]);
  }

  int Matches(const int &left, const int &right, const char *cstr, const std::string &pattern) {
    if (left > right) return -1;

    int mid = (left + right) / 2;
    int match = pattern.compare(0, pattern.length(), cstr + suffix_arr[mid], pattern.length());
    if (match == 0) {
      return mid;
    } else if (match < 0) {
      return Matches(left, mid - 1, cstr, pattern);
    } else {
      return Matches(mid + 1, right, cstr, pattern);
    }
  }
};

#endif //ALGORITHMS_ARCHIVE_SUFFIX_ARRAY_H_

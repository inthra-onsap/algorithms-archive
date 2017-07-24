#ifndef ALGORITHMS_ARCHIVE_KNUTH_MORRIS_PATT_H
#define ALGORITHMS_ARCHIVE_KNUTH_MORRIS_PATT_H

#include <vector>
#include <string>

namespace algorithms_archive {
namespace string {

class KnuthMorrisPatt {
 public:
  KnuthMorrisPatt(std::string text_) : text{text_} {}

  const std::vector<int> FindOccurences(std::string pattern) {
    std::string str = pattern + "$" + text;
    std::vector<int> prefix_arr(str.length(), 0);
    std::vector<int> occorrences;
    ProcessPrefix(str, prefix_arr);
    for (int i = (pattern.length() + 1); i < prefix_arr.size(); ++i)
      if (pattern.length() == prefix_arr[i])
        occorrences.push_back(i - (2 * pattern.length()));
    return occorrences;
  }

 private:
  std::string text;

  void ProcessPrefix(std::string &str, std::vector<int> &prefix_arr) {
    prefix_arr[0] = 0;
    int border = 0;
    for (int i = 1; i < str.length(); ++i) {
      while (border > 0 && str[i] != str[border])
        border = prefix_arr[border - 1];
      border = (str[i] == str[border]) ? border + 1 : 0;
      prefix_arr[i] = border;
    }
  }
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_KNUTH_MORRIS_PATT_H

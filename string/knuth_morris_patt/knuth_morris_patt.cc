#include "knuth_morris_patt.h"

namespace algorithms_archive {
namespace string {

const std::vector<int> KnuthMorrisPatt::FindOccurences(std::string pattern) {
  std::string str;
  str = pattern + "$" + text;
  std::vector<int> prefix_arr(str.length(), 0);
  std::vector<int> occorrences;
  ProcessPrefix(str, prefix_arr);
  for (int i = (pattern.length() + 1); i < prefix_arr.size(); ++i)
    if (pattern.length() == prefix_arr[i])
      occorrences.push_back(i - (2 * pattern.length()));
  return occorrences;
}

void KnuthMorrisPatt::ProcessPrefix(std::string &str, std::vector<int> &prefix_arr) {
  prefix_arr[0] = 0;
  int border = 0;
  for (int i = 1; i < str.length(); ++i) {
    while (border > 0 && str[i] != str[border])
      border = prefix_arr[border - 1];
    border = (str[i] == str[border]) ? border + 1 : 0;
    prefix_arr[i] = border;
  }
}

} // namespace string
} // namespace algorithms_archive
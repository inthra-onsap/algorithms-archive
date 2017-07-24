#ifndef ALGORITHMS_ARCHIVE_KNUTH_MORRIS_PATT_H
#define ALGORITHMS_ARCHIVE_KNUTH_MORRIS_PATT_H

#include <vector>
#include <string>

namespace algorithms_archive {
namespace string {

class KnuthMorrisPatt {
 public:
  KnuthMorrisPatt(std::string text_) : text{text_} {}

  const std::vector<int> FindOccurences(std::string pattern);

 private:
  std::string text;

  void ProcessPrefix(std::string &str, std::vector<int> &prefix_arr);
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_KNUTH_MORRIS_PATT_H

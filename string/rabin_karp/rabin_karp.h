
#ifndef ALGORITHMS_ARCHIVE_RABIN_KARP_H_
#define ALGORITHMS_ARCHIVE_RABIN_KARP_H_

#include <string>
#include <vector>
#include <cmath>

namespace algorithms_archive {
namespace string {

class RabinKarp {
 public:
  long long Hash(std::string str);

  long long Rehash(long long hash, std::string str, int start, int length);

  std::vector<int> PatternMatching(std::string pattern, std::string text);

 private:
  const int kPrimeNumber = 13;
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_RABIN_KARP_H_

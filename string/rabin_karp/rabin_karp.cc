#include "rabin_karp.h"

namespace algorithms_archive {
namespace string {

long long RabinKarp::Hash(std::string str) {
  long long hash = 0;
  for (int i = 0; i < str.length(); ++i) {
    hash += str[i] * std::pow(kPrimeNumber, i);
  }
  return hash;
}

long long RabinKarp::Rehash(long long hash, std::string str, int start, int length) {
  if(start == 0){
    return Hash(str.substr(start, length));
  }
  return ((hash - str[start - 1]) / kPrimeNumber) +
      (str[start + length - 1] * std::pow(kPrimeNumber, length - 1));
}

std::vector<int> RabinKarp::PatternMatching(std::string pattern, std::string text) {
  std::vector<int> all_occurrences;
  if (pattern.length() > text.length()) {
    return all_occurrences;
  }

  long long hashed_pattern = Hash(pattern);
  long long hashed_runner = 0;
  int l_limit = text.size() - pattern.size();
  for (int i = 0; i <= l_limit; ++i) {
    hashed_runner = Rehash(hashed_runner, text, i, pattern.length());
    if (hashed_pattern == hashed_runner) {
      all_occurrences.push_back(i);
    }
  }

  return all_occurrences;
}

} // namespace string
} // namespace algorithms_archive
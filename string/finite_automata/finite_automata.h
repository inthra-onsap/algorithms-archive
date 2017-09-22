#ifndef ALGORITHMS_ARCHIVE_FINITE_AUTOMATA_H_
#define ALGORITHMS_ARCHIVE_FINITE_AUTOMATA_H_

#include <vector>
#include <string>

namespace algorithms_archive {
namespace string {

class FiniteAutomata {
 public:
  std::vector<int> PatternMatching(std::string pattern, std::string text);

 private:
  std::vector<int> ProcessLps(std::string str);

  std::vector<std::vector<int>> PreprocessStates(std::string str);
};

}
}
#endif //ALGORITHMS_ARCHIVE_FINITE_AUTOMATA_H_

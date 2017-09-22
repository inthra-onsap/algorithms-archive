#include "finite_automata.h"

namespace algorithms_archive{
namespace string{

std::vector<int> FiniteAutomata::ProcessLps(std::string str) {
  std::vector<int> lps(str.length(), 0);
  int border = 0;

  lps[0] = 0;
  for (int i = 1; i < str.length(); ++i) {
    while (border > 0 && str[i] != str[border])
      border = lps[border - 1];
    border = (str[i] == str[border]) ? border + 1 : 0;
    lps[i] = border;
  }
  return lps;
}

std::vector<std::vector<int>> FiniteAutomata::PreprocessStates(std::string str) {
  int num_states = str.length() + 1;
  std::vector<std::vector<int>> states(num_states, std::vector<int>(256, 0));
  int prefix_border;

  std::vector<int> lps = ProcessLps(str);
  for (int state = 0; state < num_states; ++state) {
    for (int ch = 0; ch < 256; ++ch) {
      if (state < str.length() && ch == str[state]) {
        states[state][ch] = state + 1;
      } else {
        prefix_border = (state > 0) ? lps[state - 1] : 0;
        while (prefix_border > 0 && ch != str[prefix_border])
          prefix_border = lps[prefix_border - 1];
        states[state][ch] = (ch == str[prefix_border]) ? prefix_border + 1 : 0;
      }
    }
  }

  return states;
}

std::vector<int> FiniteAutomata::PatternMatching(std::string pattern, std::string text) {
  std::vector<int> all_occurrences;
  if (pattern.length() > text.length()) {
    return all_occurrences;
  }

  std::vector<std::vector<int>> states_tbl = PreprocessStates(pattern);
  int curr_state = 0;
  for (int i = 0; i < text.length(); ++i) {
    curr_state = states_tbl[curr_state][text[i]];
    if (curr_state == pattern.length()) {
      all_occurrences.push_back((i+1) - pattern.length());
    }
  }

  return all_occurrences;
}

} // namespace string
} // namespace algorithms_archive
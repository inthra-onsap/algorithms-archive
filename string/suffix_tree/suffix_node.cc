#include <unordered_map>

namespace algorithms_archive {
namespace string {

struct SuffixNode {
  int start;
  int *end;
  std::unordered_map<char, SuffixNode *> children;
  SuffixNode *suffix_link;
  int suffix_index;

  SuffixNode(SuffixNode *suffix_link_, int start_, int *end_)
      : suffix_link{suffix_link_}, start{start_}, end{end_}, suffix_index{-1} {}

  ~SuffixNode() {
    if (suffix_index == -1) {
      delete end;
    }
  }

  bool HasChild(char ch) {
    return (children[ch] == nullptr) ? false : true;
  }

  void SetChild(char ch, SuffixNode *node) {
    children[ch] = node;
  }

  void SetSuffixLink(SuffixNode *node) {
    suffix_link = node;
  }

  SuffixNode *GetChild(char ch) {
    return children[ch];
  }

  int EdgeLength() {
    if (start == -1) {
      return 0;
    }
    return *end - start + 1;
  }

  void SetEnd(int *end_pos) {
    end = end_pos;
  }

  void SetSuffixIndex(int idx) {
    suffix_index = idx;
  }
};

} // namespace string
} // namespace algorithms_archive
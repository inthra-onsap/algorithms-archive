#ifndef ALGORITHMS_ARCHIVE_SUFFIX_TREE_H_
#define ALGORITHMS_ARCHIVE_SUFFIX_TREE_H_

#include "suffix_node.cc"

#include <string>
#include <vector>

namespace algorithms_archive {
namespace string {

class SuffixTree {
 public:
  SuffixTree(std::string text_) : text{text_ + "$"} {
    BuildTree();
  }

  ~SuffixTree() {
    Clear(root);
  }

  std::vector<int> Search(std::string keyword);

 private:
  SuffixNode *root;
  SuffixNode *prev_internal_node;
  SuffixNode *active_node;
  int active_edge;
  int active_length;
  std::string text;
  int remaining_suffix;
  int leaf_end;

  void Clear(SuffixNode *node);

  void FindAllOccurrences(SuffixNode *node, std::vector<int> &all_occurrences);

  SuffixNode *NewSuffixNode(int start, int *end);

  bool ChangeActivePointByWalkDown(SuffixNode *node);

  void ExtendPhaseOf(int pos);

  void UpdateSuffixIndex(SuffixNode *node, int accumulate);

  void BuildTree();
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_SUFFIX_TREE_H_

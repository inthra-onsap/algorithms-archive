#ifndef ALGORITHMS_ARCHIVE_LCA_H_
#define ALGORITHMS_ARCHIVE_LCA_H_

#include <vector>
#include <cmath>

namespace algorithms_archive {
namespace tree {

class Lca {
 public:
  Lca(int size_) : size{size_ + 1} {
    parent.resize(size, -1);
    level.resize(size);
    tree.resize(size, std::vector<int>());
  }

  void AddNode(int from, int to);

  int CommonAncestorOf(int n1, int n2);

 private:
  int size;
  bool has_changed;
  std::vector<std::vector<int>> tree;
  std::vector<std::vector<int>> dp;
  std::vector<int> parent;
  std::vector<int> level;

  void PreProcess();
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_LCA_H_

#ifndef ALGORITHMS_ARCHIVE_SPLAY_TREE_H_
#define ALGORITHMS_ARCHIVE_SPLAY_TREE_H_

#include "splay_tree_node.cc"

#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class SplayTree {
 public:

 private:
  SplayTreeNode<Comparable> *root;

};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_SPLAY_TREE_H_

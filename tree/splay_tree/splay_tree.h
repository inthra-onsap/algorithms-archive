#ifndef ALGORITHMS_ARCHIVE_SPLAY_TREE_H_
#define ALGORITHMS_ARCHIVE_SPLAY_TREE_H_

#include "splay_tree_node.cc"

#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class SplayTree {
 public:
  SplayTree() : root{nullptr} {
  }
  SplayTree(const SplayTree &rhs) {
    root = Clone(rhs.root);
  }
  SplayTree(const SplayTree &&rhs) {
    root = Move(std::move(rhs.root));
  }

  ~SplayTree() {
    root = Clear(root);
  }

  void Clear() {
    root = Clear(root);
  }

 private:
  SplayTreeNode<Comparable> *root;

  SplayTreeNode<Comparable> *Clone(const SplayTreeNode<Comparable> *rhs) {
    if (rhs == nullptr) {
      return nullptr;
    } else {
      return new SplayTreeNode<Comparable>(rhs->data, Clone(rhs->left), Clone(rhs->right));
    }
  }

  SplayTreeNode<Comparable> *Move(const SplayTreeNode<Comparable> *&&rhs) {
    if (rhs == nullptr) {
      return nullptr;
    } else {
      return new SplayTreeNode<Comparable>(std::move(rhs->data),
                                           Clone(std::move(rhs->left)),
                                           Clone(std::move(rhs->right)));
    }
  }

  SplayTreeNode<Comparable> *Clear(SplayTreeNode<Comparable> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
      node = nullptr;
    }
    return node;
  }
};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_SPLAY_TREE_H_

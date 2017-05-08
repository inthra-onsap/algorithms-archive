#ifndef ALGORITHMS_ARCHIVE_BINARY_SEARCH_TREE_H_
#define ALGORITHMS_ARCHIVE_BINARY_SEARCH_TREE_H_

#include "bst_node.cc"

#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class BinarySearchTree {
 public:
  BinarySearchTree() : root{nullptr} {}

  BinarySearchTree(const BinarySearchTree &rhs) {
    root = Clone(rhs.root);
  }

  BinarySearchTree(BinarySearchTree &&rhs) {
    root = Move(std::move(rhs.root));
  }

  ~BinarySearchTree() {
    Clear(root);
  }

  const Comparable &FindMin() const {
    BstNode<Comparable> *temp_node = FindMin(root);
    return (temp_node != nullptr) ? temp_node->data : NULL;
  }

  const Comparable &FindMax() const {
    BstNode<Comparable> *temp_node = FindMax(root);
    return (temp_node != nullptr) ? temp_node->data : NULL;
  }

  bool Contains(const Comparable &value) const {
    return Contains(value, root);
  }

  bool IsEmpty() const {
    return root == nullptr;
  }

  void Clear() {
    Clear(root);
  }

  void Insert(const Comparable &value) {
    Insert(value, root);
  }

  void Insert(Comparable &&value) {
    Insert(std::move(value), root);
  }

  void Remove(const Comparable &value) {
    Remove(value, root);
  }

 private:
  BstNode<Comparable> *root;

  void Insert(const Comparable &value, BstNode<Comparable> *&node) {
    if (node == nullptr) {
      node = new BstNode<Comparable>(value);
    } else if (value < node->data) {
      Insert(value, node->left);
    } else if (value > node->data) {
      Insert(value, node->right);
    } else {
      // TODO: handle duplicate element
    }
  }

  BstNode<Comparable> Insert(Comparable &&value, BstNode<Comparable> *&node) {
    if (node == nullptr) {
      node = new BstNode<Comparable>(std::move(value));
    } else if (value < node->data) {
      Insert(std::move(value), node->left);
    } else if (value > node->data) {
      Insert(std::move(value), node->right);
    } else {
      // TODO: handle duplicate element
    }
  }

  void Remove(const Comparable &value, BstNode<Comparable> *&node) {
    if (node == nullptr) return;

    if (value < node->data) {
      Remove(value, node->left);
    } else if (value > node->data) {
      Remove(value, node->right);
    } else if (node->left != nullptr && node->right != nullptr) {
      BstNode<Comparable> *min_node = FindMin(node->right);
      node->data = min_node->data;
      Remove(node->data, node->right);
    } else {
      BstNode<Comparable> *old_node = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old_node;
    }
  }

  BstNode<Comparable> *FindMin(BstNode<Comparable> *node) const {
    if (node != nullptr) {
      while (node->left != nullptr) {
        node = node->left;
      }
    }
    return node;
  }

  BstNode<Comparable> *FindMax(BstNode<Comparable> *node) const {
    if (node != nullptr) {
      while (node->right != nullptr) {
        node = node->right;
      }
    }
    return node;
  }

  bool Contains(const Comparable &value, BstNode<Comparable> *node) const {
    if (node == nullptr) {
      return false;
    } else if (value < node->data) {
      return Contains(value, node->left);
    } else if (value > node->data) {
      return Contains(value, node->right);
    } else {
      return true;
    }
  }

  void Clear(BstNode<Comparable> *&node) {
    if (node != nullptr) {
      Clear(node->left);
      Clear(node->right);
      delete node;
      node = nullptr;
    }
  }

  BstNode<Comparable> *Clone(BstNode<Comparable> *node) const {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new BstNode<Comparable>{node->data, Clone(node->left), Clone(node->right)};
    }
  }

  BstNode<Comparable> *Move(BstNode<Comparable> *&&node) const {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new BstNode<Comparable>{std::move(node->data),
                                     Move(std::move(node->left)),
                                     Move(std::move(node->right))};
    }
  }
};
} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_BINARY_SEARCH_TREE_H_

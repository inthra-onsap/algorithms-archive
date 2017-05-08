#ifndef ALGORITHMS_ARCHIVE_AVL_TREE_H_
#define ALGORITHMS_ARCHIVE_AVL_TREE_H_

#include "avl_node.cc"

#include <algorithm>
#include<utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class AvlTree {
 public:
  AvlTree() : root{nullptr} {}

  AvlTree(const AvlTree &rhs) {
    root = Clone(rhs.root);
  }

  AvlTree(const AvlTree &&rhs) {
    root = Move(std::move(rhs.root));
  }

  ~AvlTree() {
    root = Clear(root);
  }

  const Comparable &FindMin() const {
    AvlNode<Comparable> *temp_node = FindMin(root);
    return (temp_node != nullptr) ? temp_node->data : NULL;
  }

  const Comparable &FindMax() const {
    AvlNode<Comparable> *temp_node = FindMax(root);
    return (temp_node != nullptr) ? temp_node->data : NULL;
  }

  void Insert(const Comparable &value) {
    root = Insert(value, root);
  }

  void Insert(const Comparable &&value) {
    root = Insert(std::move(value), root);
  }

  bool Contains(const Comparable &value) const {
    return Contains(value, root);
  }

  bool IsEmpty() {
    return root == nullptr;
  }

  void Clear() {
    root = Clear(root);
  }

  void Remove(const Comparable &value) {
    root = Remove(value, root);
  }

  int TreeHeight() {
    return Height(root);
  }

 private:
  enum BALANCE_TYPE {
    LEFT_HEAVY,
    BALANCE,
    RIGHT_HEAVY
  };
  AvlNode<Comparable> *root;

  BALANCE_TYPE BalanceFactor(AvlNode<Comparable> *node) {
    if ((Height(node->right) - Height(node->left)) > 1) {
      return RIGHT_HEAVY;
    } else if ((Height(node->right) - Height(node->left)) < -1) {
      return LEFT_HEAVY;
    } else {
      return BALANCE;
    }
  }

  int Height(AvlNode<Comparable> *node) {
    return (node == nullptr) ? 0 : node->height;
  }

  int MaxHeight(AvlNode<Comparable> *node) {
    return 1 + std::max(Height(node->left), Height(node->right));
  }

  AvlNode<Comparable> *Rebalance(AvlNode<Comparable> *node) {
    if (node == nullptr) return nullptr;
    node->height = MaxHeight(node);
    if (BalanceFactor(node) == LEFT_HEAVY) {
      if (Height(node->left->right) > Height(node->left->left)) {
        return RotateLeftRight(node);
      } else {
        return RotateRight(node);
      }
    } else if (BalanceFactor(node) == RIGHT_HEAVY) {
      if (Height(node->right->left) > Height(node->right->right)) {
        return RotateRightLeft(node);
      } else {
        return RotateLeft(node);
      }
    }
    return node;
  }

  AvlNode<Comparable> *RotateRight(AvlNode<Comparable> *node) {
    AvlNode<Comparable> *subtree_root = node->left;
    node->left = subtree_root->right;
    subtree_root->right = node;
    node->height = MaxHeight(node);
    subtree_root->height = MaxHeight(subtree_root);
    return subtree_root;
  }

  AvlNode<Comparable> *RotateLeft(AvlNode<Comparable> *node) {
    AvlNode<Comparable> *subtree_root = node->right;
    node->right = subtree_root->left;
    subtree_root->left = node;
    node->height = MaxHeight(node);
    subtree_root->height = MaxHeight(subtree_root);
    return subtree_root;
  }

  AvlNode<Comparable> *RotateLeftRight(AvlNode<Comparable> *node) {
    node->left = RotateLeft(node->left);
    return RotateRight(node);
  }

  AvlNode<Comparable> *RotateRightLeft(AvlNode<Comparable> *node) {
    node->right = RotateRight(node->right);
    return RotateLeft(node);
  }

  AvlNode<Comparable> *Insert(const Comparable &value, AvlNode<Comparable> *node) {
    if (node == nullptr) {
      return new AvlNode<Comparable>{value};
    } else if (value < node->data) {
      node->left = Insert(value, node->left);
    } else if (value > node->data) {
      node->right = Insert(value, node->right);
    }
    return Rebalance(node);
  }

  AvlNode<Comparable> *Insert(const Comparable &&value, AvlNode<Comparable> *node) {
    if (node == nullptr) {
      return new AvlNode<Comparable>{std::move(value)};
    } else if (value < node->data) {
      node->left = Insert(std::move(value), node->left);
    } else if (value > node->data) {
      node->right = Insert(std::move(value), node->right);
    }
    return Rebalance(node);
  }

  AvlNode<Comparable> *FindMin(AvlNode<Comparable> *node) const {
    if (node != nullptr) {
      while (node->left != nullptr) {
        node = node->left;
      }
    }
    return node;
  }

  AvlNode<Comparable> *FindMax(AvlNode<Comparable> *node) const {
    if (node != nullptr) {
      while (node->right != nullptr) {
        node = node->right;
      }
    }
    return node;
  }

  bool Contains(const Comparable &value, AvlNode<Comparable> *node) const {
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

  AvlNode<Comparable> *Clear(AvlNode<Comparable> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
      node = nullptr;
    }
    return node;
  }

  AvlNode<Comparable> *Clone(const AvlNode<Comparable> *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new AvlNode<Comparable>{node->data, Clone(node->left), Clone(node->right), node->height};
    }
  }

  AvlNode<Comparable> *Move(const AvlNode<Comparable> *&&node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new AvlNode<Comparable>{std::move(node->data),
                                     Clone(std::move(node->left)),
                                     Clone(std::move(node->right)),
                                     std::move(node->height)};
    }
  }

  AvlNode<Comparable> *Remove(const Comparable &value, AvlNode<Comparable> *node) {
    if (node == nullptr) return nullptr;

    if (value < node->data) {
      node->left = Remove(value, node->left);
    } else if (value > node->data) {
      node->right = Remove(value, node->right);
    } else if (node->left != nullptr && node->right != nullptr) {
      AvlNode<Comparable> *min_node = FindMin(node->right);
      node->data = min_node->data;
      node->right = Remove(node->data, node->right);
    } else {
      AvlNode<Comparable> *old_node = node;
      node = (node->left != nullptr) ? node->left : node->right;
      delete old_node;
    }
    return Rebalance(node);
  }
};
} // namespace tree
} // namespace algorithm_archive

#endif //ALGORITHMS_ARCHIVE_AVL_TREE_H_

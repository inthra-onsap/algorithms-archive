#ifndef ALGORITHMS_ARCHIVE_TOPDOWN_SPLAY_TREE_H_
#define ALGORITHMS_ARCHIVE_TOPDOWN_SPLAY_TREE_H_

#include "splay_tree_node.cc"

#include <utility>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class TopDownSplayTree {
 public:
  TopDownSplayTree() : root{nullptr} {}

  ~TopDownSplayTree() {
    root = Clear(root);
  }

  TopDownSplayTree(const TopDownSplayTree &rhs) {
    root = Clone(rhs.root);
  }

  TopDownSplayTree(TopDownSplayTree &&rhs) {
    root = Clone(std::move(rhs.root));
  }

  void Clear() {
    root = Clear(root);
  }

  void Insert(const Comparable &value) {
    root = Insert(value, root);
  }

  void Insert(const Comparable &&value) {
    root = Insert(std::move(value), root);
  }

  bool Contains(const Comparable &value) {
    TopDownSplayTreeNode<Comparable> *node = Find(value, root);
    root = Splay(value, root);
    return (node != nullptr && node->data == value);
  }

  const TopDownSplayTreeNode<Comparable> *Find(const Comparable &value) {
    TopDownSplayTreeNode<Comparable> *node = Find(value, root);
    root = Splay(value, root);
    return node;
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  void Remove(const Comparable &value) {
    root = Remove(value, root);
  }

 private:
  TopDownSplayTreeNode<Comparable> *root;

  TopDownSplayTreeNode<Comparable> *Clone(TopDownSplayTreeNode<Comparable> *node) {
    if (node == nullptr) return nullptr;
    return new TopDownSplayTreeNode<Comparable>{node->data, Clone(node->left), Clone(node->right)};
  }

  TopDownSplayTreeNode<Comparable> *Move(TopDownSplayTreeNode<Comparable> *&&node) {
    if (node == nullptr) return nullptr;
    return new TopDownSplayTreeNode<Comparable>{std::move(node->data),
                                                Clone(std::move(node->left)),
                                                Clone(std::move(node->right))};
  }

  TopDownSplayTreeNode<Comparable> *Clear(TopDownSplayTreeNode<Comparable> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
    }
    return nullptr;
  }

  TopDownSplayTreeNode<Comparable> *Insert(const Comparable &value, TopDownSplayTreeNode<Comparable> *root) {
    if (root == nullptr) {
      return new TopDownSplayTreeNode<Comparable>{value};
    }
    root = Splay(value, root);
    if (value < root->data) {
      root = new TopDownSplayTreeNode<Comparable>{value, root->left, root};
      root->right->left = nullptr;
    } else if (value > root->data) {
      root = new TopDownSplayTreeNode<Comparable>{value, root, root->right};
      root->left->right = nullptr;
    }
    return root;
  }

  TopDownSplayTreeNode<Comparable> *Insert(const Comparable &&value, TopDownSplayTreeNode<Comparable> *root) {
    if (root == nullptr) {
      return new TopDownSplayTreeNode<Comparable>{std::move(value)};
    }
    root = Splay(value, root);
    if (value < root->data) {
      root = new TopDownSplayTreeNode<Comparable>{std::move(value), root->left, root};
      root->right->left = nullptr;
    } else if (value > root->data) {
      root = new TopDownSplayTreeNode<Comparable>{std::move(value), root, root->right};
      root->left->right = nullptr;
    }
    return root;
  }

  TopDownSplayTreeNode<Comparable> *FindMax(TopDownSplayTreeNode<Comparable> *node) {
    if (node != nullptr) {
      while (node->right != nullptr) {
        node = node->right;
      }
    }
    return node;
  }

  TopDownSplayTreeNode<Comparable> *Remove(const Comparable &value, TopDownSplayTreeNode<Comparable> *root) {
    if (root == nullptr) {
      return nullptr;
    }
    root = Splay(value, root);
    if (root->data == value) {
      TopDownSplayTreeNode<Comparable> *del_node = root;
      if (root->left != nullptr && root->right != nullptr) {
        // Case 1. root has both left & right subtree
        TopDownSplayTreeNode<Comparable> *right_tree = root->right;
        TopDownSplayTreeNode<Comparable> *max_node = FindMax(root->left);
        root = Splay(max_node->data, root->left);
        root->right = right_tree;
      } else if (root->left == nullptr) {
        // Case 2. root has only right subtree
        root = root->right;
      } else if (root->right == nullptr) {
        // Case 3. root has only left subtree
        root = root->left;
      } else {
        // Case 4. root is only one node
        root = nullptr;
      }
      delete del_node;
    }
    return root;
  }

  TopDownSplayTreeNode<Comparable> *Find(const Comparable &value, TopDownSplayTreeNode<Comparable> *node) {
    if (node == nullptr) {
      return nullptr;
    } else if (value < node->data && node->left != nullptr) {
      return Find(value, node->left);
    } else if (value > node->data && node->right != nullptr) {
      return Find(value, node->right);
    } else {
      return node;
    }
  }

  TopDownSplayTreeNode<Comparable> *RotateLeft(TopDownSplayTreeNode<Comparable> *node) {
    TopDownSplayTreeNode<Comparable> *root = node->right;
    node->right = root->left;
    root->left = node;
    return root;
  }

  TopDownSplayTreeNode<Comparable> *RotateRight(TopDownSplayTreeNode<Comparable> *node) {
    TopDownSplayTreeNode<Comparable> *root = node->left;
    node->left = root->right;
    root->right = node;
    return root;
  }

  TopDownSplayTreeNode<Comparable> *Splay(const Comparable &value, TopDownSplayTreeNode<Comparable> *root) {
    if (root == nullptr) {
      return nullptr;
    }

    TopDownSplayTreeNode<Comparable> *left_tree{nullptr};
    TopDownSplayTreeNode<Comparable> *right_tree{nullptr};
    TopDownSplayTreeNode<Comparable> tmp_tree{root->data};
    while (true) {
      if (value < root->data) {
        if (root->left != nullptr && value < root->left->data) root = RotateRight(root);
        if (root->left == nullptr) break;
        if (tmp_tree.right == nullptr) {
          tmp_tree.right = right_tree = root;
        } else {
          right_tree->left = root;
          right_tree = root;
        }
        root = root->left;
      } else if (value > root->data) {
        if (root->right != nullptr && value > root->right->data) root = RotateLeft(root);
        if (root->right == nullptr) break;
        if (tmp_tree.left == nullptr) {
          tmp_tree.left = left_tree = root;
        } else {
          left_tree->right = root;
          left_tree = root;
        }
        root = root->right;
      } else {
        break;
      }
    }
    if (left_tree != nullptr) left_tree->right = root->left;
    if (right_tree != nullptr) right_tree->left = root->right;
    if (tmp_tree.left != nullptr) root->left = tmp_tree.left;
    if (tmp_tree.right != nullptr) root->right = tmp_tree.right;
    return root;
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_TOPDOWN_SPLAY_TREE_H_

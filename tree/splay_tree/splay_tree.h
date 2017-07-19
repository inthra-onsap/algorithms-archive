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

  const SplayTreeNode<Comparable> *Find(const Comparable &value) {
    SplayTreeNode<Comparable> *new_root = Find(value, root);
    Splay(new_root);
    return new_root;
  }

  bool Contains(const Comparable &value) {
    const SplayTreeNode<Comparable> *new_root = Find(value);
    if (new_root == nullptr) {
      return false;
    }
    return (new_root->data == value);
  }

  void Insert(const Comparable &value) {
    root = Insert(value, root);
  }

  void Insert(const Comparable &&value) {
    root = Insert(std::move(value), root);
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  void Remove(const Comparable &value) {
    root = Remove(value, root);
  }

 private:
  SplayTreeNode<Comparable> *root;

  SplayTreeNode<Comparable> *Clone(const SplayTreeNode<Comparable> *rhs) {
    if (rhs == nullptr) {
      return nullptr;
    } else {
      SplayTreeNode<Comparable> *left = Clone(rhs->left);
      SplayTreeNode<Comparable> *right = Clone(rhs->right);
      SplayTreeNode<Comparable> *node = new SplayTreeNode<Comparable>(rhs->data, left, right);

      if (left != nullptr) left->parent = node;
      if (right != nullptr) right->parent = node;
      return node;
    }
  }

  SplayTreeNode<Comparable> *Move(const SplayTreeNode<Comparable> *&&rhs) {
    if (rhs == nullptr) {
      return nullptr;
    } else {
      SplayTreeNode<Comparable> *left = Move(std::move(rhs->left));
      SplayTreeNode<Comparable> *right = Move(std::move(rhs->right));
      SplayTreeNode<Comparable> *node = new SplayTreeNode<Comparable>(
          std::move(rhs->data), std::move(left), std::move(right));

      if (left != nullptr) left->parent = node;
      if (right != nullptr) right->parent = node;
      return node;
    }
  }

  SplayTreeNode<Comparable> *Clear(SplayTreeNode<Comparable> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
    }
    return nullptr;
  }

  SplayTreeNode<Comparable> *Find(const Comparable &value, SplayTreeNode<Comparable> *node) {
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

  void RotateLeft(SplayTreeNode<Comparable> *node) {
    SplayTreeNode<Comparable> *subtree_root = node->right;
    node->right = subtree_root->left;
    subtree_root->left = node;
    if (node->parent != nullptr) {
      if (node->parent->left == node) {
        node->parent->left = subtree_root;
      } else {
        node->parent->right = subtree_root;
      }
    }
    subtree_root->parent = node->parent;
    node->parent = subtree_root;
    if (node->right != nullptr) {
      node->right->parent = node;
    }
  }

  void RotateRight(SplayTreeNode<Comparable> *node) {
    SplayTreeNode<Comparable> *subtree_root = node->left;
    node->left = subtree_root->right;
    subtree_root->right = node;
    if (node->parent != nullptr) {
      if (node->parent->left == node) {
        node->parent->left = subtree_root;
      } else {
        node->parent->right = subtree_root;
      }
    }
    subtree_root->parent = node->parent;
    node->parent = subtree_root;
    if (node->left != nullptr) {
      node->left->parent = node;
    }
  }

  void Splay(SplayTreeNode<Comparable> *node) {
    if (node == nullptr || node->parent == nullptr) {
      return;
    }

    while (node->parent != nullptr) {
      if (node->parent->parent != nullptr) {
        if (node == node->parent->left && node->parent == node->parent->parent->left) {
          // Zig-Zig
          RotateRight(node->parent->parent);
          RotateRight(node->parent);
        } else if (node == node->parent->right && node->parent == node->parent->parent->right) {
          // Zag-Zag
          RotateLeft(node->parent->parent);
          RotateLeft(node->parent);
        } else if (node == node->parent->right && node->parent == node->parent->parent->left) {
          // Zig-Zag
          RotateLeft(node->parent);
          RotateRight(node->parent);
        } else {
          // Zag-Zig
          RotateRight(node->parent);
          RotateLeft(node->parent);
        }
      } else {
        // Zig
        if (node == node->parent->left) {
          RotateRight(node->parent);
        } else {
          RotateLeft(node->parent);
        }
      }
    }
    root = node;
  }

  SplayTreeNode<Comparable> *Insert(const Comparable &value, SplayTreeNode<Comparable> *node) {
    SplayTreeNode<Comparable> *curr_root = Find(value, node);
    // Empty Tree
    if (curr_root == nullptr) {
      return new SplayTreeNode<Comparable>{value};
    }
    Splay(curr_root);
    // Already Existed
    if (curr_root->data == value) {
      return curr_root;
    }
    // Add new root
    SplayTreeNode<Comparable> *new_root = new SplayTreeNode<Comparable>{value};
    if (value < curr_root->data) {
      new_root->right = curr_root;
      new_root->left = curr_root->left;
      curr_root->left = nullptr;
      curr_root->parent = new_root;
      if (new_root->left != nullptr) {
        new_root->left->parent = new_root;
      }
    } else {
      new_root->left = curr_root;
      new_root->right = curr_root->right;
      curr_root->right = nullptr;
      curr_root->parent = new_root;
      if (new_root->right != nullptr) {
        new_root->right->parent = new_root;
      }
    }
    return new_root;
  }

  SplayTreeNode<Comparable> *Insert(const Comparable &&value, SplayTreeNode<Comparable> *node) {
    SplayTreeNode<Comparable> *curr_root = Find(value, node);
    // Empty Tree
    if (curr_root == nullptr) {
      return new SplayTreeNode<Comparable>{std::move(value)};
    }
    Splay(curr_root);
    // Already Existed
    if (curr_root->data == value) {
      return curr_root;
    }
    // Add new root
    SplayTreeNode<Comparable> *new_root = new SplayTreeNode<Comparable>{std::move(value)};
    if (curr_root->data > value) {
      new_root->right = curr_root;
      new_root->left = curr_root->left;
      curr_root->left = nullptr;
      curr_root->parent = new_root;
      if (new_root->left != nullptr) {
        new_root->left->parent = new_root;
      }
    } else {
      new_root->left = curr_root;
      new_root->right = curr_root->right;
      curr_root->right = nullptr;
      curr_root->parent = new_root;
      if (new_root->right != nullptr) {
        new_root->right->parent = new_root;
      }
    }
    return new_root;
  }

  SplayTreeNode<Comparable> *FindMin(SplayTreeNode<Comparable> *node) {
    if (node != nullptr) {
      while (node->left != nullptr) {
        node = node->left;
      }
    }
    return node;
  }

  SplayTreeNode<Comparable> *Remove(const Comparable &value, SplayTreeNode<Comparable> *node) {
    SplayTreeNode<Comparable> *find_node = Find(value, node);
    if (find_node == nullptr) {
      return nullptr;
    }
    Splay(find_node);
    if (find_node->data == value) {
      if (find_node->left != nullptr && find_node->right != nullptr) {
        // Case 1. find_node has both left & right subtree
        SplayTreeNode<Comparable> *new_root = FindMin(find_node->right);
        if (new_root->parent != find_node) {
          new_root->parent->left = new_root->right;
          new_root->right = find_node->right;
          new_root->right->parent = new_root;
        }
        new_root->left = find_node->left;
        new_root->left->parent = new_root;
      } else if (find_node->right != nullptr) {
        // Case 2. find_node has only right subtree
        node = find_node->right;
        node->parent = nullptr;
      } else if (find_node->left != nullptr) {
        // Case 3. find_node has only left subtree
        node = find_node->left;
        node->parent = nullptr;
      } else {
        // Case 4. find_node is only one node
        node = nullptr;
      }
      delete find_node;
    }
    return node;
  }
};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_SPLAY_TREE_H_

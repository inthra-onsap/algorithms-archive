#ifndef ALGORITHMS_ARCHIVE_REDBLACK_TREE_H_
#define ALGORITHMS_ARCHIVE_REDBLACK_TREE_H_

#include "redblack_node.cc"

#include <utility>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class RedBlackTree {
 public:
  enum Color : char { RED = 'r', BLACK = 'b' };

  RedBlackTree() : root{nullptr} {}

  RedBlackTree(const RedBlackTree &rhs) {
    root = Clone(rhs.root, nullptr);
  }

  RedBlackTree(const RedBlackTree &&rhs) {
    root = Move(std::move(rhs.root), nullptr);
  }

  ~RedBlackTree() {
    root = Clear(root);
  }

  const RedBlackNode<Comparable> Find(const Comparable &value) {
    return Find(value, root);
  }

  void Clear() {
    root = Clear(root);
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  void Insert(const Comparable &value) {
    Insert(value, root, nullptr);
  }

  void Remove(const Comparable &value) {
    Remove(value, root);
  }

 private:
  RedBlackNode<Comparable> *root;

  RedBlackNode<Comparable> *Clone(RedBlackNode<Comparable> *node, RedBlackNode<Comparable> *parent) {
    if (node == nullptr) return nullptr;
    RedBlackNode<Comparable>
        *new_node = new RedBlackNode<Comparable>{node->data, nullptr, nullptr, parent, node->color};
    new_node->left = Clone(node->left, new_node);
    new_node->right = Clone(node->right, new_node);
    return new_node;
  }

  RedBlackNode<Comparable> *Move(RedBlackNode<Comparable> *&&node, RedBlackNode<Comparable> *parent) {
    if (node == nullptr) return nullptr;
    RedBlackNode<Comparable> *new_node = new RedBlackNode<Comparable>{std::move(node->data),
                                                                      nullptr,
                                                                      nullptr,
                                                                      parent,
                                                                      std::move(node->color)};
    new_node->left = Move(std::move(node->left), new_node);
    new_node->right = Move(std::move(node->right), new_node);
    return new_node;
  }

  RedBlackNode<Comparable> *Clear(RedBlackNode<Comparable> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
    }
    return nullptr;
  }

  RedBlackNode<Comparable> *Find(const Comparable &value, RedBlackNode<Comparable> *node) {
    if (node == nullptr) return nullptr;
    if (value < node->data) {
      return Find(value, node->left);
    } else if (value > node->data) {
      return Find(value, node->right);
    } else {
      return node;
    }
  }

  RedBlackNode<Comparable> *FindMin(RedBlackNode<Comparable> *node) {
    if (node != nullptr) {
      while (node->left != nullptr) {
        node = node->left;
      }
    }
    return node;
  }

  void Remove(const Comparable &value, RedBlackNode<Comparable> *&node) {
    if (node == nullptr) return;
    if (value < node->data) {
      Remove(value, node->left);
    } else if (value > node->data) {
      Remove(value, node->right);
    } else if (node->right != nullptr) {
      RedBlackNode<Comparable> *successor = FindMin(node->right);
      node->data = successor->data;
      Remove(successor->data, node->right);
    } else {
      if (node->color == BLACK) {

      }
      delete node;
      node = nullptr;
    }

  }

  void Insert(const Comparable &value,
              RedBlackNode<Comparable> *&node,
              RedBlackNode<Comparable> *parent) {
    if (node == nullptr) {
      node = new RedBlackNode<Comparable>{value, nullptr, nullptr, parent, RED};
    } else {
      if (value < node->data) {
        Insert(value, node->left, node);
      } else if (value > node->data) {
        Insert(value, node->right, node);
      } else {
        // Todo: handle duplicate element
      }
    }
    Recolor(node);
  }

  void RotateLeft(RedBlackNode<Comparable> *&node, bool change_color) {
    RedBlackNode<Comparable> *root = node->right;
    RedBlackNode<Comparable> *node_parent = node->parent;
    node->right = root->left;
    root->left = node;

    node->right->parent = node;
    node->parent = root;
    root->parent = node_parent;

    if (node_parent != nullptr) {
      if (node == node_parent->left) node_parent->left = root;
      else node_parent->right = root;
    }
    if (change_color) {
      root->color = BLACK;
      node->color = RED;
    }
  }

  void RotateRight(RedBlackNode<Comparable> *&node, bool change_color) {
    RedBlackNode<Comparable> *root = node->left;
    RedBlackNode<Comparable> *node_parent = node->parent;
    node->left = root->right;
    root->right = node;

    node->left->parent = node;
    node->parent = root;
    root->parent = node_parent;

    if (node_parent != nullptr) {
      if (node == node_parent->left) node_parent->left = root;
      else node_parent->right = root;
    }
    if (change_color) {
      root->color = BLACK;
      node->color = RED;
    }
  }

  void Rotate(RedBlackNode<Comparable> *&node) {
    if (node == node->parent->left) {
      if (node->parent == node->parent->parent->left) {
        // LL
        RotateRight(node->parent->parent, true);
      } else {
        // LR
        RotateRight(node->parent, false);
        RotateLeft(node->parent, true);
      }
    } else {
      if (node->parent == node->parent->parent->right) {
        // RR
        RotateLeft(node->parent->parent, true);
      } else {
        // RL
        RotateLeft(node->parent, false);
        RotateRight(node->parent, true);
      }
    }
  }

  void Recolor(RedBlackNode<Comparable> *&node) {
    if (node->parent == nullptr) {
      node->color = BLACK;
      root = node;
    } else {
      if (node->color == RED && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
          if (node->parent->parent->right == nullptr || node->parent->parent->right->color == BLACK) {
            Rotate(node);
          } else {
            node->parent->parent->color = RED;
            node->parent->color = BLACK;
            node->parent->parent->right->color = BLACK;
          }
        } else {
          if (node->parent->parent->left == nullptr || node->parent->parent->left->color == BLACK) {
            Rotate(node);
          } else {
            node->parent->parent->color = RED;
            node->parent->color = BLACK;
            node->parent->parent->left->color = BLACK;
          }
        }
      }
    }
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_REDBLACK_TREE_H_

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

  const RedBlackNode<Comparable> *Find(const Comparable &value) {
    return Find(value, root);
  }

  bool Contains(const Comparable &value) {
    return (Find(value, root) != nullptr);
  }

  void Clear() {
    root = Clear(root);
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  void Insert(const Comparable &value) {
    RedBlackNode<Comparable> *new_node = Insert(value, root, nullptr);
    Recolor(new_node);
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

  RedBlackNode<Comparable> *Insert(const Comparable &value,
                                   RedBlackNode<Comparable> *&node,
                                   RedBlackNode<Comparable> *parent) {
    if (node == nullptr) {
      node = new RedBlackNode<Comparable>{value, nullptr, nullptr, parent, RED};
      return node;
    } else if (value < node->data) {
      return Insert(value, node->left, node);
    } else {
      return Insert(value, node->right, node);
    }
  }

  void RotateLeft(RedBlackNode<Comparable> *node, bool flip_color) {
    RedBlackNode<Comparable> *n_root = node->right;
    RedBlackNode<Comparable> *p_root = node->parent;
    node->right = n_root->left;
    n_root->left = node;

    node->parent = n_root;
    n_root->parent = p_root;

    if (node->right != nullptr) {
      node->right->parent = node;
    }

    if (p_root == nullptr) {
      root = n_root;
    } else if (node == p_root->left) {
      p_root->left = n_root;
    } else {
      p_root->right = n_root;
    }

    if (flip_color) {
      n_root->color = node->color;
      node->color = RED;
    }
  }

  void RotateRight(RedBlackNode<Comparable> *node, bool flip_color) {
    RedBlackNode<Comparable> *n_root = node->left;
    RedBlackNode<Comparable> *p_root = node->parent;
    node->left = n_root->right;
    n_root->right = node;

    node->parent = n_root;
    n_root->parent = p_root;

    if (node->left != nullptr) {
      node->left->parent = node;
    }

    if (p_root == nullptr) {
      root = n_root;
    } else if (node == p_root->left) {
      p_root->left = n_root;
    } else {
      p_root->right = n_root;
    }

    if (flip_color) {
      n_root->color = node->color;
      node->color = RED;
    }
  }

  void Recolor(RedBlackNode<Comparable> *node) {
    while (IsRed(node->parent)) {
      if (node->parent == node->parent->parent->left) {
        if (IsRed(node->parent->parent->right)) {
          node->parent->parent->color = RED;
          node->parent->color = BLACK;
          node->parent->parent->right->color = BLACK;
          node = node->parent->parent;
        } else {
          if (node == node->parent->right) {
            node = node->parent;
            RotateLeft(node, false);
          }
          RotateRight(node->parent->parent, true);
        }
      } else {
        if (IsRed(node->parent->parent->left)) {
          node->parent->parent->color = RED;
          node->parent->color = BLACK;
          node->parent->parent->left->color = BLACK;
          node = node->parent->parent;
        } else {
          if (node == node->parent->left) {
            node = node->parent;
            RotateRight(node, false);
          }
          RotateLeft(node->parent->parent, true);
        }
      }
    }

    root->color = BLACK;
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
    } else if (node->left != nullptr && node->right != nullptr) {
      RedBlackNode<Comparable> *successor = FindMin(node->right);
      node->data = successor->data;
      Remove(successor->data, node->right);
    } else {
      RedBlackNode<Comparable> *delete_node = node;
      RedBlackNode<Comparable> *replace_node = (node->left != nullptr) ? node->left : node->right;

      if (replace_node != nullptr) {
        replace_node->parent = node->parent;
      }

      if (IsBlack(delete_node)) {
        if (IsRed(replace_node)) {
          replace_node->color = BLACK;
        } else {
          RemoveCase1(delete_node);
        }
      }

      node = replace_node;
      delete delete_node;
    }
  }

  void RemoveCase1(RedBlackNode<Comparable> *double_black) {
    if (double_black->parent == nullptr) return;
    RemoveCase2(double_black);
  }

  void RemoveCase2(RedBlackNode<Comparable> *double_black) {
    RedBlackNode<Comparable> *sibling = GetSibling(double_black);
    if (IsRed(sibling)) {
      if (double_black == double_black->parent->left) {
        RotateLeft(double_black->parent, true);
      } else {
        RotateRight(double_black->parent, true);
      }
      if (sibling->parent == nullptr) {
        root = sibling;
      }
    }
    RemoveCase3(double_black);
  }

  void RemoveCase3(RedBlackNode<Comparable> *double_black) {
    RedBlackNode<Comparable> *sibling = GetSibling(double_black);
    if (IsBlack(double_black->parent) &&
        IsBlack(sibling) &&
        IsBlack(sibling->left) &&
        IsBlack(sibling->right)) {
      sibling->color = RED;
      RemoveCase1(double_black->parent);
    } else {
      RemoveCase4(double_black);
    }
  }

  void RemoveCase4(RedBlackNode<Comparable> *double_black) {
    RedBlackNode<Comparable> *sibling = GetSibling(double_black);
    if (IsRed(double_black->parent) &&
        IsBlack(sibling) &&
        IsBlack(sibling->left) &&
        IsBlack(sibling->right)) {
      double_black->parent->color = BLACK;
      sibling->color = RED;
      return;
    }
    RemoveCase5(double_black);
  }

  void RemoveCase5(RedBlackNode<Comparable> *double_black) {
    RedBlackNode<Comparable> *sibling = GetSibling(double_black);
    if (IsBlack(sibling)) {
      if (double_black == double_black->parent->left && IsRed(sibling->left) && IsBlack(sibling->right)) {
        RotateRight(sibling, true);
      } else {
        if (double_black == double_black->parent->right && IsRed(sibling->right) && IsBlack(sibling->left)) {
          RotateLeft(sibling, true);
        }
      }
    }
    RemoveCase6(double_black);
  }

  void RemoveCase6(RedBlackNode<Comparable> *double_black) {
    RedBlackNode<Comparable> *sibling = GetSibling(double_black);
    sibling->color = sibling->parent->color;
    sibling->parent->color = BLACK;
    if (double_black == double_black->parent->left) {
      sibling->right->color = BLACK;
      RotateLeft(sibling->parent, false);
    } else {
      sibling->left->color = BLACK;
      RotateRight(sibling->parent, false);
    }
    if (sibling->parent == nullptr) {
      root = sibling;
    }
  }

  RedBlackNode<Comparable> *GetSibling(RedBlackNode<Comparable> *node) {
    return (node == node->parent->left) ? node->parent->right : node->parent->left;
  }

  bool IsBlack(RedBlackNode<Comparable> *node) {
    return (node == nullptr || node->color == BLACK);
  }

  bool IsRed(RedBlackNode<Comparable> *node) {
    return (node != nullptr && node->color == RED);
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_REDBLACK_TREE_H_

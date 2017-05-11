#ifndef ALGORITHMS_ARCHIVE_ROPE_TREE_H_
#define ALGORITHMS_ARCHIVE_ROPE_TREE_H_

#include "rope_node.cc"

#include <utility>
#include <string>
#include <list>
#include <algorithm>

namespace algorithms_archive {
namespace tree {
class RopeString {
 public:
  RopeString() : root{nullptr} {
  }

  RopeString(const RopeString &rhs) {
    root = Clone(rhs.root);
  }

  RopeString(const RopeString &&rhs) {
    root = Move(std::move(rhs.root));
  }

  ~RopeString() {
    Empty(root);
  }

  /**
   * 1-based index
   * @param uint64_t index
   * @return char
   */
  char Index(const uint64_t index) {
    return Index(index, root);
  }

  void Insert(const uint64_t index, const std::string text) {
    RopeNode *left;
    RopeNode *right;
    Split(index, root, left, right);
    RopeNode *new_node = new RopeNode{text, text.length(), text.length()};
    root = Merge(Merge(left, new_node), right);
  }

  void Append(std::string text) {
    RopeNode *new_node = new RopeNode{text, text.length(), text.length()};
    root = Merge(root, new_node);
  }

  void Prepend(std::string text) {
    RopeNode *new_node = new RopeNode{text, text.length(), text.length()};
    root = Merge(new_node, root);
  }

  void Delete(const uint64_t start, const uint64_t end) {
    RopeNode *left;
    RopeNode *middle;
    RopeNode *right;
    Split(start, root, left, middle);
    Split(end, middle, middle, right);
    Empty(middle);
    root = Merge(left, right);
  }

  void Empty() {
    Empty(root);
  }

  std::string ToString() {
    std::string result;
    ToString(result, root);
    return result;
  }

  void Concat(const RopeString &tree) {
    root = Merge(root, tree.root);
  }

 private:
  enum BALANCE_TYPE { LEFT_HEAVY, BALANCE, RIGHT_HEAVY };
  RopeNode *root;

  RopeNode *Clone(const RopeNode *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new RopeNode{
          node->data,
          node->weight,
          node->length,
          Clone(node->left),
          Clone(node->right),
          node->height
      };
    }
  }

  RopeNode *Move(const RopeNode *&&node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new RopeNode{
          std::move(node->data),
          std::move(node->weight),
          std::move(node->length),
          Clone(node->left),
          Clone(node->right),
          node->height
      };
    }
  }

  char Index(const uint64_t &index, RopeNode *node) {
    if (node == nullptr) {
      return '\0';
    }
    if (index > node->weight) {
      return Index(index - node->weight, node->right);
    } else {
      if (node->left != nullptr) {
        return Index(index, node->left);
      } else {
        return node->data[index - 1];
      }
    }
  }

  RopeNode *RotateLeft(RopeNode *node) {
    RopeNode *subtree_root = node->right;
    node->right = subtree_root->left;
    subtree_root->left = node;
    node->height = GetHeight(node);
    node->length = GetLength(node);
    subtree_root->height = GetHeight(subtree_root);
    subtree_root->length = GetLength(subtree_root);
    subtree_root->weight = node->length;
    return subtree_root;
  }

  RopeNode *RotateRight(RopeNode *node) {
    RopeNode *subtree_root = node->left;
    node->left = subtree_root->right;
    subtree_root->right = node;
    node->height = GetHeight(node);
    node->length = GetLength(node);
    node->weight = Weight(node->left);
    subtree_root->height = GetHeight(subtree_root);
    subtree_root->length = GetLength(subtree_root);
    return subtree_root;
  }

  BALANCE_TYPE BalanceFactor(RopeNode *node) {
    if (node == nullptr) {
      return BALANCE;
    }
    if (Height(node->right) - Height(node->left) > 1) {
      return RIGHT_HEAVY;
    } else if (Height(node->right) - Height(node->left) < -1) {
      return LEFT_HEAVY;
    } else {
      return BALANCE;
    }

  }

  uint64_t Height(RopeNode *node) {
    return (node != nullptr) ? node->height : 0;
  }

  uint64_t Length(RopeNode *node) {
    return (node != nullptr) ? node->length : 0;
  }

  uint64_t Weight(RopeNode *node) {
    return (node != nullptr) ? node->weight : 0;
  }

  uint64_t GetHeight(RopeNode *node) {
    return 1 + std::max(Height(node->left), Height(node->right));
  }

  uint64_t GetLength(RopeNode *node) {
    return Length(node->left) + Length(node->right);
  }

  RopeNode *Rebalance(RopeNode *node) {
    if (node == nullptr) {
      return nullptr;
    }
    node->height = GetHeight(node);
    BALANCE_TYPE balance = BalanceFactor(node);
    if (balance == LEFT_HEAVY) {
      if (Height(node->left->left) < Height(node->left->right)) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
      } else {
        return RotateRight(node);
      }
    } else if (balance == RIGHT_HEAVY) {
      if (Height(node->right->left) > Height(node->right->right)) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
      } else {
        return RotateLeft(node);
      }
    } else {
      return node;
    }
  }

  RopeNode *Merge(RopeNode *left, RopeNode *right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;
    RopeNode *new_root = new RopeNode{
        "",
        left->weight,
        left->length + right->length,
        left,
        right,
        (left->height > right->height) ? left->height : right->height
    };
    return Rebalance(new_root);
  }

  void Split(const uint64_t index, RopeNode *&node, RopeNode *&left, RopeNode *&right) {
    if (index > node->weight) {
      left = Merge(left, node->left);
      if (node->right != nullptr) {
        // Traverse to right sub-tree
        Split(index - node->weight, node->right, left, right);
        delete node;
      }
    } else {
      right = Merge(node->right, right);
      if (node->left != nullptr) {
        // Traverse to left sub-tree
        Split(index, node->left, left, right);
        delete node;
      } else {
        /**
         * If the index is the last position of string then merge it to left tree
         * If the index is the first position of string then merge it to right tree
         * Otherwise split to 2 nodes then merge them to left and right trees.
         */
        if (index == node->weight) {
          left = Merge(left, node);
        } else if (index == 1) {
          right = Merge(node, right);
        } else {
          RopeNode *new_left = new RopeNode{node->data.substr(0, index), index, index};
          uint64_t right_len = node->data.length() - index;
          RopeNode *new_right = new RopeNode{node->data.substr(index), right_len, right_len};
          left = Merge(left, new_left);
          right = Merge(new_right, right);
          delete node;
        }
      }
    }
  }

  void ToString(std::string &str, RopeNode *node) {
    if (node == nullptr) {
      return;
    }
    ToString(str, node->left);
    if (node->data != "") {
      str += node->data;
    }
    ToString(str, node->right);
  }

  void Empty(RopeNode *&node) {
    if (node == nullptr) {
      return;
    }
    Empty(node->left);
    Empty(node->right);
    delete node;
    node = nullptr;
  }
};
} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_ROPE_TREE_H_

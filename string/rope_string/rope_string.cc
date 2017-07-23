#include "rope_string.h"

namespace algorithms_archive {
namespace string {
RopeString::RopeString() : root{nullptr} {
}

RopeString::RopeString(const RopeString &rhs) {
  root = Clone(rhs.root);
}

RopeString::RopeString(const RopeString &&rhs) {
  root = Move(std::move(rhs.root));
}

RopeString::~RopeString() {
  Empty(root);
}

char RopeString::Index(const uint64_t index) {
  return Index(index, root);
}

void RopeString::Insert(const uint64_t index, const std::string text) {
  RopeNode *left = nullptr;
  RopeNode *right = nullptr;
  Split(index, root, left, right);
  RopeNode *new_node = new RopeNode{text, text.length(), text.length()};
  root = Merge(Merge(left, new_node), right);
}

void RopeString::Append(std::string text) {
  RopeNode *new_node = new RopeNode{text, text.length(), text.length()};
  root = Merge(root, new_node);
}

void RopeString::Prepend(std::string text) {
  RopeNode *new_node = new RopeNode{text, text.length(), text.length()};
  root = Merge(new_node, root);
}

void RopeString::Delete(const uint64_t start, const uint64_t length) {
  RopeNode *left = nullptr;
  RopeNode *middle = nullptr;
  RopeNode *tmp_right = nullptr;
  RopeNode *right = nullptr;
  Split(start, root, left, tmp_right);
  Split(length + 1, tmp_right, middle, right);
  Empty(middle);
  root = Merge(left, right);
}

void RopeString::Empty() {
  Empty(root);
}

std::string RopeString::ToString() {
  std::string result;
  ToString(result, root);
  return result;
}

void RopeString::Concat(RopeString &tree) {
  root = Merge(root, tree.root);
  tree.root = nullptr;
}

RopeNode *RopeString::Clone(const RopeNode *node) {
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

RopeNode *RopeString::Move(const RopeNode *&&node) {
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

char RopeString::Index(const uint64_t &index, RopeNode *node) {
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

RopeNode *RopeString::RotateLeft(RopeNode *node) {
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

RopeNode *RopeString::RotateRight(RopeNode *node) {
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

RopeString::BALANCE_TYPE RopeString::BalanceFactor(RopeNode *node) {
  if (node == nullptr) {
    return BALANCE;
  }
  int balance_constant = Height(node->right) - Height(node->left);
  if (balance_constant > 1) {
    return RIGHT_HEAVY;
  } else if (balance_constant < -1) {
    return LEFT_HEAVY;
  } else {
    return BALANCE;
  }
}

uint64_t RopeString::Height(RopeNode *node) {
  return (node != nullptr) ? node->height : 0;
}

uint64_t RopeString::Length(RopeNode *node) {
  return (node != nullptr) ? node->length : 0;
}

uint64_t RopeString::Weight(RopeNode *node) {
  return (node != nullptr) ? node->weight : 0;
}

uint64_t RopeString::GetHeight(RopeNode *node) {
  return 1 + std::max(Height(node->left), Height(node->right));
}

uint64_t RopeString::GetLength(RopeNode *node) {
  return Length(node->left) + Length(node->right);
}

RopeNode *RopeString::Rebalance(RopeNode *node) {
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

RopeNode *RopeString::Merge(RopeNode *left, RopeNode *right) {
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

void RopeString::Split(const uint64_t index, RopeNode *&node, RopeNode *&left, RopeNode *&right) {
  if (node == nullptr) {
    return;
  }
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
       * Split into 2 nodes then merge them to left and right trees.
       */
      uint64_t left_len = index - 1;
      uint64_t right_len = node->data.length() - left_len;
      RopeNode *new_left = new RopeNode{node->data.substr(0, left_len), left_len, left_len};
      RopeNode *new_right = new RopeNode{node->data.substr(left_len), right_len, right_len};
      left = Merge(left, new_left);
      right = Merge(new_right, right);
      delete node;
    }
  }
}

void RopeString::ToString(std::string &str, RopeNode *node) {
  if (node == nullptr) {
    return;
  }
  ToString(str, node->left);
  if (node->data != "") {
    str += node->data;
  }
  ToString(str, node->right);
}

void RopeString::Empty(RopeNode *&node) {
  if (node == nullptr) {
    return;
  }
  Empty(node->left);
  Empty(node->right);
  delete node;
  node = nullptr;
}
} // namespace string
} // namespace algorithms_archive
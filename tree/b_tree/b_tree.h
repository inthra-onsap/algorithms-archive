#ifndef ALGORITHMS_ARCHIVE_B_TREE_H_
#define ALGORITHMS_ARCHIVE_B_TREE_H_

#include "b_tree_node.cc"

#include <string>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class BTree {
 public:

  BTree(int min_degree_) : root{nullptr}, min_degree{min_degree_} {
  }

  BTree(BTree &rhs) {
  }

  BTree(BTree &&rhs) {
  }

  ~BTree() {
    Clear(root);
  }

  void Insert(Comparable &value) {
    Insert(value, root);
  }

  void Insert(Comparable &&value) {

  }

  bool IsEmpty() {
    return root == nullptr;
  }

  bool Contain(const Comparable &value) {
    return Contain(value, root);
  }

  void Clear() {
    Clear(root);
  }

  std::string ToString() {
    std::string result = "";
    TraverseInorder(result, root);
    return result;
  }

 private:
  BTreeNode<Comparable> *root;
  int min_degree;

  bool Contain(const Comparable &value, BTreeNode<Comparable> *node) {
    if (node == nullptr) {
      return false;
    }
    int i = 0;
    while (value > node->keys[i] && i < node->num_of_keys) {
      ++i;
    }
    if (node->keys[i] == value) {
      return true;
    } else if (node->is_leaf) {
      return false;
    } else {
      Contain(value, node->p_children[i]);
    }
  }

  void Clear(BTreeNode<Comparable> *&node) {
    if (node == nullptr) {
      return;
    }
    if (!node->is_leaf) {
      for (int i = 0; i <= node->num_of_keys; ++i) {
        Clear(node->p_children[i]);
      }
    }
    delete node;
    node = nullptr;
  }

  void TraverseInorder(std::string &result, BTreeNode<Comparable> *node) {
    if (node == nullptr) {
      return;
    }
    for (int i = 0; i <= node->num_of_keys; ++i) {
      TraverseInorder(result, node->p_children[i]);
      if (i < node->num_of_keys) {
        result += std::to_string(node->keys[i]);
      }
    }
  }

  void Insert(Comparable &value, BTreeNode<Comparable> *&node) {
    if (node == nullptr) {
      node = new BTreeNode<Comparable>{value, min_degree, true};
      return;
    }

    if (node->IsFull()) {
      BTreeNode<Comparable> *new_root = new BTreeNode<Comparable>(min_degree, false);
      new_root->AddChildAt(0, node);
      new_root->SplitChildAt(0);
      Insert(value, new_root);
      node = new_root;
    } else {
      if (node->IsLeaf()) {
        node->AddKey(value);
      } else {
        int child_index = node->NextIndex(value);
        BTreeNode<Comparable> *next_child = node->GetChildAt(child_index);
        if (next_child->IsFull()) {
          node->SplitChildAt(child_index);
          if (value > node->GetKeyAt(child_index)) {
            child_index += 1;
          }
          next_child = node->GetChildAt(child_index);
        }
        Insert(value, next_child);
      }
    }
  }
};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_B_TREE_H_

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
    min_degree = rhs.min_degree;
    root = Clone(rhs.root);
  }

  ~BTree() {
    Clear(root);
  }

  void Insert(Comparable &value) {
    Insert(value, root);
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  bool Contain(const Comparable &value) {
    return Contain(value, root);
  }

  void Remove(const Comparable &value) {
    Remove(value, root);
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

  BTreeNode<Comparable> *Clone(BTreeNode<Comparable> *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      BTreeNode<Comparable> *new_node = new BTreeNode<Comparable>{node->min_degree, node->is_leaf};
      new_node->CloneKeys(node);
      for (int i = 0; i <= node->num_of_keys; ++i) {
        new_node->AddChildAt(i, Clone(node->GetChildAt(i)));
      }
      return new_node;
    }
  }

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

  void Remove(const Comparable &value, BTreeNode<Comparable> *&node) {
    if (node == nullptr) {
      return;
    }
    int key_index = node->HasKey(value);
    if (node->IsLeaf()) {
      if (key_index != -1) {
        node->RemoveAt(key_index);
      }
    } else if (!node->IsLeaf() && key_index != -1) {
      if (!node->p_children[key_index]->IsMinimumNode()) {
        // Case 1) Find predecessor from child node
        Comparable predecessor = node->GetPredecessor(key_index);
        node->UpdateKeyAt(key_index, predecessor);
        Remove(predecessor, node->GetRefChildAt(key_index));
      } else if (!node->p_children[key_index + 1]->IsMinimumNode()) {
        // Case 2) Find successor from next-child node
        Comparable successor = node->GetSuccessor(key_index + 1);
        node->UpdateKeyAt(key_index, successor);
        Remove(successor, node->GetRefChildAt(key_index + 1));
      } else {
        // Case 3) Merge child and next-child together
        node->MergeChildAt(key_index);
        Remove(value, node->GetRefChildAt(key_index));
      }
    } else {
      int next_pindex = node->NextIndex(value);
      BTreeNode<Comparable> *next_child = node->GetChildAt(next_pindex);
      bool merge_from_left = (next_pindex == 0) ? true : false;
      int prev_num_keys = node->num_of_keys;
      if (next_child->IsMinimumNode()) {
        /**
        * MakeChildAtNotMinimum()
        * Case 1) Rotate child value from sibling left or right
        * Case 2) Merge child and left/right child together
        */
        node->MakeChildAtNotMinimum(next_pindex);
        if (!merge_from_left && prev_num_keys > node->num_of_keys) {
          next_child = node->GetRefChildAt(next_pindex - 1);
        }
      }
      Remove(value, next_child);
    }
  }
};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_B_TREE_H_

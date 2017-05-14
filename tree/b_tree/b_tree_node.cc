#include <utility>
#include<algorithm>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct BTreeNode {
  Comparable *keys;
  bool is_leaf;
  int num_of_keys;
  int min_degree;
  int key_size;
  BTreeNode<Comparable> **p_children;

  BTreeNode(int min_degree_, bool is_leaf_)
      : min_degree{min_degree_}, is_leaf{is_leaf_}, num_of_keys{0} {
    key_size = 2 * min_degree - 1;
    keys = new Comparable[key_size];
    p_children = new BTreeNode<Comparable> *[2 * min_degree_]{nullptr};
  }

  BTreeNode(Comparable value, int min_degree_, bool is_leaf_)
      : min_degree{min_degree_}, is_leaf{is_leaf_}, num_of_keys{1} {
    key_size = 2 * min_degree - 1;
    keys = new Comparable[key_size];
    keys[0] = value;
    p_children = new BTreeNode<Comparable> *[2 * min_degree_]{nullptr};
  }

  void CloneKeys(BTreeNode<Comparable> *node) {
    for (int i = 0; i < node->num_of_keys; ++i) {
      keys[i] = node->keys[i];
    }
    num_of_keys = node->num_of_keys;
    key_size = node->key_size;
  }

  bool IsFull() {
    return (num_of_keys == key_size);
  }

  bool IsLeaf() {
    return is_leaf;
  }

  bool IsMinimumNode() {
    return (num_of_keys < min_degree);
  }

  int HasKey(const Comparable &value) {
    int i = num_of_keys;
    while ((i - 1) >= 0 && value < keys[i - 1]) {
      --i;
    }
    return (keys[i] == value) ? i : -1;
  }

  void AddKey(Comparable &value) {
    int i = num_of_keys;
    while ((i - 1) >= 0 && value < keys[i - 1]) {
      std::swap(keys[i - 1], keys[i]);
      --i;
    }
    keys[i] = value;
    ++num_of_keys;
  }

  void UpdateKeyAt(const int &index, Comparable &value) {
    keys[index] = value;
  }

  Comparable GetKeyAt(const Comparable &index) {
    return keys[index];
  }

  void AddChildAt(const int &p_index, BTreeNode<Comparable> *node) {
    p_children[p_index] = node;
  }

  BTreeNode<Comparable> *GetChildAt(const int &p_index) {
    return p_children[p_index];
  }

  int NextIndex(const Comparable &value) {
    int i = num_of_keys;
    while ((i - 1) >= 0 && value < keys[i - 1]) {
      --i;
    }
    return i;
  }

  BTreeNode<Comparable> *&GetRefChildAt(const int &index) {
    return p_children[index];
  }

  void SplitChildAt(int index) {
    BTreeNode<Comparable> *child = p_children[index];
    BTreeNode<Comparable> *new_sibling = new BTreeNode<Comparable>{child->min_degree, child->is_leaf};

    // Move half of keys and pointers to new sibling
    for (int i = 0; i < child->min_degree; ++i) {
      if (i < (child->min_degree - 1)) {
        new_sibling->AddKey(child[child->min_degree + i]);
        child->num_of_keys -= 1;
      }
      new_sibling->p_children[i] = child->p_children[child->min_degree + i];
      child->p_children[child->min_degree + i] = nullptr;
    }

    // Adjust and move the splited key and pointer to parent
    for (int i = num_of_keys; i > index; --i) {
      p_children[i + 1] = p_children[i];
    }
    AddChildAt(index + 1, new_sibling);
    AddKey(child->keys[min_degree - 1]);
    child->num_of_keys -= 1;
  }

  void MergeChildAt(int p_index) {
    BTreeNode<Comparable> *child = p_children[p_index];
    BTreeNode<Comparable> *sibling = p_children[p_index + 1];
    // Move the merged key of child and sibling downward
    child->keys[min_degree - 1] = keys[p_index];
    for (int i = (p_index + 1); i < num_of_keys; ++i) {
      keys[i - 1] = keys[i];
    }
    for (int i = (p_index + 2); i <= num_of_keys; ++i) {
      p_children[i - 1] = p_children[i];
    }
    num_of_keys -= 1;
    // Move sibling data to node
    for (int i = 0; i < sibling->num_of_keys; ++i) {
      child->keys[i + min_degree] = sibling->keys[i];
      ++child->num_of_keys;
    }
    if (!sibling->IsLeaf()) {
      for (int i = 0; i <= sibling->num_of_keys; ++i) {
        child->p_children[i + min_degree] = sibling->p_children[i];
      }
    }
    delete sibling;
  }

  void BorrowFromPrev(int p_index) {
    BTreeNode<Comparable> *child = p_children[p_index];
    BTreeNode<Comparable> *left_sibling = p_children[p_index - 1];
    // Move child keys & pointers one position ahead
    for (int i = child->num_of_keys; i >= 0; --i) {
      child->keys[i] = child->keys[i - 1];
    }
    if (!child->IsLeaf()) {
      for (int i = child->num_of_keys; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
      }
    }
    child->num_of_keys += 1;
    // Move parent key & left sibling pointer to child
    child->keys[0] = keys[p_index - 1];
    if (!child->IsLeaf()) {
      child->p_children[0] = left_sibling->p_children[left_sibling->num_of_keys];
    }
    keys[p_index - 1] = left_sibling->keys[left_sibling->num_of_keys - 1];
    left_sibling->num_of_keys -= 1;
  }

  void BorrowFromNext(int p_index) {
    BTreeNode<Comparable> *child = p_children[p_index];
    BTreeNode<Comparable> *right_sibling = p_children[p_index + 1];

    // Move parent key & right sibling pointer to child
    child->keys[child->num_of_keys] = keys[p_index];
    if (!child->IsLeaf()) {
      child->p_children[child->num_of_keys + 1] = right_sibling->p_children[0];
    }
    child->num_of_keys += 1;
    // Move right sibling keys & pointers one position backward
    keys[p_index] = right_sibling->keys[0];
    for (int i = 0; i < right_sibling->num_of_keys; ++i) {
      right_sibling->keys[i] = right_sibling->keys[i + 1];
    }
    if (!right_sibling->IsLeaf()) {
      for (int i = 0; i <= right_sibling->num_of_keys; ++i) {
        right_sibling->p_children[i] = right_sibling->p_children[i + 1];
      }
    }
    right_sibling->num_of_keys -= 1;
  }

  void MakeChildAtNotMinimum(int p_index) {
    if (p_index != 0 && !p_children[p_index - 1]->IsMinimumNode()) {
      BorrowFromPrev(p_index);
    } else if (p_index != num_of_keys && !p_children[p_index + 1]->IsMinimumNode()) {
      BorrowFromNext(p_index);
    } else {
      if (p_index != 0) {
        MergeChildAt(p_index - 1);
      } else {
        MergeChildAt(p_index);
      }
    }
  }

  Comparable GetPredecessor(const int &p_index) {
    BTreeNode<Comparable> *node = p_children[p_index];
    while (!node->IsLeaf()) {
      node = node->p_children[node->num_of_keys];
    }
    return node->keys[node->num_of_keys - 1];
  }

  Comparable GetSuccessor(const int &p_index) {
    BTreeNode<Comparable> *node = p_children[p_index];
    while (!node->IsLeaf()) {
      node = node->p_children[0];
    }
    return node->keys[0];
  }

  void RemoveAt(const int &index) {
    for (int i = index; i < num_of_keys; ++i) {
      keys[i] = keys[i + 1];
    }
    num_of_keys -= 1;
  }
};
} // namespace tree
} // namespace algorithms_archive
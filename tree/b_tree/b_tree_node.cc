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
    p_children = new BTreeNode *[2 * min_degree_]{nullptr};
  }

  BTreeNode(Comparable value, int min_degree_, bool is_leaf_)
      : min_degree{min_degree_}, is_leaf{is_leaf_}, num_of_keys{1} {
    key_size = 2 * min_degree - 1;
    keys = new Comparable[key_size];
    keys[0] = value;
    p_children = new BTreeNode *[2 * min_degree_]{nullptr};
  }

  BTreeNode(int &&min_degree_, bool &&is_leaf_)
      : min_degree{std::move(min_degree_)}, is_leaf{std::move(is_leaf_)}, num_of_keys{0} {
    key_size = 2 * min_degree - 1;
    keys = new Comparable[key_size];
    p_children = new BTreeNode *[2 * min_degree_]{nullptr};
  }

  BTreeNode(Comparable &&value, int &&min_degree_, bool &&is_leaf_)
      : min_degree{std::move(min_degree_)}, is_leaf{std::move(is_leaf_)}, num_of_keys{1} {
    key_size = 2 * min_degree - 1;
    keys = new Comparable[key_size];
    keys[0] = std::move(value);
    p_children = new BTreeNode *[2 * min_degree_]{nullptr};
  }

  bool IsFull() {
    return (num_of_keys == key_size);
  }

  bool IsLeaf() {
    return is_leaf;
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

  Comparable GetKeyAt(const Comparable &index) {
    return keys[index];
  }

  void AddChildAt(const int &index, BTreeNode<Comparable> *node) {
    p_children[index] = node;
  }

  BTreeNode<Comparable> *GetChildAt(const int &index) {
    return p_children[index];
  }

  int NextIndex(const Comparable &value) {
    int i = num_of_keys;
    while ((i - 1) >= 0 && value < keys[i - 1]) {
      --i;
    }
    return i;
  }

  void *SplitChildAt(int index) {
    BTreeNode<Comparable> *child = p_children[index];
    BTreeNode<Comparable> *new_sibling = new BTreeNode{child->min_degree, child->is_leaf};

    // Move half of keys and pointers to new sibling
    for (int i = 0; i < child->min_degree; ++i) {
      if (i < (child->min_degree - 1)) {
        new_sibling->AddKey(child[child->min_degree + i]);
        child->num_of_keys -= 1;
      }
      new_sibling->p_children[i] = child->p_children[child->min_degree + i];
      child->p_children[child->min_degree + i] = nullptr;
    }

    // Move the splited key and pointer to parent
    for (int i = num_of_keys; i > index; --i) {
      p_children[i + 1] = p_children[i];
    }
    AddChildAt(index + 1, new_sibling);
    AddKey(child->keys[min_degree - 1]);
    child->num_of_keys -= 1;
  }
};
} // namespace tree
} // namespace algorithms_archive
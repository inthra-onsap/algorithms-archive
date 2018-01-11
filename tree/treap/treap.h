#ifndef ALGORITHMS_ARCHIVE_TREAP_H_
#define ALGORITHMS_ARCHIVE_TREAP_H_

#include "treap_node.cc"

#include <utility>
#include <random>
#include <climits>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class Treap {
 public:
  Treap() : root{nullptr}, generator(random_dev()) {
  }

  Treap(const Treap<Comparable> &rhs) {
    root = Clone(rhs.root);
  }

  Treap(const Treap<Comparable> &&rhs) {
    root = Move(std::move(rhs.root));
  }

  ~Treap() {
    root = Clear(root);
  }

  void Insert(const Comparable &value) {
    root = Insert(value, root);
  }

  void Clear() {
    root = Clear(root);
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  bool Contains(const Comparable &value) {
    return (Find(value, root) != nullptr);
  }

  const TreapNode<Comparable> *Find(const Comparable &value) {
    return Find(value, root);
  }

  void Remove(const Comparable &value) {
    root = Remove(value, root);
  }

 private:
  TreapNode<Comparable> *root;
  std::random_device random_dev;
  std::mt19937 generator;
  std::uniform_int_distribution<int> distributor;

  int RandomInt() {
    return distributor(generator);
  }

  TreapNode<Comparable> *Clone(TreapNode<Comparable> *node) {
    if (node == nullptr) return nullptr;
    return new TreapNode<Comparable>{node->data, node->priority, Clone(node->left), Clone(node->right)};
  }

  TreapNode<Comparable> *Move(TreapNode<Comparable> *&&node) {
    if (node == nullptr) return nullptr;
    return new TreapNode<Comparable>{std::move(node->data),
                                     std::move(node->priority),
                                     Move(std::move(node->left)),
                                     Move(std::move(node->right))};
  }

  TreapNode<Comparable> *Clear(TreapNode<Comparable> *node) {
    if (node != nullptr) {
      node->left = Clear(node->left);
      node->right = Clear(node->right);
      delete node;
    }
    return nullptr;
  }

  TreapNode<Comparable> *RotateRight(TreapNode<Comparable> *node) {
    TreapNode<Comparable> *root = node->left;
    node->left = root->right;
    root->right = node;
    return root;
  }

  TreapNode<Comparable> *RotateLeft(TreapNode<Comparable> *node) {
    TreapNode<Comparable> *root = node->right;
    node->right = root->left;
    root->left = node;
    return root;
  }

  TreapNode<Comparable> *Insert(const Comparable &value, TreapNode<Comparable> *node) {
    if (node == nullptr) {
      return new TreapNode<Comparable>{value, RandomInt(), nullptr, nullptr};
    }

    if (value < node->data) {
      node->left = Insert(value, node->left);
      if (node->left->priority < node->priority) {
        return RotateRight(node);
      }
    } else if (value > node->data) {
      node->right = Insert(value, node->right);
      if (node->right->priority < node->priority) {
        return RotateLeft(node);
      }
    }

    return node;
  }

  TreapNode<Comparable> *Remove(const Comparable &value, TreapNode<Comparable> *node) {
    if (node == nullptr) return nullptr;
    if (value < node->data) {
      node->left = Remove(value, node->left);
    } else if (value > node->data) {
      node->right = Remove(value, node->right);
    } else {
      if (node->left != nullptr && node->right != nullptr) {
        if (node->left->priority < node->right->priority) {
          node = RotateRight(node);
          node->right = Remove(value, node->right);
        } else {
          node = RotateLeft(node);
          node->left = Remove(value, node->left);
        }
      } else {
        TreapNode<Comparable> *delete_node = node;
        node = (node->left != nullptr) ? node->left : node->right;
        delete delete_node;
      }
    }
    return node;
  }

  TreapNode<Comparable> *Find(const Comparable &value, TreapNode<Comparable> *node) {
    if (node == nullptr) return nullptr;
    if (value < node->data) {
      return Find(value, node->left);
    } else if (value > node->data) {
      return Find(value, node->right);
    } else {
      return node;
    }
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_TREAP_H_

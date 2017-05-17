#ifndef ALGORITHMS_ARCHIVE_LEFTISTHEAP_H_
#define ALGORITHMS_ARCHIVE_LEFTISTHEAP_H_

#include "leftist_heap_node.cc"

#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class LeftistHeap {
 public:
  LeftistHeap() : root{nullptr} {}

  LeftistHeap(const LeftistHeap &rhs) {
    root = Clone(rhs.root);
  }

  LeftistHeap(const LeftistHeap &&rhs) {
    root = Move(std::move(rhs.root));
  }

  ~LeftistHeap() {}

  void Insert(const Comparable &value) {
    root = Merge(root, new LeftistHeapNode<Comparable>{value, nullptr, nullptr});
  }

  void Insert(const Comparable &&value) {
    root = Merge(root, new LeftistHeapNode<Comparable>{std::move(value), nullptr, nullptr});
  }

  bool IsEmpty() {
    return (root == nullptr);
  }

  const Comparable &FindMin() {
    if (root == nullptr) {
      return NULL;
    }
    return root->data;
  }

  void DeleteMin() {
    LeftistHeapNode<Comparable> *old_root = root;
    root = Merge(root->left, root->right);
    delete old_root;
  }

  void Empty() {
    Empty(root);
  }

  void Merge(LeftistHeap<Comparable> &rhs) {
    if (this == &rhs) {
      return;
    }
    root = Merge(root, rhs.root);
    rhs.root = nullptr;
  }

 private:
  LeftistHeapNode<Comparable> *root;

  LeftistHeapNode<Comparable> *Clone(const LeftistHeapNode<Comparable> *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new LeftistHeapNode<Comparable>{node->data, Clone(node->left), Clone(node->right), node->npl};
    }
  }

  LeftistHeapNode<Comparable> *Move(const LeftistHeapNode<Comparable> *&&node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new LeftistHeapNode<Comparable>{std::move(node->data),
                                             Move(std::move(node->left)),
                                             Clone(std::move(node->right)),
                                             node->npl};
    }
  }

  void Empty(LeftistHeapNode<Comparable> *&node) {
    if (node == nullptr) {
      return;
    }
    Empty(node->left);
    Empty(node->right);
    delete node;
    node = nullptr;
  }

  LeftistHeapNode<Comparable> *Merge(LeftistHeapNode<Comparable> *heap1, LeftistHeapNode<Comparable> *heap2) {
    if (heap1 == nullptr) {
      return heap2;
    } else if (heap2 == nullptr) {
      return heap1;
    } else {
      if (heap1->data <= heap2->data) {
        heap1->right = Merge(heap1->right, heap2);
        if (heap1->left == nullptr) {
          heap1->left = heap1->right;
          heap1->right = nullptr;
          heap1->npl = 0;
        } else if (heap1->left->npl < heap1->right->npl) {
          SwapChildren(heap1);
          heap1->npl = 1 + heap1->right->npl;
        }
        return heap1;
      } else {
        heap2->right = Merge(heap1, heap2->right);
        if (heap2->left == nullptr) {
          heap2->left = heap2->right;
          heap2->right = nullptr;
          heap2->npl = 0;
        } else if (heap2->left->npl < heap2->right->npl) {
          SwapChildren(heap2);
          heap2->npl = 1 + heap2->right->npl;
        }
        return heap2;
      }
    }
  }

  void SwapChildren(LeftistHeapNode<Comparable> *node) {
    LeftistHeapNode<Comparable> *tmp_right = node->right;
    node->right = node->left;
    node->left = tmp_right;
  }

};
} // namespace tree
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_LEFTISTHEAP_H_

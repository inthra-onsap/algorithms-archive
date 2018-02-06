#ifndef ALGORITHMS_ARCHIVE_FIBONACCI_HEAP_H_
#define ALGORITHMS_ARCHIVE_FIBONACCI_HEAP_H_

#include "fibonacci_heap_node.cc"

#include <vector>
#include <cmath>
#include <string>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class FibonacciHeap {
 public:
  FibonacciHeap() : size{0}, root_list{nullptr}, minimum_heap{nullptr} {}

  ~FibonacciHeap() {
    Clear();
  }

  void Insert(Comparable key) {
    FibonacciHeapNode<Comparable> *new_node = new FibonacciHeapNode<Comparable>(key);

    if (root_list == nullptr) {
      root_list = new_node;
      minimum_heap = new_node;
    } else {
      FibonacciHeapNode<Comparable> *prev_min_left = minimum_heap->left;
      new_node->right = minimum_heap;
      new_node->left = prev_min_left;
      prev_min_left->right = new_node;
      minimum_heap->left = new_node;

      if (new_node->key < minimum_heap->key) {
        minimum_heap = new_node;
      }
    }
    ++size;
  }

  Comparable ExtractMin() {
    Comparable key = GetMinimum();

    if (minimum_heap != nullptr) {
      FibonacciHeapNode<Comparable> *tmp_node = minimum_heap;
      FibonacciHeapNode<Comparable> *child = minimum_heap->child;

      if (child != nullptr) {
        while (child->parent != nullptr) {
          child->parent = nullptr;
          child = child->right;
        }

        // Move children to root_list
        FibonacciHeapNode<Comparable> *left_heap = root_list->left;
        FibonacciHeapNode<Comparable> *child_left_heap = child->left;
        root_list->left = child_left_heap;
        child_left_heap->right = root_list;
        left_heap->right = child;
        child->left = left_heap;
      }

      // Split the minimum node out of root_list
      minimum_heap->left->right = minimum_heap->right;
      minimum_heap->right->left = minimum_heap->left;

      if (minimum_heap == minimum_heap->right) {
        root_list = nullptr;
        minimum_heap = nullptr;
      } else {
        root_list = minimum_heap = minimum_heap->right;
        Consolidate();
      }

      delete tmp_node;
      size -= 1;
    }
    return key;
  }

  Comparable GetMinimum() {
    return (minimum_heap != nullptr) ? minimum_heap->key : 0;
  }

  void DecreaseKey(FibonacciHeapNode<Comparable> *node, Comparable key) {
    if (key > node->key) {
      throw std::invalid_argument("key must less than " + std::to_string(node->key));
    }

    FibonacciHeapNode<Comparable> *node_parent = node->parent;
    node->key = key;

    if (node_parent != nullptr && node->key < node_parent->key) {
      Cut(node, node_parent);
      CascadingCut(node_parent);
    }

    if (node->key < minimum_heap->key) {
      minimum_heap = node;
    }
  }

  void Delete(FibonacciHeapNode<Comparable> *node) {
    DecreaseKey(node, std::numeric_limits<Comparable>::min());
    ExtractMin();
  }

  FibonacciHeapNode<Comparable> *Find(Comparable key) {
    return Find(root_list, key);
  }

  void Union(FibonacciHeap<Comparable> &rhs) {
    if (root_list != nullptr && rhs.root_list != nullptr) {
      FibonacciHeapNode<Comparable> *next_heap = root_list->right;
      FibonacciHeapNode<Comparable> *rhs_left_heap = rhs.root_list->left;

      root_list->right = rhs.root_list;
      rhs.root_list->left = root_list;
      next_heap->left = rhs_left_heap;
      rhs_left_heap->right = next_heap;
    } else {
      if (rhs.root_list != nullptr) {
        root_list = rhs.root_list;
      }
    }

    if (minimum_heap == nullptr ||
        (rhs.minimum_heap != nullptr && rhs.minimum_heap->key < minimum_heap->key)) {
      minimum_heap = rhs.minimum_heap;
    }

    rhs.root_list = nullptr;
    size += rhs.size;
  }

  bool IsEmpty() {
    return (root_list == nullptr);
  }

  void Empty() {
    Clear();
  }
 private:
  FibonacciHeapNode<Comparable> *root_list;
  FibonacciHeapNode<Comparable> *minimum_heap;
  int size;

  void Clear() {
    while (root_list != nullptr)
      ExtractMin();
  }

  void Consolidate() {
    std::vector<FibonacciHeapNode<Comparable> *> degree_vec(std::ceil(std::log2(size)), nullptr);
    std::vector<FibonacciHeapNode<Comparable> *> tree_vec;
    FibonacciHeapNode<Comparable> *curr_heap = root_list, *tmp_heap;
    int degree;

    tree_vec.reserve(std::ceil(std::log2(size)));
    do {
      curr_heap = curr_heap->right;
      tree_vec.push_back(curr_heap);
    } while (curr_heap != root_list);

    for (int i = 0; i < tree_vec.size(); ++i) {
      curr_heap = tree_vec[i];
      degree = curr_heap->degree;

      while (degree_vec[degree] != nullptr) {
        tmp_heap = degree_vec[degree];
        Link(tmp_heap, curr_heap);
        degree_vec[degree] = nullptr;
        ++degree;
      }

      degree_vec[degree] = curr_heap;
      if (curr_heap->key < minimum_heap->key) {
        root_list = minimum_heap = curr_heap;
      }
    }
  }

  void Link(FibonacciHeapNode<Comparable> *&heap1, FibonacciHeapNode<Comparable> *&heap2) {
    if (heap1->key < heap2->key) {
      std::swap(heap1, heap2);
    }

    FibonacciHeapNode<Comparable> *heap2_child = heap2->child;
    // remove heap1 from root_list
    heap1->left->right = heap1->right;
    heap1->right->left = heap1->left;
    heap1->left = heap1;
    heap1->right = heap1;
    // make heap1 a child of heap2
    heap2->degree += 1;
    heap2->child = heap1;
    heap1->mark = false;
    heap1->parent = heap2;

    if (heap2_child != nullptr) {
      heap1->left = heap2_child->left;
      heap1->right = heap2_child;

      heap2_child->left->right = heap1;
      heap2_child->left = heap1;
    }
  }

  void Cut(FibonacciHeapNode<Comparable> *node, FibonacciHeapNode<Comparable> *parent) {
    parent->degree -= 1;
    if (parent->degree == 0) {
      parent->child = nullptr;
    } else {
      node->left->right = node->right;
      node->right->left = node->left;

      if (parent->child == node) {
        parent->child = node->right;
      }
    }

    // add node to root_list
    node->left = root_list->left;
    node->right = root_list;
    root_list->left->right = node;
    root_list->left = node;

    node->parent = nullptr;
    node->mark = false;
  }

  void CascadingCut(FibonacciHeapNode<Comparable> *node) {
    if (node->parent != nullptr) {
      if (node->mark == false) {
        node->mark = true;
      } else {
        Cut(node, node->parent);
        CascadingCut(node->parent);
      }
    }
  }

  FibonacciHeapNode<Comparable> *Find(FibonacciHeapNode<Comparable> *node, Comparable key) {
    if (node == nullptr) return nullptr;

    FibonacciHeapNode<Comparable> *curr = node, *tmp;
    do {
      curr = curr->right;
      if (curr->key == key) {
        return curr;
      }

      tmp = Find(curr->child, key);
      if (tmp) {
        return tmp;
      }
    } while (node != curr);

    return nullptr;
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_FIBONACCI_HEAP_H_

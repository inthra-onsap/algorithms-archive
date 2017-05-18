#ifndef ALGORITHMS_ARCHIVE_BINOMIAL_HEAP_H_
#define ALGORITHMS_ARCHIVE_BINOMIAL_HEAP_H_

#include "binomial_heap_node.cc"

#include <vector>
#include <utility>
#include <algorithm>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
class BinomialTree {
 public:
  BinomialTree() : number_of_nodes{0} {}

  BinomialTree(const BinomialTree &rhs) {
    tree.resize(rhs.tree.size());
    number_of_nodes = rhs.number_of_nodes;
    for (int i = 0; i < rhs.tree.size(); ++i) {
      tree[i] = Clone(rhs.tree[i]);
    }
  }

  BinomialTree(BinomialTree &&rhs) {
    tree.resize(rhs.tree.size());
    number_of_nodes = std::move(rhs.number_of_nodes);
    for (int i = 0; i < rhs.tree.size(); ++i) {
      tree[i] = Move(std::move(rhs.tree[i]));
    }
  }

  ~BinomialTree() {
    Empty();
  }

  void Insert(const Comparable &value) {
    BinomialTree<Comparable> new_tree;
    new_tree.tree.push_back(new BinomialHeapNode<Comparable>{value});
    new_tree.number_of_nodes = 1;
    Merge(new_tree);
  }

  void Insert(Comparable &&value) {
    BinomialTree<Comparable> new_tree;
    new_tree.tree.emplace_back(new BinomialHeapNode<Comparable>{std::move(value)});
    new_tree.number_of_nodes = 1;
    Merge(new_tree);
  }

  bool IsEmpty() {
    return (number_of_nodes == 0);
  }

  void Empty() {
    for (int i = 0; i < tree.size(); ++i) {
      Empty(tree[i]);
    }
    number_of_nodes = 0;
  }

  const Comparable &FindMin() {
    if (IsEmpty()) {
      return NULL;
    }
    return tree[FindMinIndex()]->data;
  }

  void DeleteMin() {
    if (IsEmpty()) {
      return;
    }
    uint64_t min_index = FindMinIndex();
    BinomialHeapNode<Comparable> *deleted_node = tree[min_index];
    BinomialHeapNode<Comparable> *deleted_child = deleted_node->child;
    delete deleted_node;

    BinomialTree<Comparable> new_tree;
    new_tree.tree.resize(min_index + 1);
    new_tree.number_of_nodes = (1 << min_index) - 1;
    for (int i = (min_index - 1); i >= 0; --i) {
      new_tree.tree[i] = deleted_child;
      deleted_child = deleted_child->next_sibling;
      new_tree.tree[i]->next_sibling = nullptr;
    }
    tree[min_index] = nullptr;
    number_of_nodes -= (new_tree.number_of_nodes + 1);
    Merge(new_tree);
  }

  void Merge(BinomialTree &rhs) {
    if (this == &rhs) {
      return;
    }
    number_of_nodes += rhs.number_of_nodes;
    if (tree.size() <= rhs.tree.size()) {
      uint64_t new_size = std::max(tree.size(), rhs.tree.size()) + 1;
      tree.resize(new_size, nullptr);
    }
    BinomialHeapNode<Comparable> *prev_heap = nullptr;
    for (int i = 0; i < tree.size(); ++i) {
      BinomialHeapNode<Comparable> *heap1 = tree[i];
      BinomialHeapNode<Comparable> *heap2 = (i < rhs.tree.size()) ? rhs.tree[i] : nullptr;
      int case_index = (heap1 == nullptr) ? 0 : 1;
      case_index += (heap2 == nullptr) ? 0 : 2;
      case_index += (prev_heap == nullptr) ? 0 : 4;
      switch (case_index) {
        case 0:
        case 1:break;
        case 2:tree[i] = heap2;
          break;
        case 3:prev_heap = Link(heap1, heap2);
          tree[i] = nullptr;
          break;
        case 4:tree[i] = prev_heap;
          prev_heap = nullptr;
          break;
        case 5:prev_heap = Link(heap1, prev_heap);
          tree[i] = nullptr;
          break;
        case 6:prev_heap = Link(heap2, prev_heap);
          break;
        case 7:tree[i] = prev_heap;
          prev_heap = Link(heap1, heap2);
          break;
      }
    }
    // Clean pointers in rhs tree
    rhs.number_of_nodes = 0;
    for (int i = 0; i < rhs.tree.size(); ++i) {
      rhs.tree[i] = nullptr;
    }
  }

 private:
  std::vector<BinomialHeapNode<Comparable> *> tree;
  uint64_t number_of_nodes;

  BinomialHeapNode<Comparable> *Clone(BinomialHeapNode<Comparable> *node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new BinomialHeapNode<Comparable>{node->data, Clone(node->child), Clone(node->next_sibling)};
    }
  }

  BinomialHeapNode<Comparable> *Move(BinomialHeapNode<Comparable> *&&node) {
    if (node == nullptr) {
      return nullptr;
    } else {
      return new BinomialHeapNode<Comparable>{std::move(node->data),
                                              Move(std::move(node->child)),
                                              Move(std::move(node->next_sibling))};
    }
  }

  uint64_t FindMinIndex() {
    uint64_t min_index = 0;
    while (tree[min_index] == nullptr) {
      ++min_index;
    }
    for (int i = (min_index + 1); i < tree.size(); ++i) {
      if (tree[i] != nullptr && tree[i]->data < tree[min_index]->data) {
        min_index = i;
      }
    }
    return min_index;
  }

  BinomialHeapNode<Comparable> *Link(BinomialHeapNode<Comparable> *heap1, BinomialHeapNode<Comparable> *heap2) {
    if (heap1->data > heap2->data) {
      std::swap(heap1, heap2);
    }
    heap2->next_sibling = heap1->child;
    heap1->child = heap2;
    return heap1;
  }

  void Empty(BinomialHeapNode<Comparable> *&node) {
    if (node == nullptr) {
      return;
    }
    Empty(node->next_sibling);
    Empty(node->child);
    delete node;
    node = nullptr;
  }
};
} // namespace tree
} // namespacee algorithms_archive

#endif //ALGORITHMS_ARCHIVE_BINOMIAL_HEAP_H_

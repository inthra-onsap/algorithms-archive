#ifndef ALGORITHMS_ARCHIVE_Interval_TREAP_H_
#define ALGORITHMS_ARCHIVE_Interval_TREAP_H_

#include "implicit_treap_node.cc"

#include <vector>
#include <random>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class ImplicitTreap {
 public:
  ImplicitTreap() {
    init();
  };

  ImplicitTreap(std::vector<Comparable> keys) {
    init();
    Treapify(keys);
  }

  ~ImplicitTreap(){
    Clear(root);
  }

  void init() {
    root = nullptr;
    generator.seed(random_dev());
  }

  Comparable RangeQuery(int start, int length) {
    ImplicitTreapNode<Comparable> *left;
    ImplicitTreapNode<Comparable> *mid;
    ImplicitTreapNode<Comparable> *right;

    Split(root, left, mid, start);
    Split(mid, mid, right, length);
    Comparable sum = mid->sum;
    Merge(root, left, mid);
    Merge(root, root, right);
    return sum;
  }

  void RangeUpdate(int start, int length, Comparable value) {
    ImplicitTreapNode<Comparable> *left;
    ImplicitTreapNode<Comparable> *mid;
    ImplicitTreapNode<Comparable> *right;

    Split(root, left, mid, start);
    Split(mid, mid, right, length);
    mid->lazy += value;
    Merge(root, left, mid);
    Merge(root, root, right);
  }

  void Append(Comparable value) {
    ++size;
    Insert(root, NewNode(value), size);
  }

  void Prepend(Comparable value) {
    Insert(root, NewNode(value), 0);
    ++size;
  }

  void Erase(int index) {
    if (index < 0 || index >= size) {
      throw std::out_of_range(
          "Error: available range is between 0 to " + std::to_string((size) ? size - 1 : 0) + " (inclusive)");
    }

    Erase(root, index + 1);
  }

  void Set(int index, Comparable value) {
    if (index < 0 || index >= size) {
      throw std::out_of_range(
          "Error: available range is between 1 to " + std::to_string((size) ? size - 1 : 0) + " (inclusive)");
    }

     Update(root, index + 1, value);
  }

  Comparable Get(int index) {
    if (index < 0 || index >= size) {
      throw std::out_of_range(
          "Error: available range is between 1 to " + std::to_string((size) ? size - 1 : 0) + " (inclusive)");
    }

    ImplicitTreapNode<Comparable> *node = Find(root, index + 1);
    return (node) ? node->value : Comparable();
  }

  bool IsEmpty() {
    return root == nullptr;
  }

  std::vector<Comparable> ToVector() {
    std::vector<Comparable> result;
    InorderTraverse(root, result);
    return result;
  }

  int Size() {
    return size;
  }

 private:
  ImplicitTreapNode<Comparable> *root;
  int size = 0;
  std::random_device random_dev;
  std::mt19937 generator;
  std::uniform_int_distribution<int> distributor;


  void Clear(ImplicitTreapNode<Comparable> *&node){
    if(node == nullptr) return;

    Clear(node->left);
    Clear(node->right);
    delete node;
    node = nullptr;
  }

  int NodeSize(ImplicitTreapNode<Comparable> *node) {
    return (node != nullptr) ? node->size : 0;
  }

  int CurrentIndex(ImplicitTreapNode<Comparable> *node) {
    return 1 + NodeSize(node->left);
  }

  int IntRandom() {
    return distributor(generator);
  }

  void UpdateNodeSize(ImplicitTreapNode<Comparable> *node) {
    if (node != nullptr) {
      node->size = 1 + NodeSize(node->left) + NodeSize(node->right);
    }
  }

  Comparable NodeSum(ImplicitTreapNode<Comparable> *node) {
    LazyPropagate(node);
    return (node != nullptr) ? node->sum : 0;
  }

  void UpdateNodeSum(ImplicitTreapNode<Comparable> *node) {
    if (node != nullptr) {
      node->sum = node->value + NodeSum(node->left) + NodeSum(node->right);
    }
  }

  void LazyPropagate(ImplicitTreapNode<Comparable> *node) {
    if (!node || !node->lazy) return;

    node->value += node->lazy;
    node->sum += node->lazy * NodeSize(node);
    if (node->left != nullptr) {
      node->left->lazy += node->lazy;
    }
    if (node->right != nullptr) {
      node->right->lazy += node->lazy;
    }
    node->lazy = 0;
  }

  void Split(ImplicitTreapNode<Comparable> *node,
             ImplicitTreapNode<Comparable> *&left,
             ImplicitTreapNode<Comparable> *&right,
             int index) {
    if (node == nullptr) {
      left = right = nullptr;
      return;
    }

    LazyPropagate(node);
    int curr_index = CurrentIndex(node);

    if (index >= curr_index) {
      Split(node->right, node->right, right, index - curr_index);
      left = node;
    } else {
      Split(node->left, left, node->left, index);
      right = node;
    }

    UpdateNodeSize(node);
    UpdateNodeSum(node);
  }

  void Merge(ImplicitTreapNode<Comparable> *&node,
             ImplicitTreapNode<Comparable> *left,
             ImplicitTreapNode<Comparable> *right) {
    LazyPropagate(left);
    LazyPropagate(right);

    if (!left || !right) {
      node = (left != nullptr) ? left : right;
    } else if (left->priority > right->priority) {
      Merge(left->right, left->right, right);
      node = left;
    } else {
      Merge(right->left, left, right->left);
      node = right;
    }

    UpdateNodeSize(node);
    UpdateNodeSum(node);
  }

  ImplicitTreapNode<Comparable> *NewNode(Comparable value) {
    return new ImplicitTreapNode<Comparable>(value, IntRandom());
  }

  void Treapify(std::vector<Comparable> keys) {
    size = keys.size();
    for (int i = 0; i < keys.size(); ++i)
      Insert(root, NewNode(keys[i]), i);
  }

  void Insert(ImplicitTreapNode<Comparable> *&node, ImplicitTreapNode<Comparable> *new_node, int index) {
    if (node == nullptr) {
      node = new_node;
    } else if (node->priority < new_node->priority) {
      Split(node, new_node->left, new_node->right, index);
      node = new_node;
    } else {
      LazyPropagate(node);
      if (index >= CurrentIndex(node)) {
        Insert(node->right, new_node, index - CurrentIndex(node));
      } else {
        Insert(node->left, new_node, index);
      }
    }

    UpdateNodeSize(node);
    UpdateNodeSum(node);
  }

  void Update(ImplicitTreapNode<Comparable> *&node, int index, Comparable value){
    LazyPropagate(node);
    int curr_index = CurrentIndex(node);

    if (index > curr_index) {
      Update(node->right, index - curr_index, value);
    } else if(index < curr_index){
      Update(node->left, index, value);
    }else {
      node->value = value;
    }

    UpdateNodeSum(node);
  }

  void Erase(ImplicitTreapNode<Comparable> *&node, int index) {
    if (node == nullptr) return;

    LazyPropagate(node);

    if (index > CurrentIndex(node)) {
      Erase(node->right, index - CurrentIndex(node));
    } else if (CurrentIndex(node) > index) {
      Erase(node->left, index);
    } else {
      ImplicitTreapNode<Comparable> *tmp = node;
      Merge(node, node->left, node->right);
      delete tmp;
      --size;
    }

    UpdateNodeSize(node);
    UpdateNodeSum(node);
  }

  ImplicitTreapNode<Comparable> *Find(ImplicitTreapNode<Comparable> *node, int index) {
    if (node == nullptr) {
      return nullptr;
    }

    LazyPropagate(node);

    if (index > CurrentIndex(node)) {
      return Find(node->right, index - CurrentIndex(node));
    } else if (index < CurrentIndex(node)) {
      return Find(node->left, index);
    } else {
      return node;
    }
  }

  void InorderTraverse(ImplicitTreapNode<Comparable> *node, std::vector<Comparable> &result) {
    if (node == nullptr) return;

    LazyPropagate(node);
    InorderTraverse(node->left, result);
    result.push_back(node->value);
    InorderTraverse(node->right, result);
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_Interval_TREAP_H_

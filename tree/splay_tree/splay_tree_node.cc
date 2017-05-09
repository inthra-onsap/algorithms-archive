#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct SplayTreeNode {
  Comparable data;
  SplayTreeNode<Comparable> *left;
  SplayTreeNode<Comparable> *right;
  SplayTreeNode<Comparable> *parent;

  SplayTreeNode(const Comparable &element,
                SplayTreeNode<Comparable> *left_child = nullptr,
                SplayTreeNode<Comparable> *right_child = nullptr,
                SplayTreeNode<Comparable> *parent_node = nullptr)
      : data{element}, left{left_child}, right{right_child}, parent{parent_node} {
  }
  SplayTreeNode(const Comparable &&element,
                SplayTreeNode<Comparable> *&&left_child = nullptr,
                SplayTreeNode<Comparable> *&&right_child = nullptr,
                SplayTreeNode<Comparable> *&&parent_node = nullptr)
      : data{std::move(element)},
        left{std::move(left_child)},
        right{std::move(right_child)},
        parent{std::move(parent_node)} {
  }
};
} // namespace tree
} // namespace algorithms_archive
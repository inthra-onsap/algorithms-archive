#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct SplayTreeNode {
  Comparable data;
  SplayTreeNode<Comparable> *left;
  SplayTreeNode<Comparable> *right;

  SplayTreeNode(const Comparable &element,
                SplayTreeNode<Comparable> *left_child = nullptr,
                SplayTreeNode<Comparable> *right_child = nullptr)
      : data{element}, left{left_child}, right{right_child} {
  }
  SplayTreeNode(const Comparable &&element,
                SplayTreeNode<Comparable> *&&left_child = nullptr,
                SplayTreeNode<Comparable> *&&right_child = nullptr)
      : data{std::move(element)}, left{std::move(left_child)}, right{std::move(right_child)} {
  }
};
} // namespace tree
} // namespace algorithms_archive
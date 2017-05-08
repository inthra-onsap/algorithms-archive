#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct BstNode {
  Comparable data;
  BstNode<Comparable> *left;
  BstNode<Comparable> *right;

  BstNode(const Comparable &element,
          BstNode<Comparable> *left_child = nullptr,
          BstNode<Comparable> *right_child = nullptr)
      : data{element}, left{left_child}, right{right_child} {
  }
  BstNode(Comparable &&element,
          BstNode<Comparable> *&&left_child = nullptr,
          BstNode<Comparable> *&&right_child = nullptr)
      : data{std::move(element)}, left{std::move(left_child)}, right{std::move(right_child)} {
  }
};
} // namespace tree
} // namespace algorithm_archive
#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct AvlNode {
  Comparable data;
  AvlNode<Comparable> *left;
  AvlNode<Comparable> *right;
  int height;

  AvlNode(const Comparable &element,
          AvlNode<Comparable> *left_child = nullptr,
          AvlNode<Comparable> *right_child = nullptr,
          int h = 1)
      : data{element}, left{left_child}, right{right_child}, height{h} {
  }
  AvlNode(const Comparable &&element,
          AvlNode<Comparable> *&&left_child = nullptr,
          AvlNode<Comparable> *&&right_child = nullptr,
          int &&h = 1)
      : data{std::move(element)}, left{std::move(left_child)}, right{std::move(right_child)}, height{std::move(h)} {
  }
};
} // namespace tree
} // namespace algorithm_archive
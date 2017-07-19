#include <utility>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
struct TopDownSplayTreeNode {
  Comparable data;
  TopDownSplayTreeNode<Comparable> *left;
  TopDownSplayTreeNode<Comparable> *right;

  TopDownSplayTreeNode(const Comparable &data_,
                       TopDownSplayTreeNode<Comparable> *left_ = nullptr,
                       TopDownSplayTreeNode<Comparable> *right_ = nullptr)
      : data{data_}, left{left_}, right{right_} {}
  TopDownSplayTreeNode(const Comparable &&data_,
                       TopDownSplayTreeNode<Comparable> *left_ = nullptr,
                       TopDownSplayTreeNode<Comparable> *right_ = nullptr)
      : data{std::move(data_)}, left{left_}, right{right_} {}
};

}
}
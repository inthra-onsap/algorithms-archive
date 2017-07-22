#include <utility>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
struct TreapNode {
  Comparable data;
  TreapNode<Comparable> *left;
  TreapNode<Comparable> *right;
  int priority;

  TreapNode(const Comparable &data_,
            int priority_,
            TreapNode<Comparable> *left_ = nullptr,
            TreapNode<Comparable> *right_ = nullptr)
      : data{data_}, left{left_}, right{right_}, priority{priority_} {}
  TreapNode(const Comparable &&data_,
            int &&priority_,
            TreapNode<Comparable> *left_ = nullptr,
            TreapNode<Comparable> *right_ = nullptr)
      : data{std::move(data_)}, left{left_}, right{right_}, priority{std::move(priority_)} {}
};

} // namespace tree
} // namespace algorithms_archive
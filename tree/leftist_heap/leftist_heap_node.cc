
#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct LeftistHeapNode {
  Comparable data;
  LeftistHeapNode<Comparable> *left;
  LeftistHeapNode<Comparable> *right;
  int npl;

  LeftistHeapNode(const Comparable &data_,
                  LeftistHeapNode<Comparable> *left_,
                  LeftistHeapNode<Comparable> *right_,
                  int npl_ = 0)
      : data{data_}, left{left_}, right{right_}, npl{npl_} {}
  LeftistHeapNode(const Comparable &&data_,
                  LeftistHeapNode<Comparable> *&&left_,
                  LeftistHeapNode<Comparable> *&&right_,
                  int &&npl_ = 0)
      : data{std::move(data_)}, left{std::move(left_)}, right{std::move(right_)}, npl{npl_} {}
};
} // namespace tree
} // namespace algorithms_archive
#include <utility>

namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct BinomialHeapNode {
  Comparable data;
  BinomialHeapNode<Comparable> *child;
  BinomialHeapNode<Comparable> *next_sibling;

  BinomialHeapNode(const Comparable &data_,
                   BinomialHeapNode<Comparable> *child_ = nullptr,
                   BinomialHeapNode<Comparable> *next_sibling_ = nullptr)
      : data{data_}, child{child_}, next_sibling{next_sibling_} {}
  BinomialHeapNode(Comparable &&data_,
                   BinomialHeapNode<Comparable> *&&child_ = nullptr,
                   BinomialHeapNode<Comparable> *&&next_sibling_ = nullptr)
      : data{std::move(data_)}, child{std::move(child_)}, next_sibling{std::move(next_sibling_)} {}
};
}
}
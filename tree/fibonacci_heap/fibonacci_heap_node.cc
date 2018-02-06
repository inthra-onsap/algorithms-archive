namespace algorithms_archive {
namespace tree {

template<typename Comparable>
struct FibonacciHeapNode {
  Comparable key;
  int degree;
  bool mark;
  FibonacciHeapNode<Comparable> *left;
  FibonacciHeapNode<Comparable> *right;
  FibonacciHeapNode<Comparable> *child;
  FibonacciHeapNode<Comparable> *parent;

  FibonacciHeapNode(Comparable key_) :
      key{key_},
      degree{0},
      mark{false},
      left{this},
      right{this},
      child{nullptr},
      parent{nullptr} {}
};

}
}
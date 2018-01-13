
namespace algorithms_archive{
namespace tree{

template <typename Comparable>
struct ImplicitTreapNode{
  Comparable value;
  Comparable sum;
  int priority;
  int size ;
  Comparable lazy;
  ImplicitTreapNode<Comparable> *left;
  ImplicitTreapNode<Comparable> *right;

  ImplicitTreapNode(Comparable value_, int priority_):
      value{value_},
      priority{priority_},
      sum{value_},
      size{1},
      lazy{0},
      left{nullptr},
      right{nullptr}{}
};

} // namespace tree
} // namespace algorithms_archive
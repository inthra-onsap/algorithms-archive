namespace algorithms_archive {
namespace tree {

template<typename Comparable>
struct RedBlackNode {
  Comparable data;
  RedBlackNode<Comparable> *left;
  RedBlackNode<Comparable> *right;
  RedBlackNode<Comparable> *parent;
  char color;

  RedBlackNode(Comparable &data_,
               RedBlackNode<Comparable> *left_ = nullptr,
               RedBlackNode<Comparable> *right_ = nullptr,
               RedBlackNode<Comparable> *parent_ = nullptr,
               char color_ = 'r')
      : data{data_}, left{left_}, right{right_}, parent{parent_}, color{color_} {}
};

} // namespace tree
} // namespace algorithms_archive
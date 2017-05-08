namespace algorithms_archive {
namespace tree {
template<typename Comparable>
struct SplayTreeNode {
  Comparable data;
  SplayTreeNode<Comparable> *left;
  SplayTreeNode<Comparable> *right;

};
} // namespace tree
} // namespace algorithms_archive
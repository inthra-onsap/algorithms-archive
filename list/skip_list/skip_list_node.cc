#include <vector>

namespace algorithms_archive {
namespace list {

template<typename Comparable>
struct SkipListNode {
  Comparable key;
  std::vector<SkipListNode<Comparable> *> forwards;

  SkipListNode(Comparable key_, int level_) : key{key_} {
    forwards.resize(level_, nullptr);
  }
};

} // namespace list
} // namespace algorithms_archive
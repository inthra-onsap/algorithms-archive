#ifndef ALGORITHMS_ARCHIVE_DISJOINT_SETS_H_
#define ALGORITHMS_ARCHIVE_DISJOINT_SETS_H_

#include <vector>

namespace algorithms_archive {
namespace disjoint_sets {
class DisjointSets {
 public:
  DisjointSets(int size) {
    set.resize(size, -1);
  }

  const int Find(const int idx);

  /**
   * Keep heights of each tree in negative number
   * Find height by abs(set[i] - (-1))
   * Ex. If root set[1] = -4 then the set[1] has height 3
   * @param int root1
   * @param int root2
   */
  void UnionByHeight(int root1, int root2);

 private:
  std::vector<int> set;
};
} // namespace disjoint_sets
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_DISJOINT_SETS_H_

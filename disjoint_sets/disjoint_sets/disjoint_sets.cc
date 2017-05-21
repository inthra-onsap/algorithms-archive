#include "disjoint_sets.h"

namespace algorithms_archive {
namespace disjoint_sets {
const int DisjointSets::Find(const int idx) {
  if (set[idx] <= -1) {
    return idx;
  } else {
    return set[idx] = Find(set[idx]);
  }
}

void DisjointSets::UnionBySize(int set1, int set2) {
  int root1 = Find(set1);
  int root2 = Find(set2);
  if (set[root2] < set[root1]) {
    set[root2] += (set[root1] + 1);
    set[root1] = root2;
  } else {
    set[root1] += (set[root2] + 1);
    set[root2] = root1;
  }
}
} // namespace disjoint_sets
} // namespace algorithms_archive
#include "disjoint_sets.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace disjoint_sets {
class DisjointSetsTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(DisjointSetsTest, ExpectDisjointSetsTransitiveSuccess) {
  DisjointSets disj_set(5);
  disj_set.UnionBySize(0, 1);
  disj_set.UnionBySize(1, 2);
  disj_set.UnionBySize(2, 3);
  disj_set.UnionBySize(3, 4);
  EXPECT_EQ(0, disj_set.Find(4));
}
} // namespace disjoint_sets
} // namespace algorithms_archive
#include "segment_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {

class SegmentTreeTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/** RangeQuery Tests **/
TEST_F(SegmentTreeTest, ExpectSegmentTreeReturnMinElementByRangeQuerySuccess) {
  SegmentTree<int> tree({2, 3, 4, 5, 9, 3, 6, 5, 7});

  EXPECT_EQ(2, tree.RangeQuery(0, 8));
  EXPECT_EQ(5, tree.RangeQuery(7, 8));
  EXPECT_EQ(2, tree.RangeQuery(0, 1));
  EXPECT_EQ(9, tree.RangeQuery(4, 4));
}

/** IncreaseValueByRange Tests **/
TEST_F(SegmentTreeTest, ExpectSegmentTreeIncreaseValueByRangeSuccess) {
  SegmentTree<int> tree({-1, 2, 4, 1, 7, 1, 3, 2});

  tree.IncreaseValueByRange(0, 3, 3);
  EXPECT_EQ(2, tree.RangeQuery(0, 3));

  tree.IncreaseValueByRange(0, 3, 1);
  EXPECT_EQ(3, tree.RangeQuery(0, 3));

  tree.IncreaseValueByRange(0, 0, 2);
  EXPECT_EQ(5, tree.RangeQuery(0, 1));

  EXPECT_EQ(1, tree.RangeQuery(0, 7));
}

} // namespace tree
} // namespace algorithms_archive
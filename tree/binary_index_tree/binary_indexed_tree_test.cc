#include "binary_indexed_tree.h"

#include<gtest/gtest.h>

namespace algorithms_archive {
namespace tree {

class BinaryIndexedTreeTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(BinaryIndexedTreeTest, ExpectSumByRangeReturnSuccess) {
  BinaryIndexedTree<int> tree({-1, 2, 4, 1, 7, 1, 3, 2});

  EXPECT_EQ(-1, tree.SumByRange(0, 0));
  EXPECT_EQ(2, tree.SumByRange(7, 7));
  EXPECT_EQ(6, tree.SumByRange(0, 3));
  EXPECT_EQ(13, tree.SumByRange(4, 7));
  EXPECT_EQ(19, tree.SumByRange(0, 7));
}

TEST_F(BinaryIndexedTreeTest, ExpectUpdateAtReturnNewSumValueSuccess) {
  BinaryIndexedTree<int> tree({-1, 2, 4, 1, 7, 1, 3, 2});

  tree.UpdateAt(0, 5);
  EXPECT_EQ(4, tree.SumByRange(0, 0));

  tree.UpdateAt(7, 5);
  EXPECT_EQ(7, tree.SumByRange(7, 7));

  EXPECT_EQ(11, tree.SumByRange(0, 3));
  EXPECT_EQ(18, tree.SumByRange(4, 7));
  EXPECT_EQ(29, tree.SumByRange(0, 7));
}

} // namespace algorithms_archive
} // namespace tree
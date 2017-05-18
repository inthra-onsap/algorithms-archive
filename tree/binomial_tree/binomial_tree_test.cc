#include <gtest/gtest.h>
#include "binomial_tree.h"

namespace algorithms_archive {
namespace tree {
class BinomialHeapTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/**
 * IsEmpty() & Empty() Tests
 */
TEST_F(BinomialHeapTest, ExpectTreeEmptySuccess) {
  BinomialTree<int> binomial_tree;
  EXPECT_TRUE(binomial_tree.IsEmpty());
}

TEST_F(BinomialHeapTest, ExpectTreeNotEmptySuccess) {
  BinomialTree<int> binomial_tree;
  binomial_tree.Insert(1);
  EXPECT_FALSE(binomial_tree.IsEmpty());
}

TEST_F(BinomialHeapTest, ExpectTreeEmptyAfterEmptyCalledSuccess) {
  BinomialTree<int> binomial_tree;
  binomial_tree.Insert(1);
  binomial_tree.Empty();
  EXPECT_TRUE(binomial_tree.IsEmpty());
}

/**
 * FindMin() & DeleteMin() Tests
 */
TEST_F(BinomialHeapTest, ExpectFindMinSuccess) {
  BinomialTree<int> binomial_tree;
  binomial_tree.Insert(1);
  binomial_tree.Insert(3);
  binomial_tree.Insert(5);
  EXPECT_EQ(1, binomial_tree.FindMin());
}

TEST_F(BinomialHeapTest, ExpectDeleteMinSuccess) {
  BinomialTree<int> binomial_tree;
  binomial_tree.Insert(1);
  binomial_tree.Insert(3);
  binomial_tree.Insert(5);
  binomial_tree.DeleteMin();
  EXPECT_EQ(3, binomial_tree.FindMin());
}

/**
 * Merge() Tests
 */
TEST_F(BinomialHeapTest, ExpectMergeTreeSuccess) {
  BinomialTree<int> binomial_tree1;
  BinomialTree<int> binomial_tree2;
  binomial_tree1.Insert(1);
  binomial_tree1.Insert(2);
  binomial_tree1.Insert(3);
  binomial_tree2.Insert(10);
  binomial_tree2.Insert(11);
  binomial_tree2.Insert(12);
  binomial_tree2.Insert(13);
  binomial_tree2.Insert(14);
  binomial_tree2.Insert(15);
  binomial_tree1.Merge(binomial_tree2);

  EXPECT_TRUE(binomial_tree2.IsEmpty());
  EXPECT_EQ(1, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(2, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(3, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(10, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(11, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(12, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(13, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(14, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_EQ(15, binomial_tree1.FindMin());
  binomial_tree1.DeleteMin();
  EXPECT_TRUE(binomial_tree1.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST_F(BinomialHeapTest, ExpectCopyConstructorSuccess) {
  BinomialTree<int> binomial_tree;
  binomial_tree.Insert(1);
  binomial_tree.Insert(3);
  binomial_tree.Insert(5);
  BinomialTree<int> binomial_tree2 = binomial_tree;
  EXPECT_EQ(1, binomial_tree2.FindMin());
  binomial_tree2.DeleteMin();
  EXPECT_EQ(3, binomial_tree2.FindMin());
  binomial_tree2.DeleteMin();
  EXPECT_EQ(5, binomial_tree2.FindMin());
  binomial_tree2.DeleteMin();
  EXPECT_TRUE(binomial_tree2.IsEmpty());
}

TEST_F(BinomialHeapTest, ExpectMoveConstructorSuccess) {
  BinomialTree<int> binomial_tree;
  binomial_tree.Insert(1);
  binomial_tree.Insert(3);
  binomial_tree.Insert(5);
  BinomialTree<int> binomial_tree2 = std::move(binomial_tree);
  EXPECT_EQ(1, binomial_tree2.FindMin());
  binomial_tree2.DeleteMin();
  EXPECT_EQ(3, binomial_tree2.FindMin());
  binomial_tree2.DeleteMin();
  EXPECT_EQ(5, binomial_tree2.FindMin());
  binomial_tree2.DeleteMin();
  EXPECT_TRUE(binomial_tree2.IsEmpty());
}

} // namespace tree
} // namespace algorithms_archive
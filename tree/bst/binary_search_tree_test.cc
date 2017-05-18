#include "binary_search_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
class BinarySearchTreeTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};
/**
 * IsEmpty() Tests
 */
TEST_F(BinarySearchTreeTest, ExpectTreeIsEmpty) {
  BinarySearchTree<int> bst;
  EXPECT_TRUE(bst.IsEmpty());
}

TEST_F(BinarySearchTreeTest, ExpectTreeIsNotEmpty) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  EXPECT_FALSE(bst.IsEmpty());
}

/**
 * Insert() and Contain() Tests
 */
TEST_F(BinarySearchTreeTest, ExpectInsertAndContainElementSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  EXPECT_TRUE(bst.Contains(5));
}

TEST_F(BinarySearchTreeTest, ExpectOnLeftSideOfTreeContainElementSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(4);
  EXPECT_TRUE(bst.Contains(4));
}

TEST_F(BinarySearchTreeTest, ExpectOnRightSideOfTreeContainElementSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(6);
  EXPECT_TRUE(bst.Contains(6));
}

TEST_F(BinarySearchTreeTest, ExpectNotContainElementFail) {
  BinarySearchTree<int> bst;
  EXPECT_FALSE(bst.Contains(5));
}

/**
 * FindMin() and FindMax() Tests
 */
TEST_F(BinarySearchTreeTest, ExpectFindMinElementSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(4);
  bst.Insert(6);
  int min = bst.FindMin();
  EXPECT_EQ(4, min);
}
TEST_F(BinarySearchTreeTest, ExpectFindMinElementOnEmptyTreeFail) {
  BinarySearchTree<int> bst;
  int null_value = bst.FindMin();
  EXPECT_EQ(NULL, null_value);
}

TEST_F(BinarySearchTreeTest, ExpectFindMaxElementSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(4);
  bst.Insert(6);
  int max = bst.FindMax();
  EXPECT_EQ(6, max);
}

TEST_F(BinarySearchTreeTest, ExpectFindMaxElementOnEmptyTreeFail) {
  BinarySearchTree<int> bst;
  int null_value = bst.FindMax();
  EXPECT_EQ(NULL, null_value);
}

/**
 * Remove() Tests
 */
TEST_F(BinarySearchTreeTest, ExpectRemoveElementSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Remove(5);
  EXPECT_TRUE(bst.IsEmpty());
}

TEST_F(BinarySearchTreeTest, ExpectRemoveElementOnRightSideOfTreeSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(6);
  bst.Insert(7);

  bst.Remove(7);
  EXPECT_FALSE(bst.Contains(7));
}

TEST_F(BinarySearchTreeTest, ExpectRemoveElementOnLeftSideOfTreeSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(7);
  bst.Insert(6);
  bst.Insert(5);

  bst.Remove(5);
  EXPECT_FALSE(bst.Contains(5));
}

TEST_F(BinarySearchTreeTest, ExpectRemoveRootElementOfTreeSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(6);
  bst.Insert(7);

  bst.Remove(5);
  EXPECT_FALSE(bst.Contains(5));

  EXPECT_TRUE(bst.Contains(6));
  EXPECT_TRUE(bst.Contains(7));
}

/**
 * Clear() Tests
 */
TEST_F(BinarySearchTreeTest, ExpectClearAllElementsSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(6);
  bst.Insert(7);
  bst.Clear();

  EXPECT_TRUE(bst.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST_F(BinarySearchTreeTest, ExpectCopyAllElementsFromTreeSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(4);
  bst.Insert(7);
  BinarySearchTree<int> new_bst = bst;

  EXPECT_TRUE(new_bst.Contains(4));
  EXPECT_TRUE(new_bst.Contains(5));
  EXPECT_TRUE(new_bst.Contains(7));
}

TEST_F(BinarySearchTreeTest, ExpectMoveAllElementsFromTreeSuccess) {
  BinarySearchTree<int> bst;
  bst.Insert(5);
  bst.Insert(4);
  bst.Insert(7);
  BinarySearchTree<int> new_bst = std::move(bst);

  EXPECT_TRUE(new_bst.Contains(4));
  EXPECT_TRUE(new_bst.Contains(5));
  EXPECT_TRUE(new_bst.Contains(7));
}
} // namespace tree
} // namespace algorithms_archive
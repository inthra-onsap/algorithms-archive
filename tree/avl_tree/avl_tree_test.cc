#include "avl_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
/**
 * IsEmpty() Tests
 */
TEST(AvlTreeTest, ExpectTreeIsEmpty) {
  AvlTree<int> avl_tree;
  EXPECT_TRUE(avl_tree.IsEmpty());
}

TEST(AvlTreeTest, ExpectTreeIsNotEmpty) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_FALSE(avl_tree.IsEmpty());
}

/**
 * Insert() and Contain() Tests
 */
TEST(AvlTreeTest, ExpectInsertAndContainElementSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  EXPECT_TRUE(avl_tree.Contains(5));
}

TEST(AvlTreeTest, ExpectOnLeftSideOfTreeContainElementSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(4);
  EXPECT_TRUE(avl_tree.Contains(4));
}

TEST(AvlTreeTest, ExpectOnRightSideOfTreeContainElementSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(6);
  EXPECT_TRUE(avl_tree.Contains(6));
}

TEST(AvlTreeTest, ExpectNotContainElementFail) {
  AvlTree<int> avl_tree;
  EXPECT_FALSE(avl_tree.Contains(5));
}

TEST(AvlTreeTest, ExpectBalancingLeftHeavySubtreeRightRotationSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(9);
  avl_tree.Insert(8);
  avl_tree.Insert(7);
  EXPECT_EQ(2, avl_tree.TreeHeight());
}

TEST(AvlTreeTest, ExpectBalancingRightHeavySubtreeLeftRotationSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(6);
  avl_tree.Insert(7);
  EXPECT_EQ(2, avl_tree.TreeHeight());
}

TEST(AvlTreeTest, ExpectBalancingLeftHeavySubtreeLeftRightRotationSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(5);
  avl_tree.Insert(8);
  EXPECT_EQ(2, avl_tree.TreeHeight());
}

TEST(AvlTreeTest, ExpectBalancingRightHeavySubtreeRightLeftRotationSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(8);
  avl_tree.Insert(5);
  avl_tree.Insert(10);
  EXPECT_EQ(2, avl_tree.TreeHeight());
}

/**
 * FindMin() and FindMax() Tests
 */
TEST(AvlTreeTest, ExpectFindMinElementSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(4);
  avl_tree.Insert(6);
  int min = avl_tree.FindMin();
  EXPECT_EQ(4, min);
}
TEST(AvlTreeTest, ExpectFindMinElementOnEmptyTreeFail) {
  AvlTree<int> avl_tree;
  int null_value = avl_tree.FindMin();
  EXPECT_EQ(NULL, null_value);
}

TEST(AvlTreeTest, ExpectFindMaxElementSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(4);
  avl_tree.Insert(6);
  int max = avl_tree.FindMax();
  EXPECT_EQ(6, max);
}

TEST(AvlTreeTest, ExpectFindMaxElementOnEmptyTreeFail) {
  AvlTree<int> avl_tree;
  int null_value = avl_tree.FindMax();
  EXPECT_EQ(NULL, null_value);
}

/**
 * Remove() Tests
 */
TEST(AvlTreeTest, ExpectRemoveElementSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Remove(5);
  EXPECT_TRUE(avl_tree.IsEmpty());
}

TEST(AvlTreeTest, ExpectRemoveElementOnRightSideOfTreeSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(6);
  avl_tree.Insert(7);

  avl_tree.Remove(7);
  EXPECT_FALSE(avl_tree.Contains(7));
}

TEST(AvlTreeTest, ExpectRemoveElementOnLeftSideOfTreeSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(7);
  avl_tree.Insert(6);
  avl_tree.Insert(5);

  avl_tree.Remove(5);
  EXPECT_FALSE(avl_tree.Contains(5));
}

TEST(AvlTreeTest, ExpectRemoveRootElementOfTreeSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(6);
  avl_tree.Insert(7);

  avl_tree.Remove(5);
  EXPECT_FALSE(avl_tree.Contains(5));

  EXPECT_TRUE(avl_tree.Contains(6));
  EXPECT_TRUE(avl_tree.Contains(7));
}

/**
 * Clear() Tests
 */
TEST(AvlTreeTest, ExpectClearAllElementsSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(6);
  avl_tree.Insert(7);
  avl_tree.Clear();

  EXPECT_TRUE(avl_tree.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST(AvlTreeTest, ExpectCopyAllElementsFromTreeSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(4);
  avl_tree.Insert(7);
  AvlTree<int> new_avl_tree = avl_tree;

  EXPECT_TRUE(new_avl_tree.Contains(4));
  EXPECT_TRUE(new_avl_tree.Contains(5));
  EXPECT_TRUE(new_avl_tree.Contains(7));
}

TEST(AvlTreeTest, ExpectMoveAllElementsFromTreeSuccess) {
  AvlTree<int> avl_tree;
  avl_tree.Insert(5);
  avl_tree.Insert(4);
  avl_tree.Insert(7);
  AvlTree<int> new_avl_tree = std::move(avl_tree);

  EXPECT_TRUE(new_avl_tree.Contains(4));
  EXPECT_TRUE(new_avl_tree.Contains(5));
  EXPECT_TRUE(new_avl_tree.Contains(7));
}
} // namespace tree
} // namespace algorithm_archive
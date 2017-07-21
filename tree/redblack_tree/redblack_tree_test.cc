#include "redblack_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {

class RedBlackTreeTest : public testing::Test {
 public:
  enum Color : char { RED = 'r', BLACK = 'b' };

  virtual void SetUp() {}
  virtual void TearDown() {}
};

/**
 * IsEmpty() Tests
 */
TEST_F(RedBlackTreeTest, ExpectTreeIsEmpty) {
  RedBlackTree<int> tree;
  EXPECT_TRUE(tree.IsEmpty());
}

TEST_F(RedBlackTreeTest, ExpectTreeIsNotEmpty) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  EXPECT_FALSE(tree.IsEmpty());
}

/**
 * Insert() and Find() Tests
 */
TEST_F(RedBlackTreeTest, ExpectInsertAndContainฺBlackNodeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);

  const RedBlackNode<int> *node = tree.Find(5);
  EXPECT_EQ(5, node->data);
  EXPECT_EQ(BLACK, node->color);
}

TEST_F(RedBlackTreeTest, ExpectOnLeftSideOfTreeContainRedNodeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(4);

  const RedBlackNode<int> *node = tree.Find(4);
  EXPECT_EQ(4, node->data);
  EXPECT_EQ(RED, node->color);
}

TEST_F(RedBlackTreeTest, ExpectOnRightSideOfTreeContainRedNodeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(6);

  const RedBlackNode<int> *node = tree.Find(6);
  EXPECT_EQ(6, node->data);
  EXPECT_EQ(RED, node->color);
}

TEST_F(RedBlackTreeTest, ExpectTreeHandleRightRedSiblingAndRecolorSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(15);
  tree.Insert(10);
  tree.Insert(5);
  tree.Insert(3);

  const RedBlackNode<int> *node = tree.Find(3);
  EXPECT_EQ(3, node->data);
  EXPECT_EQ(RED, node->color);
  const RedBlackNode<int> *parent_node = node->parent;
  EXPECT_EQ(5, parent_node->data);
  EXPECT_EQ(BLACK, parent_node->color);
  const RedBlackNode<int> *grand_parent = node->parent->parent;
  EXPECT_EQ(10, grand_parent->data);
  EXPECT_EQ(BLACK, grand_parent->color);
  const RedBlackNode<int> *sibling_node = grand_parent->right;
  EXPECT_EQ(15, sibling_node->data);
  EXPECT_EQ(BLACK, sibling_node->color);
}

TEST_F(RedBlackTreeTest, ExpectTreeHandleLeftRedSiblingAndRecolorSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(3);
  tree.Insert(5);
  tree.Insert(10);
  tree.Insert(15);

  const RedBlackNode<int> *node = tree.Find(15);
  EXPECT_EQ(15, node->data);
  EXPECT_EQ(RED, node->color);
  const RedBlackNode<int> *parent_node = node->parent;
  EXPECT_EQ(10, parent_node->data);
  EXPECT_EQ(BLACK, parent_node->color);
  const RedBlackNode<int> *grand_parent = node->parent->parent;
  EXPECT_EQ(5, grand_parent->data);
  EXPECT_EQ(BLACK, grand_parent->color);
  const RedBlackNode<int> *sibling_node = grand_parent->left;
  EXPECT_EQ(3, sibling_node->data);
  EXPECT_EQ(BLACK, sibling_node->color);
}

TEST_F(RedBlackTreeTest, ExpectTreeHandleRightBlackSiblingRightLeftCaseAndRotateLeftRightSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(60);
  tree.Insert(50);
  tree.Insert(40);
  tree.Insert(10);
  tree.Insert(20);

  const RedBlackNode<int> *root = tree.Find(50);
  EXPECT_EQ(50, root->data);
  EXPECT_EQ(BLACK, root->color);
  const RedBlackNode<int> *right_child = root->right;
  EXPECT_EQ(60, right_child->data);
  EXPECT_EQ(BLACK, right_child->color);
  const RedBlackNode<int> *left_child = root->left;
  EXPECT_EQ(20, left_child->data);
  EXPECT_EQ(BLACK, left_child->color);
  const RedBlackNode<int> *left_grand_child = left_child->left;
  EXPECT_EQ(10, left_grand_child->data);
  EXPECT_EQ(RED, left_grand_child->color);
  const RedBlackNode<int> *right_grand_child = left_child->right;
  EXPECT_EQ(40, right_grand_child->data);
  EXPECT_EQ(RED, right_grand_child->color);
}

TEST_F(RedBlackTreeTest, ExpectTreeHandleLeftBlackSiblingLeftRightCaseAndRotateRightLeftSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);
  tree.Insert(50);
  tree.Insert(40);

  const RedBlackNode<int> *root = tree.Find(20);
  EXPECT_EQ(20, root->data);
  EXPECT_EQ(BLACK, root->color);
  const RedBlackNode<int> *right_child = root->right;
  EXPECT_EQ(40, right_child->data);
  EXPECT_EQ(BLACK, right_child->color);
  const RedBlackNode<int> *left_child = root->left;
  EXPECT_EQ(10, left_child->data);
  EXPECT_EQ(BLACK, left_child->color);
  const RedBlackNode<int> *left_grand_child = right_child->left;
  EXPECT_EQ(30, left_grand_child->data);
  EXPECT_EQ(RED, left_grand_child->color);
  const RedBlackNode<int> *right_grand_child = right_child->right;
  EXPECT_EQ(50, right_grand_child->data);
  EXPECT_EQ(RED, right_grand_child->color);
}

/**
 * Remove() & Contains() Tests
 */
TEST_F(RedBlackTreeTest, ExpectNotContainElementFail) {
  RedBlackTree<int> tree;
  EXPECT_FALSE(tree.Contains(5));
}

TEST_F(RedBlackTreeTest, ExpectRemoveRedNodeOnRightSideOfTreeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(6);
  tree.Insert(7);

  tree.Remove(7);
  EXPECT_FALSE(tree.Contains(7));
}

TEST_F(RedBlackTreeTest, ExpectRemoveRedNodeOnLeftSideOfTreeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(7);
  tree.Insert(6);
  tree.Insert(5);

  tree.Remove(5);
  EXPECT_FALSE(tree.Contains(5));
}

TEST_F(RedBlackTreeTest, ExpectRemoveRootElementOfTreeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(6);
  tree.Insert(7);

  tree.Remove(5);
  EXPECT_FALSE(tree.Contains(5));

  EXPECT_TRUE(tree.Contains(6));
  EXPECT_TRUE(tree.Contains(7));
}

TEST_F(RedBlackTreeTest, ExpectRemoveBlankAndReplaceWithRedNodeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);
  tree.Insert(25);

  tree.Remove(25);
  EXPECT_FALSE(tree.Contains(25));

  const RedBlackNode<int> *root = tree.Find(20);
  EXPECT_EQ(20, root->data);
  EXPECT_EQ(BLACK, root->color);
  const RedBlackNode<int> *left_child = root->left;
  EXPECT_EQ(10, left_child->data);
  EXPECT_EQ(BLACK, left_child->color);
  const RedBlackNode<int> *right_child = root->right;
  EXPECT_EQ(30, right_child->data);
  EXPECT_EQ(BLACK, right_child->color);
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase1Success) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Remove(5);
  EXPECT_TRUE(tree.IsEmpty());
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase2RotateRightAndCase4Success) {
  RedBlackTree<int> tree;
  tree.Insert(60);
  tree.Insert(50);
  tree.Insert(40);
  tree.Insert(30);
  tree.Insert(20);
  tree.Insert(10);

  tree.Remove(60);
  EXPECT_FALSE(tree.Contains(60));
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase2RotateLeftAndCase4Success) {
  RedBlackTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);
  tree.Insert(40);
  tree.Insert(50);
  tree.Insert(60);

  tree.Remove(10);
  EXPECT_FALSE(tree.Contains(10));
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase3RotateLeftAndCase4Success) {
  RedBlackTree<int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);
  tree.Insert(40);
  tree.Insert(50);
  tree.Insert(60);

  tree.Remove(10);
  EXPECT_FALSE(tree.Contains(10));
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase3Success) {
  RedBlackTree<int> tree;
  tree.Insert(7);
  tree.Insert(6);
  tree.Insert(5);
  tree.Insert(3);

  tree.Remove(5);
  tree.Remove(3);
  EXPECT_FALSE(tree.Contains(5));
  EXPECT_FALSE(tree.Contains(3));
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase5RotateLeftSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(70);
  tree.Insert(60);
  tree.Insert(50);
  tree.Insert(55);

  tree.Remove(70);
  EXPECT_FALSE(tree.Contains(70));
}


TEST_F(RedBlackTreeTest, ExpectRemoveCase5RotateRightSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(50);
  tree.Insert(60);
  tree.Insert(70);
  tree.Insert(65);

  tree.Remove(50);
  EXPECT_FALSE(tree.Contains(50));
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase6RotateRigthSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(7);
  tree.Insert(6);
  tree.Insert(5);
  tree.Insert(3);

  tree.Remove(7);
  EXPECT_FALSE(tree.Contains(7));
}

TEST_F(RedBlackTreeTest, ExpectRemoveCase6RotateLeftSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(3);
  tree.Insert(4);
  tree.Insert(5);
  tree.Insert(6);

  tree.Remove(3);
  EXPECT_FALSE(tree.Contains(3));
}

/**
 * Clear() Tests
 */
TEST_F(RedBlackTreeTest, ExpectClearAllElementsSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(6);
  tree.Insert(7);
  tree.Clear();

  EXPECT_TRUE(tree.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST_F(RedBlackTreeTest, ExpectCopyAllElementsFromTreeSuccess) {
  RedBlackTree<int> tree;
  tree.Insert(5);
  tree.Insert(4);
  tree.Insert(7);
  RedBlackTree<int> new_tree = tree;

  EXPECT_TRUE(tree.Contains(4));
  EXPECT_TRUE(tree.Contains(5));
  EXPECT_TRUE(tree.Contains(7));
}

} // namespace tree
} // namespace algorithms_archive
#include "topdown_splay_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
class TopDownSplayTreeTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};
/**
 * IsEmpty() Tests
 */
TEST_F(TopDownSplayTreeTest, ExpectTreeIsEmpty) {
  TopDownSplayTree<int> splay_tree;
  EXPECT_TRUE(splay_tree.IsEmpty());
}

TEST_F(TopDownSplayTreeTest, ExpectTreeIsNotEmpty) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  EXPECT_FALSE(splay_tree.IsEmpty());
}

/**
 * Insert() and Find() Tests
 */
TEST_F(TopDownSplayTreeTest, ExpectInsertAndFindElementSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  const TopDownSplayTreeNode<int> *find_node = splay_tree.Find(5);
  EXPECT_EQ(5, find_node->data);
  EXPECT_EQ(nullptr, find_node->left);
  EXPECT_EQ(nullptr, find_node->right);
}

TEST_F(TopDownSplayTreeTest, ExpectLeftElementSplayToRootSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(4);
  const TopDownSplayTreeNode<int> *new_root = splay_tree.Find(4);
  // new root
  EXPECT_EQ(4, new_root->data);
  EXPECT_EQ(nullptr, new_root->left);

  // old root
  EXPECT_EQ(5, new_root->right->data);
  EXPECT_EQ(nullptr, new_root->right->right);
  EXPECT_EQ(nullptr, new_root->right->left);
}

TEST_F(TopDownSplayTreeTest, ExpectRightElementSplayToRootSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  const TopDownSplayTreeNode<int> *new_root = splay_tree.Find(6);
  // new root
  EXPECT_EQ(6, new_root->data);
  EXPECT_EQ(nullptr, new_root->right);

  // old root
  EXPECT_EQ(5, new_root->left->data);
  EXPECT_EQ(nullptr, new_root->left->right);
  EXPECT_EQ(nullptr, new_root->left->left);
}

/**
 * Remove() Tests
 */
TEST_F(TopDownSplayTreeTest, ExpectRemoveElementSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Remove(5);
  EXPECT_TRUE(splay_tree.IsEmpty());
}

TEST_F(TopDownSplayTreeTest, ExpectRemoveElementOnRightSideOfTreeSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  splay_tree.Insert(7);
  splay_tree.Remove(7);
  EXPECT_FALSE(splay_tree.Contains(7));
}

TEST_F(TopDownSplayTreeTest, ExpectRemoveElementOnLeftSideOfTreeSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(7);
  splay_tree.Insert(6);
  splay_tree.Insert(5);
  splay_tree.Remove(5);
  EXPECT_FALSE(splay_tree.Contains(5));
}

TEST_F(TopDownSplayTreeTest, ExpectRemoveRootElementOfTreeSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  splay_tree.Insert(7);

  splay_tree.Remove(5);
  EXPECT_FALSE(splay_tree.Contains(5));
  EXPECT_TRUE(splay_tree.Contains(6));
  EXPECT_TRUE(splay_tree.Contains(7));
}

/**
 * Clear() Tests
 */
TEST_F(TopDownSplayTreeTest, ExpectClearAllElementsSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  splay_tree.Insert(7);
  splay_tree.Clear();

  EXPECT_TRUE(splay_tree.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST_F(TopDownSplayTreeTest, ExpectCopyAllElementsFromTreeSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(4);
  splay_tree.Insert(7);
  TopDownSplayTree<int> new_splay_tree = splay_tree;

  EXPECT_EQ(4, new_splay_tree.Find(4)->data);
  EXPECT_EQ(5, new_splay_tree.Find(5)->data);
  EXPECT_EQ(7, new_splay_tree.Find(7)->data);
}

TEST_F(TopDownSplayTreeTest, ExpectMoveAllElementsFromTreeSuccess) {
  TopDownSplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(4);
  splay_tree.Insert(7);
  TopDownSplayTree<int> new_splay_tree = std::move(splay_tree);

  EXPECT_EQ(5, new_splay_tree.Find(5)->data);
  EXPECT_EQ(4, new_splay_tree.Find(4)->data);
  EXPECT_EQ(7, new_splay_tree.Find(7)->data);
}
} // namespace tree
} // namespace algorithms_archive
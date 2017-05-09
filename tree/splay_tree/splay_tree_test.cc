#include "splay_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
/**
 * IsEmpty() Tests
 */
TEST(SplayTreeTest, ExpectTreeIsEmpty) {
  SplayTree<int> splay_tree;
  EXPECT_TRUE(splay_tree.IsEmpty());
}

TEST(SplayTreeTest, ExpectTreeIsNotEmpty) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  EXPECT_FALSE(splay_tree.IsEmpty());
}

/**
 * Insert() and Find() Tests
 */
TEST(SplayTreeTest, ExpectInsertAndFindElementSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  const SplayTreeNode<int> *find_node = splay_tree.Find(5);
  EXPECT_EQ(5, find_node->data);
  EXPECT_EQ(nullptr, find_node->parent);
  EXPECT_EQ(nullptr, find_node->left);
  EXPECT_EQ(nullptr, find_node->right);
}

TEST(SplayTreeTest, ExpectLeftElementSplayToRootSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(4);
  const SplayTreeNode<int> *new_root = splay_tree.Find(4);
  // new root
  EXPECT_EQ(4, new_root->data);
  EXPECT_EQ(nullptr, new_root->parent);
  EXPECT_EQ(nullptr, new_root->left);

  // old root
  EXPECT_EQ(5, new_root->right->data);
  EXPECT_EQ(new_root, new_root->right->parent);
  EXPECT_EQ(nullptr, new_root->right->right);
  EXPECT_EQ(nullptr, new_root->right->left);
}

TEST(SplayTreeTest, ExpectRightElementSplayToRootSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  const SplayTreeNode<int> *new_root = splay_tree.Find(6);
  // new root
  EXPECT_EQ(6, new_root->data);
  EXPECT_EQ(nullptr, new_root->parent);
  EXPECT_EQ(nullptr, new_root->right);

  // old root
  EXPECT_EQ(5, new_root->left->data);
  EXPECT_EQ(new_root, new_root->left->parent);
  EXPECT_EQ(nullptr, new_root->left->right);
  EXPECT_EQ(nullptr, new_root->left->left);
}

/**
 * Remove() Tests
 */
TEST(SplayTreeTest, ExpectRemoveElementSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Remove(5);
  EXPECT_TRUE(splay_tree.IsEmpty());
}

TEST(SplayTreeTest, ExpectRemoveElementOnRightSideOfTreeSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  splay_tree.Insert(7);
  splay_tree.Remove(7);
  EXPECT_FALSE(splay_tree.Contains(7));
}

TEST(SplayTreeTest, ExpectRemoveElementOnLeftSideOfTreeSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(7);
  splay_tree.Insert(6);
  splay_tree.Insert(5);
  splay_tree.Remove(5);
  EXPECT_FALSE(splay_tree.Contains(5));
}

TEST(SplayTreeTest, ExpectRemoveRootElementOfTreeSuccess) {
  SplayTree<int> splay_tree;
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
TEST(SplayTreeTest, ExpectClearAllElementsSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(6);
  splay_tree.Insert(7);
  splay_tree.Clear();

  EXPECT_TRUE(splay_tree.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST(SplayTreeTest, ExpectCopyAllElementsFromTreeSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(4);
  splay_tree.Insert(7);
  SplayTree<int> new_splay_tree = splay_tree;

  EXPECT_EQ(4, new_splay_tree.Find(4)->data);
  EXPECT_EQ(5, new_splay_tree.Find(5)->data);
  EXPECT_EQ(7, new_splay_tree.Find(7)->data);
}

TEST(SplayTreeTest, ExpectMoveAllElementsFromTreeSuccess) {
  SplayTree<int> splay_tree;
  splay_tree.Insert(5);
  splay_tree.Insert(4);
  splay_tree.Insert(7);
  SplayTree<int> new_splay_tree = std::move(splay_tree);

  EXPECT_EQ(5, new_splay_tree.Find(5)->data);
  EXPECT_EQ(4, new_splay_tree.Find(4)->data);
  EXPECT_EQ(7, new_splay_tree.Find(7)->data);
}
} // namespace tree
} // namespace algorithms_archive
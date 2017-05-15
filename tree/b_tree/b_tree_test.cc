#include "b_tree.h"

#include<gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
// Predicate function
bool IsNull(BTreeNode<int> *node) {
  return (node == nullptr);
}
bool IsNotNull(BTreeNode<int> *node) {
  return (node != nullptr);
}

// BTreeTest class
class BTreeTest : public testing::Test {
 protected:
  virtual void SetUp() {}

  virtual void TearDown() {}
};

/**
* IsEmpty() Tests
*/
TEST_F(BTreeTest, ExpectTreeIsEmpty) {
  BTree<int> b_tree{3};
  EXPECT_TRUE(b_tree.IsEmpty());
}

TEST_F(BTreeTest, ExpectTreeIsNotEmpty) {
  BTree<int> b_tree{3};
  b_tree.Insert(5);
  EXPECT_FALSE(b_tree.IsEmpty());
}

/**
 * Insert() and Contain() Tests
 */
TEST_F(BTreeTest, ExpectInsertFirstElementSuccess) {
  BTree<int> b_tree{3};
  b_tree.Insert(5);
  EXPECT_TRUE(b_tree.Contain(5));
}

TEST_F(BTreeTest, ExpectInsert5ElementsToRootSuccess) {
  BTree<int> b_tree{3};
  b_tree.Insert(1);
  b_tree.Insert(2);
  b_tree.Insert(3);
  b_tree.Insert(4);
  b_tree.Insert(5);
  EXPECT_TRUE(b_tree.Contain(1));
  EXPECT_TRUE(b_tree.Contain(2));
  EXPECT_TRUE(b_tree.Contain(3));
  EXPECT_TRUE(b_tree.Contain(4));
  EXPECT_TRUE(b_tree.Contain(5));
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(5, root->num_of_keys);
  EXPECT_EQ(1, root->keys[0]);
  EXPECT_EQ(2, root->keys[1]);
  EXPECT_EQ(3, root->keys[2]);
  EXPECT_EQ(4, root->keys[3]);
  EXPECT_EQ(5, root->keys[4]);
  EXPECT_PRED1(IsNull, root->p_children[0]);
  EXPECT_PRED1(IsNull, root->p_children[1]);
  EXPECT_PRED1(IsNull, root->p_children[2]);
  EXPECT_PRED1(IsNull, root->p_children[3]);
  EXPECT_PRED1(IsNull, root->p_children[4]);
  EXPECT_PRED1(IsNull, root->p_children[5]);
}

TEST_F(BTreeTest, ExpectInsertElementsAndBuildNewRootSuccess) {
  BTree<int> b_tree{3};
  b_tree.Insert(1);
  b_tree.Insert(2);
  b_tree.Insert(3);
  b_tree.Insert(4);
  b_tree.Insert(5);
  b_tree.Insert(6);
  EXPECT_TRUE(b_tree.Contain(1));
  EXPECT_TRUE(b_tree.Contain(2));
  EXPECT_TRUE(b_tree.Contain(3));
  EXPECT_TRUE(b_tree.Contain(4));
  EXPECT_TRUE(b_tree.Contain(5));
  EXPECT_TRUE(b_tree.Contain(6));
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(1, root->num_of_keys);
  EXPECT_EQ(3, root->keys[0]);
  EXPECT_PRED1(IsNotNull, root->p_children[0]);
  EXPECT_PRED1(IsNotNull, root->p_children[1]);
  // Expect first leaf as following
  BTreeNode<int> *first_leaf = root->p_children[0];
  EXPECT_EQ(2, first_leaf->num_of_keys);
  EXPECT_EQ(1, first_leaf->keys[0]);
  EXPECT_EQ(2, first_leaf->keys[1]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[0]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[1]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[2]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[3]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[4]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[5]);
  //Expect second leaf as following
  BTreeNode<int> *second_leaf = root->p_children[1];
  EXPECT_EQ(3, second_leaf->num_of_keys);
  EXPECT_EQ(4, second_leaf->keys[0]);
  EXPECT_EQ(5, second_leaf->keys[1]);
  EXPECT_EQ(6, second_leaf->keys[2]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[0]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[1]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[2]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[3]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[4]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[5]);
}

TEST_F(BTreeTest, ExpectInsertElementsToChildWithoutSplitChildSuccess) {
  BTree<int> b_tree{3};
  b_tree.Insert(1);
  b_tree.Insert(2);
  b_tree.Insert(3);
  b_tree.Insert(4);
  b_tree.Insert(5);
  b_tree.Insert(6);
  b_tree.Insert(7);
  EXPECT_TRUE(b_tree.Contain(1));
  EXPECT_TRUE(b_tree.Contain(2));
  EXPECT_TRUE(b_tree.Contain(3));
  EXPECT_TRUE(b_tree.Contain(4));
  EXPECT_TRUE(b_tree.Contain(5));
  EXPECT_TRUE(b_tree.Contain(6));
  EXPECT_TRUE(b_tree.Contain(7));
  //Expect second leaf as following
  BTreeNode<int> *second_leaf = b_tree.root->p_children[1];
  EXPECT_EQ(4, second_leaf->num_of_keys);
  EXPECT_EQ(4, second_leaf->keys[0]);
  EXPECT_EQ(5, second_leaf->keys[1]);
  EXPECT_EQ(6, second_leaf->keys[2]);
  EXPECT_EQ(7, second_leaf->keys[3]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[0]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[1]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[2]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[3]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[4]);
  EXPECT_PRED1(IsNull, second_leaf->p_children[5]);
}

TEST_F(BTreeTest, ExpectInsertElementsToChildWithSplitChildSuccess) {
  BTree<int> b_tree{3};
  b_tree.Insert(10);
  b_tree.Insert(11);
  b_tree.Insert(12);
  b_tree.Insert(13);
  b_tree.Insert(14);
  b_tree.Insert(9);
  b_tree.Insert(8);
  b_tree.Insert(7);
  b_tree.Insert(6);
  EXPECT_TRUE(b_tree.Contain(6));
  EXPECT_TRUE(b_tree.Contain(7));
  EXPECT_TRUE(b_tree.Contain(8));
  EXPECT_TRUE(b_tree.Contain(9));
  EXPECT_TRUE(b_tree.Contain(10));
  EXPECT_TRUE(b_tree.Contain(11));
  EXPECT_TRUE(b_tree.Contain(12));
  EXPECT_TRUE(b_tree.Contain(13));
  EXPECT_TRUE(b_tree.Contain(14));
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(2, root->num_of_keys);
  EXPECT_EQ(9, root->keys[0]);
  EXPECT_EQ(12, root->keys[1]);
  EXPECT_PRED1(IsNotNull, root->p_children[0]);
  EXPECT_PRED1(IsNotNull, root->p_children[1]);
  EXPECT_PRED1(IsNotNull, root->p_children[2]);
  //Expect first leaf as following
  BTreeNode<int> *first_leaf = root->p_children[0];
  EXPECT_EQ(3, first_leaf->num_of_keys);
  EXPECT_EQ(6, first_leaf->keys[0]);
  EXPECT_EQ(7, first_leaf->keys[1]);
  EXPECT_EQ(8, first_leaf->keys[2]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[0]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[1]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[2]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[3]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[4]);
  EXPECT_PRED1(IsNull, first_leaf->p_children[5]);
}

/**
 * Remove() Tests
 */
TEST_F(BTreeTest, ExpectRemoveElementFromLeafSuccess) {
  BTree<int> b_tree{3};
  b_tree.Insert(10);
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(1, root->num_of_keys);
  b_tree.Remove(10);
  EXPECT_EQ(0, root->num_of_keys);
}

TEST_F(BTreeTest, ExpectRemoveElementFromNonLeafByPredecessorAndLeafByBorrowLeftSuccess) {
  BTree<int> b_tree{2};
  b_tree.Insert(11);
  b_tree.Insert(12);
  b_tree.Insert(13);
  b_tree.Insert(14);
  b_tree.Insert(15);
  b_tree.Insert(16);
  b_tree.Insert(17);
  b_tree.Insert(18);
  b_tree.Insert(8);
  b_tree.Insert(9);
  b_tree.Insert(10);
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(14, root->keys[0]);
  b_tree.Remove(14);
  EXPECT_EQ(13, root->keys[0]);
}

TEST_F(BTreeTest, ExpectRemoveElementFromNonLeafBySuccessorAndLeafByBorrowRightSuccess) {
  BTree<int> b_tree{2};
  b_tree.Insert(10);
  b_tree.Insert(20);
  b_tree.Insert(30);
  b_tree.Insert(40);
  b_tree.Insert(50);
  b_tree.Insert(60);
  b_tree.Insert(70);
  b_tree.Insert(80);
  b_tree.Insert(90);
  b_tree.Insert(100);
  b_tree.Insert(75);
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(40, root->keys[0]);
  b_tree.Remove(40);
  EXPECT_EQ(50, root->keys[0]);
}

TEST_F(BTreeTest, ExpectRemoveElementFromNonLeafByMergingSuccess) {
  BTree<int> b_tree{2};
  b_tree.Insert(10);
  b_tree.Insert(20);
  b_tree.Insert(30);
  b_tree.Insert(40);
  b_tree.Insert(50);
  b_tree.Insert(60);
  b_tree.Insert(70);
  b_tree.Insert(80);
  b_tree.Insert(90);
  // Expect root as following
  BTreeNode<int> *root = b_tree.root;
  EXPECT_EQ(40, root->keys[0]);
  b_tree.Remove(40);
  // Get new root
  root = b_tree.root;
  EXPECT_EQ(20, root->keys[0]);
  EXPECT_EQ(60, root->keys[1]);
}
} // namespace tree
} // namespace algorithms_archive
#include "treap.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {

class TreapTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/**
 * IsEmpty() Tests
 */
TEST_F(TreapTest, ExpectTreeIsEmpty) {
  Treap<int> treap;
  EXPECT_TRUE(treap.IsEmpty());
}

TEST_F(TreapTest, ExpectTreeIsNotEmpty) {
  Treap<int> treap;
  treap.Insert(5);
  EXPECT_FALSE(treap.IsEmpty());
}

/**
 * Insert() and Contains() Tests
 */
TEST_F(TreapTest, ExpectInsertAndContainElementSuccess) {
  Treap<int> treap;
  treap.Insert(5);
  EXPECT_TRUE(treap.Contains(5));
}

TEST_F(TreapTest, ExpectInsertNewElementSuccess) {
  Treap<int> treap;
  treap.Insert(5);
  treap.Insert(4);
  EXPECT_TRUE(treap.Contains(4));
}

TEST_F(TreapTest, ExpectNotContainElementFail) {
  Treap<int> treap;
  EXPECT_FALSE(treap.Contains(5));
}


/**
 * Remove() Tests
 */
TEST_F(TreapTest, ExpectRemoveElementSuccess) {
  Treap<int> treap;
  treap.Insert(5);
  treap.Remove(5);
  EXPECT_TRUE(treap.IsEmpty());
}

TEST_F(TreapTest, ExpectRemoveElementInTreeSuccess) {
  Treap<int> treap;
  treap.Insert(5);
  treap.Insert(6);
  treap.Insert(7);

  treap.Remove(7);
  EXPECT_FALSE(treap.Contains(7));
}

/**
 * Clear() Tests
 */
TEST_F(TreapTest, ExpectClearAllElementsSuccess) {
  Treap<int> treap;
  treap.Insert(5);
  treap.Insert(6);
  treap.Insert(7);
  treap.Clear();

  EXPECT_TRUE(treap.IsEmpty());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST_F(TreapTest, ExpectCopyAllElementsFromTreeSuccess) {
  Treap<int> treap;
  treap.Insert(5);
  treap.Insert(4);
  treap.Insert(7);
  Treap<int> new_treap = treap;

  EXPECT_TRUE(new_treap.Contains(4));
  EXPECT_TRUE(new_treap.Contains(5));
  EXPECT_TRUE(new_treap.Contains(7));
}

} // namespace tree
} // namespace algorithms_archive
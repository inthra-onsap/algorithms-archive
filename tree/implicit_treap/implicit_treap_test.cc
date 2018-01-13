#include "implicit_treap.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {

class ImplicitTreapTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};

/**
 * IsEmpty() & Size()Tests
 */
TEST_F(ImplicitTreapTest, ExpectTreeIsEmptySuccess) {
  ImplicitTreap<int> treap;
  EXPECT_TRUE(treap.IsEmpty());
  EXPECT_EQ(0, treap.Size());
}


/**
 * Erase() Tests
 */
TEST_F(ImplicitTreapTest, ExpectAddOneRemoveOneThenTreeIsEmptySuccess) {
  ImplicitTreap<int> treap({1});

  EXPECT_EQ(1, treap.Size());
  treap.Erase(0);
  EXPECT_EQ(0, treap.Size());
  EXPECT_TRUE(treap.IsEmpty());
}

TEST_F(ImplicitTreapTest, ExpectThrowErrorWhenAccessExceedSizeSucess) {
  ImplicitTreap<int> treap({1, 2, 3, 6, 8});
  ASSERT_THROW(treap.Erase(5), std::out_of_range);
}

TEST_F(ImplicitTreapTest, ExpectThrowErrorWhenAccessLowerThanOneSucess) {
  ImplicitTreap<int> treap({1, 2, 3, 6, 8});
  ASSERT_THROW(treap.Erase(-1), std::out_of_range);
}

TEST_F(ImplicitTreapTest, ExpectNextElementAsCurrentValueAfterEraseSucess) {
  ImplicitTreap<int> treap({1, 2, 3, 6, 8});
  treap.Erase(0);
  EXPECT_EQ(2, treap.Get(0));
  EXPECT_EQ(4, treap.Size());
}

/**
 * Append() & Prepend() Tests
 */
TEST_F(ImplicitTreapTest, ExpectAppendElementsSucess) {
  ImplicitTreap<int> treap;
  treap.Append(0);
  treap.Append(1);
  treap.Append(2);

  std::vector<int> result = treap.ToVector();
  EXPECT_EQ(0, result[0]);
  EXPECT_EQ(1, result[1]);
  EXPECT_EQ(2, result[2]);
  EXPECT_EQ(3, treap.Size());
}

TEST_F(ImplicitTreapTest, ExpectPrependElementsSucess) {
  ImplicitTreap<int> treap;
  treap.Prepend(10);
  treap.Prepend(20);
  treap.Prepend(30);

  std::vector<int> result = treap.ToVector();
  EXPECT_EQ(30, result[0]);
  EXPECT_EQ(20, result[1]);
  EXPECT_EQ(10, result[2]);
  EXPECT_EQ(3, treap.Size());
}


/**
 * Set() & Get() Tests
 */
TEST_F(ImplicitTreapTest, ExpectSetAndGetElementSuccess) {
  ImplicitTreap<int> treap({1, 3, 7});
  treap.Set(0, 10);
  EXPECT_EQ(10, treap.Get(0));
  EXPECT_EQ(3, treap.Get(1));
  EXPECT_EQ(7, treap.Get(2));
}

TEST_F(ImplicitTreapTest, ExpectSetMethodThrowErrorWhenAccessLowerThanOneSucess) {
  ImplicitTreap<int> treap;
  ASSERT_THROW(treap.Set(-1, 5), std::out_of_range);
}

TEST_F(ImplicitTreapTest, ExpectSetMethodThrowErrorWhenAccessExceedSizeSucess) {
  ImplicitTreap<int> treap;
  ASSERT_THROW(treap.Set(1, 5), std::out_of_range);
}

TEST_F(ImplicitTreapTest, ExpectGetMethodThrowErrorWhenAccessLowerThanOneSucess) {
  ImplicitTreap<int> treap;
  ASSERT_THROW(treap.Get(-1), std::out_of_range);
}

TEST_F(ImplicitTreapTest, ExpectGetMethodThrowErrorWhenAccessExceedSizeSucess) {
  ImplicitTreap<int> treap;
  ASSERT_THROW(treap.Get(1), std::out_of_range);
}

/**
 * RangeQuery() Tests
 */
TEST_F(ImplicitTreapTest, ExpectRangeSumFrom1To5Success) {
  ImplicitTreap<int> treap({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  EXPECT_EQ(20, treap.RangeQuery(1, 5));
  EXPECT_EQ(9, treap.RangeQuery(8, 1));
}


/**
 * RangeUpdate() Tests
 */
TEST_F(ImplicitTreapTest, ExpectRangeUpdateFrom1To5Success) {
  ImplicitTreap<int> treap({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
  treap.RangeUpdate(1, 5, 1);
  treap.RangeUpdate(8, 1, 1);

  EXPECT_EQ(25, treap.RangeQuery(1, 5));
  EXPECT_EQ(10, treap.RangeQuery(8, 1));
}

} // namespace tree
} // namespace algorithms_archive
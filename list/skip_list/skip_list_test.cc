#include "skip_list.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace list {

class SkipListTest : public testing::Test {
 protected:
  virtual void SetUp() {}

  virtual void TearDown() {}
};

/**
* Insert() Tests
*/
TEST_F(SkipListTest, ExpectInsertElementsSuccess) {
  SkipList<int> slist(3);

  slist.Insert(3);
  slist.Insert(6);
  slist.Insert(7);
  slist.Insert(9);
  slist.Insert(12);
  slist.Insert(19);
  slist.Insert(17);
  slist.Insert(26);
  slist.Insert(21);
  slist.Insert(25);
}

/**
 * Search() Tests
 */
TEST_F(SkipListTest, ExpectSearchElementSuccess) {
  SkipList<int> slist(3);

  slist.Insert(3);
  slist.Insert(6);
  slist.Insert(7);
  slist.Insert(9);

  EXPECT_EQ(3, slist.Search(3)->key);
  EXPECT_EQ(6, slist.Search(6)->key);
  EXPECT_EQ(7, slist.Search(7)->key);
  EXPECT_EQ(9, slist.Search(9)->key);
}

TEST_F(SkipListTest, ExpectSearchNonMemberElementSuccess) {
  SkipList<int> slist(3);

  slist.Insert(3);
  slist.Insert(6);
  slist.Insert(7);
  slist.Insert(9);

  EXPECT_EQ(nullptr, slist.Search(1));
}

/**
 * Delete() Tests
 */
TEST_F(SkipListTest, ExpectDeleteElementSuccess) {
  SkipList<int> slist(3);

  slist.Insert(3);
  slist.Insert(6);
  slist.Insert(7);
  slist.Insert(9);

  slist.Delete(3);
  EXPECT_EQ(nullptr, slist.Search(3));
}

TEST_F(SkipListTest, ExpectDeleteNonMemberElementSuccess) {
  SkipList<int> slist(3);

  slist.Insert(3);
  slist.Insert(6);
  slist.Insert(7);
  slist.Insert(9);

  slist.Delete(1);
  EXPECT_EQ(3, slist.Search(3)->key);
  EXPECT_EQ(6, slist.Search(6)->key);
  EXPECT_EQ(7, slist.Search(7)->key);
  EXPECT_EQ(9, slist.Search(9)->key);

}

} // namespace list
} // namespace algorithms_archive
#include "radix_tree.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace string {

class RadixTreeTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/** AddWord() & Search() Testcases **/
TEST_F(RadixTreeTest, ExpectAddWordsReturnSuccess) {
  RadixTree radix_tree;

  radix_tree.AddWord("abc");
  radix_tree.AddWord("ab");
  radix_tree.AddWord("abd");

  EXPECT_TRUE(radix_tree.SearchWord("abc"));
  EXPECT_TRUE(radix_tree.SearchWord("ab"));
  EXPECT_TRUE(radix_tree.SearchWord("abd"));
}

TEST_F(RadixTreeTest, ExpectSearchReturnUnknownWordAsFalseSuccess) {
  RadixTree radix_tree;

  radix_tree.AddWord("abc");
  radix_tree.AddWord("ab");
  radix_tree.AddWord("abd");

  EXPECT_FALSE(radix_tree.SearchWord("zzz"));
  EXPECT_FALSE(radix_tree.SearchWord("a"));
}

/** DeleteWord() Testcases **/
TEST_F(RadixTreeTest, ExpectSearchReturnDeletedWordAsFalseSuccess) {
  RadixTree radix_tree;

  radix_tree.AddWord("abc");
  radix_tree.AddWord("ab");
  radix_tree.AddWord("abd");

  radix_tree.DeleteWord("abc");
  EXPECT_FALSE(radix_tree.SearchWord("abc"));
  EXPECT_TRUE(radix_tree.SearchWord("ab"));
  EXPECT_TRUE(radix_tree.SearchWord("abd"));

  radix_tree.DeleteWord("ab");
  EXPECT_FALSE(radix_tree.SearchWord("abc"));
  EXPECT_FALSE(radix_tree.SearchWord("ab"));
  EXPECT_TRUE(radix_tree.SearchWord("abd"));

  radix_tree.DeleteWord("abd");
  EXPECT_FALSE(radix_tree.SearchWord("abc"));
  EXPECT_FALSE(radix_tree.SearchWord("ab"));
  EXPECT_FALSE(radix_tree.SearchWord("abd"));
}

} // namespace string
} // namespace algorithms_archive
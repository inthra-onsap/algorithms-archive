#include "trie.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace string {

class TrieTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/** AddWord() & Search() Testcases **/
TEST_F(TrieTest, ExpectAddWordsReturnSuccess) {
  Trie trie;

  trie.AddWord("abc");
  trie.AddWord("ab");
  trie.AddWord("abd");

  EXPECT_TRUE(trie.Search("abc"));
  EXPECT_TRUE(trie.Search("ab"));
  EXPECT_TRUE(trie.Search("abd"));
}

TEST_F(TrieTest, ExpectSearchReturnUnknownWordAsFalseSuccess) {
  Trie trie;

  trie.AddWord("abc");
  trie.AddWord("ab");
  trie.AddWord("abd");

  EXPECT_FALSE(trie.Search("zzz"));
  EXPECT_FALSE(trie.Search("a"));
}

/** DeleteWord() Testcases **/
TEST_F(TrieTest, ExpectSearchReturnDeletedWordAsFalseSuccess) {
  Trie trie;

  trie.AddWord("abc");
  trie.AddWord("ab");
  trie.AddWord("abd");

  trie.DeleteWord("abc");
  EXPECT_FALSE(trie.Search("abc"));
  EXPECT_TRUE(trie.Search("ab"));
  EXPECT_TRUE(trie.Search("abd"));

  trie.DeleteWord("ab");
  EXPECT_FALSE(trie.Search("abc"));
  EXPECT_FALSE(trie.Search("ab"));
  EXPECT_TRUE(trie.Search("abd"));

  trie.DeleteWord("abd");
  EXPECT_FALSE(trie.Search("abc"));
  EXPECT_FALSE(trie.Search("ab"));
  EXPECT_FALSE(trie.Search("abd"));
}

} // namespace string
} // namespace algorithms_archive
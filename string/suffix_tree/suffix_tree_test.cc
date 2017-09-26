#include "suffix_tree.h"

#include <gtest/gtest.h>
#include <vector>

namespace algorithms_archive {
namespace string {

class SuffixTreeTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(SuffixTreeTest, ExpectSearchKeywordReturnResultSuccess) {
  SuffixTree s_tree("abcabxabcdabz");

  std::vector<int> result = s_tree.Search("abc");
  EXPECT_EQ(6, result[0]);
  EXPECT_EQ(0, result[1]);

  result = s_tree.Search("abx");
  EXPECT_EQ(3, result[0]);

  result = s_tree.Search("a");
  EXPECT_EQ(10, result[0]);
  EXPECT_EQ(3, result[1]);
  EXPECT_EQ(6, result[2]);
  EXPECT_EQ(0, result[3]);
}

TEST_F(SuffixTreeTest, ExpectSearchKeywordReturnEmptySuccess) {
  SuffixTree s_tree("abcabxabcdabz");

  std::vector<int> result = s_tree.Search("o");
  EXPECT_EQ(0, result.size());

  result = s_tree.Search("aby");
  EXPECT_EQ(0, result.size());
}

} // namespace string
} // namespace algorithms_archive
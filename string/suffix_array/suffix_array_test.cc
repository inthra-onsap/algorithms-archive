#include "suffix_array.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace string {

class SuffixArrayTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(SuffixArrayTest, ExpectGetSuffixArraySuccess){
  SuffixArray sa("banana");
  std::vector<int> result = sa.GetSuffixArray();

  EXPECT_EQ(5, result[0]);
  EXPECT_EQ(3, result[1]);
  EXPECT_EQ(1, result[2]);
  EXPECT_EQ(0, result[3]);
  EXPECT_EQ(4, result[4]);
  EXPECT_EQ(2, result[5]);
}

TEST_F(SuffixArrayTest, ExpectStringContainPatternSuccess){
  SuffixArray sa("banana");

  EXPECT_TRUE(sa.Contains("ba"));
}

TEST_F(SuffixArrayTest, ExpectReturnNumberOfOccurrencesSuccess){
  SuffixArray sa("banana");
  std::vector<int> lcp = sa.NumberOccurrence();

  EXPECT_EQ(0, lcp[0]);
  EXPECT_EQ(1, lcp[1]);
  EXPECT_EQ(3, lcp[2]);
  EXPECT_EQ(0, lcp[3]);
  EXPECT_EQ(0, lcp[4]);
  EXPECT_EQ(2, lcp[5]);
}

} // namespace string
} // namespace algorithms_archive
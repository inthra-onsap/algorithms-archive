#include "rabin_karp.h"

#include <gtest/gtest.h>
#include <vector>

namespace algorithms_archive {
namespace string {

class RabinKarpTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(RabinKarpTest, ExpectPatternMatchingSuccess){
  RabinKarp rk;
  std::vector<int> occur = rk.PatternMatching("AAA", "AAAAAA");

  EXPECT_EQ(0, occur[0]);
  EXPECT_EQ(1, occur[1]);
  EXPECT_EQ(2, occur[2]);
  EXPECT_EQ(3, occur[3]);
}

TEST_F(RabinKarpTest, ExpectPatternMatchingPrfixAndSuffixSuccess){
  RabinKarp rk;
  std::vector<int> occur = rk.PatternMatching("AB", "ABAAAB");

  EXPECT_EQ(0, occur[0]);
  EXPECT_EQ(4, occur[1]);
}

TEST_F(RabinKarpTest, ExpectPatternNoMatchingSuccess){
  RabinKarp rk;
  std::vector<int> occur = rk.PatternMatching("AAA", "BBBBBB");

  EXPECT_EQ(0, occur.size());
}

TEST_F(RabinKarpTest, ExpectPatternMatchingFail){
  RabinKarp rk;
  std::vector<int> occur = rk.PatternMatching("AAA", "A");

  EXPECT_EQ(0, occur.size());
}

} // namespace string
} // namespace algorithms_archive
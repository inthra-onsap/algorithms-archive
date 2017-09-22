#include "finite_automata.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace string {

class FiniteAutomataTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(FiniteAutomataTest, ExpectPatternMatchingSuccess) {
  FiniteAutomata fa;
  std::vector<int> occur = fa.PatternMatching("AAA", "AAAAAA");

  EXPECT_EQ(0, occur[0]);
  EXPECT_EQ(1, occur[1]);
  EXPECT_EQ(2, occur[2]);
  EXPECT_EQ(3, occur[3]);
}

TEST_F(FiniteAutomataTest, ExpectPatternMatchingPrfixAndSuffixSuccess) {
  FiniteAutomata fa;
  std::vector<int> occur = fa.PatternMatching("AB", "ABAAAB");

  EXPECT_EQ(0, occur[0]);
  EXPECT_EQ(4, occur[1]);
}

TEST_F(FiniteAutomataTest, ExpectPatternMatchingWholeStringSuccess) {
  FiniteAutomata fa;
  std::vector<int> occur = fa.PatternMatching("AB", "AB");

  EXPECT_EQ(0, occur[0]);
}

TEST_F(FiniteAutomataTest, ExpectPatternNoMatchingSuccess) {
  FiniteAutomata fa;
  std::vector<int> occur = fa.PatternMatching("AAA", "BBBBBB");

  EXPECT_EQ(0, occur.size());
}

TEST_F(FiniteAutomataTest, ExpectPatternMatchingFail) {
  FiniteAutomata fa;
  std::vector<int> occur = fa.PatternMatching("AAA", "A");

  EXPECT_EQ(0, occur.size());
}

} // namespace string
} // namespace algorithms_archive
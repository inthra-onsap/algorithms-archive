#include "knuth_morris_patt.h"

#include <gtest/gtest.h>
#include <vector>

namespace algorithms_archive {
namespace string {

class KnuthMorrisPattTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(KnuthMorrisPattTest, ExpectReturnOccurrencesSuccess) {
  KnuthMorrisPatt kmp("banana");
  const std::vector<int> occurrences = kmp.FindOccurences("na");

  EXPECT_EQ(2, occurrences.size());
  EXPECT_EQ(2, occurrences[0]);
  EXPECT_EQ(4, occurrences[1]);
}

}
}
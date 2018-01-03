#include "selection.h"

#include <vector>

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace order_statistic {

TEST(SelectionTest, ExpectPick2ndSmallestElementSuccess) {
  std::vector<int> data{2, 7, 1, 6, 4, 3};
  Selection<int> selection;

  EXPECT_EQ(2, selection.randomizedSelect(data, 0, data.size()-1, 2));
}

TEST(SelectionTest, ExpectPick5thSmallestElementButReturnFirstElementWhenTheIndexExceedArraySizeSuccess) {
  std::vector<int> data{1};
  Selection<int> selection;

  EXPECT_EQ(1, selection.randomizedSelect(data, 0, data.size()-1, 5));
}
} // namespace order_statistic
} // namespace algorithms_archive

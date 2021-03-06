#include "merge_sort.h"

#include <vector>

#include <gtest/gtest.h>

namespace algorithms_archive{
namespace sorting{
TEST(MergeSortTest, ExpectSortUnsortedArraySuccess) {
  std::vector<int> container{2, 7, 1, 6, 4, 3};
  MergeSort<int>(container);
  EXPECT_EQ(1, container[0]);
  EXPECT_EQ(2, container[1]);
  EXPECT_EQ(3, container[2]);
  EXPECT_EQ(4, container[3]);
  EXPECT_EQ(6, container[4]);
  EXPECT_EQ(7, container[5]);
}

TEST(MergeSortTest, ExpectSortSortedArraySuccess) {
  std::vector<int> container{1, 2, 3, 4, 5, 6};
  MergeSort<int>(container);
  EXPECT_EQ(1, container[0]);
  EXPECT_EQ(2, container[1]);
  EXPECT_EQ(3, container[2]);
  EXPECT_EQ(4, container[3]);
  EXPECT_EQ(5, container[4]);
  EXPECT_EQ(6, container[5]);
}
} // namespace sorting
} // namespace algorithms_archive
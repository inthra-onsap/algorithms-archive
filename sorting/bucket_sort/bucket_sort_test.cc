#include "bucket_sort.h"

#include <vector>

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace sorting {
TEST(BucketSortTest, ExpectSortUnsortedArrayISuccess) {
  std::vector<int> container{2, 7, 1, 6, 4, 3};
  BucketSort<int>(container);
  EXPECT_EQ(1, container[0]);
  EXPECT_EQ(2, container[1]);
  EXPECT_EQ(3, container[2]);
  EXPECT_EQ(4, container[3]);
  EXPECT_EQ(6, container[4]);
  EXPECT_EQ(7, container[5]);
}

TEST(BucketSortTest, ExpectSortSortedArrayIISuccess) {
  std::vector<int> container{10, 20, 30, 40, 50, 60, 11, 21, 31, 41, 51, 61};
  BucketSort<int>(container);
  EXPECT_EQ(10, container[0]);
  EXPECT_EQ(11, container[1]);
  EXPECT_EQ(20, container[2]);
  EXPECT_EQ(21, container[3]);
  EXPECT_EQ(30, container[4]);
  EXPECT_EQ(31, container[5]);
  EXPECT_EQ(40, container[6]);
  EXPECT_EQ(41, container[7]);
  EXPECT_EQ(50, container[8]);
  EXPECT_EQ(51, container[9]);
  EXPECT_EQ(60, container[10]);
  EXPECT_EQ(61, container[11]);
}

TEST(BucketSortTest, ExpectSortSortedArraySuccess) {
  std::vector<int> container{1, 2, 3, 4, 5, 6};
  BucketSort<int>(container);
  EXPECT_EQ(1, container[0]);
  EXPECT_EQ(2, container[1]);
  EXPECT_EQ(3, container[2]);
  EXPECT_EQ(4, container[3]);
  EXPECT_EQ(5, container[4]);
  EXPECT_EQ(6, container[5]);
}
} // namespace sorting
} // namespace algorithms_archive
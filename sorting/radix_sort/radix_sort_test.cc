#include "radix_sort.h"

#include <string>
#include <vector>

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace sorting {
TEST(RadixSortTest, ExpectSortUnsortedArraySuccess) {
  std::vector<std::string> container{"bat", "dog", "cat", "fox", "egg", "ant"};
  RadixSort<std::string>(container, 3);
  EXPECT_EQ("ant", container[0]);
  EXPECT_EQ("bat", container[1]);
  EXPECT_EQ("cat", container[2]);
  EXPECT_EQ("dog", container[3]);
  EXPECT_EQ("egg", container[4]);
  EXPECT_EQ("fox", container[5]);
}

TEST(RadixSortTest, ExpectSortSortedArraySuccess) {
  std::vector<std::string> container{"a", "b", "c", "d", "e", "f"};
  RadixSort<std::string>(container, 1);
  EXPECT_EQ("a", container[0]);
  EXPECT_EQ("b", container[1]);
  EXPECT_EQ("c", container[2]);
  EXPECT_EQ("d", container[3]);
  EXPECT_EQ("e", container[4]);
  EXPECT_EQ("f", container[5]);
}
} // namespace sorting
} // namespace algorithms_archive
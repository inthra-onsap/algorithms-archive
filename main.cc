#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  //testing::GTEST_FLAG(filter) = "SuffixArrayTest.ExpectReturnNumberOfOccurrencesSuccess";
  return RUN_ALL_TESTS();
}
#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  //testing::GTEST_FLAG(filter) = "RabinKarpTest.ExpectPatternMatchingSuccess";
  return RUN_ALL_TESTS();
}
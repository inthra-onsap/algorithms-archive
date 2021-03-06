#include "rope_string.h"

#include <string>

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace string {
class RopeStringTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};
/**
 * ToString() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringIsEmpty) {
  RopeString str;
  EXPECT_EQ("", str.ToString());
}

/**
 * Append() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringAppendSuccess) {
  RopeString str;
  str.Append("append1 ");
  str.Append("append2");
  EXPECT_EQ("append1 append2", str.ToString());
}

/**
 * Prepend() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringPrependSuccess) {
  RopeString str;
  str.Prepend("prepend1");
  str.Prepend("prepend2 ");
  EXPECT_EQ("prepend2 prepend1", str.ToString());
}

/**
 * Empty() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringEmptySuccess) {
  RopeString str;
  str.Prepend("prepend1");
  str.Empty();
  EXPECT_EQ("", str.ToString());
}

/**
 * Concat() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringConcatSuccess) {
  RopeString str1;
  RopeString str2;
  str1.Append("str1 ");
  str2.Append("str2");
  str1.Concat(str2);
  EXPECT_EQ("str1 str2", str1.ToString());
}

/**
 * Index() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringReturn1thCharSuccess) {
  RopeString str;
  str.Prepend("character");
  EXPECT_EQ('c', str.Index(1));
}
TEST_F(RopeStringTest, ExpectRopeStringReturn8thCharSuccess) {
  RopeString str;
  str.Prepend("character");
  EXPECT_EQ('r', str.Index(9));
}
TEST_F(RopeStringTest, ExpectRopeStringReturnNullCharSuccess) {
  RopeString str;
  str.Prepend("character");
  EXPECT_EQ('\0', str.Index(100));
}

/**
 * Delete() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringDeleteSuccess) {
  RopeString str;
  str.Append("character");
  str.Delete(3, 2);
  EXPECT_EQ("chacter", str.ToString());
}
TEST_F(RopeStringTest, ExpectRopeStringDeleteFirstPartSuccess) {
  RopeString str;
  str.Append("character");
  str.Delete(1, 3);
  EXPECT_EQ("racter", str.ToString());
}
TEST_F(RopeStringTest, ExpectRopeStringDeleteLastPartSuccess) {
  RopeString str;
  str.Append("character");
  str.Delete(8, 50);
  EXPECT_EQ("charact", str.ToString());
}

/**
 * Insert() Tests
 */
TEST_F(RopeStringTest, ExpectRopeStringInsertStringSuccess) {
  RopeString str;
  str.Insert(0, "insertion");
  EXPECT_EQ("insertion", str.ToString());
}
TEST_F(RopeStringTest, ExpectRopeStringInsertStringAnyPositionSuccess) {
  RopeString str;
  str.Insert(5, "insertion");
  EXPECT_EQ("insertion", str.ToString());
}
TEST_F(RopeStringTest, ExpectRopeStringInsertStringAt3rdPositionSuccess) {
  RopeString str;
  str.Insert(0, "insertion");
  str.Insert(3, " middle ");
  EXPECT_EQ("in middle sertion", str.ToString());
}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST_F(RopeStringTest, ExpectCopyAllElementsFromRopeStringSuccess) {
  RopeString str;
  str.Append("abc");
  RopeString new_str = str;
  EXPECT_EQ("abc", str.ToString());
  EXPECT_EQ("abc", new_str.ToString());
}

TEST_F(RopeStringTest, ExpectMoveAllElementsFromRopeStringSuccess) {
  RopeString str;
  str.Append("abc");
  RopeString new_str = std::move(str);
  EXPECT_EQ("abc", new_str.ToString());
}
} // namespace tree
} // namespace algorithms_archive
#include "rope_string.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
/**
 * ToString() tests
 */
TEST(RopeStringTest, ExpectRopeStringIsEmpty) {
  RopeString str;
  EXPECT_EQ("", str.ToString());
}

/**
 * Append() tests
 */
TEST(RopeStringTest, ExpectRopeStringAppendSuccess) {
  RopeString str;
  str.Append("append1 ");
  str.Append("append2");
  EXPECT_EQ("append1 append2", str.ToString());
}

/**
 * Prepend() tests
 */
TEST(RopeStringTest, ExpectRopeStringPrependSuccess) {
  RopeString str;
  str.Prepend("prepend1");
  str.Prepend("prepend2 ");
  EXPECT_EQ("prepend2 prepend1", str.ToString());
}

/**
 * Empty() tests
 */
TEST(RopeStringTest, ExpectRopeStringEmptySuccess) {
  RopeString str;
  str.Prepend("prepend1");
  str.Empty();
  EXPECT_EQ("", str.ToString());
}

/**
 * Concat() tests
 */
//TEST(RopeStringTest, ExpectRopeStringConcatSuccess){
//  RopeString str1;
//  RopeString str2;
//  str1.Prepend("str1 ");
//  str2.Prepend("str2");
//  str1.Concat(str2);
//  EXPECT_EQ("str1 str2", str1.ToString());
//}

/**
 * Index() tests
 */
TEST(RopeStringTest, ExpectRopeStringReturn1thCharSuccess) {
  RopeString str;
  str.Prepend("character");
  EXPECT_EQ('c', str.Index(1));
}
TEST(RopeStringTest, ExpectRopeStringReturn8thCharSuccess) {
  RopeString str;
  str.Prepend("character");
  EXPECT_EQ('r', str.Index(9));
}
TEST(RopeStringTest, ExpectRopeStringReturnNullCharSuccess) {
  RopeString str;
  str.Prepend("character");
  EXPECT_EQ('\0', str.Index(100));
}

/**
 * Delete() tests
 */
//TEST(RopeStringTest, ExpectRopeStringDeleteSuccess) {
//  RopeString str;
//  str.Prepend("character");
//  str.Delete(3,5);
//  EXPECT_EQ("chacter", str.ToString());
//}
//TEST(RopeStringTest, ExpectRopeStringDeleteFirstPartSuccess) {
//  RopeString str;
//  str.Prepend("character");
//  str.Delete(1,3);
//  EXPECT_EQ("racter", str.ToString());
//}
//TEST(RopeStringTest, ExpectRopeStringDeleteLastPartSuccess) {
//  RopeString str;
//  str.Prepend("character");
//  str.Delete(8,9);
//  EXPECT_EQ("charact", str.ToString());
//}

/**
 * Insert() tests
 */
//TEST(RopeStringTest, ExpectRopeStringInsertStringSuccess) {
//  RopeString str;
//  str.Insert(0, "insertion");
//  EXPECT_EQ("insertion", str.ToString());
//}
//TEST(RopeStringTest, ExpectRopeStringInsertStringSuccess) {
//  RopeString str;
//  str.Insert(5, "insertion");
//  EXPECT_EQ("insertion", str.ToString());
//}
//TEST(RopeStringTest, ExpectRopeStringInsertStringSuccess) {
//  RopeString str;
//  str.Insert(0, "insertion");
//  str.Insert(3, " middle ");
//  EXPECT_EQ("in middle sertion", str.ToString());
//}

/**
 * Copy Constructor & Move Constructor Tests
 */
TEST(RopeStringTest, ExpectCopyAllElementsFromRopeStringSuccess) {
  RopeString str;
  str.Append("abc");
  RopeString new_str = str;
  EXPECT_EQ("abc", str.ToString());
  EXPECT_EQ("abc", new_str.ToString());
}

TEST(RopeStringTest, ExpectMoveAllElementsFromRopeStringSuccess) {
  RopeString str;
  str.Append("abc");
  RopeString new_str = std::move(str);
  EXPECT_EQ("abc", new_str.ToString());
}
} // namespace tree
} // namespace algorithms_archive
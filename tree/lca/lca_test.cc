#include "lca.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {

class LcaTests : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(LcaTests, ExpectLcaReturnCommonAncestorSuccess) {
  Lca tree(13);

  tree.AddNode(1, 2);
  tree.AddNode(1, 3);
  tree.AddNode(1, 4);
  tree.AddNode(3, 5);
  tree.AddNode(3, 6);
  tree.AddNode(3, 7);
  tree.AddNode(6, 8);
  tree.AddNode(6, 9);
  tree.AddNode(7, 10);
  tree.AddNode(7, 11);
  tree.AddNode(10, 12);
  tree.AddNode(10, 13);

  EXPECT_EQ(3, tree.CommonAncestorOf(5, 11));
  EXPECT_EQ(7, tree.CommonAncestorOf(10, 11));
  EXPECT_EQ(1, tree.CommonAncestorOf(1, 1));
}

} // namespace tree
} // namespace algorithms_archive
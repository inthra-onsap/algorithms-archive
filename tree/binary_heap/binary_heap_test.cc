#include "binary_heap.h"

#include <vector>

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
class BinaryHeapTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};

/**
 * IsEmpty() Tests
 */
TEST_F(BinaryHeapTest, ExpectEmptyHeapSuccess) {
  BinaryHeap<int> heap;
  EXPECT_TRUE(heap.IsEmpty());
}

TEST_F(BinaryHeapTest, ExpectNotEmptyHeapSuccess) {
  BinaryHeap<int> heap;
  heap.Insert(15);
  EXPECT_FALSE(heap.IsEmpty());
}

/**
 * Empty() Tests
 */
TEST_F(BinaryHeapTest, ExpectClearHeapSuccess) {
  BinaryHeap<int> heap;
  heap.Insert(10);
  heap.Empty();
  EXPECT_TRUE(heap.IsEmpty());
}

/**
 * BuildHeap() & FindMin() & DeleteMin() Tests
 */
TEST_F(BinaryHeapTest, ExpectBuildHeapSuccess) {
  std::vector<int> v{6, 16, 7, 237, 171, 71, 3};
  BinaryHeap<int> heap(v);
  EXPECT_EQ(3, heap.FindMin());
}

TEST_F(BinaryHeapTest, ExpectDeleteMinSuccess) {
  std::vector<int> v{6, 16, 7, 237, 171, 71, 3};
  BinaryHeap<int> heap(v);
  heap.DeleteMin();
  EXPECT_EQ(6, heap.FindMin());
}

/**
 * Insert() Tests
 */
TEST_F(BinaryHeapTest, ExpectInsertElementsExceedTheSizeSuccess) {
  BinaryHeap<int> heap(2);
  heap.Insert(5);
  heap.Insert(6);
  heap.Insert(7);
  EXPECT_EQ(4, heap.tree.size());
  EXPECT_EQ(5, heap.tree[1]);
  EXPECT_EQ(6, heap.tree[2]);
  EXPECT_EQ(7, heap.tree[3]);
}

TEST_F(BinaryHeapTest, ExpectFindMinAndDeleteMinAllElementsSuccess) {
  BinaryHeap<int> heap;
  heap.Insert(5);
  heap.Insert(6);
  heap.Insert(7);

  EXPECT_EQ(5, heap.FindMin());
  heap.DeleteMin();
  EXPECT_EQ(6, heap.FindMin());
  heap.DeleteMin();
  EXPECT_EQ(7, heap.FindMin());
  heap.DeleteMin();
  EXPECT_TRUE(heap.IsEmpty());
}

} // namespace tree
} // namespace algorithms_archive
#include "leftist_heap.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace tree {
class LeftistHeapTest : public testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/**
 * Empty() & IsEmpty() Tests
 */
TEST_F(LeftistHeapTest, ExpectIsEmptySuccess) {
  LeftistHeap<int> heap;
  EXPECT_TRUE(heap.IsEmpty());
}

TEST_F(LeftistHeapTest, ExpectIsNotEmptySuccess) {
  LeftistHeap<int> heap;
  heap.Insert(1);
  EXPECT_FALSE(heap.IsEmpty());
}

TEST_F(LeftistHeapTest, ExpectHeapEmptyAfterEmptyCalledSuccess) {
  LeftistHeap<int> heap;
  heap.Insert(1);
  heap.Empty();
  EXPECT_TRUE(heap.IsEmpty());
}

/**
 * FindMin() & DeleteMin() Tests
 */
TEST_F(LeftistHeapTest, ExpectFindMinSuccess) {
  LeftistHeap<int> heap;
  heap.Insert(5);
  heap.Insert(1);
  heap.Insert(8);
  EXPECT_EQ(1, heap.FindMin());
}

TEST_F(LeftistHeapTest, ExpectDeleteMinSuccess) {
  LeftistHeap<int> heap;
  heap.Insert(5);
  heap.Insert(1);
  heap.Insert(8);
  heap.DeleteMin();
  EXPECT_EQ(5, heap.FindMin());
}

/**
 * Merge() Tests
 */
TEST_F(LeftistHeapTest, ExpectMergeHeapSuccess) {
  LeftistHeap<int> heap1;
  LeftistHeap<int> heap2;
  heap1.Insert(5);
  heap1.Insert(1);
  heap2.Insert(4);
  heap2.Insert(10);
  heap1.Merge(heap2);

  EXPECT_TRUE(heap2.IsEmpty());
  EXPECT_EQ(1, heap1.FindMin());
  heap1.DeleteMin();
  EXPECT_EQ(4, heap1.FindMin());
  heap1.DeleteMin();
  EXPECT_EQ(5, heap1.FindMin());
  heap1.DeleteMin();
  EXPECT_EQ(10, heap1.FindMin());
  heap1.DeleteMin();
  EXPECT_TRUE(heap1.IsEmpty());
}

TEST_F(LeftistHeapTest, ExpectMergeSameHeapSuccess) {
  LeftistHeap<int> heap;
  heap.Insert(5);
  heap.Insert(1);
  heap.Merge(heap);
  heap.DeleteMin();
  heap.DeleteMin();
  EXPECT_TRUE(heap.IsEmpty());
}

} // namespace tree
} // namespace algorithms_archive
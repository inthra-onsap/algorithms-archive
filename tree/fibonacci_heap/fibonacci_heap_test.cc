#include <gtest/gtest.h>
#include "fibonacci_heap.h"

namespace algorithms_archive {
namespace tree {
class FibonacciHeapTest : public testing::Test {
 protected:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

/**
 * IsEmpty() & Empty() Tests
 */
TEST_F(FibonacciHeapTest, ExpectTreeEmptySuccess) {
  FibonacciHeap<int> fibo_heap;
  EXPECT_TRUE(fibo_heap.IsEmpty());
}

TEST_F(FibonacciHeapTest, ExpectTreeNotEmptySuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(1);
  EXPECT_FALSE(fibo_heap.IsEmpty());
}

TEST_F(FibonacciHeapTest, ExpectTreeEmptyAfterEmptyCalledSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(1);
  fibo_heap.Empty();
  EXPECT_TRUE(fibo_heap.IsEmpty());
}

/**
 * GetMinimum() & ExtractMin() Tests
 */
TEST_F(FibonacciHeapTest, ExpectGetMinimumSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(1);
  fibo_heap.Insert(3);
  fibo_heap.Insert(5);
  EXPECT_EQ(1, fibo_heap.GetMinimum());
}

TEST_F(FibonacciHeapTest, ExpectExtractMinimumSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(1);
  fibo_heap.Insert(3);
  fibo_heap.Insert(5);
  fibo_heap.ExtractMin();
  EXPECT_EQ(3, fibo_heap.GetMinimum());
}

/**
 * Delete() & Find() Tests
 */
TEST_F(FibonacciHeapTest, ExpectDeleteNodeSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(1);
  fibo_heap.Insert(3);
  fibo_heap.Insert(5);
  fibo_heap.Insert(7);
  fibo_heap.Insert(8);
  fibo_heap.Insert(10);
  fibo_heap.Insert(11);

  fibo_heap.Delete(fibo_heap.Find(11));
  EXPECT_EQ(nullptr, fibo_heap.Find(11));
  EXPECT_EQ(1, fibo_heap.GetMinimum());

  fibo_heap.Delete(fibo_heap.Find(1));
  EXPECT_EQ(nullptr, fibo_heap.Find(1));
  EXPECT_EQ(3, fibo_heap.GetMinimum());

  fibo_heap.Delete(fibo_heap.Find(3));
  EXPECT_EQ(nullptr, fibo_heap.Find(3));
  EXPECT_EQ(5, fibo_heap.GetMinimum());

  fibo_heap.Delete(fibo_heap.Find(5));
  EXPECT_EQ(nullptr, fibo_heap.Find(5));
  EXPECT_EQ(7, fibo_heap.GetMinimum());

  fibo_heap.Delete(fibo_heap.Find(7));
  EXPECT_EQ(nullptr, fibo_heap.Find(7));
  EXPECT_EQ(8, fibo_heap.GetMinimum());

  fibo_heap.Delete(fibo_heap.Find(8));
  EXPECT_EQ(nullptr, fibo_heap.Find(8));
  EXPECT_EQ(10, fibo_heap.GetMinimum());

  fibo_heap.Delete(fibo_heap.Find(10));
  EXPECT_EQ(nullptr, fibo_heap.Find(10));
  EXPECT_TRUE(fibo_heap.IsEmpty());
}

/**
 * DecreaseKey() & Find() Tests
 */
TEST_F(FibonacciHeapTest, ExpectDecreaseKeyAsFirstMininumSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(3);
  fibo_heap.Insert(5);
  fibo_heap.Insert(7);
  fibo_heap.Insert(8);
  fibo_heap.Insert(10);
  fibo_heap.Insert(11);

  fibo_heap.DecreaseKey(fibo_heap.Find(11), 1);
  EXPECT_EQ(nullptr, fibo_heap.Find(11));
  EXPECT_EQ(1, fibo_heap.GetMinimum());
}

TEST_F(FibonacciHeapTest, ExpectDecreaseKeyAsSecondMininumSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(3);
  fibo_heap.Insert(5);
  fibo_heap.Insert(7);
  fibo_heap.Insert(8);
  fibo_heap.Insert(10);
  fibo_heap.Insert(11);

  fibo_heap.DecreaseKey(fibo_heap.Find(11), 4);
  EXPECT_EQ(nullptr, fibo_heap.Find(11));
  EXPECT_EQ(3, fibo_heap.ExtractMin());
  EXPECT_EQ(4, fibo_heap.ExtractMin());
}

TEST_F(FibonacciHeapTest, ExpectDecreaseKeyAndCascadingCutSuccess) {
  FibonacciHeap<int> fibo_heap;
  fibo_heap.Insert(1);
  fibo_heap.Insert(3);
  fibo_heap.Insert(5);
  fibo_heap.Insert(7);
  fibo_heap.Insert(8);
  fibo_heap.Insert(10);
  fibo_heap.Insert(11);
  fibo_heap.Insert(12);
  fibo_heap.Insert(13);
  fibo_heap.Insert(14);
  fibo_heap.Insert(15);
  EXPECT_EQ(1, fibo_heap.ExtractMin());

  fibo_heap.DecreaseKey(fibo_heap.Find(12), 1);
  EXPECT_EQ(1, fibo_heap.ExtractMin());
  fibo_heap.DecreaseKey(fibo_heap.Find(14), 1);
  EXPECT_EQ(1, fibo_heap.ExtractMin());
  fibo_heap.DecreaseKey(fibo_heap.Find(13), 1);
  EXPECT_EQ(1, fibo_heap.ExtractMin());
}

/**
 * Union() Tests
 */
TEST_F(FibonacciHeapTest, ExpectUnion2HeapsSuccess) {
  FibonacciHeap<int> fibo_heap1;
  FibonacciHeap<int> fibo_heap2;
  fibo_heap1.Insert(1);
  fibo_heap1.Insert(2);
  fibo_heap1.Insert(3);
  fibo_heap2.Insert(10);
  fibo_heap2.Insert(11);
  fibo_heap2.Insert(12);
  fibo_heap2.Insert(13);
  fibo_heap2.Insert(14);
  fibo_heap2.Insert(15);
  fibo_heap1.Union(fibo_heap2);

  EXPECT_TRUE(fibo_heap2.IsEmpty());
  EXPECT_EQ(1, fibo_heap1.ExtractMin());
  EXPECT_EQ(2, fibo_heap1.ExtractMin());
  EXPECT_EQ(3, fibo_heap1.ExtractMin());
  EXPECT_EQ(10, fibo_heap1.ExtractMin());
  EXPECT_EQ(11, fibo_heap1.ExtractMin());
  EXPECT_EQ(12, fibo_heap1.ExtractMin());
  EXPECT_EQ(13, fibo_heap1.ExtractMin());
  EXPECT_EQ(14, fibo_heap1.ExtractMin());
  EXPECT_EQ(15, fibo_heap1.ExtractMin());
  EXPECT_TRUE(fibo_heap1.IsEmpty());
}

} // namespace tree
} // namespace algorithms_archive
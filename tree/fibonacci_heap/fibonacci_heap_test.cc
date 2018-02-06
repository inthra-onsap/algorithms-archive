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


///**
// * Merge() Tests
// */
//TEST_F(FibonacciHeapTest, ExpectMergeTreeSuccess) {
//  BinomialTree<int> binomial_tree1;
//  BinomialTree<int> binomial_tree2;
//  binomial_tree1.Insert(1);
//  binomial_tree1.Insert(2);
//  binomial_tree1.Insert(3);
//  binomial_tree2.Insert(10);
//  binomial_tree2.Insert(11);
//  binomial_tree2.Insert(12);
//  binomial_tree2.Insert(13);
//  binomial_tree2.Insert(14);
//  binomial_tree2.Insert(15);
//  binomial_tree1.Merge(binomial_tree2);
//
//  EXPECT_TRUE(binomial_tree2.IsEmpty());
//  EXPECT_EQ(1, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(2, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(3, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(10, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(11, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(12, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(13, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(14, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_EQ(15, binomial_tree1.FindMin());
//  binomial_tree1.DeleteMin();
//  EXPECT_TRUE(binomial_tree1.IsEmpty());
//}
//
///**
// * Copy Constructor & Move Constructor Tests
// */
//TEST_F(FibonacciHeapTest, ExpectCopyConstructorSuccess) {
//  BinomialTree<int> binomial_tree;
//  binomial_tree.Insert(1);
//  binomial_tree.Insert(3);
//  binomial_tree.Insert(5);
//  BinomialTree<int> binomial_tree2 = binomial_tree;
//  EXPECT_EQ(1, binomial_tree2.FindMin());
//  binomial_tree2.DeleteMin();
//  EXPECT_EQ(3, binomial_tree2.FindMin());
//  binomial_tree2.DeleteMin();
//  EXPECT_EQ(5, binomial_tree2.FindMin());
//  binomial_tree2.DeleteMin();
//  EXPECT_TRUE(binomial_tree2.IsEmpty());
//}
//
//TEST_F(FibonacciHeapTest, ExpectMoveConstructorSuccess) {
//  BinomialTree<int> binomial_tree;
//  binomial_tree.Insert(1);
//  binomial_tree.Insert(3);
//  binomial_tree.Insert(5);
//  BinomialTree<int> binomial_tree2 = std::move(binomial_tree);
//  EXPECT_EQ(1, binomial_tree2.FindMin());
//  binomial_tree2.DeleteMin();
//  EXPECT_EQ(3, binomial_tree2.FindMin());
//  binomial_tree2.DeleteMin();
//  EXPECT_EQ(5, binomial_tree2.FindMin());
//  binomial_tree2.DeleteMin();
//  EXPECT_TRUE(binomial_tree2.IsEmpty());
//}

} // namespace tree
} // namespace algorithms_archive
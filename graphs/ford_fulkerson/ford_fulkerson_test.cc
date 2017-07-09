#include "ford_fulkerson.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace graphs {

class FordFulkersonTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(FordFulkersonTest, ExpectReturnMaxFlowSuccess) {
  FordFulkerson graph(7);
  graph.AddEdge(0, 1, 3);
  graph.AddEdge(0, 3, 3);
  graph.AddEdge(1, 2, 4);
  graph.AddEdge(2, 0, 3);
  graph.AddEdge(2, 3, 1);
  graph.AddEdge(2, 4, 2);
  graph.AddEdge(3, 4, 2);
  graph.AddEdge(3, 5, 6);
  graph.AddEdge(4, 6, 1);
  graph.AddEdge(5, 6, 9);
  EXPECT_EQ(5, graph.FindMaxFlow(0, 6));
}

} // namespace graphs
} // namespace algorithms_archive
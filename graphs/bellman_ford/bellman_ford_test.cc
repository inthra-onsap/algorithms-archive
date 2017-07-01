#include "bellman_ford.h"

#include <gtest/gtest.h>
#include <vector>

namespace algorithms_archive {
namespace graphs {

class BellmanFordTest : public testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(BellmanFordTest, ExpectReturnShortestPathSuccess) {
  BellmanFord graph(5);

  graph.AddEdge(0, 1, 1);
  graph.AddEdge(1, 2, 1);
  graph.AddEdge(2, 3, 1);
  graph.AddEdge(3, 4, 1);
  graph.AddEdge(4, 0, 1);
  graph.AddEdge(0, 4, 2);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 4);
  EXPECT_EQ(0, shortest_path[0]);
  EXPECT_EQ(4, shortest_path[1]);
}

TEST_F(BellmanFordTest, ExpectReturnShortestPathWithNegativeEdgeNoCycleSuccess) {
  BellmanFord graph(5);

  graph.AddEdge(0, 1, 1);
  graph.AddEdge(1, 2, 1);
  graph.AddEdge(2, 3, 1);
  graph.AddEdge(3, 4, 1);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 4);
  EXPECT_EQ(0, shortest_path[0]);
  EXPECT_EQ(1, shortest_path[1]);
  EXPECT_EQ(2, shortest_path[2]);
  EXPECT_EQ(3, shortest_path[3]);
  EXPECT_EQ(4, shortest_path[4]);
}

TEST_F(BellmanFordTest, ExpectReturnEmptyPathWithNegativeCycleSuccess) {
  BellmanFord graph(6);

  graph.AddEdge(0, 1, 1);
  graph.AddEdge(1, 2, 1);
  graph.AddEdge(2, 3, 1);
  graph.AddEdge(3, 4, 1);
  graph.AddEdge(3, 5, 1);
  graph.AddEdge(5, 2, -5);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 4);
  EXPECT_EQ(0, shortest_path.size());
}

TEST_F(BellmanFordTest, ExpectOneVertexGraphReturnShortestPathSuccess) {
  BellmanFord graph(1);

  graph.AddEdge(0, 0, 1);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 0);
  EXPECT_EQ(0, shortest_path[0]);
}

} // namespace graphs
} // namespace algorithms_archive
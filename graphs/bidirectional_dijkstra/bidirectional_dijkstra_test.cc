#include "bidirectional_dijkstra.h"

#include <gtest/gtest.h>
#include <vector>

namespace algorithms_archive {
namespace graphs {

class BidirectionalDijkstraTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(BidirectionalDijkstraTest, ExpectNoRoutesFromSourceToTerminalThenReturnEmptyPathSuccess) {
  BidirectionalDijkstra graph(4);

  graph.AddEdge(0, 1, 1);
  graph.AddEdge(2, 3, 1);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 3);
  EXPECT_EQ(0, shortest_path.size());
}

TEST_F(BidirectionalDijkstraTest, ExpectReturnShortestPathSuccess) {
  BidirectionalDijkstra graph(6);

  graph.AddEdge(0, 1, 4);
  graph.AddEdge(0, 3, 2);
  graph.AddEdge(0, 4, 1);
  graph.AddEdge(1, 2, 8);
  graph.AddEdge(1, 4, 5);
  graph.AddEdge(1, 5, 6);
  graph.AddEdge(2, 5, 1);
  graph.AddEdge(3, 4, 3);
  graph.AddEdge(4, 5, 9);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 5);
  EXPECT_EQ(0, shortest_path[0]);
  EXPECT_EQ(1, shortest_path[1]);
  EXPECT_EQ(5, shortest_path[2]);
}

TEST_F(BidirectionalDijkstraTest, ExpectOneVertexGraphReturnShortestPathSuccess) {
  BidirectionalDijkstra graph(1);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 0);
  EXPECT_EQ(0, shortest_path.size());
}

} // namespace graphs
} // namespace algorithms_archive
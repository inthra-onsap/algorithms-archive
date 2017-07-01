#include "dijkstra.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace graphs {
class DijkstraTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(DijkstraTest, ExpectReturnShortestPathSuccess) {
  Dijkstra graph(5);

  graph.AddEdge(0, 1, 2);
  graph.AddEdge(0, 4, 5);
  graph.AddEdge(1, 2, 3);
  graph.AddEdge(4, 3, 5);
  graph.AddEdge(3, 2, 1);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 2);
  EXPECT_EQ(0, shortest_path[0]);
  EXPECT_EQ(1, shortest_path[1]);
  EXPECT_EQ(2, shortest_path[2]);
}

TEST_F(DijkstraTest, ExpectEmptyGraphReturnEmptySuccess) {
  Dijkstra graph{};

  std::vector<int> shortest_path = graph.GetShortestPath(0, 2);
  EXPECT_EQ(0, shortest_path.size());
}

TEST_F(DijkstraTest, ExpectOneVertexGraphReturnShortestPathSuccess) {
  Dijkstra graph(1);

  graph.AddEdge(0, 0, 1);

  std::vector<int> shortest_path = graph.GetShortestPath(0, 0);
  EXPECT_EQ(0, shortest_path[0]);
}

} // namespace graphs
} // namespace algorithms_archive
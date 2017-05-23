#include "graph_topological_sort.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace graphs {
class GraphTopologicalSortTest : public testing::Test {
  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(GraphTopologicalSortTest, ExpectDagTopologicalSortSuccess){
  GraphTopologicalSort graph(5);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 4);
  const std::vector<int> sorted_vertices = graph.TopologicalSort();
  EXPECT_EQ(0, sorted_vertices[0]);
  EXPECT_EQ(1, sorted_vertices[1]);
  EXPECT_EQ(2, sorted_vertices[2]);
  EXPECT_EQ(3, sorted_vertices[3]);
  EXPECT_EQ(4, sorted_vertices[4]);
}

TEST_F(GraphTopologicalSortTest, ExpectCyclicGraphTopologicalSortFail){
  GraphTopologicalSort graph(5);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 4);
  graph.AddEdge(4, 0);
  const std::vector<int> sorted_vertices = graph.TopologicalSort();
  EXPECT_EQ(0, sorted_vertices.size());
}

} // namespace graphs
} // namespace algorithms_archive
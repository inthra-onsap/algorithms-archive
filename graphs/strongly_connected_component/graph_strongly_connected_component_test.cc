
#include "graph_strongly_connected_component.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace graphs {
class GraphStronglyConnectedComponentTest : public testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(GraphStronglyConnectedComponentTest, ExpectReturnNumberOfStronglyConnectedComponentCaseISuccess) {
  GraphStronglyConnectedComponent graph(4);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);

  EXPECT_EQ(4, graph.GetTotalComponents());
}

TEST_F(GraphStronglyConnectedComponentTest, ExpectReturnNumberOfStronglyConnectedComponentCaseIISuccess) {
  GraphStronglyConnectedComponent graph(9);
  graph.AddEdge(0, 1);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 3);
  graph.AddEdge(2, 4);
  graph.AddEdge(3, 0);
  graph.AddEdge(4, 5);
  graph.AddEdge(5, 6);
  graph.AddEdge(6, 4);
  graph.AddEdge(7, 6);
  graph.AddEdge(7, 8);

  EXPECT_EQ(4, graph.GetTotalComponents());
}

}
}
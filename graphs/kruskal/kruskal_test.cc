#include <gtest/gtest.h>
#include "kruskal.h"

namespace algorithms_archive {
namespace graphs {

class KruskalTest : public testing::Test {
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(KruskalTest, ExpectReturnTheMininumSpaningValueSuccess) {
  Kruskal graph(6);

  graph.AddEdge(0, 1, 4);
  graph.AddEdge(0, 3, 2);
  graph.AddEdge(0, 4, 1);
  graph.AddEdge(1, 2, 8);
  graph.AddEdge(1, 4, 5);
  graph.AddEdge(1, 5, 6);
  graph.AddEdge(2, 5, 1);
  graph.AddEdge(3, 4, 3);
  graph.AddEdge(4, 5, 9);

  EXPECT_EQ(14, graph.GetMinimumSpaningValue());
}

} // namespace graphs
} // namespace algorithms_archive
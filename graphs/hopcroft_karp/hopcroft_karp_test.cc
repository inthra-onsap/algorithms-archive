#include "hopcroft_karp.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace graphs {

class HopcroftKarpTest : public testing::Test {
 public:
  virtual void SetUp() {}
  virtual void TearDown() {}
};

TEST_F(HopcroftKarpTest, ExpectReturnMaxFlowSuccess) {
  HopcroftKarp bp_graph(4, 4);
  bp_graph.addEdge(1, 2);
  bp_graph.addEdge(1, 3);
  bp_graph.addEdge(2, 1);
  bp_graph.addEdge(3, 2);
  bp_graph.addEdge(4, 2);
  bp_graph.addEdge(4, 4);
  EXPECT_EQ(4, bp_graph.getMaxFlow());
}

} // namespace graphs
} // namespace algorithms_archive
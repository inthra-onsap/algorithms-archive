#ifndef ALGORITHMS_ARCHIVE_FORD_FULKERSON_H_
#define ALGORITHMS_ARCHIVE_FORD_FULKERSON_H_

#include <queue>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

namespace algorithms_archive {
namespace graphs {

class FordFulkerson {
 public:
  FordFulkerson(int size_) : size{size_} {
    graph.resize(size, std::vector<int>(size, 0));
  }

  void AddEdge(int vertex1, int vertex2, int weight);

  int FindMaxFlow(int source, int sink);
 private:
  int size;
  std::vector<std::vector<int>> graph;

  bool IsSinkReachable(
      std::vector<std::vector<std::pair<int, int>>> residual_graph,
      std::vector<int> &prev, int source, int sink);

  std::vector<std::vector<std::pair<int, int>>> GetResidualGraph(std::vector<std::vector<int>> &flow_graph);

  int ProcessAugmentingPath(std::vector<std::vector<int>> &flow_graph, std::vector<int> &prev, int sink);
};

} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_FORD_FULKERSON_H_

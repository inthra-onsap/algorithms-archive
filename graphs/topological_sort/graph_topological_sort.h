#ifndef ALGORITHMS_ARCHIVE_GRAPHTOPOLOGICALSORT_H
#define ALGORITHMS_ARCHIVE_GRAPHTOPOLOGICALSORT_H

#include <vector>
#include <algorithm>

namespace algorithms_archive {
namespace graphs {
class GraphTopologicalSort {
 public:
  GraphTopologicalSort(const int num_node_) {
    graph.resize(num_node_, std::vector<int>());
  }

  /**
   * 0 based-index
   * @param int vertex1
   * @param int vertex2
   */
  void AddEdge(int vertex1, int vertex2);

  const std::vector<int> TopologicalSort();
 private:
  std::vector<std::vector<int>> graph;

  bool IsCyclicGraph(std::vector<bool> &visited, std::vector<bool> &visiting, int vertex);

  void Bfs(std::vector<int> &sorted, std::vector<bool> &visited, int vertex);
};
} // namespace graphs
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_GRAPHTOPOLOGICALSORT_H

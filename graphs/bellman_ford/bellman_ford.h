#ifndef ALGORITHMS_ARCHIVE_BELLMANFORD_H_
#define ALGORITHMS_ARCHIVE_BELLMANFORD_H_

#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

namespace algorithms_archive {
namespace graphs {

class BellmanFord {
 public:
  BellmanFord(int num_vertices_) : num_vertices{num_vertices_} {
    graph.resize(num_vertices, std::vector<std::pair<int, int>>());
  }

  void AddEdge(int vertex_1, int vertex_2, int weight);

  std::vector<int> GetShortestPath(int source, int terminal);

 private:
  int num_vertices;
  std::vector<std::vector<std::pair<int, int>>> graph;
};

} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_BELLMANFORD_H_

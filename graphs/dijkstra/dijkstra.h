#ifndef ALGORITHMS_ARCHIVE_DIJKSTRA_H_
#define ALGORITHMS_ARCHIVE_DIJKSTRA_H_

#include <vector>
#include <set>
#include <utility>
#include <climits>
#include <algorithm>

namespace algorithms_archive {
namespace graphs {
class Dijkstra {
 public:
  Dijkstra(int num_vertices_ = 0) : num_vertices{num_vertices_} {
    adj_list.resize(num_vertices, std::vector<std::pair<int, int>>());
  };

  ~Dijkstra() {}

  void AddEdge(int vertex_1, int vertex_2, int weight);

  std::vector<int> GetShortestPath(int source, int sink);

 private:
  int num_vertices;
  std::vector<std::vector<std::pair<int, int>>> adj_list;
};
} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_DIJKSTRA_H_

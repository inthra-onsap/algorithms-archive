#ifndef ALGORITHMS_ARCHIVE_BIDIRECTIONAL_DIJKSTRA_H_
#define ALGORITHMS_ARCHIVE_BIDIRECTIONAL_DIJKSTRA_H_

#include "../utility/graph_min_heap.h"

#include <vector>
#include <utility>
#include <climits>
#include <algorithm>

namespace algorithms_archive {
namespace graphs {

class BidirectionalDijkstra {
 public:
  BidirectionalDijkstra(int num_vertex_) : num_vetex{num_vertex_} {
    graph.resize(num_vetex, std::vector<std::pair<int, int>>());
  }

  void AddEdge(int vertex1, int vertex2, int weight);

  std::vector<int> GetShortestPath(int source, int terminal);
 private:
  int num_vetex;
  std::vector<std::vector<std::pair<int, int>>> graph;

  std::vector<std::vector<std::pair<int, int>>> GetReverseGraph();

  void Relax(std::vector<std::vector<std::pair<int, int>>> &graph,
             int vertex,
             std::vector<int> &dist,
             std::vector<int> &prev,
             std::vector<bool> &visited,
             GraphMinHeap<int> &min_heap);

  std::vector<int> ProcessShortestPath(int source,
                                       int terminal,
                                       std::vector<int> &dist,
                                       std::vector<int> &dist_reserve,
                                       std::vector<int> &prev,
                                       std::vector<int> &prev_reserve,
                                       std::vector<bool> &visited,
                                       std::vector<bool> &visited_reserve);
};

} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_BIDIRECTIONAL_DIJKSTRA_H_

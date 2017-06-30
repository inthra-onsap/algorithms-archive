#ifndef ALGORITHMS_ARCHIVE_KRUSKAL_H
#define ALGORITHMS_ARCHIVE_KRUSKAL_H

#include "../../disjoint_sets/disjoint_sets/disjoint_sets.h"
#include "../utility/graph_min_heap.h"

#include <vector>
#include <utility>

namespace algorithms_archive {
namespace graphs {

class Kruskal {
 public:
  Kruskal(int num_vertex_) : num_vertex{num_vertex_} {
    graph.resize(num_vertex, std::vector<std::pair<int, int>>());
  }

  void AddEdge(int vertex_1, int vertex_2, int weight);

  int GetMinimumSpaningValue();

 private:
  int num_vertex;
  std::vector<std::vector<std::pair<int, int>>> graph;
};

} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_KRUSKAL_H

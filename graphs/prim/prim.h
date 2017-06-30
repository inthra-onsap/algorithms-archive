#ifndef ALGORITHMS_ARCHIVE_PRIM_H
#define ALGORITHMS_ARCHIVE_PRIM_H

#include "../utility/graph_min_heap.h"

#include <vector>
#include <utility>
#include <cstdlib>

namespace algorithms_archive {
namespace graphs {

class Prim {
 public:
  Prim(int num_vertex_) : num_vertex{num_vertex_} {
    graph.resize(num_vertex, std::vector<std::pair<int, int>>());
  }

  void AddEdge(int vertex1, int vertex2, int weight);

  int GetMinimumSpaningValue();

 private:
  int num_vertex;
  std::vector<std::vector<std::pair<int, int>>> graph;
};

} // namespace graphs
} // namespace algorithms_archive


#endif //ALGORITHMS_ARCHIVE_PRIM_H

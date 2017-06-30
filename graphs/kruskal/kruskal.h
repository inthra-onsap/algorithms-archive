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

  void AddEdge(int vertex_1, int vertex_2, int weight) {
    graph[vertex_1].push_back(std::make_pair(vertex_2, weight));
  }

  int GetMinimumSpaningValue() {
    disjoint_sets::DisjointSets disj_set(num_vertex);
    int min_spaining_value = 0;
    GraphMinHeap<std::pair<int, int>> min_heap;

    for (int i = 0; i < num_vertex; ++i) {
      for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
        min_heap.Insert(std::make_pair(std::make_pair(i, it->first), it->second));
      }
    }

    while (!min_heap.Empty()) {
      int vertex1 = min_heap.GetMin().first.first;
      int vertex2 = min_heap.GetMin().first.second;
      int vertex1_set_no = disj_set.Find(vertex1);
      int vertex2_set_no = disj_set.Find(vertex2);

      if ((vertex1_set_no == -1 && vertex2_set_no == -1) || vertex1_set_no != vertex2_set_no) {
        min_spaining_value += min_heap.GetMin().second;
        disj_set.UnionBySize(vertex1, vertex2);
      }

      min_heap.DeleteMin();
    }

    return min_spaining_value;
  }

 private:
  int num_vertex;
  std::vector<std::vector<std::pair<int, int>>> graph;
};

} // namespace graphs
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_KRUSKAL_H

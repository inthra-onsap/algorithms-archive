#include "kruskal.h"

namespace algorithms_archive {
namespace graphs {

void Kruskal::AddEdge(int vertex_1, int vertex_2, int weight) {
  graph[vertex_1].push_back(std::make_pair(vertex_2, weight));
}

int Kruskal::GetMinimumSpaningValue() {
  disjoint_sets::DisjointSets disj_set(num_vertex);
  int min_spaning_value = 0;
  GraphMinHeap<std::pair<int, int>> min_heap;

  for (int i = 0; i < num_vertex; ++i) {
    for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
      min_heap.Insert(
          std::make_pair(
              std::make_pair(i, it->first),
              it->second
          )
      );
    }
  }

  while (!min_heap.Empty()) {
    int vertex1 = min_heap.GetMin().first.first;
    int vertex2 = min_heap.GetMin().first.second;
    int vertex1_set_no = disj_set.Find(vertex1);
    int vertex2_set_no = disj_set.Find(vertex2);

    if ((vertex1_set_no == -1 && vertex2_set_no == -1) || vertex1_set_no != vertex2_set_no) {
      min_spaning_value += min_heap.GetMin().second;
      disj_set.UnionBySize(vertex1, vertex2);
    }

    min_heap.DeleteMin();
  }

  return min_spaning_value;
}

} // namespace graphs
} // namespace algorithms_archive
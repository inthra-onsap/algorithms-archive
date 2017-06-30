#include "prim.h"

namespace algorithms_archive {
namespace graphs {

void Prim::AddEdge(int vertex1, int vertex2, int weight) {
  graph[vertex1].push_back(std::make_pair(vertex2, weight));
  graph[vertex2].push_back(std::make_pair(vertex1, weight));
}

int Prim::GetMinimumSpaningValue() {
  GraphMinHeap<int> min_heap;
  std::vector<bool> visited(num_vertex, false);
  std::vector<int> dist(num_vertex, INT_MAX);
  int min_spaning_value = 0;

  dist[std::rand() % num_vertex] = 0;
  for (int i = 0; i < num_vertex; ++i) {
    min_heap.Insert(std::make_pair(i, dist[i]));
  }

  while (!min_heap.Empty()) {
    int min_vertex = min_heap.GetMin().first;
    min_heap.DeleteMin();
    visited[min_vertex] = true;

    for (auto it = graph[min_vertex].begin(); it != graph[min_vertex].end(); ++it) {
      if (!visited[it->first] && dist[it->first] > dist[min_vertex] + it->second) {
        dist[it->first] = dist[min_vertex] + it->second;
        min_heap.UpdateWeight(it->first, dist[it->first]);
      }
    }
  }

  for (int i = 0; i < num_vertex; ++i) {
    min_spaning_value += dist[i];
  }
  return min_spaning_value;
}

} // namespace graphs
} // namespace algorithms_archive
#include "dijkstra.h"

namespace algorithms_archive {
namespace graphs {

void Dijkstra::AddEdge(int vertex_1, int vertex_2, int weight) {
  adj_list[vertex_1].push_back(std::make_pair(vertex_2, weight));
  adj_list[vertex_2].push_back(std::make_pair(vertex_1, weight));
}

std::vector<int> Dijkstra::GetShortestPath(int source, int terminal) {

  if (terminal >= num_vertices || num_vertices <= 0 || source < 0) {
    return std::vector<int>();
  }

  GraphMinHeap<int> queue;
  std::vector<int> dist(num_vertices, INT_MAX);
  std::vector<int> prev(num_vertices, -1);
  std::vector<bool> visited(num_vertices, false);
  std::vector<int> shortest_path;

  queue.Insert(std::make_pair(source, 0));
  dist[source] = 0;
  for (int i = 0; i < dist.size(); ++i) {
    if (dist[i] == INT_MAX) {
      queue.Insert(std::make_pair(i, dist[i]));
    }
  }

  while (!queue.Empty()) {
    int curr_vertex = queue.GetMin().first;
    int curr_weight = queue.GetMin().second;
    queue.DeleteMin();
    visited[curr_vertex] = true;

    for (auto it = adj_list[curr_vertex].begin(); it != adj_list[curr_vertex].end(); ++it) {
      int vertex = it->first;
      int weight = it->second;

      if (!visited[vertex] && dist[vertex] > curr_weight + weight) {
        dist[vertex] = curr_weight + weight;
        prev[vertex] = curr_vertex;
        queue.UpdateWeight(vertex, dist[vertex]);
      }
    }
  }

  while (terminal != -1) {
    shortest_path.push_back(terminal);
    terminal = prev[terminal];
  }
  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

} // namespace graphs
} // namespace algorithms_archive


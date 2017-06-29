#include "dijkstra.h"

namespace algorithms_archive {
namespace graphs {

void Dijkstra::AddEdge(int vertex_1, int vertex_2, int weight) {
  adj_list[vertex_1].push_back(std::make_pair(weight, vertex_2));
  adj_list[vertex_2].push_back(std::make_pair(weight, vertex_1));
}

std::vector<int> Dijkstra::GetShortestPath(int source, int sink) {

  if (sink >= num_vertices || num_vertices <= 0 || source < 0) {
    return std::vector<int>();
  }

  std::set<std::pair<int, int>> queue;
  std::vector<int> dist(num_vertices, INT_MAX);
  std::vector<int> prev(num_vertices, -1);
  std::vector<bool> visited(num_vertices, false);
  std::vector<int> shortest_path;

  queue.insert(std::make_pair(0, source));
  dist[source] = 0;
  while (!queue.empty()) {
    int curr_vertex = queue.begin()->second;
    int curr_weight = queue.begin()->first;
    queue.erase(queue.begin());
    visited[curr_vertex] = true;

    for (auto it = adj_list[curr_vertex].begin(); it != adj_list[curr_vertex].end(); ++it) {
      int weight = it->first;
      int vertex = it->second;

      if (!visited[vertex] && dist[vertex] > curr_weight + weight) {
        if (dist[vertex] != INT_MAX) {
          queue.erase(queue.find(std::make_pair(dist[vertex], vertex)));
        }
        dist[vertex] = curr_weight + weight;
        queue.insert(std::make_pair(dist[vertex], vertex));
        prev[vertex] = curr_vertex;
      }
    }
  }

  while (prev[sink] != -1) {
    shortest_path.push_back(sink);
    sink = prev[sink];
  }
  shortest_path.push_back(source);
  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

} // namespace graphs
} // namespace algorithms_archive


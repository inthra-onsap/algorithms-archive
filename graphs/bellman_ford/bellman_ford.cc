#include "bellman_ford.h"

namespace algorithms_archive {
namespace graphs {

void BellmanFord::AddEdge(int vertex_1, int vertex_2, int weight) {
  graph[vertex_1].push_back(std::make_pair(vertex_2, weight));
}

std::vector<int> BellmanFord::GetShortestPath(int source, int terminal) {
  std::vector<int> dist(num_vertices, INT_MAX);
  std::vector<int> prev(num_vertices, -1);
  std::vector<int> shortest_path;

  dist[source] = 0;
  for (int i = 0; i < (num_vertices - 1); ++i) {
    for (int j = 0; j < num_vertices; ++j) {
      for (auto it = graph[j].begin(); it != graph[j].end(); ++it) {
        if (dist[j] != INT_MAX && dist[it->first] > dist[j] + it->second) {
          dist[it->first] = dist[j] + it->second;
          prev[it->first] = j;
        }
      }
    }
  }

  for (int j = 0; j < num_vertices; ++j) {
    for (auto it = graph[j].begin(); it != graph[j].end(); ++it) {
      if (dist[it->first] > dist[j] + it->second) {
        return std::vector<int>();
      }
    }
  }

  while (prev[terminal] != -1) {
    shortest_path.push_back(terminal);
    terminal = prev[terminal];
  }
  shortest_path.push_back(source);
  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

} // namespace graphs
} // namespace algorithms_archive
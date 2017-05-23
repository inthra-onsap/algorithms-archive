#include "graph_topological_sort.h"

namespace algorithms_archive {
namespace graphs {

void GraphTopologicalSort::AddEdge(int vertex1, int vertex2) {
  graph[vertex1].push_back(vertex2);
}

const std::vector<int> GraphTopologicalSort::TopologicalSort() {
  std::vector<bool>visited(graph.size(), false);
  std::vector<bool>visiting(graph.size(), false);
  std::vector<int> sorted;
  for (int i = 0; i < graph.size(); ++i) {
    if (IsCyclicGraph(visited, visiting, i)) {
      return sorted;
    }
  }

  std::fill(visited.begin(), visited.end(), 0);
  for (int i = 0; i < graph.size(); ++i) {
    if (!visited[i]) {
      Bfs(sorted, visited, i);
    }
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

bool GraphTopologicalSort::IsCyclicGraph(std::vector<bool> &visited, std::vector<bool> &visiting, int vertex) {
  if (!visited[vertex]) {
    visited[vertex] = true;
    visiting[vertex] = true;
    for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
      if (!visited[*it] && IsCyclicGraph(visited, visiting, *it)) {
        return true;
      } else if (visiting[*it]) {
        return true;
      }
    }
  }
  visiting[vertex] = false;
  return false;
}

void GraphTopologicalSort::Bfs(std::vector<int> &sorted, std::vector<bool> &visited, int vertex) {
  visited[vertex] = true;
  for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
    if (!visited[*it]) {
      Bfs(sorted, visited, *it);
    }
  }
  sorted.push_back(vertex);
}

} // namespace graphs
} // namespace algorithms_archive
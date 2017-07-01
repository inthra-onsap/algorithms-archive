#include "bidirectional_dijkstra.h"

namespace algorithms_archive {
namespace graphs {

void BidirectionalDijkstra::AddEdge(int vertex1, int vertex2, int weight) {
  graph[vertex1].push_back(std::make_pair(vertex2, weight));
}

std::vector<int> BidirectionalDijkstra::GetShortestPath(int source, int terminal) {
  std::vector<std::vector<std::pair<int, int>>> reverse_graph = GetReverseGraph();
  std::vector<int> dist(num_vetex, INT_MAX);
  std::vector<int> dist_reverse(num_vetex, INT_MAX);
  std::vector<int> prev(num_vetex, -1);
  std::vector<int> prev_reverse(num_vetex, -1);
  std::vector<bool> visited(num_vetex, false);
  std::vector<bool> visited_reverse(num_vetex, false);
  GraphMinHeap<int> min_heap;
  GraphMinHeap<int> min_heap_reverse;

  dist[source] = 0;
  dist_reverse[terminal] = 0;
  min_heap.Insert(std::make_pair(source, dist[source]));
  min_heap_reverse.Insert(std::make_pair(terminal, dist_reverse[terminal]));

  while (!min_heap.Empty() && !min_heap_reverse.Empty()) {
    int vertex = min_heap.GetMin().first;
    min_heap.DeleteMin();
    visited[vertex] = true;
    Relax(graph, vertex, dist, prev, visited, min_heap);

    if (visited_reverse[vertex]) {
      return ProcessShortestPath(source, terminal, dist, dist_reverse, prev, prev_reverse, visited, visited_reverse);
    }

    int vertex_reverse = min_heap_reverse.GetMin().first;
    min_heap_reverse.DeleteMin();
    visited_reverse[vertex_reverse] = true;
    Relax(reverse_graph, vertex_reverse, dist_reverse, prev_reverse, visited_reverse, min_heap_reverse);
  }

  return std::vector<int>();
}

std::vector<std::vector<std::pair<int, int>>> BidirectionalDijkstra::GetReverseGraph() {
  std::vector<std::vector<std::pair<int, int>>> reverse_graph(num_vetex, std::vector<std::pair<int, int>>());
  for (int i = 0; i < num_vetex; ++i) {
    for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
      reverse_graph[it->first].push_back(std::make_pair(i, it->second));
    }
  }
  return reverse_graph;
};

void BidirectionalDijkstra::Relax(std::vector<std::vector<std::pair<int, int>>> &graph,
                                  int vertex,
                                  std::vector<int> &dist,
                                  std::vector<int> &prev,
                                  std::vector<bool> &visited,
                                  GraphMinHeap<int> &min_heap) {
  for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
    if (!visited[it->first] && dist[it->first] > dist[vertex] + it->second) {
      dist[it->first] = dist[vertex] + it->second;
      prev[it->first] = vertex;
      min_heap.Upsert(it->first, dist[it->first]);
    }
  }
}

std::vector<int> BidirectionalDijkstra::ProcessShortestPath(int source,
                                                            int terminal,
                                                            std::vector<int> &dist,
                                                            std::vector<int> &dist_reserve,
                                                            std::vector<int> &prev,
                                                            std::vector<int> &prev_reserve,
                                                            std::vector<bool> &visited,
                                                            std::vector<bool> &visited_reserve) {
  int distance = INT_MAX;
  int meeting_vertex;
  std::vector<int> shortest_path;
  int last;

  for (int i = 0; i < num_vetex; ++i) {
    if (visited[i] && visited_reserve[i] && distance > dist[i] + dist_reserve[i]) {
      distance = dist[i] + dist_reserve[i];
      meeting_vertex = i;
    }
  }

  last = meeting_vertex;
  while (last != -1) {
    shortest_path.push_back(last);
    last = prev[last];
  }
  std::reverse(shortest_path.begin(), shortest_path.end());
  last = prev_reserve[meeting_vertex];
  while (last != -1) {
    shortest_path.push_back(last);
    last = prev_reserve[last];
  }
  return shortest_path;
}

} // namespace graphs
} // namespace algorithms_archive
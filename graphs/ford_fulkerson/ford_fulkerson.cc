#include "ford_fulkerson.h"

namespace algorithms_archive {
namespace graphs {

void FordFulkerson::AddEdge(int vertex1, int vertex2, int weight) {
  graph[vertex1][vertex2] = weight;
}

int FordFulkerson::FindMaxFlow(int source, int sink) {
  std::vector<std::vector<int>> flow_graph(size, std::vector<int>(size, 0));
  std::vector<int> prev(size, -1);
  int max_flow = 0;

  while (IsSinkReachable(
      GetResidualGraph(flow_graph),
      prev,
      source,
      sink
  )) {
    max_flow += ProcessAugmentingPath(flow_graph, prev, sink);
  }
  return max_flow;
}

bool FordFulkerson::IsSinkReachable(
    std::vector<std::vector<std::pair<int, int>>> residual_graph,
    std::vector<int> &prev, int source, int sink) {
  std::queue<int> q;
  std::vector<bool> visited(size, false);
  int p_vertex;
  std::fill(prev.begin(), prev.end(), -1);
  q.push(source);
  while (!q.empty() && prev[sink] == -1) {
    p_vertex = q.front();
    q.pop();
    visited[p_vertex] = true;
    for (auto it = residual_graph[p_vertex].begin(); it != residual_graph[p_vertex].end(); ++it) {
      if (!visited[it->first] && it->second > 0) {
        q.push(it->first);
        prev[it->first] = p_vertex;
      }
    }
  }
  return (prev[sink] != -1);
}

std::vector<std::vector<std::pair<int, int>>> FordFulkerson::GetResidualGraph(std::vector<std::vector<int>> &flow_graph) {
  std::vector<std::vector<std::pair<int, int>>> residual_graph(size, std::vector<std::pair<int, int>>());
  for (int v1 = 0; v1 < size; ++v1) {
    for (int v2 = 0; v2 < size; ++v2) {
      if (graph[v1][v2] != 0) {
        residual_graph[v1].push_back(std::make_pair(v2, graph[v1][v2] - flow_graph[v1][v2]));
        residual_graph[v2].push_back(std::make_pair(v1, flow_graph[v1][v2]));
      }
    }
  }
  return residual_graph;
}

int FordFulkerson::ProcessAugmentingPath(std::vector<std::vector<int>> &flow_graph, std::vector<int> &prev, int sink) {
  std::stack<int> augmenting_path;
  int min_flow = INT_MAX;
  int v1, v2;
  while (sink != -1) {
    augmenting_path.push(sink);
    if (prev[sink] != -1)
      min_flow = std::min(min_flow, graph[prev[sink]][sink]);
    sink = prev[sink];
  }
  v1 = augmenting_path.top();
  augmenting_path.pop();
  while (!augmenting_path.empty()) {
    v2 = augmenting_path.top();
    augmenting_path.pop();
    if (graph[v1][v2] > 0) {
      flow_graph[v1][v2] = flow_graph[v1][v2] + min_flow;
    } else {
      flow_graph[v2][v1] = flow_graph[v2][v1] - min_flow;
    }
    v1 = v2;
  }
  return min_flow;
}

} // namespace graphs
} // namespace algorithms_archive
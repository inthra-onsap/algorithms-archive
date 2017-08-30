#include "graph_strongly_connected_component.h"


namespace algorithms_archive {
namespace graphs {

int GraphStronglyConnectedComponent::GetTotalComponents() {
  std::vector<bool> visited(num_of_vertex, false);
  std::stack<int> visit_orders;
  std::vector<std::vector<int>> reversed_graph = ReverseDigraph(di_graph);
  for (int vertex = 0; vertex < num_of_vertex; ++vertex) {
    if (!visited[vertex]) {
      VisitDigraph(di_graph, vertex, visited, visit_orders);
    }
  }

  return ComputeStronglyConnectedComponent(reversed_graph, visit_orders);
}

void GraphStronglyConnectedComponent::VisitDigraph(std::vector<std::vector<int>> &graph,
                  int vertex,
                  std::vector<bool> &visited,
                  std::stack<int> &visit_orders) {
  visited[vertex] = true;
  for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
    if (!visited[*it]) {
      VisitDigraph(graph, *it, visited, visit_orders);
    }
  }
  visit_orders.push(vertex);
}

void GraphStronglyConnectedComponent::FlagStronglyConnectedComponent(std::vector<std::vector<int>> &graph,
                                    int vertex,
                                    int counter,
                                    std::vector<int> &component_sets) {
  component_sets[vertex] = counter;
  for (auto it = graph[vertex].begin(); it != graph[vertex].end(); ++it) {
    if (component_sets[*it] == -1) {
      FlagStronglyConnectedComponent(graph, *it, counter, component_sets);
    }
  }
}

int GraphStronglyConnectedComponent::ComputeStronglyConnectedComponent(std::vector<std::vector<int>> &graph, std::stack<int> &visit_orders) {
  int vertex;
  int counter = 0;
  std::vector<int> component_sets(num_of_vertex, -1);

  while (!visit_orders.empty()) {
    vertex = visit_orders.top();
    visit_orders.pop();
    if (component_sets[vertex] == -1) {
      ++counter;
      FlagStronglyConnectedComponent(graph, vertex, counter, component_sets);
    }
  }
  return counter;
}

std::vector<std::vector<int>> GraphStronglyConnectedComponent::ReverseDigraph(std::vector<std::vector<int>> &graph) {
  std::vector<std::vector<int>> reversed_graph(num_of_vertex, std::vector<int>());
  for (int i = 0; i < num_of_vertex; ++i) {
    for (auto vertex: graph[i]) {
      reversed_graph[vertex].push_back(i);
    }
  }
  return reversed_graph;
}

}
}
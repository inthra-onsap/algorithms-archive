#ifndef ALGORITHMS_ARCHIVE_GRAPH_STRONGLY_CONNECTED_COMPONENT_H
#define ALGORITHMS_ARCHIVE_GRAPH_STRONGLY_CONNECTED_COMPONENT_H

#include <vector>
#include <stack>
#include<algorithm>

namespace algorithms_archive {
namespace graphs {

class GraphStronglyConnectedComponent {
 public:
  GraphStronglyConnectedComponent(int num_of_vertex_) : num_of_vertex{num_of_vertex_} {
    di_graph.resize(num_of_vertex_,
                    std::vector<int>());
  }

  void AddEdge(int vertex1, int vertex2) { di_graph[vertex1].push_back(vertex2); }

  int GetTotalComponents();

 private:
  int num_of_vertex;
  std::vector<std::vector<int>> di_graph;

  void VisitDigraph(std::vector<std::vector<int>> &graph,
                    int vertex,
                    std::vector<bool> &visited,
                    std::stack<int> &visit_orders);

  void FlagStronglyConnectedComponent(std::vector<std::vector<int>> &graph,
                                      int vertex,
                                      int counter,
                                      std::vector<int> &component_sets);

  int ComputeStronglyConnectedComponent(std::vector<std::vector<int>> &graph, std::stack<int> &visit_orders);

  std::vector<std::vector<int>> ReverseDigraph(std::vector<std::vector<int>> &graph);
};

} // namespace graphs
} // namespace algorihms_archive

#endif //ALGORITHMS_ARCHIVE_GRAPH_STRONGLY_CONNECTED_COMPONENT_H

#ifndef ALGORITHMS_ARCHIVE_HOPCROFT_KARP_H_
#define ALGORITHMS_ARCHIVE_HOPCROFT_KARP_H_

#include <vector>
#include <limits>
#include <queue>

namespace algorithms_archive {
namespace graphs {

class HopcroftKarp {
 public:
  HopcroftKarp(int num_left_vertics_, int num_right_vertics_)
      : num_left_vertics{num_left_vertics_}, num_right_vertics{num_right_vertics_} {
    graph.resize(num_left_vertics_ + 1);
  }

  void addEdge(int left_vertex, int right_vertex);

  int getMaxFlow();

 private:
  std::vector<std::vector<int>> graph;
  std::vector<int> dist, left_vertics, right_vertics;
  int num_left_vertics, num_right_vertics;
  const int NIL_VERTEX = 0;
  const int INF = std::numeric_limits<int>::max();

  bool bfs();

  bool dfs(int l_vertex);
};

} // namespace graphs
} // namespace algorithms_archive
#endif //ALGORITHMS_ARCHIVE_HOPCROFT_KARP_H_

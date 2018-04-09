#include "hopcroft_karp.h"

namespace algorithms_archive {
namespace graphs {

void HopcroftKarp::addEdge(int left_vertex, int right_vertex) {
  graph[left_vertex].push_back(right_vertex);
}

int HopcroftKarp::getMaxFlow() {
  int max_flow = 0;

  dist.resize(num_left_vertics + 1);
  left_vertics.resize(num_left_vertics + 1, NIL_VERTEX);
  right_vertics.resize(num_right_vertics + 1, NIL_VERTEX);

  while (bfs()) {
    for (int l_vertex = 1; l_vertex <= num_left_vertics; ++l_vertex) {
      if (left_vertics[l_vertex] == NIL_VERTEX && dfs(l_vertex)) {
        ++max_flow;
      }
    }
  }

  return max_flow;
}

bool HopcroftKarp::bfs() {
  std::queue<int> que;
  int l_vertex;

  dist[NIL_VERTEX] = INF;
  for (l_vertex = 1; l_vertex <= num_left_vertics; ++l_vertex) {
    if (left_vertics[l_vertex] == NIL_VERTEX) {
      dist[l_vertex] = 0;
      que.push(l_vertex);
    } else {
      dist[l_vertex] = INF;
    }
  }

  while (!que.empty()) {
    l_vertex = que.front();
    que.pop();

    if (dist[l_vertex] < dist[NIL_VERTEX]) {
      for (auto r_vertex: graph[l_vertex]) {
        if (dist[right_vertics[r_vertex]] == INF) {
          dist[right_vertics[r_vertex]] = dist[l_vertex] + 1;
          que.push(right_vertics[r_vertex]);
        }
      }
    }
  }

  return dist[NIL_VERTEX] != INF;
}
bool HopcroftKarp::dfs(int l_vertex) {
  if (l_vertex == NIL_VERTEX)
    return true;

  for (auto r_vertex: graph[l_vertex]) {
    if (dist[right_vertics[r_vertex]] == dist[l_vertex] + 1) {
      if (dfs(right_vertics[r_vertex])) {
        left_vertics[l_vertex] = r_vertex;
        right_vertics[r_vertex] = l_vertex;
        return true;
      }
    }
  }
  dist[l_vertex] = INF;
  return false;
}

} // namespace graphs
} // namespace algorithms_archive
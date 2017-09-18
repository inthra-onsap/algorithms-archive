#include "lca.h"

namespace algorithms_archive {
namespace tree {

void Lca::AddNode(int from, int to) {
  tree[from].push_back(to);
  parent[to] = from;
  level[to] = level[from] + 1;
  has_changed = true;
}

int Lca::CommonAncestorOf(int n1, int n2) {
  if (has_changed) {
    PreProcess();
    has_changed = false;
  }

  int n_log = 0;
  if (level[n1] < level[n2]) {
    std::swap(n1, n2);
  }

  while ((1 << (n_log + 1)) <= level[n1]) {
    ++n_log;
  }

  for (int i = n_log; i >= 0; --i) {
    if (level[n1] - (1 << i) >= level[n2]) {
      n1 = dp[n1][i];
    }
  }

  if (n1 == n2) {
    return n1;
  }

  for (int i = n_log; i >= 0; --i) {
    if (dp[n1][i] != -1 && dp[n1][i] != dp[n2][i]) {
      n1 = dp[n1][i];
      n2 = dp[n2][i];
    }
  }

  return parent[n1];
}

void Lca::PreProcess() {
  dp.resize(size, std::vector<int>(log2(size), -1));

  for (int i = 1; i < size; ++i) {
    dp[i][0] = parent[i];
  }

  for (int j = 1; (1 << j) < size; ++j) {
    for (int i = 1; i < size; ++i) {
      if (dp[i][j - 1] != -1) {
        dp[i][j] = dp[dp[i][j - 1]][j - 1];
      }
    }
  }
}

} // namespace tree
} // namespace algorithms_archive
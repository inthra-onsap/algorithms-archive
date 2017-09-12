#ifndef ALGORITHMS_ARCHIVE_SEGMENT_TREE_H_
#define ALGORITHMS_ARCHIVE_SEGMENT_TREE_H_

#include <vector>
#include <algorithm>
#include <cmath>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class SegmentTree {
 public:
  SegmentTree(std::vector<Comparable> data)
      : original_arr{data} {
    int t_size = pow(2, log2(data.size()) + 1);
    segment_tree.resize(t_size);
    carried_tree.resize(t_size, 0);
    BuildTree(0, original_arr.size() - 1, 0);
  }

  Comparable RangeQuery(int r_low, int r_high) {
    return GetMinimumByRange(r_low, r_high, 0, original_arr.size() - 1, 0);
  }

  void IncreaseValueByRange(int r_low, int r_high, Comparable inc_value) {
    LazyUpdateValueByRange(r_low, r_high, 0, original_arr.size() - 1, 0, inc_value);
  }

 private:
  const int kMaxNum = 1e9;
  std::vector<Comparable> original_arr;
  std::vector<Comparable> segment_tree;
  std::vector<Comparable> carried_tree;

  int LeftChild(int node) {
    return 2 * node + 1;
  }

  int RightChild(int node) {
    return 2 * node + 2;
  }

  void BuildTree(int low_pos, int high_pos, int node) {
    if (low_pos == high_pos) {
      segment_tree[node] = original_arr[low_pos];
      return;
    }

    int mid_pos = (high_pos + low_pos) / 2;
    BuildTree(low_pos, mid_pos, LeftChild(node));
    BuildTree(mid_pos + 1, high_pos, RightChild(node));
    segment_tree[node] = std::min(segment_tree[LeftChild(node)], segment_tree[RightChild(node)]);
  }

  Comparable GetMinimumByRange(int r_low, int r_high, int curr_low, int curr_high, int node) {
    if (carried_tree[node] != 0) {
      if (curr_low < curr_high) {
        carried_tree[LeftChild(node)] += carried_tree[node];
        carried_tree[RightChild(node)] += carried_tree[node];
      }

      segment_tree[node] += carried_tree[node];
      carried_tree[node] = 0;
    }

    if (r_low <= curr_low && r_high >= curr_high) {
      return segment_tree[node];
    }

    if (r_low > curr_high || r_high < curr_low) {
      return kMaxNum;
    }

    int mid = (curr_high + curr_low) / 2;
    return std::min(
        GetMinimumByRange(r_low, r_high, curr_low, mid, LeftChild(node)),
        GetMinimumByRange(r_low, r_high, mid + 1, curr_high, RightChild(node))
    );
  }

  void LazyUpdateValueByRange(int r_low, int r_high, int curr_low, int curr_high, int node, Comparable value) {
    if (carried_tree[node] != 0) {
      if (curr_low < curr_high) {
        carried_tree[LeftChild(node)] += carried_tree[node];
        carried_tree[RightChild(node)] += carried_tree[node];
      }

      segment_tree[node] += carried_tree[node];
      carried_tree[node] = 0;
    }

    if (r_low <= curr_low && r_high >= curr_high) {
      if (curr_low < curr_high) {
        carried_tree[LeftChild(node)] += value;
        carried_tree[RightChild(node)] += value;
      }

      segment_tree[node] += value;
      return;
    }

    if (r_low > curr_high || r_high < curr_low) {
      return;
    }

    int mid = (curr_high + curr_low) / 2;
    LazyUpdateValueByRange(r_low, r_high, curr_low, mid, LeftChild(node), value);
    LazyUpdateValueByRange(r_low, r_high, mid + 1, curr_high, RightChild(node), value);
    segment_tree[node] = std::min(segment_tree[LeftChild(node)], segment_tree[RightChild(node)]);
  }
};

} // namespace tree
} // namespace algorithms_archive


#endif //ALGORITHMS_ARCHIVE_SEGMENT_TREE_H_

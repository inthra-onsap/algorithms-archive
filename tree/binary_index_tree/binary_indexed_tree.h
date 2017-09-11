#ifndef ALGORITHMS_ARCHIVE_BINARY_INDEXED_TREE_H_
#define ALGORITHMS_ARCHIVE_BINARY_INDEXED_TREE_H_

#include <vector>

namespace algorithms_archive {
namespace tree {

template<typename Comparable>
class BinaryIndexedTree {
 public:
  BinaryIndexedTree(std::vector<Comparable> data)
      : original_data{data} {
    binary_indexed_tree.resize(data.size() + 1, 0);
    BuildTree();
  }

  void UpdateAt(int idx, Comparable value) {
    original_data[idx] += value;
    ProcessUpdates(idx + 1, value);
  }

  Comparable SumByRange(int r_start, int r_end) {
    if (r_start == 0) {
      return ProcessSumByRange(r_end + 1);
    } else {
      return ProcessSumByRange(r_end + 1) - ProcessSumByRange(r_start);
    }
  }

 private:
  std::vector<Comparable> original_data;
  std::vector<Comparable> binary_indexed_tree;

  int NextNode(int idx) {
    return idx + (idx & -idx);
  }

  int PrevNode(int idx) {
    return idx - (idx & -idx);
  }

  void BuildTree() {
    for (int i = 1; i < binary_indexed_tree.size(); ++i) {
      ProcessUpdates(i, original_data[i - 1]);
    }
  }

  void ProcessUpdates(int idx, Comparable value) {
    while (idx < binary_indexed_tree.size()) {
      binary_indexed_tree[idx] += value;
      idx = NextNode(idx);
    }
  }

  Comparable ProcessSumByRange(int r_end) {
    Comparable sum = 0;
    while (r_end > 0) {
      sum += binary_indexed_tree[r_end];
      r_end = PrevNode(r_end);
    }
    return sum;
  }
};

} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_BINARY_INDEXED_TREE_H_

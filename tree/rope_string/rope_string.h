#ifndef ALGORITHMS_ARCHIVE_ROPE_TREE_H_
#define ALGORITHMS_ARCHIVE_ROPE_TREE_H_

#include "rope_node.cc"

#include <utility>
#include <string>
#include <list>
#include <algorithm>

namespace algorithms_archive {
namespace tree {
/**
 * 1-based index string class
 */
class RopeString {
 public:
  RopeString();

  RopeString(const RopeString &rhs);

  RopeString(const RopeString &&rhs);

  ~RopeString();

  char Index(const uint64_t index);

  void Insert(const uint64_t index, const std::string text);

  void Append(std::string text);

  void Prepend(std::string text);

  void Delete(const uint64_t start, const uint64_t length);

  void Empty();

  std::string ToString();

  void Concat(RopeString &tree);

 private:
  enum BALANCE_TYPE { LEFT_HEAVY, BALANCE, RIGHT_HEAVY };
  RopeNode *root;

  RopeNode *Clone(const RopeNode *node);

  RopeNode *Move(const RopeNode *&&node);

  char Index(const uint64_t &index, RopeNode *node);

  RopeNode *RotateLeft(RopeNode *node);

  RopeNode *RotateRight(RopeNode *node);

  BALANCE_TYPE BalanceFactor(RopeNode *node);

  uint64_t Height(RopeNode *node);

  uint64_t Length(RopeNode *node);

  uint64_t Weight(RopeNode *node);

  uint64_t GetHeight(RopeNode *node);

  uint64_t GetLength(RopeNode *node);

  RopeNode *Rebalance(RopeNode *node);

  RopeNode *Merge(RopeNode *left, RopeNode *right);

  void Split(const uint64_t index, RopeNode *&node, RopeNode *&left, RopeNode *&right);

  void ToString(std::string &str, RopeNode *node);

  void Empty(RopeNode *&node);
};
} // namespace tree
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_ROPE_TREE_H_

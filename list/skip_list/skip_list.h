#ifndef ALGORITHMS_ARCHIVE_SKIP_LIST_H_
#define ALGORITHMS_ARCHIVE_SKIP_LIST_H_

#include "skip_list_node.cc"

#include <random>
#include <vector>

namespace algorithms_archive {
namespace list {

template<typename Comparable>
class SkipList {
 public:
  SkipList(int max_level_) : distribution(0.0, 1.0), max_level{max_level_} {
    header = CreateNode(-1, max_level + 1);
  }

  void Insert(Comparable key) {
    SkipListNode<Comparable> *curr = header;
    std::vector<SkipListNode<Comparable> *> updates(max_level + 1);

    for (int i = max_level; i >= 0; --i) {
      while (curr->forwards[i] && curr->forwards[i]->key < key) {
        curr = curr->forwards[i];
      }
      updates[i] = curr;
    }

    curr = curr->forwards[0];
    if (curr == nullptr || curr->key != key) {
      int level = RandomLevel();

      SkipListNode<Comparable> *node = CreateNode(key, level);
      for (int i = 0; i < level; ++i) {
        node->forwards[i] = updates[i]->forwards[i];
        updates[i]->forwards[i] = node;
      }
    }
  }

  SkipListNode<Comparable> *Search(Comparable key) {
    SkipListNode<Comparable> *curr = header;
    for (int i = max_level; i >= 0; --i) {
      while (curr->forwards[i] && curr->forwards[i]->key < key) {
        curr = curr->forwards[i];
      }
    }
    curr = curr->forwards[0];
    return (curr->key == key) ? curr : nullptr;
  }

  void Delete(Comparable key){
    SkipListNode<Comparable> *curr = header;
    std::vector<SkipListNode<Comparable> *> updates(max_level + 1);

    for (int i = max_level; i >= 0; --i) {
      while (curr->forwards[i] && curr->forwards[i]->key < key) {
        curr = curr->forwards[i];
      }
      updates[i] = curr;
    }

    curr = curr->forwards[0];
    if (curr != nullptr && curr->key == key) {
      for (int i = 0; i <= max_level; ++i) {
        if(updates[i]->forwards[i] == curr){
          updates[i]->forwards[i] = curr->forwards[i];
        }
      }
      delete curr;
    }
  }

 private:
  SkipListNode<Comparable> *header;
  int max_level;
  std::default_random_engine generator;
  std::normal_distribution<float> distribution;

  SkipListNode<Comparable> *CreateNode(Comparable key, int level) {
    return new SkipListNode<Comparable>(key, level);
  }

  int RandomLevel() {
    int level = 1;
    float rand = distribution(generator);
    while (rand <= 0.0 && level <= max_level) {
      ++level;
      rand = distribution(generator);
    }
    return level;
  }
};

} // namespace list
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_SKIP_LIST_H_

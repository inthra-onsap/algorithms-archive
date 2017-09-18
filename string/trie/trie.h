#ifndef ALGORITHMS_ARCHIVE_TRIE_H_
#define ALGORITHMS_ARCHIVE_TRIE_H_

#include "trie_node.cc"

#include <string>
#include <stack>

namespace algorithms_archive {
namespace string {

class Trie {
 public:
  Trie() {
    root = new TrieNode{};
  }

  ~Trie() {
    Clear(root);
  }

  void AddWord(std::string word) {
    Insert(word);
  }

  void DeleteWord(std::string word) {
    Delete(word);
  }

  bool Search(std::string word) {
    TrieNode *end_node = Find(word);
    return (end_node != nullptr) ? end_node->end_word : false;
  }

 private:
  TrieNode *root;

  void Clear(TrieNode *node);

  void Insert(std::string &word);

  void Delete(std::string &word);

  TrieNode *Find(std::string &word);
};

} // namespace string
} // namespace algorithms_archive


#endif //ALGORITHMS_ARCHIVE_TRIE_H_

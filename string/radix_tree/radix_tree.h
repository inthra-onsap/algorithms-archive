#ifndef ALGORITHMS_ARCHIVE_RADIX_TREE_H_
#define ALGORITHMS_ARCHIVE_RADIX_TREE_H_

#include "trie_node.cc"

#include <string>

namespace algorithms_archive {
namespace string {

class RadixTree {
 public:
  RadixTree() {
    root = new TrieNode{};
  }

  ~RadixTree() {
    Clear(root);
  }

  void AddWord(std::string word) {
    Insert(word + "$");
  }
  void DeleteWord(std::string word) {
    Delete(word + "$");
  }

  bool SearchWord(std::string word) {
    return Search(word + "$");
  }
 private:
  TrieNode *root;

  void Clear(TrieNode *node) {
    for (auto it: node->maps) {
      if (node->maps[it.first]) {
        Clear(it.second);
      }
    }
    delete node;
  }

  void Insert(std::string word) {
    TrieNode *curr_node = root;
    int curr_idx = 0;
    int match_len;

    while (curr_idx < word.length()) {
      if (!curr_node->maps[word[curr_idx]]) {
        curr_node->maps[word[curr_idx]] = new TrieNode(word.substr(curr_idx));
        break;
      }

      curr_node = curr_node->maps[word[curr_idx]];
      match_len = 0;
      while (match_len < curr_node->data.size() && curr_node->data[match_len] == word[curr_idx])
        ++curr_idx, ++match_len;

      if (match_len < curr_node->data.size()) {
        TrieNode *tmp = new TrieNode(curr_node->data.substr(match_len), curr_node->maps);
        curr_node->maps.clear();
        curr_node->maps[tmp->data[0]] = tmp;
        curr_node->maps[word[curr_idx]] = new TrieNode(word.substr(curr_idx));
        curr_node->data = curr_node->data.substr(0, match_len);
        break;
      }
    }

  }
  void Delete(std::string word) {
    TrieNode *curr_node = root;
    TrieNode *prev_node = nullptr;
    int prev_idx;
    int curr_idx = 0;
    int match_len;

    while (curr_idx < word.length()) {
      if (!curr_node->maps[word[curr_idx]])
        break;

      prev_node = curr_node;
      prev_idx = curr_idx;
      curr_node = curr_node->maps[word[curr_idx]];
      match_len = 0;
      while (match_len < curr_node->data.size() && curr_node->data[match_len] == word[curr_idx])
        ++curr_idx, ++match_len;

      if (match_len < curr_node->data.size())
        break;
    }

    if (curr_idx == word.size()) {
      delete curr_node;
      prev_node->maps.erase(word[prev_idx]);
    }
  }

  bool Search(std::string word) {
    TrieNode *curr_node = root;
    int curr_idx = 0;
    int match_len;

    while (curr_idx < word.length()) {
      if (!curr_node->maps[word[curr_idx]])
        break;

      curr_node = curr_node->maps[word[curr_idx]];
      match_len = 0;
      while (match_len < curr_node->data.size() && curr_node->data[match_len] == word[curr_idx])
        ++curr_idx, ++match_len;

      if (match_len < curr_node->data.size())
        break;
    }

    return (curr_idx == word.size());
  }
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_RADIX_TREE_H_

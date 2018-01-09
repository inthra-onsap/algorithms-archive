#ifndef ALGORITHMS_ARCHIVE_RADIX_TREE_H_
#define ALGORITHMS_ARCHIVE_RADIX_TREE_H_

#include "trie_node.cc"

#include <stack>
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
      match_len = prefixLength(curr_idx, curr_node->label, word);
      curr_idx += match_len;

      if (match_len < curr_node->label.length()) {
        TrieNode *tmp = new TrieNode(curr_node->label.substr(match_len), curr_node->maps);
        curr_node->maps.clear();
        curr_node->maps[tmp->label[0]] = tmp;
        curr_node->maps[word[curr_idx]] = new TrieNode(word.substr(curr_idx));
        curr_node->label = curr_node->label.substr(0, match_len);
        break;
      }
    }

  }

  void Delete(std::string word) {
    std::stack<TrieNode *> st;
    TrieNode *curr_node = root;
    int curr_idx = 0;
    int match_len;

    st.push(curr_node);
    while (curr_idx < word.length() && curr_node->maps.count(word[curr_idx])) {
      curr_node = curr_node->maps[word[curr_idx]];
      match_len = prefixLength(curr_idx, curr_node->label, word);
      curr_idx += match_len;
      st.push(curr_node);

      if (match_len < curr_node->label.length())
        break;
    }

    if (curr_idx == word.length()) {
      while (!st.empty()) {
        curr_node = st.top();
        st.pop();

        if (curr_node == root) {
          curr_node->maps.erase(word[0]);
          break;
        } else {
          if (curr_node->maps.count(word[curr_idx])) {
            curr_node->maps.erase(word[curr_idx]);
          }
        }

        if (curr_node->maps.size() == 0) {
          curr_idx -= curr_node->label.length();
          delete curr_node;
        } else if (curr_node->maps.size() == 1) {
          std::pair<char, TrieNode *> only_child = *(curr_node->maps.begin());
          curr_node->maps = std::move(only_child.second->maps);
          curr_node->label += only_child.second->label;
          delete only_child.second;
          break;
        } else {
          break;
        }
      }
    }
  }

  bool Search(std::string word) {
    TrieNode *curr_node = root;
    int curr_idx = 0;
    int match_len;

    while (curr_idx < word.length() && curr_node->maps.count(word[curr_idx])) {
      curr_node = curr_node->maps[word[curr_idx]];
      match_len = prefixLength(curr_idx, curr_node->label, word);
      curr_idx += match_len;

      if (match_len < curr_node->label.length())
        break;
    }

    return (curr_idx == word.size());
  }

  int prefixLength(int start_idx, std::string &label, std::string &word) {
    int match_len = 0;
    while (match_len < label.length() && label[match_len] == word[start_idx + match_len])
      ++match_len;

    return match_len;
  }
};

} // namespace string
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_RADIX_TREE_H_

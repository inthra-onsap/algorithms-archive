#include "trie.h"

namespace algorithms_archive {
namespace string {

void Trie::Clear(TrieNode *node) {
  for (auto it = node->node_map.begin(); it != node->node_map.end(); ++it) {
    if (node->node_map[it->first]) {
      Clear(it->second);
    }
  }
  delete node;
}

void Trie::Insert(std::string &word) {
  TrieNode *curr = root;
  for (int i = 0; i < word.length(); ++i) {
    if (!curr->node_map[word[i]]) {
      curr->node_map[word[i]] = new TrieNode{};
    }
    curr = curr->node_map[word[i]];
  }
  curr->end_word = true;
}

void Trie::Delete(std::string &word) {
  std::stack<TrieNode *> st;
  TrieNode *curr = root;

  st.push(curr);
  for (int i = 0; i < word.length(); ++i) {
    if (!curr->node_map[word[i]]) {
      return;
    }
    curr = curr->node_map[word[i]];
    st.push(curr);
  }

  if (curr->end_word) {
    int idx = word.length();
    while (!st.empty()) {
      curr = st.top();
      st.pop();

      if (curr == root) {
        curr->node_map.erase(word[idx]);
        break;
      } else if (idx == word.length()) {
        curr->end_word = false;
      } else {
        if (curr->node_map[word[idx]]) {
          curr->node_map.erase(word[idx]);
        }
      }

      if (curr->node_map.size() == 0) {
        delete curr;
      } else {
        break;
      }
      --idx;
    }
  }
}

TrieNode *Trie::Find(std::string &word) {
  TrieNode *curr = root;
  for (int i = 0; i < word.length(); ++i) {
    if (curr->node_map[word[i]]) {
      curr = curr->node_map[word[i]];
    } else {
      return nullptr;
    }
  }
  return curr;
}

} // namespace string
} // namespace algorithms_archive
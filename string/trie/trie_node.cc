#include <unordered_map>

namespace algorithms_archive {
namespace string {

struct TrieNode {
  std::unordered_map<char, TrieNode *> node_map;
  bool end_word = false;
};

}
}
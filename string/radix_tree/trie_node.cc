#include <unordered_map>
#include <string>

namespace algorithms_archive {
namespace string {

struct TrieNode {
  std::unordered_map<char, TrieNode *> maps;
  std::string label;

  TrieNode() {}
  TrieNode(std::string label_) : label{label_} {}
  TrieNode(std::string label_, std::unordered_map<char, TrieNode *> maps_) : label{label_}, maps{maps_} {}
};

} // namespace string
} // namespace algorithms_archive
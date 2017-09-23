#include <unordered_map>
#include <string>

namespace algorithms_archive {
namespace string {

struct TrieNode {
  std::unordered_map<char, TrieNode *> maps;
  std::string data;

  TrieNode() {}
  TrieNode(std::string data_) : data{data_} {}
  TrieNode(std::string data_, std::unordered_map<char, TrieNode *> maps_) : data{data_}, maps{maps_} {}
};

} // namespace string
} // namespace algorithms_archive
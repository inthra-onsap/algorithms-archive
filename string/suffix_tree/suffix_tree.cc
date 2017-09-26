#include "suffix_tree.h"

namespace algorithms_archive{
namespace string{

std::vector<int> SuffixTree::Search(std::string keyword) {
  std::vector<int> all_occurrences;

  if (keyword.length() == 0) {
    return all_occurrences;
  }

  SuffixNode *tmp;
  int pos = 0;
  active_node = root;
  active_edge = 0;
  active_length = 0;

  while (pos < keyword.length()) {
    if (!active_node->GetChild(keyword[active_edge])) {
      return all_occurrences;
    }

    tmp = active_node->GetChild(keyword[active_edge]);
    if (ChangeActivePointByWalkDown(tmp)) {
      continue;
    }

    if (text[tmp->start + active_length] != keyword[pos]) {
      return all_occurrences;
    }

    ++active_length, ++pos;
  }

  FindAllOccurrences(active_node->GetChild(keyword[active_edge]), all_occurrences);
  return all_occurrences;
}

void SuffixTree::FindAllOccurrences(SuffixNode *node, std::vector<int> &all_occurrences) {
  if(node->suffix_index != -1){
    all_occurrences.push_back(node->suffix_index);
    return;
  }
  for(auto it: node->children){
    FindAllOccurrences(it.second, all_occurrences);
  }
}

void SuffixTree::Clear(SuffixNode *node) {
  for (auto it: node->children) {
    if(it.second){
      Clear(it.second);
    }
  }
  delete node;
}

SuffixNode *SuffixTree::NewSuffixNode(int start, int *end) {
  return new SuffixNode(root, start, end);
}

bool SuffixTree::ChangeActivePointByWalkDown(SuffixNode *node) {
  if (active_length >= node->EdgeLength()) {
    active_edge += node->EdgeLength();
    active_length -= node->EdgeLength();
    active_node = node;
    return true;
  }
  return false;
}

void SuffixTree::ExtendPhaseOf(int pos) {
  leaf_end = pos;
  prev_internal_node = nullptr;
  ++remaining_suffix;

  while (remaining_suffix > 0) {
    if (active_length == 0) {
      active_edge = pos;
    }

    if (!active_node->HasChild(text[active_edge])) {
      active_node->SetChild(text[active_edge], NewSuffixNode(pos, &leaf_end));
    } else {
      SuffixNode *next_node = active_node->GetChild(text[active_edge]);
      if (ChangeActivePointByWalkDown(next_node)) {
        continue;
      }

      if (text[next_node->start + active_length] == text[pos]) {
        ++active_length;
        break;
      }

      next_node->SetChild(text[next_node->start + active_length],
                          NewSuffixNode(next_node->start + active_length, &leaf_end));
      next_node->SetChild(text[pos], NewSuffixNode(pos, &leaf_end));
      next_node->SetEnd(new int(next_node->start + active_length - 1));

      if (prev_internal_node != nullptr) {
        prev_internal_node->SetSuffixLink(next_node);
      }
      prev_internal_node = next_node;
    }

    if (active_node == root && active_length > 0) {
      ++active_edge;
      --active_length;
    } else {
      if (active_node != root) {
        active_node = active_node->suffix_link;
      }
    }

    --remaining_suffix;
  }
}

void SuffixTree::UpdateSuffixIndex(SuffixNode *node, int accumulate) {
  accumulate += node->EdgeLength();

  if (node->children.size() == 0) {
    node->SetSuffixIndex(text.length() - accumulate);
    return;
  }

  for (auto it: node->children) {
    UpdateSuffixIndex(it.second, accumulate);
  }
}

void SuffixTree::BuildTree() {
  root = new SuffixNode(nullptr, -1, new int(-1));
  active_node = root;
  active_edge = -1;
  active_length = 0;
  remaining_suffix = 0;

  for (int phase = 0; phase < text.length(); ++phase) {
    ExtendPhaseOf(phase);
  }

  UpdateSuffixIndex(root, 0);
}

} // namespace string
} // namespace algorithms_archive

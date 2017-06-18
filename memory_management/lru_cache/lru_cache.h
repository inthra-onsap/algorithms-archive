#ifndef ALGORITHMS_ARCHIVE_LRU_CACHE_H_
#define ALGORITHMS_ARCHIVE_LRU_CACHE_H_

#include <list>
#include <unordered_map>

namespace algorithms_archive {
namespace memory_management {

template<typename KeyType, typename ValueType>
class LruCache {
 public:
  LruCache(int capacity_) : capacity{capacity_} {}

  ValueType Get(KeyType key) {
    auto item = cache.find(key);
    if (item == cache.end()) {
      return -1;
    }
    PromoteRecentlyUsed(item);
    return item->second.first;
  }

  void Set(KeyType key, ValueType value) {
    auto item = cache.find(key);
    if (item != cache.end()) {
      PromoteRecentlyUsed(item);
      item->second.first = value;
      return;
    }

    if (cache.size() >= capacity) {
      cache.erase(lru_rank.back());
      lru_rank.pop_back();
    }

    lru_rank.push_front(key);
    cache.insert({key, {value, lru_rank.begin()}});
  }

 private:
  int capacity;
  // <key, <value, key_iterator>>
  std::unordered_map<KeyType, std::pair<ValueType, typename std::list<KeyType>::iterator>> cache;
  std::list<KeyType> lru_rank;

  void PromoteRecentlyUsed(typename std::unordered_map<
      KeyType,
      std::pair<ValueType,
      typename std::list<KeyType>::iterator> >::iterator &item) {
    lru_rank.erase(item->second.second);
    lru_rank.push_front(item->first);
    item->second.second = lru_rank.begin();
  }
};

} // namespace memory_management
} // namespace algorithms_archive

#endif //ALGORITHMS_ARCHIVE_LRU_CACHE_H_

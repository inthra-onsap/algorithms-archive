#include "lru_cache.h"

#include <gtest/gtest.h>

namespace algorithms_archive {
namespace memory_management {
class LruCacheTest : public testing::Test {
};

TEST_F(LruCacheTest, ExpectInsertionSuccess) {
  LruCache<int, int> lru(2);

  lru.Set(1, 1);
  EXPECT_EQ(1, lru.Get(1));
}

TEST_F(LruCacheTest, ExpectItemRemovedFromLruCacheSuccess) {
  LruCache<int, int> lru(2);
  lru.Set(1, 1);
  lru.Set(2, 2);
  lru.Set(3, 3);
  EXPECT_EQ(-1, lru.Get(1));
}
}
}
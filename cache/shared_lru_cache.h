#include "LRUCache.h"
#include <mutex>
using namespace std;

template<class T>
struct default_hash
{
  size_t operator()(const T& v)
  {
    return v;
  }
};

template <class T>
struct default_equal
{
  bool operator()(const T& a, const T& b)
  {
    return a == b;
  }
};

static const int kNumShardBits = 4;
static const int kNumShards = 1 << kNumShardBits;

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC = default_hash<KEY_TYPE>, class EQUAL_FUNC = default_equal<KEY_TYPE>>
class ShardedLRUCache
{
private:
  LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC> shard_[kNumShards];

  static uint32_t Shard(uint32_t hash)
  {
    return hash >> (32 - kNumShardBits);
  }

public:
  explicit ShardedLRUCache(size_t capacity)
  {
    const size_t per_shard = (capacity + (kNumShards - 1)) / kNumShards;
    for (int s = 0; s < kNumShards; s++) {
      shard_[s].SetCapacity(per_shard);
    }
  }
  ~ShardedLRUCache() = default;

   void Set(const KEY_TYPE& key, const VALUE_TYPE& value)
   {
     const uint32_t hash = HASH_FUNC()(key);
     return shard_[Shard(hash)].Set(key, value);
   }

   Pair<KEY_TYPE, VALUE_TYPE>* Get(const KEY_TYPE& key)
   {
     const uint32_t hash = HASH_FUNC()(key);
     return shard_[Shard(hash)].Get(key);
   }
};

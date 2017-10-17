#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "tbb/concurrent_hash_map.h"

using namespace std;

// 64-bit hash for 64-bit platforms

uint64_t MurmurHash64A ( const void * key, int len, unsigned int seed )
{
	const uint64_t m = 0xc6a4a7935bd1e995;
	const int r = 47;

	uint64_t h = seed ^ (len * m);

	const uint64_t * data = (const uint64_t *)key;
	const uint64_t * end = data + (len/8);

	while(data != end)
	{
		uint64_t k = *data++;

		k *= m;
		k ^= k >> r;
		k *= m;

		h ^= k;
		h *= m;
	}

	const unsigned char * data2 = (const unsigned char*)data;

	switch(len & 7)
	{
	case 7: h ^= uint64_t(data2[6]) << 48;
	case 6: h ^= uint64_t(data2[5]) << 40;
	case 5: h ^= uint64_t(data2[4]) << 32;
	case 4: h ^= uint64_t(data2[3]) << 24;
	case 3: h ^= uint64_t(data2[2]) << 16;
	case 2: h ^= uint64_t(data2[1]) << 8;
	case 1: h ^= uint64_t(data2[0]);
	        h *= m;
	};

	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
}

struct Meta
{
  Meta(int32_t a, int32_t b):key1(a),key2(b){}
  int32_t key1;
  int32_t key2;
};

struct MetaHasher
{
  uint64_t operator ()(const Meta& key) const
  {
    unsigned int seed = 1;
    return static_cast<uint64_t>(MurmurHash64A(&key, sizeof(key), seed));
  }
};

struct MetaCompare
{
  bool operator ()(const Meta& a, const Meta& b) const
  {
    return a.key1 == b.key1 && a.key2 == b.key2;
  }
};
struct HashCompare {
  static uint64_t hash(const string& value)
  {
    char* ptr = const_cast<char*>(value.data());
    return MurmurHash64A(static_cast<void *>(ptr), value.length(), 1);
  }
};
struct info
{
  info(bool hit_cache = false, int32_t gbdt_index = -1,  double weight = 0.): hit_cache_(hit_cache), gbdt_index_(gbdt_index), weight_(weight){}
  bool hit_cache_;
  int32_t gbdt_index_;
  double weight_;
};

int main()
{
  //unordered_map<Meta, string, MetaHasher, MetaHasher> test_map;

  typedef tbb::concurrent_hash_map<string, info, HashCompare> hash_map;
  vector<shared_ptr<hash_map>> weight_cache_;
  shared_ptr<hash_map> feature0(new hash_map());
  weight_cache_.push_back(feature0);
  return 0;
}

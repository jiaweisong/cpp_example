#include "lru_cache.h"
#include "MurmurHash2_64.h"
#include <iostream>
using namespace std;

struct StrHash
{
  size_t operator()(const string& s)
  {
    char* ptr = const_cast<char*>(s.c_str());
    return MurmurHash64A(static_cast<void *>(ptr), s.length(), 0);
  }
};

int main()
{
  LRUCache<int, string> lru_cache(10, 100);
  lru_cache.Set(100, "songjw");
  string value;
  if (lru_cache.Get(100, value))
  {
    cout<<value<<endl;
  }

  SharedLRUCache<int, string> shared_lru_cache(10, 100);
  shared_lru_cache.Set(100, "songjw");
  if (shared_lru_cache.Get(100, value))
  {
    cout <<"come from shared_lru_cache "<< value << endl;
  }
  return 0;
}

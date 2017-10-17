//#include "hash_table.h"
//#include "LRUCache.h"
#include "shared_lru_cache.h"
#include "hash.h"
using namespace std;

struct str_hash
{
  int32_t operator()(const string& s)
  {
    return Hash(s.c_str(), s.length(), 0);
  }
};

int main()
{
//  HashTable<string, int, str_hash> table;
//  table.Insert("songjw", 1001);
//  table.Insert("shigf",  1001);
//  table.Insert("liuhb",  1001);
//
//  auto ptr = table.Lookup("songjw");
//  if (ptr != nullptr)
//  {
//    cout<<"key = "<<ptr->key<<" value = "<<ptr->value<<endl;
//  }

//  LRUCache<string, int, str_hash> cache;
//  cache.SetCapacity(100);
//  cache.Set("songjw", 1001);
//  Pair<string, int>* ptr = cache.Get("songjw");
//  if (ptr != nullptr)
//  {
//    cout<<"key = "<<ptr->key<<" value = "<<ptr->value<<endl;
//  }

  ShardedLRUCache<string, int, str_hash> cache(10);
  cache.Set("songjw", 1001);
  Pair<string, int>* ptr = cache.Get("songjw");
  if (ptr != nullptr)
  {
    cout<<"key = "<<ptr->key<<" value = "<<ptr->value<<endl;
  }
  return 0;
}

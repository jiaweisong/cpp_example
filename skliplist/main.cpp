#include <iostream>
#include <set>
#include "skiplist.h"

using namespace std;

typedef uint64_t Key;

struct Comparator {
  int operator()(const Key& a, const Key& b) const {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return +1;
    } else {
      return 0;
    }
  }
};


int main()
{
  Comparator cmp;
  Arena arena;
  SkipList<Key, Comparator> list(cmp, &arena);
  const int N = 2000;
  std::set<Key> keys;
  for (int i = 0; i < N; i++)
  {
    list.Insert(i);
    keys.insert(i);
  }

  for (auto it = keys.begin(); it != keys.end(); ++it)
  {
    if (!list.Contains(*it))
    {
      cout<<*it<<"\t";
    }
  }

  size_t * p = (size_t*)(arena.AllocateAligned(sizeof(size_t)));
  *p = 100;
   cout<<*p<<endl;
   list.NewNodeTest(100, 12);
  return 0;
}


#include "hash_table.h"
#include <mutex>
#include <iostream>
using namespace std;

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
class LRUCache
{
  public:
   using meta_ptr = Pair<KEY_TYPE, VALUE_TYPE>*;
  public:
    LRUCache();
    ~LRUCache();

    meta_ptr Get(const KEY_TYPE& key);
    void SetCapacity(size_t capacity) { capacity_ = capacity; }
    void Set(const KEY_TYPE& key, const VALUE_TYPE& value);
    void Release(meta_ptr e);
    void Erase(const KEY_TYPE& key);
    void Prune();

    size_t TotalCharge()
    {
      std::lock_guard<std::mutex> l(mutex_);
      return usage_;
    }

  private:
    void LRU_Remove(meta_ptr e);
    void LRU_Append(meta_ptr e);
    void Unref(meta_ptr e);

    size_t capacity_;
    size_t usage_;
    std::mutex mutex_;

    Pair<KEY_TYPE, VALUE_TYPE> lru_;
    HashTable<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC> table_;
};

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::LRUCache() : usage_(0), capacity_(0)
{
  // Make empty circular linked list
  lru_.next = &lru_;
  lru_.prev = &lru_;
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::~LRUCache()
{
  for (meta_ptr e = lru_.next; e != &lru_; ) {
    meta_ptr next = e->next;
    Unref(e);
    e = next;
  }
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::Unref(meta_ptr e)
{
    usage_ -= 1;
    delete e;
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::LRU_Remove(meta_ptr e)
{
  e->next->prev = e->prev;
  e->prev->next = e->next;
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::LRU_Append(meta_ptr e)
{
  // Make "e" newest entry by inserting just before lru_
  e->next = &lru_;
  e->prev = lru_.prev;
  e->prev->next = e;
  e->next->prev = e;
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
Pair<KEY_TYPE, VALUE_TYPE>* LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::Get(const KEY_TYPE& key)
{
  std::lock_guard<std::mutex> l(mutex_);
  meta_ptr e = table_.Lookup(key);
  if (e != nullptr) {
    LRU_Remove(e);
    LRU_Append(e);
  }
  return e;
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::Set(const KEY_TYPE& key, const VALUE_TYPE& value)
{
  std::lock_guard<std::mutex> l(mutex_);

  meta_ptr e = new Pair<KEY_TYPE, VALUE_TYPE>(key, value);
  LRU_Append(e);
  usage_ += 1;

  meta_ptr old = table_.Insert(e);
  if (old != nullptr) {
    LRU_Remove(old);
    Unref(old);
  }
  while (usage_ > capacity_ && lru_.next != &lru_) {
    meta_ptr old = lru_.next;
    LRU_Remove(old);
    table_.Remove(old->key);
    Unref(old);
  }
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::Erase(const KEY_TYPE& key)
{
  std::lock_guard<std::mutex> l(mutex_);
  meta_ptr e = table_.Remove(key);
  if (e != nullptr) {
    LRU_Remove(e);
    Unref(e);
  }
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::Prune()
{
  std::lock_guard<std::mutex> l(mutex_);
  for (meta_ptr e = lru_.next; e != &lru_; ) {
    meta_ptr next = e->next;
    if (e->refs == 1) {
      table_.Remove(e->key);
      LRU_Remove(e);
      Unref(e);
    }
    e = next;
  }
}

template<class KEY_TYPE, class VALUE_TYPE, class HASH_FUNC, class EQUAL_FUNC>
void LRUCache<KEY_TYPE, VALUE_TYPE, HASH_FUNC, EQUAL_FUNC>::Release(meta_ptr e)
{
  std::lock_guard<std::mutex> l(mutex_);
  Unref(e);
}


#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;


template<class KEY, class T>
struct Pair
{
  Pair(const KEY& k, const T& v) : key(k), value(v){}
  Pair() = default;
  KEY key;
  T value;
  Pair* next_hash = nullptr;
  Pair* next = nullptr;
  Pair* prev = nullptr;
};


//template<class KEY, class T, class HASH_FUNC = default_hash<KEY>, class EQUAL_FUNC = default_equal<KEY>>
template<class KEY, class T, class HASH_FUNC, class EQUAL_FUNC>
class HashTable
{
 public:
   using pair_ptr = Pair<KEY, T>*;
   using pair_ptr_ptr = Pair<KEY, T>**;
   HASH_FUNC hash_func;
   EQUAL_FUNC equal_func;

 private:
   uint32_t length_;
   uint32_t elems_;
   pair_ptr_ptr list_;

 public:
   HashTable() : length_(0), elems_(0), list_(nullptr) { Resize(); }
   ~HashTable() { delete[] list_; }

   pair_ptr Lookup(const KEY& key) {
     return *FindPointer(key);
   }

   pair_ptr Insert(pair_ptr pair)
   {
     assert(pair != nullptr);
     pair_ptr_ptr ptr = FindPointer(pair->key);
     pair_ptr old = *ptr;
     pair->next_hash = (old == nullptr ? nullptr : old->next_hash);
     *ptr = pair;
     if (old == nullptr)
     {
       ++elems_;
       if (elems_ > length_)
       {
         Resize();
       }
     }
     return old;
   }

   pair_ptr Insert(const KEY& key, const T& value)
   {
     pair_ptr pair = new Pair<KEY, T>(key, value);
     return Insert(pair);
   }

   pair_ptr Remove(const KEY& key) {
     pair_ptr_ptr ptr = FindPointer(key);
     pair_ptr result = *ptr;
     if (result != nullptr) {
       *ptr = result->next_hash;
       --elems_;
     }
     return result;
   }

   pair_ptr_ptr FindPointer(const KEY& key) {
     size_t hash = hash_func(key);
     pair_ptr_ptr ptr = &list_[hash & (length_ - 1)];
     while (*ptr != nullptr && !equal_func(key, (*ptr)->key))
     {
       ptr = &(*ptr)->next_hash;
     }
     return ptr;
   }

   void Resize() {
     uint32_t new_length = 4;
     while (new_length < elems_) {
       new_length *= 2;
     }
     pair_ptr_ptr new_list = new pair_ptr[new_length];
     memset(new_list, 0, sizeof(new_list[0]) * new_length);
     uint32_t count = 0;
     for (uint32_t i = 0; i < length_; i++) {
       pair_ptr h = list_[i];
       while (h != nullptr) {
         pair_ptr next = h->next_hash;
         size_t hash = hash_func(h->key);
         pair_ptr_ptr ptr = &new_list[hash & (new_length - 1)];
         h->next_hash = *ptr;
         *ptr = h;
         h = next;
         count++;
       }
     }
     assert(elems_ == count);
     delete[] list_;
     list_ = new_list;
     length_ = new_length;
   }
};


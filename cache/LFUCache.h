#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

template <class KEY_TYPE, class VALUE_TYPE>
class LFUCache
{
  struct Node
  {
    Node() = default;
    Node(const VALUE_TYPE& value) : val(value){}
    int64_t freq = 1;
    VALUE_TYPE val;
    typename list<KEY_TYPE>::iterator iter;
  };

  private:
    int capacity_;
    int size_;
    int min_freq_;
    unordered_map<KEY_TYPE, Node> key_values_;
    unordered_map<int64_t, list<KEY_TYPE>> freq_to_keys_;

  public:
    LFUCache(int capacity) : capacity_(capacity), size_(0) {}

    bool Get(const KEY_TYPE& key, VALUE_TYPE& value)
    {
      auto it = key_values_.find(key);
      if (it == key_values_.end())
      {
        return false;
      }
      Node& node = it->second;
      value = node.val;
      freq_to_keys_[node.freq].erase(node.iter);
      ++node.freq;
      freq_to_keys_[node.freq].push_front(key);
      node.iter = freq_to_keys_[node.freq].begin();
      if(freq_to_keys_[min_freq_].size() == 0)
      {
        min_freq_ = node.freq;
      }
      return true;
    }

    void Set(const KEY_TYPE& key, const VALUE_TYPE& value)
    {
      if(capacity_ <= 0)
      {
        return;
      }
      VALUE_TYPE old_value;
      if(Get(key, old_value))
      {
        key_values_[key].val=value;
        return;
      }

      if(size_ >= capacity_)
      {
        key_values_.erase( freq_to_keys_[min_freq_].back());
        freq_to_keys_[min_freq_].pop_back();
        --size_;
      }
      key_values_[key] = {Node(value)};
      freq_to_keys_[1].push_front(key);
      key_values_[key].iter = freq_to_keys_[1].begin();
      min_freq_ = 1;
      ++size_;
    }
};

//int main()
//{
//  LFUCache<int, int> cache(10);
//  cache.Set(100, 100);
//  int value;
//  if (cache.Get(100, value))
//  {
//    cout << value << endl;
//  }
//  return 0;
//}

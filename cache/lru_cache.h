#include <tbb/concurrent_hash_map.h>
#include <tbb/spin_rw_mutex.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

template< class ValueType>
class CacheNode
{
public:
  using Node    = std::shared_ptr<CacheNode<ValueType>>;
  using NodeRef = std::weak_ptr<CacheNode<ValueType>>;

  CacheNode(const ValueType& value, const int ttl) : pValue_(new ValueType(value)), expireTime_(0)
  {
    expireTime_ = time(NULL) + ttl + 1;
  }

  ~CacheNode()
  {
    if (pValue_ != nullptr)
    {
      delete pValue_;
      pValue_ = nullptr;
    }
  }

  static Node Create(const ValueType& value, int ttl)
  {
    return Node(new CacheNode<ValueType> (value, ttl));
  }

  ValueType* value()
  {
    return pValue_;
  }

  bool isExpired(time_t now)
  {
    return now >= expireTime_;
  }

private:
  ValueType* pValue_;
  time_t expireTime_;
};

template<class Type>
class ThreadSafeVector
{
  public:
    ThreadSafeVector() = default;
    ThreadSafeVector(size_t capacity){ values_.reserve(capacity); }
    void push_back(const Type& v)
    {
      rw_lock_.lock();
      values_.push_back(v);
      rw_lock_.unlock();
    }

    void pop_back()
    {
      rw_lock_.lock();
      values_.pop_back();
      rw_lock_.unlock();
    }

    size_t size()
    {
      rw_lock_.lock();
      values_.size();
      rw_lock_.unlock();
    }

    void clear_invalid()
    {
      rw_lock_.lock();
      time_t now = time(NULL);
      values_.erase(std::remove_if(values_.begin(), values_.end(), [&now](const Type& node){return node->isExpired(now);}), values_.end());
      rw_lock_.unlock();
    }
 private:
    tbb::spin_rw_mutex rw_lock_;
    vector<Type> values_;
};

template<class KeyType, class ValueType>
class LRUCache
{
public:
  using NodeRef = typename CacheNode<ValueType>::NodeRef;
  using Node = typename CacheNode<ValueType>::Node;
  using CONCURRENT_HASH_MAP = tbb::concurrent_hash_map<KeyType, NodeRef>;
  using CONCURRENT_VECTOR = ThreadSafeVector<Node>;

  explicit LRUCache(const int capacity, const int ttl = 0) : capacity_(capacity), ttl_(ttl){}
  LRUCache() = default;
  ~LRUCache() = default;

  void SetCapacity(const int capacity)
  {
    capacity_ = capacity;
  }

  void SetTTL(const int ttl)
  {
    ttl_ = ttl;
  }

  void Set(const KeyType& key, const ValueType& value)
  {
    if (values_.size() >= capacity_)
    {
      values_.clear_invalid();
    }
    Node node = CacheNode<ValueType>::Create(value, ttl_);
    NodeRef node_ref(node);
    typename CONCURRENT_HASH_MAP::accessor write_accessor;
    index_.insert(write_accessor, key);
    write_accessor->second = node_ref;
    values_.push_back(node);
  }

  bool Get(const KeyType& key, ValueType& value)
  {
    typename CONCURRENT_HASH_MAP::const_accessor read_accessor;
    time_t now = time(NULL);
    if (index_.find(read_accessor, key))
    {
      Node node = read_accessor->second.lock();
      if (node != nullptr && !node->isExpired(now))
      {
        value = *(node->value());
        return true;
      }
      index_.erase(key);
    }
    return false;
  }

private:
  int capacity_;
  int ttl_;
  CONCURRENT_HASH_MAP index_;
  CONCURRENT_VECTOR values_;
};


template <class T>
struct Default_Hash
{
  size_t operator()(const T& v)
  {
    return v;
  }
};

template<class KeyType, class ValueType, class Hash = Default_Hash<KeyType>>
class SharedLRUCache
{
  public:
    static const int kNumSharedBits = 8;
    static const int kNumShareds = 1 << kNumSharedBits;
    static const int kNumSharedsMask = 0xFF;
    explicit SharedLRUCache(const size_t capacity, const int64_t ttl = 0) : capacity_(capacity), ttl_(ttl)
    {
      const int pre_shared = (capacity + (kNumShareds - 1)) / kNumShareds;
      for (int i = 0; i < kNumShareds; ++i)
      {
        shared_[i].SetCapacity(pre_shared);
        shared_[i].SetTTL(ttl);
      }
    }

    void Set(const KeyType& key, const ValueType& value)
    {
      int32_t hash_value = Hash()(key);
      int32_t index = hash_value & kNumSharedsMask;
      shared_[index].Set(key, value);
    }

    bool Get(const KeyType& key, ValueType& value)
    {
      int32_t hash_value = Hash()(key);
      int32_t index = hash_value & kNumSharedsMask;
      return shared_[index].Get(key, value);
    }

  private:
    size_t capacity_;
    int64_t ttl_;
    LRUCache<KeyType, ValueType> shared_[kNumShareds];
};

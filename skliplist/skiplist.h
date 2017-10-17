#include <cassert>
#include <iostream>
#include "atomic_pointer.h"
#include "random.h"
#include "arena.h"

using namespace std;

template<typename Key, class Comparator>
class SkipList {
 private:
  struct Node;

 public:
  explicit SkipList(Comparator cmp, Arena* arena);
  void Insert(const Key& key);
  bool Contains(const Key& key) const;
  char* NewNodeTest(const Key& key, int height);

 private:
  enum { kMaxHeight = 12 };

  Comparator const compare_;
  Node* const head_;

  AtomicPointer max_height_;   // Height of the entire list

  inline int GetMaxHeight() const {
    return static_cast<int>(
        reinterpret_cast<intptr_t>(max_height_.NoBarrier_Load()));
  }

  Random rnd_;
  Arena* arena_;

  Node* NewNode(const Key& key, int height);
  int RandomHeight();
  bool Equal(const Key& a, const Key& b) const { return (compare_(a, b) == 0); }

  // Return true if key is greater than the data stored in "n"
  bool KeyIsAfterNode(const Key& key, Node* n) const;

  Node* FindGreaterOrEqual(const Key& key, Node** prev) const;

  Node* FindLessThan(const Key& key) const;

  Node* FindLast() const;

  // No copying allowed
  SkipList(const SkipList&);
  void operator=(const SkipList&);
};

// Implementation details follow
template<typename Key, class Comparator>
struct SkipList<Key,Comparator>::Node {
  explicit Node(const Key& k) : key(k) { }

  Key const key;

  Node* Next(int n) {
    assert(n >= 0);
    return reinterpret_cast<Node*>(next_[n].Acquire_Load());
  }
  void SetNext(int n, Node* x) {
    assert(n >= 0);
    next_[n].Release_Store(x);
  }

  Node* NoBarrier_Next(int n) {
    assert(n >= 0);
    return reinterpret_cast<Node*>(next_[n].NoBarrier_Load());
  }
  void NoBarrier_SetNext(int n, Node* x) {
    assert(n >= 0);
    next_[n].NoBarrier_Store(x);
  }

 private:
  AtomicPointer next_[1];
};

template<typename Key, class Comparator>
typename SkipList<Key,Comparator>::Node*
SkipList<Key,Comparator>::NewNode(const Key& key, int height) {
//  char* mem = arena_->AllocateAligned(sizeof(Node) + sizeof(AtomicPointer) * (height - 1));

  char* mem = static_cast<char*>(malloc(sizeof(Node) + sizeof(AtomicPointer) * (height - 1)));
  return new (mem) Node(key);
}

template<typename Key, class Comparator>
char* SkipList<Key,Comparator>::NewNodeTest(const Key& key, int height) {
  char* mem = arena_->AllocateAligned(sizeof(Node) + sizeof(AtomicPointer) * (height - 1));
  Node* node = new (mem) Node(key);
  cout<<node->key<<endl;
//  cout<<node->next_[11]<<endl;
  return mem;
}

template<typename Key, class Comparator>
int SkipList<Key,Comparator>::RandomHeight() {
  static const unsigned int kBranching = 4;
  int height = 1;
  while (height < kMaxHeight && ((rnd_.Next() % kBranching) == 0)) {
    height++;
  }
  assert(height > 0);
  assert(height <= kMaxHeight);
  return height;
}

template<typename Key, class Comparator>
bool SkipList<Key,Comparator>::KeyIsAfterNode(const Key& key, Node* n) const {
  return (n != NULL) && (compare_(n->key, key) < 0);
}

template<typename Key, class Comparator>
typename SkipList<Key,Comparator>::Node* SkipList<Key,Comparator>::FindGreaterOrEqual(const Key& key, Node** prev)
    const {
  Node* x = head_;
  int level = GetMaxHeight() - 1;
  while (true) {
    Node* next = x->Next(level);
    if (KeyIsAfterNode(key, next))
    {
      x = next;
    }
    else
    {
      if (prev != NULL)
        prev[level] = x;
      if (level == 0)
      {
        return next;
      } else {
        // Switch to next list
        level--;
      }
    }
  }
}

template<typename Key, class Comparator>
typename SkipList<Key,Comparator>::Node*
SkipList<Key,Comparator>::FindLessThan(const Key& key) const {
  Node* x = head_;
  int level = GetMaxHeight() - 1;
  while (true) {
    assert(x == head_ || compare_(x->key, key) < 0);
    Node* next = x->Next(level);
    if (next == NULL || compare_(next->key, key) >= 0) {
      if (level == 0) {
        return x;
      } else {
        // Switch to next list
        level--;
      }
    } else {
      x = next;
    }
  }
}

template<typename Key, class Comparator>
typename SkipList<Key,Comparator>::Node* SkipList<Key,Comparator>::FindLast()
    const {
  Node* x = head_;
  int level = GetMaxHeight() - 1;
  while (true) {
    Node* next = x->Next(level);
    if (next == NULL) {
      if (level == 0) {
        return x;
      } else {
        // Switch to next list
        level--;
      }
    } else {
      x = next;
    }
  }
}

template<typename Key, class Comparator>
SkipList<Key,Comparator>::SkipList(Comparator cmp, Arena* arena)
    : compare_(cmp),
      arena_(arena),
      head_(NewNode(0 /* any key will do */, kMaxHeight)),
      max_height_(reinterpret_cast<void*>(1)),
      rnd_(0xdeadbeef) {
  for (int i = 0; i < kMaxHeight; i++) {
    head_->SetNext(i, NULL);
  }
}

template<typename Key, class Comparator>
void SkipList<Key,Comparator>::Insert(const Key& key) {
  Node* prev[kMaxHeight];
  Node* x = FindGreaterOrEqual(key, prev);

  if (x != NULL && Equal(key, x->key))
  {
    return;
  }

  int height = RandomHeight();
  if (height > GetMaxHeight()) {
    for (int i = GetMaxHeight(); i < height; i++) {
      prev[i] = head_;
    }
    max_height_.NoBarrier_Store(reinterpret_cast<void*>(height));
  }

  x = NewNode(key, height);
  for (int i = 0; i < height; i++) {
    x->NoBarrier_SetNext(i, prev[i]->NoBarrier_Next(i));
    prev[i]->SetNext(i, x);
  }
}

template<typename Key, class Comparator>
bool SkipList<Key,Comparator>::Contains(const Key& key) const {
  Node* x = FindGreaterOrEqual(key, NULL);
  if (x != NULL && Equal(key, x->key)) {
    return true;
  } else {
    return false;
  }
}



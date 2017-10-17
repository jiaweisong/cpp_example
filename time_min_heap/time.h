#include <iostream>
#include <algorithm>
#include <sys/time.h>

using namespace std;

inline uint64_t GetCurrentTime()
{
  timeval time;
  gettimeofday(&time, NULL);
  return time.tv_sec*1e6 + time.tv_usec;
}

struct Time
{
  explicit Time() : time(GetCurrentTime()){}
  uint64_t time;
};

class TimeMinHeap
{
  public:
    void push_heap(Time& timestamp)
    {
      min_heap_.push_back(timestamp);
      std::push_heap(min_heap_.begin(), min_heap_.end());
    }

    Time pop_heap()
    {
      std::pop_heap(min_heap_.begin(), min_heap_.end());
    }
  private:
    vector<Time> min_heap_;
};


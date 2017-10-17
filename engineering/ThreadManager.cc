#include <iostream>
#include <memory>
#include <vector>
#include <future>
#include <functional>
#include "tbb/concurrent_queue.h"

using namespace std;

template <typename T>
class ThreadManager
{
  public:
    ThreadManager(string tag, int thread_nums = 0, int task_capacity = 100000):
      tag_(tag), thread_nums_(thread_nums), task_capacity_(task_capacity), running_(false)
    {
    }
    void start();
    void stop();
    void AddTask(std::shared_ptr<T>& data, std::function<void (std::shared_ptr<T>&)> routine);

    ThreadManager(const ThreadManager&) = delete;
    ThreadManager operator= (const ThreadManager&) = delete;
  private:
    static void* WorkThread(void*);
    void Worker();

  private:
    struct Task
    {
      std::shared_ptr<T> data_;
      std::function<void (std::shared_ptr<T>& data)> routine_;
      Task(){}
      Task(std::shared_ptr<T>& data, std::function<void (std::shared_ptr<T>& data)> routine):
        data_(data), routine_(routine)
        {}
    };

  private:
    bool running_;
    int thread_nums_;
    int task_capacity_;
    string tag_;
    vector<future<void*>> thread_objs_;
    tbb::concurrent_bounded_queue<Task> task_queue_;

};

template <typename T>
void ThreadManager<T>::AddTask(std::shared_ptr<T>& data, std::function<void (std::shared_ptr<T>& data)> routine)
{
  Task new_task(data, routine);
  task_queue_.push(new_task);
}

template <typename T>
void* ThreadManager<T>::WorkThread(void* arg)
{
  ThreadManager* tm = static_cast<ThreadManager *>(arg);
  tm->Worker();
  return nullptr;
}

template <typename T>
void ThreadManager<T>::Worker()
{
  while(running_)
  {
    Task t;
    task_queue_.pop(t);
    t.routine_(t.data_);
  }
}

template <typename T>
void ThreadManager<T>::start()
{
  running_ = true;
  //task_queue_.set_capacity(task_capacity_);
  for (int i = 0; i < thread_nums_; ++i)
  {
    thread_objs_.emplace_back(std::async(std::launch::async, ThreadManager<T>::WorkThread, this));
  }
}

template <typename T>
void ThreadManager<T>::stop()
{
  running_ = false;
  for (int i = 0; i < thread_nums_; ++i)
  {
    thread_objs_[i].get();
  }
}

void TestFunc(std::shared_ptr<int>& data)
{
  cout<<"hello world\n";
}

int main()
{
  ThreadManager<int> tm("thread_test", 10);
  tm.start();
  shared_ptr<int> ptr;
  tm.AddTask(ptr,TestFunc);
  tm.stop();
  return 0;
}

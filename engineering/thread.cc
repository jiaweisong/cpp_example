#include <iostream>
#include <thread>
#include <future>
#include <vector>

using namespace std;

int main()
{
  // future<type> type is same with return value type
  vector<future<int>> result;
  string name = "jiaweisong";
  for (int i = 0; i < 10; ++i)
  {
    auto local_process = [=]()
      {
        try
        {
          cout<<i<<name<<endl;
          return 0;
        }
        catch (std::exception& e)
        {
          return -1;
        }
      };
    // std::launch::deferred : the task is executed on the calling thread the first time its result is requested
    // std::launch::async : executed immediately
    result.emplace_back(std::async(std::launch::deferred, local_process));
  }
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    it->get();
  }
  return 0;
}

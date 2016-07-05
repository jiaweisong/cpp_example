#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <future>

using namespace std;
std::atomic<int> cnt = {0};

void f()
{
   for (int n = 0; n < 1000; ++n) {
    cnt.fetch_add(1, std::memory_order_relaxed);
  }

}

int main()
{
  //std::vector<std::thread> v;
  vector<future<void>> v;
  for (int n = 0; n < 10; ++n) {
    v.emplace_back(std::async(std::launch::async,f));
  }
  for (auto& t : v) {
    t.get();
  }
  std::cout << "Final counter value is " << cnt << '\n';
  return 0;
}

#include <iostream>
#include <random>
#include <vector>
using namespace std;
int main()
{
  int n = 100000;
  int sum = 0;
  int times = 10000;
  int total_t = 0;
  for (int i = 0; i < times; ++i)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    vector<int*> list(n, nullptr);
    clock_t start = clock();
    for (int i = 0; i < n; ++i)
    {
      list[i] = new int(dis(gen));
    }
    for (int i = 0; i < n; ++i)
    {
      sum += *(list[i]);
    }
    for (int i = 0; i < n; ++i)
    {
      delete list[i];
    }
    clock_t end = clock();
    total_t += (end - start);
  }
  cout<<"time : "<<total_t / times<<" us "<<"  sum = "<<sum<<endl;
  return 0;
}

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
using namespace std;

int main()
{
  vector<int32_t> list;
  int array_size = 65535;
  for (int i = 0; i < array_size; ++i)
  {
    list.push_back(std::rand() % 1024);
  }
  clock_t start1 = clock();
  ostringstream os;
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    os << *it << "\t";
  }
  os << "\n";
  double time1 = static_cast<double>(clock() - start1) / CLOCKS_PER_SEC;

  clock_t start2 = clock();
  string log;
  log.reserve(4096);
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    log.append(std::to_string(*it));
    log.append("\t");
  }
  log.append("\n");
  double time2 = static_cast<double>(clock() - start2) / CLOCKS_PER_SEC;

  std::cout << "os : " << time1 << std::endl;
  std::cout << "append : " << time2 << std::endl;
}

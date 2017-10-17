#include <iostream>
#include <map>
using namespace std;

int main()
{
  multimap<string, string> test_map;
  test_map.insert(std::pair<string, string>("songjw", "360"));
  test_map.insert(std::pair<string, string>("songjw", "china.chuzhou"));
  test_map.insert(std::pair<string, string>("yuandx", "yitu"));
  test_map.insert(std::pair<string, string>("yuandx", "china.wuhan"));
  test_map.insert(std::pair<string, string>("chengyu", "ucloud"));
  test_map.insert(std::pair<string, string>("chengyu", "china.wuyuan"));
  for (auto it = test_map.begin(); it != test_map.end(); ++it)
  {
    cout<<it->second<<endl;
  }
  cout<<endl;
  for (auto it = test_map.begin(); it != test_map.end(); it = test_map.upper_bound(it->first))
  {
    cout<<it->first<<endl;
  }
  return 0;
}

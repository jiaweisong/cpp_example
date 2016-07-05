#include <iostream>     // std::cout
#include <algorithm>    // std::find_if
#include <vector>       // std::vector
#include <set>

using namespace std;
struct Meta
{
  Meta(string name, string value):name_(name),value_(value){}
  string name_;
  string value_;
};

int main()
{
  vector<Meta> list;
  list.emplace_back("songjw","hello");
  list.emplace_back("yuandx","world");
  list.emplace_back("songjiawei","jiaweisong");

  vector<string> new_list;
  new_list.emplace_back("songjw","world");


/*
  for (auto& it : new_list)
  {
    vector<Meta>::iterator cit = find_if(list.begin(), list.end(), [&](const Meta& meta){ return meta.name_ ==  new_list.name_;});
    if (cit != list.end())
    {
      cout<<it<<endl;
    }
  }
*/

  set<string> name;
  name.insert("yuandx");
  name.insert("songjw");
  list.erase(remove_if(list.begin(),list.end(),[&](const Meta meta){ return name.find(meta.name_) != name.end(); }),list.end());
  for (auto& it : list)
  {
    cout<<it.name_<<endl;
  }
  return 0;
}

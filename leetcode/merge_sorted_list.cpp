#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int32_t> Merge(const vector<int32_t>& list1, const vector<int32_t>& list2)
{
  vector<int32_t> result;
  result.reserve(list1.size() + list2.size());
  auto it1 = list1.begin(), it2 = list2.begin();
  while (it1 != list1.end() && it2 != list2.end())
  {
    if (*it1 <= *it2)
    {
      result.push_back(*it1);
      ++it1;
    }
    else
    {
      result.push_back(*it2);
      ++it2;
    }
  }
  if (it1 != list1.end())
  {
    result.insert(result.end(), it1, list1.end());
  }
  if (it2 != list2.end())
  {
    result.insert(result.end(), it2, list2.end());
  }
  return result;
}


vector<int32_t> BinaryMerge(const vector<int32_t>& list1, const vector<int32_t>& list2)
{
  vector<int32_t> result;
  result.reserve(list1.size() + list2.size());
  auto base_it = list1.begin(), base_end = list1.end();
  for (auto add_it = list2.begin(); add_it != list2.end(); ++add_it)
  {
    auto split_it = std::upper_bound(base_it, base_end, *add_it);
    result.insert(result.end(), base_it, split_it);
    result.push_back(*add_it);
    base_it = split_it;
  }
  result.insert(result.end(), base_it, base_end);
  return result;
}


int main()
{
  vector<int32_t> array0 = {9, 12, 17, 15, 10, 20, 60, 65, 14, 19};
  vector<int32_t> array1 = {11, 12, 27, 30, 50, 18, 6,  5, 25, 15};
  std::sort(array0.begin(), array0.end());
  std::sort(array1.begin(), array1.end());
//  vector<int32_t> result = Merge(array0, array1);
  vector<int32_t> result = BinaryMerge(array0, array1);

  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout<<*it<<"\t";
  }
  cout<<endl;
  return 0;
}

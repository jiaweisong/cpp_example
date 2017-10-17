#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>
#include <unordered_map>
#include <initializer_list>
using namespace std;


class Solution {
public:
  void InsertTuple(map<int, int>& count, pair<int, int>& p1,pair<int, int>& p2, set<tuple<int, int, int, int>>& result_set)
  {
    if (p1.first == p2.first && p1.second == p2.second && !result_set.empty())
    {
      return;
    }
    if (p1.first == p2.first || p1.first == p2.second)
    {
      if ((p1.first == p1.second || p2.first == p2.second) && count[p1.first] < 3)
      {
        return;
      }
      if (count[p1.first] < 2)
      {
        return;
      }
    }
    else if (p1.second == p2.first || p1.second == p2.second)
    {
      if ((p1.first == p1.second || p2.first == p2.second) && count[p1.second] < 3)
      {
        return;
      }
      if (count[p1.second] < 2)
      {
        return;
      }
    }    
    if (p1.second <= p2.first)
    {
      result_set.insert(make_tuple(p1.first, p1.second, p2.first, p2.second));
    }
    else if (p1.first <= p2.first && p1.second <= p2.second)
    {
      result_set.insert(make_tuple(p1.first, p2.first, p1.second, p2.second));
    }
    else if (p1.first <= p2.first && p1.second > p2.second)
    {
      result_set.insert(make_tuple(p1.first, p2.first, p2.second, p1.second));
    }
    else if (p1.first >= p2.second)
    {
      result_set.insert(make_tuple(p2.first, p2.second, p1.first, p1.second));
    }
    else if (p2.first <= p1.first && p1.second <= p2.second)
    {
      result_set.insert(make_tuple(p2.first, p1.first, p1.second, p2.second));
    }
    else if (p2.first <= p1.first && p2.second <= p1.second)
    {
      result_set.insert(make_tuple(p2.first, p1.first, p2.second, p1.second));
    }
  }

  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ret;
    if (nums.size() < 4)
    {
      return ret;
    }

    std::sort(nums.begin(), nums.end());
    unordered_multimap<int, pair<int, int>> two_sum_map;
    vector<int> two_sum_vec;
    map<int, int> count;
    for (int i = 0; i < nums.size(); ++i)
    {
      if (count.find(nums[i]) != count.end())
      {
        ++count[nums[i]];
      }
      else
      {
        count[nums[i]] = 1;
      }
      if (i != 0 && nums[i] == nums[i-1])
      {
        continue;
      }
      for (int j = i+1; j < nums.size(); ++j)
      {
        int sum = nums[i] + nums[j];
        two_sum_vec.push_back(sum);
        two_sum_map.emplace(make_pair(sum,make_pair(nums[i],nums[j])));
      }
    }

    std::sort(two_sum_vec.begin(), two_sum_vec.end());
    set<tuple<int, int, int, int>> result_set;
    
    int begin = 0, end = two_sum_vec.size() - 1;
    int before = -1;
    while (begin < end)
    {
      if (before != -1 && two_sum_vec[begin] == two_sum_vec[before])
      {
        ++begin;
        continue;
      }
      int sum = two_sum_vec[begin] + two_sum_vec[end];
      if (sum == target)
      {
        before = begin;
        auto range1 = two_sum_map.equal_range(two_sum_vec[begin]);
        auto range2 = two_sum_map.equal_range(two_sum_vec[end]);
        for (auto it1 = range1.first; it1 != range1.second; ++it1)
        {
           for (auto it2 = range2.first; it2 != range2.second; ++it2)
           {
             InsertTuple(count, it1->second, it2->second, result_set);
           }
        }
        ++begin;
        --end;
      }
      else if (sum < target)
      {
        ++begin;
      }
      else
      {
        --end;
      }
    }//end while
    for (auto it : result_set)
    {
      ret.emplace_back(initializer_list<int>{get<0>(it), get<1>(it), get<2>(it), get<3>(it)});
    }
    return ret;
  }
};

void print(vector<vector<int>> res)
{
  for (int i = 0; i < res.size(); ++i)
  {
    vector<int>& zero = res[i];
    cout<<zero[0]<<"    "<<zero[1]<<"    "<<zero[2]<<"    "<<zero[3]<<endl;
  }
}
int main()
{
  Solution s;
  vector<vector<int>> ret;
  vector<int> nums = {-1,0,1,2,-1,-4};
  ret = s.fourSum(nums, -1);
  print(ret);

  vector<int> nums1 = {0,0,0,0};
  ret = s.fourSum(nums1, 0);
  print(ret);

  vector<int> nums2 = {1,4,-3,0,0,0,5,0};
  ret = s.fourSum(nums2, 0);
  print(ret);
  return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>

using namespace std;

class Solution {
public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> ret;
    if (nums.size() < 4)
    {
      return ret;
    }    
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); ++i)
    {
      if (i != 0 && nums[i] == nums[i-1])
      {
        continue;
      }
      for (int j = i+1; j < nums.size(); ++j)
      {
        if (j != i+1 && nums[j] == nums[j-1])
        {
          continue;
        }
        int begin = j+1, end = nums.size()-1;
        int before = -1;
        while (begin < end)
        {
           if (before != -1 && nums[before] == nums[begin])
           {
             ++begin;
             continue;
           }
           int sum =nums[i] + nums[j] + nums[begin] + nums[end];
           if (sum == target)
           {
             before = begin;
             ret.emplace_back(initializer_list<int>{nums[i],nums[j],nums[begin],nums[end]}); 
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
      }//end for (j..)
    }//end for(i..)
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

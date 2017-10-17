#include <iostream>
#include <initializer_list>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    std::sort(nums.begin(),nums.end());
    for (int index = 0; index < nums.size(); ++index)
    {
      if (index != 0 && nums[index] == nums[index-1])
      {
        continue;
      }
      int sum = -nums[index];
      int begin = index + 1, end = nums.size() - 1;
      int before = -1;
      while (begin  < end)
      {
        if (before != -1 && nums[before] == nums[begin])
        {
          ++begin;
          continue;
        }
        int tmp = nums[begin] + nums[end];
        if (tmp == sum)
        {
          res.emplace_back(initializer_list<int>{-sum,nums[begin],nums[end]});
          before = begin;
          ++begin;
          --end;
        }
        else if (tmp < sum)
        {
          ++begin;
        }
        else
        {
          --end;
        }
      }//end while
    }//end for
    return res;
  }
};

void print(vector<vector<int>> res)
{
  for (int i = 0; i < res.size(); ++i)
  {
    vector<int>& zero = res[i];
    cout<<zero[0]<<"    "<<zero[1]<<"    "<<zero[2]<<endl;
  }
}
int main()
{
  Solution s;
  vector<vector<int>> ret;
  vector<int> nums1 = {-1,0,1,2,-1,-4};
  ret = s.threeSum(nums1);
  print(ret);

 vector<int> nums2 = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
  ret = s.threeSum(nums2);
  print(ret);
  return 0;
}


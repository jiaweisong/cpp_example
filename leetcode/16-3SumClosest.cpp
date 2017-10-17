#include <iostream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

class Solution {
public:
  int threeSumClosest(vector<int>& nums, int target) {
    std::sort(nums.begin(),nums.end());
    int closest = (numeric_limits<int>::max)(); 
    if (nums.size() == 0)
    {
      return 0;
    }
    if (nums.size() == 1)
    {
      return nums[0];
    }
    else if (nums.size() == 2)
    {
      return nums[0] + nums[1];
    }
    int ret = 0;
    for (int index = 0; index < nums.size(); ++index)
    {
      int begin = index + 1, end = nums.size() - 1;
      while (begin < end)
      {
        int sum = nums[index] + nums[begin] + nums[end];
        if (sum == target)
        {
          return sum;
        }
        else if (sum < target)
        {
          if (target - sum < closest)
          {
            closest = target - sum;
            ret = sum;
          }
          ++begin;
        }
        else
        {
          if (sum - target < closest)
          {
            closest = sum - target;
            ret = sum;
          }
          --end;
        }
      }//end while
    }// end for
    return ret;    
  }
};

void expect_true(int ret, int res)
{
  if (ret != res)
  {
    cout<<"ret = "<<ret<<" != "<<res<<endl;
  }
}
int main()
{
  Solution s;
  int ret = 0;
  vector<int> nums1 = {-1, 2, 1, -4,};
  ret = s.threeSumClosest(nums1,1);
  expect_true(ret,2);
  return 0;
}

#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
  int binarySearch(vector<int>& nums, int begin, int end, int target)
  {
    while (begin <= end)
    {
      int mid = (begin + end) >> 1;
      if (nums[mid] == target)
      {
        end = mid - 1;
      }
      else if (nums[mid] < target)
      {
        begin = mid + 1;
      }
      else
      {
        end = mid - 1;
      }
    }
    return begin;
  }
    
  int searchInsert(vector<int>& nums, int target) {
    return binarySearch(nums, 0, nums.size()-1, target);
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
  vector<int> nums = {1,2,3,4};
  ret = s.searchInsert(nums, 0);
  expect_true(ret,0);

  ret = s.searchInsert(nums, 1);
  expect_true(ret,0);
  
  ret = s.searchInsert(nums, 2);
  expect_true(ret,1);
  
  ret = s.searchInsert(nums, 5);
  expect_true(ret,4);
 
  vector<int> null_num; 
  ret = s.searchInsert(null_num, 5);
  expect_true(ret,0);
}

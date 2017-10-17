#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int search(vector<int>& nums, int target) {
    int begin = 0, end = nums.size() - 1;
    while (begin <= end)
    {
      int mid = (begin + end) >> 1;
      //cout <<"begin = "<<begin<<"    "<<"mid = "<<mid<<"    "<<"end = "<<end<<endl;
      if (nums[mid] == target)
      {
        return mid;
      }
      else if (nums[begin] <= target && target < nums[mid])
      {
        end = mid - 1;
      }
      else if (nums[begin] >= target && target < nums[mid] && nums[begin] > nums[mid])
      {
        end = mid - 1;
      }
      else if (nums[begin] <= target && target > nums[mid] && nums[begin] > nums[mid])
      {
        end = mid - 1;
      }
      else if (nums[mid] < target && target <= nums[end])
      {
        begin = mid + 1;
      }
      else if (nums[mid] > target && target <= nums[end] && nums[mid] > nums[end])
      {
        begin = mid + 1;
      }
      else if (nums[mid] < target && target >= nums[end] && nums[mid] > nums[end])
      {
        begin = mid + 1;
      }
      else
      {
        cout<<"unknown operator\n";
        break;
      }
    }//end while    
    return -1;
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
  vector<int> nums =  {3,4,5,6,7,8,9,0,1,2};
  vector<int> index = {7,8,9,0,1,2,3,4,5,6};
  for (int i = 0; i < nums.size(); ++i)
  {
    ret = s.search(nums,i);
    expect_true(ret, index[i]);
  }
  return 0;
}

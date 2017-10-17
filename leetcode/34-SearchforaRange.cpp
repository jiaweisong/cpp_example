#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int binarySearch(vector<int>& nums, int begin, int end, int target, bool is_left = false)
  {
    while (begin <= end)
    {
      int mid = (begin + end) >> 1;
      if (nums[mid] == target)
      {
        if (is_left)
        {
          end = mid - 1;
        }
        else
        {
          begin = mid + 1;
        }
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
    return is_left ? begin : begin - 1;
  }

  vector<int> searchRange(vector<int>& nums, int target) {
    vector<int> res = {-1, -1};
    int left  = binarySearch(nums, 0, nums.size()-1, target, true);
    int right = binarySearch(nums, 0, nums.size()-1, target, false);
    if (left <= right)
    {
      res[0] = left;
      res[1] = right;
    }
    return res;
  }
};

int main()
{
  Solution s;
  vector<int> res;
  vector<int> nums = {3,4,5,6,8,8,8,9};
  res = s.searchRange(nums,8);
  cout<<res[0]<<"    "<<res[1]<<endl;
  return 0;
}

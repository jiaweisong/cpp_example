#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target)
  {
    vector<int> result;
    size_t size = nums.size();
    for (int begin = 0, end = size - 1; begin < end; )
    {
      if (nums[begin] + nums[end] == target)
      {
        result.push_back(nums[begin]);
        result.push_back(nums[end]);
        return result;
      }
      else if (nums[begin] + nums[end] < target)
      {
        ++begin;
      }
      else 
      {
        --end;
      }
    }
    return result;
  }
};

int main()
{
    Solution s;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = s.twoSum(nums,target);
    for (auto item : result)
    {
      cout<<item<<"    ";
    }
    return 0;
}

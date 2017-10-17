#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  bool canJump(vector<int>& nums)
  {
    int step = 0;
    for (size_t i = 0; i < nums.size() - 1; ++i)
    {
      int current = i + nums[i];
      if (current > step)
      {
        step = current;
      }
      if (step >= nums.size() - 1)
      {
        return true;
      }
      if (i >= step && nums[i] == 0)
      {
        return false;
      }
    }
    return nums.size() <= 1;
  }

//  bool canJump(vector<int>& nums)
//  {
//    return nums.size() == 0 || Jump(nums, 0);
//  }

  bool Jump(vector<int>& nums, size_t start)
  {
    if (start >= nums.size() - 1)
    {
      return true;
    }
    size_t i = nums[start];
    while(i > 0 && !Jump(nums, start+i))
    {
      --i;
    }
    return i != 0;
  }
};

int main()
{
  Solution s;

//  vector<int> nums = {3, 2, 1, 0, 4};
//  vector<int> nums = {2, 3, 1, 1, 4};
  vector<int> nums = {0,1, 0};
  for (auto it = nums.begin(); it != nums.end(); ++it)
  {
    cout << *it << "\t";
  }
  if (s.canJump(nums))
  {
    cout << "is valid" << endl;
  }
  else
  {
    cout << "is invalid" << endl;
  }
  return 0;
}

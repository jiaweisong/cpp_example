#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int maxSubArray(vector<int>& nums)
  {
    if (nums.size() <= 0)
    {
      return 0;
    }
    int left = 0, right = nums.size() - 1;
    int sum = MaxSubArrayRange(nums, left, right);
    cout<<"begin = "<<left<<" end = "<<right<<" sum = "<<sum<<endl;
    return sum;
  }

  int MaxSubArrayRange(const vector<int>& nums, int& left, int& right)
  {
    if (left == right)
    {
      return nums[left] >= nums[right] ? nums[left] : nums[right];
    }
    int mid = (left + right) >> 1;
    int left_begin = left, left_end = mid;
    int right_begin = mid+1, right_end = right;
    int max_left = MaxSubArrayRange(nums, left_begin, left_end);
    int max_right = MaxSubArrayRange(nums, right_begin, right_end);

    int max_tmp_left = nums[mid], tmp_left = nums[mid], tmp_begin = mid;
    for (int i = mid - 1; i >= left; --i)
    {
      tmp_left += nums[i];
      if (tmp_left >= max_tmp_left)
      {
        max_tmp_left = tmp_left;
        tmp_begin = i;
      }
    }

    int max_tmp_right = nums[mid+1], tmp_right = nums[mid+1], tmp_end = mid+1;
    for (int i = mid+2; i <= right; ++i)
    {
      tmp_right += nums[i];
      if (tmp_right >= max_tmp_right)
      {
        max_tmp_right = tmp_right;
        tmp_end = i;
      }
    }

    int sum = max_tmp_left + max_tmp_right;
    if (sum >= max_left && sum >= max_right)
    {
      left = tmp_begin; right = tmp_end;
      return sum;
    }

    if (max_left >= sum && max_left >= max_right)
    {
      left = left_begin; right = left_end;
      return max_left;
    }

    left = right_begin; right = right_end;
    return max_right;
  }
};

int main()
{
  Solution solution;
  vector<int> array = {-2,1,-3,4,-1,2,1,-5,4};
  solution.maxSubArray(array);

  array = {0, 0, 0, 0, 0};
  solution.maxSubArray(array);

  array = {0, 1, 2, 3, 4};
  solution.maxSubArray(array);

  array = {-2, -1};
  solution.maxSubArray(array);
  return 0;
}

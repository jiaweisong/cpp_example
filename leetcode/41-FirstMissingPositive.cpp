#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int firstMissingPositive(vector<int>& nums) {
    int i = 0, new_index = 0, size = nums.size();
    while (i < size)
    {
       new_index = nums[i] - 1;
       if (nums[i] == i+1 || new_index < 0 || new_index >= size || nums[new_index] == new_index + 1)
       {
         ++i;
       }
       else
       {
         swap(nums[i], nums[new_index]);
       }
    }
    for (int i = 0; i < size; ++i)
    {
      if (nums[i] != i+1)
      {
        return i+1;
      }
    }   
    return (size == 0 || nums[0] <= 0) ? 1 : size + 1;
  }
};

int main()
{
  Solution s;
  int ret = 0;
  vector<int> nums = {1,1};
  ret = s.firstMissingPositive(nums);
  cout<<ret<<endl;
  return 0;
}

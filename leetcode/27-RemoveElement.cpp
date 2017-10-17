#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int removeElement(vector<int>& nums, int val) {
    if (nums.empty())
    {
      return 0;
    }
    int begin = 0, end = nums.size() - 1;
    while (begin < end)
    {
      if (nums[begin] != val)
      {
        ++begin;
      }
      else if (nums[end] == val)
      {
        --end;
      }
      else
      {
        nums[begin] = nums[end];
        ++begin;
        --end;
      }
    }
    return nums[end] == val ? end : end+1; 
  }
};

int main()
{
  return 0;
}

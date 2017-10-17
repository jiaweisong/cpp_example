#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int removeDuplicates(vector<int>& nums) {
    int begin = 0, end = 1;
    if (nums.size() <= 1)
    {
      return nums.size();
    }
    while (end < nums.size())
    {
      if (nums[begin] != nums[end])
      { 
        if (begin != end-1)
        {
          nums[begin+1] = nums[end];
        }
        ++begin;
      }
      ++end;
    }
    if (begin == 0)
    {
      return 1;
    }
    return nums[begin -1] == nums[end -1] ? begin : begin + 1;    
  }
};

int main()
{
  return 0;
}

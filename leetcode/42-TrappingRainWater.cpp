#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
  int trap(vector<int>& height) {
    int size = height.size();
    int begin = 0, end = size - 1;
    int sum = 0, tmp_height = 1;

    while (begin <= end)
    {
      if (height[begin] < tmp_height)
      {
        if (height[begin] != 0)
        {
          sum = height[begin] >= tmp_height ? sum - tmp_height : sum - height[begin];
        }
        ++begin;
      }
      else if (height[end] < tmp_height)
      {
        if (height[end] != 0)
        {
          sum = height[end] >= tmp_height ? sum - tmp_height : sum - height[end];
        }
        --end;
      }
      else
      {
        sum = sum + (end - begin + 1);
        ++tmp_height;
      }
    }
    cout<<height[begin]<<"    "<<height[end]<<"    "<<tmp_height<<"    "<<sum<<endl;
    return sum;    
  }
};

int main()
{
  Solution s;
  int ret = 0;
  vector<int> nums = {0,1,0,2,1,0,1,3,2,1,2,1};
  ret = s.trap(nums);
  return 0;
}

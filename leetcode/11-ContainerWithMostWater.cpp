#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution {
public:
  int maxArea(vector<int>& height) {
    int max_area = 0;
    int begin = 0, end = height.size() - 1;
    while (begin < end)
    {
      int tmp_area = (end - begin) * std::min(height[begin],height[end]);
      if (tmp_area > max_area)
      {
        max_area = tmp_area;
      }
      if (height[end] > height[begin] && height[begin] < height[begin + 1])
      {
        ++begin;
      }
      else if (height[begin] > height[end] && height[end] <height[end - 1])
      {
        --end;
      }
      else
      {
        height[begin] > height[end] ? --end : ++begin;
      }
    }
    return max_area;    
  }
};

void expect_true(int ret, int res)
{

}
int main()
{
  Solution s;
  int ret = 0;
  vector<int> v1 = {5,3,7,6,2,5,9,4};
  ret = s.maxArea(v1);
  cout<<ret<<endl;
  return 0;
}

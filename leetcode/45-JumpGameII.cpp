#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int jump(vector<int> nums) {
    int size = nums.size();
    if (size == 1)
    {
      return 0;
    }
    int step = 0;
    int curr_index = 1, last_index = nums[0], next_index = 0;
    while (last_index < size - 1)
    {
       ++step;
       while (curr_index <= last_index)
       {
         int tmp = curr_index + nums[curr_index];
         next_index = next_index < tmp ? tmp : next_index;
         ++curr_index; 
       }
       last_index = next_index;
    }
    return step + 1;
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
  ret = s.jump({2,3,1,1,4});
  expect_true(ret, 2);

  ret = s.jump({8,2,4,4,4,9,5,2,5,8,8,0,8,6,9,1,1,6,3,5,1,2,6,6,0,4,8,6,0,3,2,8,7,6,5,1,7,0,3,4,8,3,5,9,0,4,0,1,0,5,9,2,0,7,0,2,1,0,8,2,5,1,2,3,9,7,4,7,0,0,1,8,5,6,7,5,1,9,9,3,5,0,7,5});
  expect_true(ret, 13);
  return 0;
}

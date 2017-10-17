#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
  void permutations(vector<int>& nums, int start, vector<vector<int>>& result)
  {
    if (start == nums.size() - 1)
    {
      result.push_back(nums);
      return;
    }

    set<int> invalid_nums;
    for (int i = start; i < nums.size(); ++i)
    {
      if (invalid_nums.find(nums[i]) == invalid_nums.end())
      {
        invalid_nums.insert(nums[i]);
        std::swap(nums[start], nums[i]);
        permutations(nums, start+1, result);
        std::swap(nums[start], nums[i]);
      }
    }
  }

  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> result;
    permutations(nums, 0, result);
    return result;
  }
};

int main()
{
  Solution s;
  //vector<int> nums = {0,1,9,0,0};
  vector<int> nums = {1,1,2,2};
  vector<vector<int>> res = s.permuteUnique(nums);
  for (int i = 0; i < res.size(); ++i)
  {
      for (int j = 0; j < res[i].size(); ++j)
      {
        cout<<res[i][j]<<"    ";
      }
      cout<<endl;
  }
  return 0;
}

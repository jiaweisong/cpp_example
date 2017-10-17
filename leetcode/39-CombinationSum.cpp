#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
  bool DeepSearch(vector<int>& nums, int target, vector<int>& res, vector<vector<int>>& ret)
  {
    if (0 == target)
    {
      return true;
    }
    else if (target < 0)
    {
      return false;
    }
    for (int i = 0; i < nums.size(); ++i)
    {
      if (res.empty() || res.back() <= nums[i])
      {
        res.push_back(nums[i]);
      }
      else
      {
        continue;
      }
      if (DeepSearch(nums, target - nums[i], res, ret))
      {
        ret.push_back(res);
      }
      res.pop_back();
    }
    return false;
  }

  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> ret;
    sort(candidates.begin(),candidates.end());
    vector<int> res;
    DeepSearch(candidates, target, res, ret);
    return ret;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> ret;
  vector<int> nums = {1,2,4,3};
  ret = s.combinationSum(nums, 10);
  for (int i = 0; i < ret.size(); ++i)
  {
    for (int j = 0; j < ret[i].size(); ++j)
    {
      cout<<ret[i][j]<<"    ";
    }
    cout<<endl;
  }
  cout<<endl;
  return 0;
}

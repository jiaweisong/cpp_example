#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
  bool DeepSearch(vector<int>& nums, int pos, int target, vector<int>& res, vector<vector<int>>& ret)
  {
    if (0 == target)
    {
      return true;
    }
    else if (target < 0)
    {
      return false;
    }
    for (int i = pos; i < nums.size(); ++i)
    {
      if (i != pos && nums[i] == nums[i-1])
      {
        continue;
      }

      res.push_back(nums[i]);
      if (DeepSearch(nums, i + 1, target - nums[i], res, ret))
      {
        ret.push_back(res);
      }
      res.pop_back();
    }
    return false;
  }

  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    vector<vector<int>> ret;
    sort(candidates.begin(),candidates.end());
    vector<int> res;
    DeepSearch(candidates, 0, target, res, ret);
    return ret;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> ret;
  vector<int> nums = {10,1,2,7,6,1,5};
  ret = s.combinationSum2(nums, 8);
  for (int i = 0; i < ret.size(); ++i)
  {
    for (int j = 0; j < ret[i].size(); ++j)
    {
      cout<<ret[i][j]<<"    ";
    }
    cout<<endl;
  }
  return 0;
}


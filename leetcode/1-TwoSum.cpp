#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target)
  {
   map<int,size_t> num2index;
    vector<int> result;

    for (size_t index = 0; index < nums.size(); ++index)
    {
      num2index.insert(std::make_pair(nums[index],index));
    }

    for(size_t index = 0; index < nums.size(); ++index)
    {
      int another = target - nums[index];
      map<int,size_t>::iterator it;
      if ( (it = num2index.find(another)) != num2index.end() && it->second != index)
      {
        result.push_back(index);
        result.push_back(it->second);
        return result;
      }
    }
    return result;
  }//end twoSum
};

int main()
{
  vector<int> nums = {3,2,4};
  int target = 6;
  Solution s;
  vector<int> result = s.twoSum(nums,target);
  for (auto item : result)
  {
    cout<<item<<"    ";
  }
  return 0;
}

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> result;
    result.resize(strs.size());
    unordered_map<string,int> string2index;
    int index = 0;
    for (int i = 0; i < strs.size(); ++i)
    {
      string str_sorted(strs[i]);
      sort(str_sorted.begin(),str_sorted.end());
      auto it = string2index.find(str_sorted);
      if (it != string2index.end())
      {
        result[it->second].emplace_back(strs[i]);
      }
      else
      {
        string2index[str_sorted] = index;
        result[index].emplace_back(strs[i]);
        ++index;
      }
    }
    result.resize(index);
    for (int i = 0; i < result.size(); ++i)
    {
      make_heap(result[i].begin(), result[i].end());
      sort_heap(result[i].begin(), result[i].end());
    }
    return result;
  }
};

int main()
{
  Solution s;
  vector<string> strs = {"and","dan"};
  vector<vector<string>> result = s.groupAnagrams(strs);
  for (int i = 0; i < result.size(); ++i)
  {
    for (int j = 0; j < result[i].size(); ++j)
    {
      cout<<result[i][j]<<"    ";
    }
    cout<<endl;
  }
  return 0;
}

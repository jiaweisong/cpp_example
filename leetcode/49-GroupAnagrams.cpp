#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> result;
    result.resize(strs.size());
    map<char,int> char2index;
    int index = 0;
    while (!strs.empty())
    {
      make_heap(strs.begin(),strs.end(), greater<string>());
      string& str = strs.front();

      int pos = 0;
      bool is_new = false;
      for (int i = 0; i < str.length(); ++i)
      {
        auto it = char2index.find(str[i]);
        if (it != char2index.end())
        {
          pos = (pos < it->second) ? it->second : pos;
        }
        else
        {
          is_new = true;
          char2index[str[i]] = index;
        }
      }
      if (is_new == true)
      {
        result[index].emplace_back(str);
        ++index;
      }
      else
      {
        result[pos].emplace_back(str);
      }
      pop_heap(strs.begin(),strs.end());
      strs.pop_back();
    }
    result.resize(index);
    return result;
  }
};

int main()
{
  Solution s;
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
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

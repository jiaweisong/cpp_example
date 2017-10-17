#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
  string longestCommonPrefix(vector<string>& strs) {
    if (strs.empty())
    {
      return "";
    }
    string common = strs[0];
    for (int index = 1; index < strs.size(); ++index)
    {
      string& str = strs[index];
      int len = 0;
      for (; len < str.length() && len < common.length(); ++len)
      {
        if (str[len] != common[len])
        {
          break;
        }
      }
      common.resize(len);
    }
    return common;
  }
};

int main()
{
  Solution s;
  vector<string> strs;
  strs.push_back("abced");
  strs.push_back("abcef");
  strs.push_back("abc");
  string ret = s.longestCommonPrefix(strs);
  cout<<ret<<endl;
  return 0;
}

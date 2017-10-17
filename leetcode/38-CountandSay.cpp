#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  string countAndSay(int n)
  {
    if (n < 1)
    {
      return "";
    }
    if (n == 1)
    {
      return "1";
    }
    string s = countAndSay(n-1);
    string ret;
    ret.reserve(64);
    int count = 1;
    int begin = 0, end = begin + 1;
    while (end < s.length())
    {
      if (s[begin] == s[end])
      {
        ++count;
        ++end;
      }
      else
      {
        ret.push_back(count + '0');
        ret.push_back(s[begin]);
        count = 1;
        begin = end;
        ++end;
      }
    }
    ret.push_back(count + '0');
    ret.push_back(s.back());
    return ret;
  }
};


int main()
{
  Solution s;
  string ret;
  for (int i = 1; i < 10; ++i)
  {
    ret = s.countAndSay(i);
    cout<<ret<<endl;
  }
}

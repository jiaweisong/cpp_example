#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    if (s.empty())
    {
      return 0;
    }
    size_t size = s.length();
    size_t begin = 0, end = 0, max_length = 0;
    std::map<char,size_t> char2index;

    while (end < size)
    {
      map<char,size_t>::iterator it = char2index.find(s[end]);
      if (it != char2index.end() && it->second >= begin)
      {
        size_t tmp_length = end - begin;
        max_length = std::max(tmp_length, max_length);
        begin = char2index[s[end]] + 1;
      }
      char2index[s[end]] = end;
      ++end;
    }//end while
    size_t tmp_length = end - begin;
    return std::max(tmp_length, max_length); 
  }
};

void expect_true(int ret, int res)
{
  if (res != ret)
  {
    cout<<"ret "<< ret <<" != " << res <<endl;
  }
}
int main()
{
   Solution s;
   string str1 = "cbabcadac";
   int ret = s.lengthOfLongestSubstring(str1);
   expect_true(ret,4);
   
   string str2;
   ret = s.lengthOfLongestSubstring(str2);
   expect_true(ret, 0);
   
   string str3 = "aaaa";
   ret = s.lengthOfLongestSubstring(str3);
   expect_true(ret,1);
   return 0;
}

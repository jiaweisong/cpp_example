#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    if (s.empty())
    {
      return s;
    }
    int begin = 0, end = 0, max = 1;
    size_t size = s.length();
    while (end < size)
    {
      int begin1 = end, end1 = end;
      int begin2 = end, end2 = begin2 + 1;
      while (begin1 >= 0 && end1 < size && s[begin1] == s[end1])
      {
        --begin1;
        ++end1;
      }
      while (begin2 >= 0 && end2 < size && s[begin2] == s[end2])
      {
        --begin2;
        ++end2;
      }
      int max1 = end1 - begin1 - 1;
      int max2 = end2 - begin2 - 1;
      if (max1 > max2 && max1 > max)
      {
        begin = begin1 + 1;
        max = max1;
      }
      else if (max2 > max1 && max2 > max)
      {
        begin = begin2 + 1;
        max = max2;
      }
	  ++end;
    }//end while
    return s.substr(begin,max);
  }
};

void expect_true(string ret, string res)
{
  if (ret.compare(res) != 0)
  {
    cout<< "ret = "<<ret <<" != "<<res<<endl;
  }
}

int main()
{
  Solution s;
  string s1 = "cbabcadac";
  string ret = s.longestPalindrome(s1);
  expect_true(ret,"cbabc");
  
  string s2 = "xabbaabbay";
  ret = s.longestPalindrome(s2);
  expect_true(ret,"abbaabba");
  
  string s3 = "aaaa";
  ret = s.longestPalindrome(s3);
  expect_true(ret,"aaaa");
  
  string s4 = "eeeee";
  ret = s.longestPalindrome(s4);
  expect_true(ret,"eeeee");
  
  return 0;
}

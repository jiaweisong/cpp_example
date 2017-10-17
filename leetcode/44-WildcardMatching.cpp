#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
 
  bool isMatch(const char* s, const char* p)
  {
    const char* nextp = nullptr;
    const char* nexts = nullptr;
    while (*s != '\0')
    {
      if (*s == *p || *p == '?')
      {
        ++s;
        ++p;
      }
      else if (*p == '*')
      {
        nextp = p;
        nexts = s;
        ++p;
      }
      else if (nextp != nullptr)
      {
        p = nextp + 1;
        s = nexts + 1;
        ++nexts;
      }
      else
      {
        return false;
      }
    }
    while (*p == '*')
    {
      ++p;
    }
    return *p == '\0';    
  }

  bool isMatch(string s, string p) {
    return isMatch(s.c_str(), p.c_str()); 
  }
};

void expect_true(bool ret, bool res, string ret_str, string res_str)
{
  if (ret != res)
  {
    cout<<"ret = "<<ret_str<<" != "<<res_str<<endl;
  }
}

int main()
{
  Solution ss;
  bool ret = false;
  string s,p;
  s = "";
  p = "";
  ret = ss.isMatch(s, p);
  expect_true(ret,true,s,p);

  s = "cab";
  p = "c*ab";
  ret = ss.isMatch(s, p);
  expect_true(ret,true,s,p);

  s = "cabab";
  p = "c*ab";
  ret = ss.isMatch(s, p);
  expect_true(ret, true, s, p);

  s = "cab";
  p = "a*ab";
  ret = ss.isMatch(s, p);
  expect_true(ret, false, s, p);

  s = "cab";
  p = "cab";
  ret = ss.isMatch(s, p);
  expect_true(ret, true, s, p);

  s = "";
  p = "*";
  ret = ss.isMatch(s, p);
  expect_true(ret, true, s, p);

  s = "";
  p = "?";
  ret = ss.isMatch(s, p);
  expect_true(ret, false, s, p);

  s = "";
  p = "*ab";
  ret = ss.isMatch(s, p);
  expect_true(ret, false, s, p);

  s = "aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba";
  p ="a*******b";
  ret = ss.isMatch(s, p);
  expect_true(ret, false, s, p);

  s = "abbabaaabbabbaababbabbbbbabbbabbbabaaaaababababbbabababaabbababaabbbbbbaaaabababbbaabbbbaabbbbababababbaabbaababaabbbababababbbbaaabbbbbabaaaabbababbbbaababaabbababbbbbababbbabaaaaaaaabbbbbaabaaababaaaabb";
  p = "**aa*****ba*a*bb**aa*ab****a*aaaaaa***a*aaaa**bbabb*b*b**aaaaaaaaa*a********ba*bbb***a*ba*bb*bb**a*b*bb";
  ret = ss.isMatch(s, p);
  expect_true(ret, false, s, p);
  return 0;
}

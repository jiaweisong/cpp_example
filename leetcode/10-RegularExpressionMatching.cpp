#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
   bool isMatch(const char *s, const char *p)
   {
     if (*p == '\0')
     {
       return (*s == '\0' && *p == '\0');
     }

     if (*(p+1) != '*')
     {
       if (*s == '\0' || (*s != *p && *p != '.'))
       {
         return false;
       }
       return isMatch(++s,++p);
     }
     else
     {
       int count = 0;
       while ((*s == *p) || (*p == '.' && *s != '\0'))
       {
         if (isMatch(s+1,p+2))
         {
           return true;
         }
         ++s;
         ++count;
       }
       return isMatch(s,p+2) || isMatch(s-count,p+2);
     }
   }
   bool isMatch(string s, string p) {
     return isMatch(s.c_str(), p.c_str());   
  }
};

void expect_true(bool ret, bool res, string s, string p)
{
  if (ret != res)
  {
    cout<<"string s = "<<s<<" != "<<p<<endl;
  }
}
int main()
{
  Solution s;
  bool ret = false;
  string s1, p1;
  ret = s.isMatch(s1,p1);
  expect_true(ret, true,s1,p1);

  string s2 = "aaa";
  string p2 = "ab*a";
  ret = s.isMatch(s2, p2);
  expect_true(ret,false,s2,p2);
  
  string s3 = "ab";
  string p3 = ".*";
  ret = s.isMatch(s3,p3);
  expect_true(ret,true,s3,p3);

  string s4 = "bbbbbba";
  string p4 = ".*a*a";
  ret = s.isMatch(s4,p4);
  expect_true(ret,true,s4,p4);
  
  string s5 = "aab";
  string p5 = "c*a*b";
  ret = s.isMatch(s5,p5);
  expect_true(ret,true,s5,p5);
  
  string s6 = "aaa";
  string p6 = ".*b";
  ret = s.isMatch(s6,p6);
  expect_true(ret,false,s6,p6);

  string s7 = "a";
  string p7 = "ab*";
  ret = s.isMatch(s7,p7);
  expect_true(ret,true,s7,p7);
  string s8 = "a";
  string p8 = ".*..a*";
  ret = s.isMatch(s8,p8);
  expect_true(ret,false,s8,p8);
  return 0;
}

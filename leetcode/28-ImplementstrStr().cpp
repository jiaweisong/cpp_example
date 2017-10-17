#include <iostream>
using namespace std;
class Solution {
public:
  int strStr(string haystack, string needle) {
    if (needle.empty())
    {
      return 0;
    }    
    if (haystack.empty())
    {
      return -1;
    }
    int* next = new int[needle.length()+1];
    next[0] = -1;
    for (int i = 0, j = -1; i < needle.length();)
    {
      if (j == -1 || needle[i] == needle[j])
      {
        ++i;
        ++j;
        next[i] = j;
      }
      else
      {
        j = next[j];
      }
    }
    for (int i =0; i<needle.length(); ++i)
    {
      cout<<next[i]<<"   ";
    }
    cout<<endl;
    int i = 0, j = 0;
    int length1 = haystack.length(), length2 = needle.length();
    while (i < length1 && j < length2 )
    {
      if (haystack[i] == needle[j])
      {
        ++i;
        ++j;
      }
      else
      {
        j = next[j];
        if (j < 0)
        {
          j = 0;
          ++i;
        }
      }
    }
    cout<<i<<"   "<<j<<endl;
    delete next;
    return j == length2 ? i - length2 : -1;
  }
};

int main()
{
  Solution s;
  int ret = 0;
  ret = s.strStr("mississippi","pi");
  cout<<ret<<endl;
  return 0;
}

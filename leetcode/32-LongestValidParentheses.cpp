#include <iostream>
#include <stack>
using namespace std;
class Solution {
public:
  int DeepSearch(stack<pair<char,int>>& mystack, string& s, int size, int pos, int& count, int& end)
  {
    int max = count;
    if (pos >= size)
    {
      return max;
    }
    if (s[pos] == '(' && pos+1 < size)
    {
      mystack.push(make_pair('(', pos));
      if(s[pos+1] == '(')
      {
        int tmp_count = 0;
        max = DeepSearch(mystack, s, size, pos+1, tmp_count, ++end);
        cout<<"count = "<<count<<" tmp_count = "<<tmp_count<<"size ="<<mystack.size()<<endl;
        if (mystack.empty() || mystack.top().second < pos)
        {
          count += tmp_count;
        }
        else
        {
          mystack.pop();
        }
      }
      else
      {
        max = DeepSearch(mystack, s, size, pos+1, count, ++end);
      }
      return count > max ? count : max;  
    }
    else
    {
      if (s[pos] == ')' && !mystack.empty())
      {
        ++count;
        mystack.pop();
        return DeepSearch(mystack, s, size, pos+1, count, ++end);
      }
      else
      {
        return max;
      }           
    }
  }
  int longestValidParentheses(string s) {
    int max = 0;
    int end = 0, size = s.length();
    stack<pair<char,int>> mystack;
    while (end < size)
    {
      int begin = end;
      int count = 0;
      int tmp_max = DeepSearch(mystack, s, size, begin, count, end);
      max = tmp_max > max ? tmp_max : max;
      ++end;
    }
    return max<<1;
  }
};

void expect_true(int ret, int res)
{
  if (ret != res)
  {
    cout<<"ret "<<ret<<" != "<<res<<endl;
  }
}
int main()
{
  Solution s;
  int ret = 0;
  ret = s.longestValidParentheses(")(((()))()(()))(");
  expect_true(ret,4);
}

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  void Recursion(int pos, int left, int right, int n, char* res, vector<string>& ret)
  {
    if (pos == n<<1)
    {
      ret.push_back(res);
      return;
    }
    if (left < n)
    {
      res[pos] = '(';
      Recursion(pos+1, left+1, right, n, res, ret);
    }
    if (right < left)
    {
      res[pos] = ')';
      Recursion(pos+1, left, right+1, n, res, ret);
    }
  }
  vector<string> generateParenthesis(int n) {
    vector<string> ret;
    if (n <= 0)
    {
      return ret;
    }
    int size = n<<1;
    char* res = new char(size + 1);
    res[size] = '\0';
    Recursion(0, 0, 0, n, res, ret);
    return ret;
  }
};

int main()
{
  Solution s;
  vector<string> ret;
  ret = s.generateParenthesis(3);
  for (int i = 0; i < ret.size(); ++i)
  {
    cout<<ret[i]<<endl;
  }
  return 0;
}

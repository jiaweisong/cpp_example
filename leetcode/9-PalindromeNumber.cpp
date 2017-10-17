#include <iostream>
using namespace std;

class Solution {
public:
    int reverse(int x,int sum)
    {
      if (x / 10 == 0)
      {
        return sum * 10 + x; 
      }
      else
      {
        return reverse(x / 10, sum * 10 + x % 10);
      }
    }
    bool isPalindrome(int x) {
      if (x < 0)
      {
        return false;
      }
      return reverse(x,0) == x;
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
  cout << -2147447412 / 10 <<endl;
  cout<<-2147447412 % 10 <<endl;
  
  ret = s.reverse(-2147447412 , 0);
  expect_true(ret,1);

  ret = s.reverse(121, 0);
  expect_true(ret,121);
  return 0;
}

#include <iostream>
#include <limits>
using namespace std;

class Solution {
public:
  int divide(int dividend, int divisor) {
    const int MAX_INT = (numeric_limits<int>::max)();
    const int MIN_INT = (numeric_limits<int>::min)();

    int ret = 0; 

    if (0 == divisor)
    {
      return MAX_INT;
    }
    if (1 == divisor)
    {
      return dividend;
    }
    if (-1 == divisor)
    {
      return MIN_INT == dividend ? MAX_INT : -dividend;
    }
    if (MIN_INT == divisor)
    {
      return MIN_INT == dividend ? 1 : 0;
    }
    if (MIN_INT == dividend)
    {
      ret = 1;
      dividend += abs(divisor);
    }
    bool is_negative  = ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) ? true : false;

    dividend = abs(dividend);
    divisor  = abs(divisor);
    int count = 0;
    while (divisor <= (dividend >> 1))
    {
      ++count;
      divisor = divisor << 1;
    }
    while (count >= 0)
    {
      if (dividend >= divisor)
      {
        ret = ret + (1 << count);
        dividend = dividend - divisor;
      }
      divisor = divisor >> 1;
      --count;
    }
    return is_negative ? -ret : ret; 
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
  ret = s.divide(-10, 3);
  expect_true(ret, -3); 

  ret = s.divide(2147483647, -2);
  expect_true(ret, -1073741823); 

  ret = s.divide((numeric_limits<int>::min)(), -1);
  expect_true(ret, (numeric_limits<int>::max)());

  ret = s.divide((numeric_limits<int>::min)(), (numeric_limits<int>::max)());
  expect_true(ret, -1);

  ret = s.divide((numeric_limits<int>::min)(), (numeric_limits<int>::min)());
  expect_true(ret, 1);

  ret = s.divide((numeric_limits<int>::max)(), (numeric_limits<int>::min)());
  expect_true(ret, 0);
  
  return 0;
}

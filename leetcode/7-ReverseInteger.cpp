#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

class Solution {
public:
  int reverse(int x) {
    if (x > (numeric_limits<int>::max)() || x < (numeric_limits<int>::min)())
    {
      return 0;
    }
    bool is_negative = x > 0 ? false : true;
    int num = abs(x);
    int new_num = 0 ,unit = 0;
	int max_int = (numeric_limits<int>::max)() / 10;
	int max_mod = (numeric_limits<int>::max)() - max_int;
    while (num > 0)
    {
      unit = num % 10;
      num = num / 10;
      new_num = new_num * 10 + unit;     
      if (new_num > max_int || (new_num == max_int && num > max_mod))
      {
        return 0;
      }
    }    
    if (is_negative)
    {
      new_num *= -1;
    }
    return new_num;
  }
};

void expect_true(int ret, int res)
{
  if (ret != res)
  {
    cout<<"\nret "<<ret<<" != "<<res<<endl;
  }
}

int main()
{
  Solution s;
  int ret = 0;
  //ret =s.reverse(-123);
  //expect_true(ret,-321);

  ret = s.reverse(1534236469);
  expect_true(ret,0);

  //ret = s.reverse(1000);
  //expect_true(ret,1);

  //ret = s.reverse(-1000);
  //expect_true(ret,-1);

  //ret = s.reverse(-1001);
  //expect_true(ret,-1001);
  return 0;
}

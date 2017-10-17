#include <iostream>
#include <limits>
using namespace std;

class Solution {
public:
  double myPow(double x, int n) {
    if (n == 0)
    {
      return 1.0;
    }
    if (n < 0)
    {
     if (n == std::numeric_limits<int>::min())
     {
       return 1.0 / (myPow(x, std::numeric_limits<int>::max()) * x);
     }
     else
     {
       return 1.0 / myPow(x, -n);
     }
    }
    double ret = 1.0;
    while (n > 0)
    {
      if (n&1 > 0)
      {
        ret *= x;
      }
      n >>= 1;
      x *= x;
    }
    return ret;
  }
};

int main()
{
  Solution s;
  double res = s.myPow(2.0, 3);
  cout<<res<<endl;
  return 0;
}

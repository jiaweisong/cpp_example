#include <iostream>
using namespace std;

class Solution
{
public:
  int climbStairs(int n)
  {
    if (n == 1 || n == 2)
      return n;
    int a = 1, b = 2, c = 0;
    while (n-- > 2)
    {
      c = a + b;
      a = b;
      b = c;
    }
    return c;
  }

//  int climbStairs(int n)
//  {
//    if (n < 0)
//      return 0;
//    if (n == 0)
//      return 1;
//    return climbStairs(n-1) + climbStairs(n-2);
//  }
};


int main()
{
  Solution s;
  int n = 0;

  n = 1;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;


  n = 2;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;

  n = 3;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;

  n = 4;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;

  n = 5;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;

  n = 6;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;

  n = 7;
  cout << "n = " << n << "result = " << s.climbStairs(n) << endl;
  return 0;
}

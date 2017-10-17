#include <iostream>
using namespace std;

class Solution
{
public:
  string addBinary(string a, string b)
  {
    if (a.empty() || b.empty())
      return a.empty() ? b : a;

    int i = a.length() - 1, j = b.length() - 1;
    string& s = i > j ? a : b;
    int k = s.length() - 1;
    int mod = 0;
    while (i >= 0 && j >= 0)
    {
      int c = a[i] + b[j] + mod - '0' - '0';
      if (c > 1)
      {
        s[k] = '0' + c - 2;
        mod = 1;
      }
      else
      {
        s[k] = '0' + c;
        mod = 0;
      }
      --i; --j; --k;
    }
    k = i >= 0 ? i : j;
    while (k >= 0 && mod > 0)
    {
      int c = s[k] + mod - '0';
      if (c > 1)
      {
        s[k] = '0';
        mod = 1;
      }
      else
      {
        s[k] = '1';
        mod = 0;
      }
      --k;
    }
    if (mod > 0)
    {
      string tmp = '1' + s;
      return tmp;
    }
    return s;
  }
};


int main()
{
  Solution s;
  string a, b, result;

  a = "0", b = "0";
  result = s.addBinary(a, b);
  cout << result << " = " <<  a << " + " << b << endl;

  a = "", b = "11";
  result = s.addBinary(a, b);
  cout << result << " = " <<  a << " + " << b << endl;

  a = "111", b = "11";
  result = s.addBinary(a, b);
  cout << result << " = " <<  a << " + " << b << endl;

  a = "111", b = "111";
  result = s.addBinary(a, b);
  cout << result << " = " <<  a << " + " << b << endl;
  return 0;
}

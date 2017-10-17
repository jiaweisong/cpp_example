#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  string multiply(string num1, string num2) {
    int mod = 0, carry = 0, value = 0;
    int size1 = num1.length(), size2 = num2.length();
    int size = size1 + size2;
    int pos = 0, count = size;
    vector<int> tmp(size,0);
    string ret;
    ret.reserve(size);
    for (int i = size1 - 1; i >= 0; --i)
    {
      carry = 0;
      --count;
      pos = count;
      for(int j = size2 - 1; j >= 0; --j)
      {
        value = (num1[i] - '0') * (num2[j] - '0') + carry;
        carry = value / 10;
        mod = value % 10;
        tmp[pos] += mod;
        if (tmp[pos] > 9)
        {
          tmp[pos] = tmp[pos] - 10;
          tmp[pos-1] += 1;
        }
        --pos;
      }
      tmp[pos] += carry;
      if (tmp[pos] > 9)
      {
        tmp[pos] = tmp[pos] - 10;
        tmp[pos-1] += 1;
      }
    }
    int i = 0;
    while (i < size && tmp[i] == 0)
    {
      ++i;
    }
    if (i >= size)
    {
      return "0";
    }
    for (; i < tmp.size(); ++i)
    {
      ret.push_back(tmp[i] + '0');
    }
    return ret;
  }
};

void expect_true(string ret, string res)
{
  if (ret.compare(res) != 0)
  {
    cout<<"ret = "<<ret<<" != "<<res<<endl;
  }
}
int main()
{
  Solution s;
  string ret;
  ret = s.multiply("99","0");
  expect_true(ret, "9801");
  return 0;
}

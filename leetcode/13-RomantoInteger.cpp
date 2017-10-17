#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <stack>
using namespace std;

class Solution {
public:
  int romanToInt(string s) {
    map<char, int> char2int;
    char2int.insert(std::make_pair('I',1));
    char2int.insert(std::make_pair('V',5));
    char2int.insert(std::make_pair('X',10));
    char2int.insert(std::make_pair('L',50));
    char2int.insert(std::make_pair('C',100));
    char2int.insert(std::make_pair('D',500));
    char2int.insert(std::make_pair('M',1000));

    size_t size = s.length();
    map<char, int>::iterator it;
    int before = 0;
    int num = 0;
    for (int index = size - 1; index >= 0; --index)
    {
      if (num > 2999)
      {
        cout<<"invalid num"<<endl;
        return 0;
      }
      if ((it = char2int.find(s[index])) != char2int.end())
      {
        if (it->second < before)
        {
          num -= it->second;
        }
        else
        {
          num += it->second;
        }
        before = it->second;
      }
      else
      {
        cout<<"can't find  ";
        return 0;
      }
    }
    return num;
  }
};

void expect_true(int ret, int res)
{
  if (ret != res)
  {
    cout<<"ret = "<<ret<<" != "<<res<<endl;
  }
}

int main()
{
  Solution s;
  int ret = 0;

  ret = s.romanToInt("I");
  expect_true(ret,1);

  ret = s.romanToInt("V");
  expect_true(ret,5);

  ret = s.romanToInt("X");
  expect_true(ret,10);

  ret = s.romanToInt("L");
  expect_true(ret,50);

  ret = s.romanToInt("C");
  expect_true(ret,100);

  ret = s.romanToInt("MCMLXXXIV");
  expect_true(ret,1984);
  return 0;
}

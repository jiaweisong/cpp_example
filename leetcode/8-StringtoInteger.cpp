#include <iostream>
#include <limits>
using namespace std;

class Solution {
public:
  int myAtoi(string str) {
    if (str.empty())
    {
      return 0;
    }
    size_t size = str.length();
    int num = 0;
    bool is_negative = false;
    int index = 0;
   
	int max_int = (numeric_limits<int>::max)() / 10;
	int max_mod = (numeric_limits<int>::max)() - max_int*10;

    for (index = 0; index < size; ++index)
    {
      if (str[index] == ' ')
      {
        continue;
      }
      else if (str[index] == '+')
      {
        ++index;
        break;
      }
      else if (str[index] == '-')
      {
        is_negative = true;
        ++index;
        break;
      }
      else
      {
        break;
      }
    }
    for (; index < size; ++index)
    {
      if (str[index] >= '0' && str[index] <= '9')
      {
		if (num > max_int) 
		{
		  return is_negative ? (numeric_limits<int>::min)() : (numeric_limits<int>::max)();
		}
		else if (num == max_int && !is_negative && str[index] - '0' > max_mod)
		{
	      return numeric_limits<int>::max();
		}
		else if (num == max_int && is_negative && str[index] -'0' > max_mod + 1)
		{
		  return numeric_limits<int>::min();
		}
        num = num * 10 + (str[index] - '0');
		//cout<<num<<endl;
      }
      else  //input error, return directly 
      {
        break;
      }
    }
    if (is_negative)
    {
      num = -1 * num;
    }
    return num;
  }
};

void expect_true(int ret,int res)
{
  if (ret != res)
  {
    cout<<"ret "<<ret<<" != "<<res<<endl;
  }
}

int main()
{
  Solution s;
  int ret;

  string s1;
  ret = s.myAtoi(s1);
  expect_true(ret,0);

  string s2 = "-123";
  ret = s.myAtoi(s2);
  expect_true(ret,-123);

  string s3 = "-123s90";
  ret = s.myAtoi(s3);
  expect_true(ret,-123);

  string s4 = "-000001";
  ret = s.myAtoi(s4);
  expect_true(ret,-1);

  string s5 = "     +004500";
  ret = s.myAtoi(s5);
  expect_true(ret,4500);

  string s6 = "2147483648";
  ret = s.myAtoi(s6);
  expect_true(ret,2147483647);
  
  string s7 = "-2147483647";
  ret = s.myAtoi(s7);
  expect_true(ret,-2147483647);
  return 0;
}

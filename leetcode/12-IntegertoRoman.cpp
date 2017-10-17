#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <stack>
using namespace std;

class Solution {
public:

    string intToRoman(int num) {
      if (num < 1 || num > 3999)
      {
        return "";
      }
      map<int,char> int2char;
      int2char.insert(std::make_pair(1,'I'));
      int2char.insert(std::make_pair(5,'V'));
      int2char.insert(std::make_pair(10,'X'));
      int2char.insert(std::make_pair(50,'L'));
      int2char.insert(std::make_pair(100,'C'));
      int2char.insert(std::make_pair(500,'D'));
      int2char.insert(std::make_pair(1000,'M'));
      stack<char> roman;
      int mod = 0;
      int times = 1;
      map<int, char>::iterator it;
      map<int, char>::iterator lag;
      while (num > 0) 
      {
        mod = num % 10;
        num = num / 10;
        mod *= times;
        times *= 10;

        if (mod == 0)
        {
          continue;
        }
        if ((it = int2char.lower_bound(mod)) != int2char.end())
        {
          if (it->first == mod)
          {
            roman.push(it->second);
          }
          else if ((lag = int2char.find(it->first - mod)) != int2char.end())
          {
            roman.push(it->second);
            roman.push(lag->second);
          }
          else
          {
            stack<int> tmp_stack;
            while (mod > 0)
            {
              lag = int2char.lower_bound(mod);
              if (lag->first != mod)
              {
                --lag;
              }
              mod = mod - lag->first;
              tmp_stack.push(lag->second); 
            }
            while (!tmp_stack.empty())
            {
              roman.push(tmp_stack.top());
              tmp_stack.pop();
            }
          }
        }
        else
        {
          --it;
          while (mod > 0)
          {
            mod = mod - it->first;
            roman.push(it->second);
          }
        }
      }//end while

      string roman_str;
      roman_str.reserve(roman.size());
      while (!roman.empty())
      {
        roman_str.push_back(roman.top());
        roman.pop();
      }
      return roman_str;
    }
};

void expect_true(string ret, stirng res)
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
  ret = s.intToRoman(10);
  expect_true(ret,"X");

  ret = s.intToRoman(1984);
  expect_true(ret, "MCMLXXXIV");
  return 0;
}

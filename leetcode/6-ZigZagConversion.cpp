#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
  string convert(string s, int numRows) {
    if (s.empty() || numRows <= 0)
    {
      return s;
    }

    string ret;
    ret.reserve(s.length());
    int step = numRows == 1 ? 1 : (numRows - 1) << 1;
    size_t size = s.length();
    for (int line = 0; line < numRows; ++line)
    {
      if (line == 0 || line == numRows - 1)
      {
        int index = line;
        while (index < size)
        {
          ret.push_back(s[index]);
          index += step;
        }
      }
      else
      {
        int index = line;
        int j = 0;
        int odd_step = line << 1;
        int even_step = step - odd_step;

        while (true)
        {
          if (index < size)
          {
            ret.push_back(s[index]);
          }
          else
          {
            break;
          }
          if (j%2 == 0)
          {
            index += even_step;
          }
          else
          {
            index += odd_step;
          }

          ++j;
        }//end while
      }
    }//end for
    return ret;
  }
};

void expect_true(string ret, string res)
{
  if (ret.compare(res) != 0)
  {
    cout<<"\nret "<<ret<<" != "<<res<<endl; 
  }
}

int main()
{
  Solution s;
  string s1 = "PAYPALISHIRING";
  string ret = s.convert(s1,3);
  expect_true(ret,"PAHNAPLSIIGYIR");
  
  ret = s.convert(s1,1);
  expect_true(ret, s1);
  
  ret = s.convert(s1,2);
  expect_true(ret,"PYAIHRNAPLSIIG");
  
  string s2 = "abcd";
  ret = s.convert(s2,4);
  expect_true(ret,"abcd");
  return 0;
}

#include <iostream>
using namespace std;

class Solution
{
public:
  bool isNumber(string s)
  {
    if (s.empty())
    {
      return false;
    }
    size_t front = 0;
    while (s[front] == ' '){ ++front; }

    if (s[front] == '-' || s[front] == '+')
      ++front;

    size_t tail = s.length() - 1;
    while (tail >= 0 && s[tail] == ' ') { --tail; }
    string new_s = s.substr(front, tail-front+1);

//    cout << new_s << ";length=" << new_s.length() << endl;
    size_t segment = 0;
    bool has_number = false, has_dot = false, has_e = false;
    while (segment < new_s.length() && new_s[segment] != 'e' && new_s[segment] != 'E') { ++segment; }
    if (new_s[segment] == 'e' || new_s[segment] == 'E')
      has_e = true;

    size_t i = 0;
    while (i < segment && new_s[i] != '.')
    {
      if ((new_s[i] < '0' || new_s[i] > '9'))
        return false;
      ++i;
      has_number = true;
    }
    if (new_s[i] == '.')
    {
      ++i;
    }
    while (i < segment)
    {
      if ((new_s[i] < '0' || new_s[i] > '9'))
        return false;
      ++i;
      has_number = true;
    }

    if (!has_number)
      return false;

    has_number = !has_e;
    i = segment+1;
    while (i < new_s.length())
    {
      if ((new_s[i] == '+' || new_s[i] == '-') && (new_s[i+1] < '0' || new_s[i+1] > '9'))
        return false;
      if ((new_s[i] < '0' || new_s[i] > '9') && new_s[i] != '+' && new_s[i] != '-')
        return false;
      ++i;
      has_number = true;
    }
    return has_number;
  }
};

int main()
{
  string str;
  Solution s;
  str = "    0.0001   ";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = " 005047e+6";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = "2e10";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = " -1.";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = " .9";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = "2. ";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = " 46.e3";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = "0e10";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = "e10";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = "      ";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = ". ";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = " .";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = "1e ";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;


  str = ".1.";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  str = ".e1";
  str +=  s.isNumber(str) ? "  is valid" : " is invalid";
  cout << str << endl;

  return 0;
}

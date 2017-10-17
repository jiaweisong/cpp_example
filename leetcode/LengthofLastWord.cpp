#include <iostream>
using namespace std;

class Solution
{
public:
  int lengthOfLastWord(string s)
  {
    int length = s.length();
    char* c = const_cast<char*>(s.c_str()) + length - 1;
    while (*c == ' ' && length > 0) { --c; --length; }
    int end = length;
    while (*c != ' ' && length > 0){--c; --length;};
    return length == 0 ? end : end - length;
  }
};

int main()
{
  Solution s;

  cout << s.lengthOfLastWord("    ") << endl;
  cout << s.lengthOfLastWord("  c  ") << endl;
  cout << s.lengthOfLastWord("hello word   ") << endl;
  cout << s.lengthOfLastWord("helloword    ") << endl;
  return 0;
}

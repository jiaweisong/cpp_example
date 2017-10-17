#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
  void BreadthFirstSearch(vector<string>& letter, string& digits, int pos, char* res, vector<string>& ret)
  {
    if (pos == digits.length())
    {
      ret.push_back(res);
      return;
    }
    string& str = letter[digits[pos] - '0'];
    for (int index = 0; index < str.length(); ++index)
    {
      res[pos] = str[index];
      BreadthFirstSearch(letter, digits, pos+1, res, ret);
    }
  }
  
  vector<string> letterCombinations(string digits) {
    vector<string> letter;
    if (digits.empty())
    {
      return letter;
    }
    letter.emplace_back("0");
    letter.emplace_back("1");
    letter.emplace_back("abc");
    letter.emplace_back("def");
    letter.emplace_back("ghi");
    letter.emplace_back("jkl");
    letter.emplace_back("mno");
    letter.emplace_back("pqrs");
    letter.emplace_back("tuv");
    letter.emplace_back("wxyz");
    vector<string> ret;
    int size = digits.length();
    char* res = new char(size + 1);
    res[size] = '\0';     
    BreadthFirstSearch(letter,digits,0,res,ret);
    delete res;
    return ret;
  }
};


int main()
{
  Solution s;
  vector<string> ret = s.letterCombinations("2");
  for (int i = 0; i < ret.size(); ++i)
  {
    cout<<ret[i]<<endl;
  }
  return 0;
}

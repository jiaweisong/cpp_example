#include <iostream>
#include <vector>
using namespace std;


class Solution
{
public:
  vector<int> plusOne(vector<int>& digits)
  {
    if (digits.empty())
    {
      digits.push_back(1);
      return digits;
    }
    ++digits.back();
    for (size_t i = digits.size()-1; i >= 1 && digits[i] > 9; --i)
    {
      digits[i] = 0;
      ++digits[i-1];
    }
    if (digits[0] > 9)
    {
      digits[0] = 0;
      digits.resize(digits.size() + 1);
      for (size_t i = digits.size()-2; i > 0; --i)
      {
        digits[i+1] = digits[i];
      }
      digits[0] = 1;
    }
    return digits;
  }
};


int main()
{
  Solution s;
  vector<int> digits, result;

  digits = {};
  for (auto it = digits.begin(); it != digits.end(); ++it)
  {
    cout << *it;
  }
  cout << endl;
  result = s.plusOne(digits);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << *it;
  }
  cout << endl << "--------" << "end" << "------------" << endl;

  digits = {9,9};
  for (auto it = digits.begin(); it != digits.end(); ++it)
  {
    cout << *it;
  }
  cout << endl;
  result = s.plusOne(digits);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << *it;
  }
  cout << endl << "--------" << "end" << "------------" << endl;

  digits = {1,2,3,4,9};
  for (auto it = digits.begin(); it != digits.end(); ++it)
  {
    cout << *it;
  }
  cout << endl;
  result = s.plusOne(digits);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << *it;
  }
  cout << endl << "--------" << "end" << "------------" << endl;

  digits = {1,2,3,4,2};
  for (auto it = digits.begin(); it != digits.end(); ++it)
  {
    cout << *it;
  }
  cout << endl;
  result = s.plusOne(digits);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << *it;
  }
  cout << endl << "--------" << "end" << "------------" << endl;

  return 0;
}

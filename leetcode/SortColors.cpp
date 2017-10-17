#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  void swap(int& a, int& b)
  { int tmp = a; a = b; b = tmp; }

  void sortColors(vector<int>& nums)
  {
    int red = 0, curr = 0, blue = nums.size()-1;
    while (curr <= blue)
    {
      if (nums[curr] == 0)
      {
        swap(nums[curr++], nums[red++]);
      }
      else if (nums[curr] == 2)
      {
        swap(nums[curr], nums[blue--]);
      }
      else
        ++curr;
    }
  }
};

int main()
{
  Solution s;
  vector<int> colors;

  colors = {};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;

  colors = {0, 0, 0};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;

  colors = {1, 1, 1};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;

  colors = {2, 2, 2};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;

  colors = {2, 2, 2, 0, 0, 0, 1, 1, 1};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;

  colors = {0, 0, 0, 1, 1, 1, 2, 2, 2};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;

  colors = {1, 1, 1, 2, 2, 2, 0, 0, 0};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;


  colors = {2, 2, 2, 0, 0, 0, 1, 1, 1};
  s.sortColors(colors);
  for (size_t i = 0; i < colors.size(); ++i)
    cout << colors[i] << "\t";
  cout << endl;
  return 0;
}

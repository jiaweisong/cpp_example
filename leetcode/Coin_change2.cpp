#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
  int change(int amount, vector<int>& coins)
  {
    vector<vector<int>> result;
    vector<int> tmp;
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    DeepFirst(amount, coins, result, tmp);
    for (int i = 0; i < result.size(); ++i)
    {
      for (auto it = result[i].begin(); it != result[i].end(); ++it)
      {
        cout<<*it<<"\t";
      }
      cout<<endl;
    }
    return result.size();
  }

  void DeepFirst(int amount, vector<int>& coins, vector<vector<int>>& result, vector<int>& tmp)
  {
    if (amount == 0)
    {
      result.push_back(tmp);
    }
    for (auto it = coins.begin(); it != coins.end(); ++it)
    {
      if ((amount >= *it) && (tmp.empty() || tmp.back() >= *it))
      {
        tmp.push_back(*it);
        DeepFirst(amount - *it, coins, result, tmp);
        tmp.pop_back();
      }
    }
  }
};

int main()
{
  Solution s;
  vector<int> coins = {1, 5, 2};
  int amount = 5;
  s.change(amount, coins);
  return 0;
}

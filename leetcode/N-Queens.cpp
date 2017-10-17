#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_set>
using namespace std;

class Solution
{
  public:
  bool IsValid(vector<tuple<int32_t, int32_t>>& selected_cords,int32_t n, int32_t x1, int32_t y1)
  {
     if (x1 >= n || y1 >= n)
     {
       return false;
     }
    for (auto it = selected_cords.begin(); it != selected_cords.end(); ++it)
    {
       int32_t x2 = std::get<0>(*it);
       int32_t y2 = std::get<1>(*it);
       if ( x2 == x1 || y2 == y1 || (abs(x2 - x1) == abs(y2 - y1)))
       {
          return false;
       }
    }
    return true;

  }

  vector<vector<string>> solveNQueens(int n)
  {
    vector<vector<string>> res;
    if (n < 1)
    {
      return res;
    }
    vector<tuple<int32_t, int32_t>> selected_cords;
    selected_cords.reserve(n);

    int32_t x = 0, y = 0;
    while (x < n || y < n)
    {
      if (IsValid(selected_cords, n, x , y))
      {
        selected_cords.emplace_back(x, y);
        if (selected_cords.size() == n)
        {
          vector<string> board(n, string(n, '.'));
          for (auto it = selected_cords.begin(); it != selected_cords.end(); ++it)
          {
             int32_t i = std::get<0>(*it);
             int32_t j = std::get<1>(*it);
             board[i][j] = 'Q';
          }
          res.emplace_back(std::move(board));
        }
        else
        {
          ++x;
          y = 0;
        }
      }
      else
      {
        if (y < n)
        {
          ++y;
        }
        else if (!selected_cords.empty())
        {
          auto prev = selected_cords.back();
          x = std::get<0>(prev);
          y = std::get<1>(prev) + 1;
          selected_cords.pop_back();
        }
        else
        {
          break;
        }
      }
    }
   return res;
  }

};

int main()
{
  Solution s;
  auto res = s.solveNQueens(1);
  cout<<"size = "<<res.size()<<endl;
  for (auto it = res.begin(); it != res.end(); ++it)
  {
     for (auto line = it->begin(); line != it->end(); ++line)
     {
       cout<<*line<<endl;
     }
     cout<<"================"<<endl;
  }
  return 0;
}

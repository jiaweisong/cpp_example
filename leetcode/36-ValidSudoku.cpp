#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    unordered_multimap<int, pair<int , int>> int2corrd;
    for (int i = 0; i < board.size(); ++i)
    {
      for (int j = 0; j < board[i].size(); ++j)
      {
        if (board[i][j] != '.')
        {
          //cout<<board[i][j]<<"    ";
          int2corrd.emplace(make_pair(board[i][j] - '0',make_pair(i,j)));
        }
      }
      //cout<<endl;
    }
    int i1 = 0, i2 = 0, j1 = 0, j2 = 0;
    for (int i = 1; i <= 9; ++i)
    {
      auto range = int2corrd.equal_range(i);
      for (auto before = range.first; before != range.second ; ++before)
      {
        auto next = before;
        for (++next; next != range.second; ++next)
        {
           i1 = before->second.first;
           j1 = before->second.second;
           i2 = next->second.first;
           j2 = next->second.second;
           if (i1 == i2 || j1 == j2)
          {
            return false;
          }
          if ((i1 % 3 == i2 % 3) && (j1 % 3 == j2 % 3) && (abs(i1 - i2) < 3) && (abs(j1 - j2) < 3))
          {
            return false;
          }
        }
      }
    }
    return true;
  }
};

void expect_true(bool ret, bool res)
{
  if (ret != res)
  {
    cout<<"ret = "<<ret<<" != "<<res<<endl;
  }
}

int main()
{
  Solution s;
  bool ret = false;
  vector<vector<char>> board;
  board.push_back({'.','.','5','.','.','.','.','.','6'});
  board.push_back({'.','.','.','.','1','4','.','.','.'});
  board.push_back({'.','.','.','.','.','.','.','.','.'});
  board.push_back({'.','.','.','.','.','9','2','.','.'});
  board.push_back({'5','.','.','.','.','2','.','.','.'});
  board.push_back({'.','.','.','.','.','.','.','3','.'});
  board.push_back({'.','.','.','5','4','.','.','.','.'});
  board.push_back({'3','.','.','.','.','.','4','2','.'});
  board.push_back({'.','.','.','2','7','.','6','.','.'});
 ret = s.isValidSudoku(board);
expect_true(ret,true); 
  return 0;
}

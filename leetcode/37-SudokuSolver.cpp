#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;

class Solution {
public:
  bool IsValid(unordered_multimap<int, pair<int,int>>& int2coord, vector<tuple<int, int, int>>& valid_coord, int key, int x, int y)
  {
    int i1 = 0, j1 = 0;
    auto range = int2coord.equal_range(key);
    for (auto before = range.first; before != range.second ; ++before)
    {
      i1 = before->second.first;
      j1 = before->second.second;
      if (i1 == x || j1 == y)
      {
        return false;
      }
      if ((i1 / 3 == x / 3) && (j1 / 3 == y / 3) && (abs(i1 - x) < 3) && (abs(j1 - y) < 3))
      {
        return false;
      }
    }
    for (int i = 0; i < valid_coord.size(); ++i)
    {
      if (get<0>(valid_coord[i]) == key)
      {
          i1 = get<1>(valid_coord[i]);
          j1 = get<2>(valid_coord[i]);
          if (i1 == x || j1 == y)
          {
            return false;
          }
          if ((i1 / 3 == x / 3) && (j1 / 3 == y / 3) && (abs(i1 - x) < 3) && (abs(j1 - y) < 3))
          {
            return false;
          }
      }
    }
    return true;
  }

  bool DeepSearch(vector<vector<char>>& board, unordered_multimap<int, pair<int, int>>& int2coord, vector<tuple<int, int, int>>& valid_coord, int x, int y)
  {
    if (y > 8)
    {
      ++x;
      y = 0;
    }
    if (x > 8)
    {
      return true;
    }

    if ('.' != board[x][y])
    {
      return DeepSearch(board, int2coord, valid_coord, x, y+1);
    }
    for (int key = 1; key <= 9; ++key)
    {
      if (IsValid(int2coord, valid_coord, key, x, y))
      {
        valid_coord.push_back(make_tuple(key,x,y));
        if (DeepSearch(board, int2coord, valid_coord, x, y+1))
        {
          return true;
        }
        else
        {
          valid_coord.pop_back();
        }
      }
    }
    return false;
  }

  void solveSudoku(vector<vector<char>>& board) {
    unordered_multimap<int, pair<int , int>> int2coord;
    vector<tuple<int, int, int>> valid_coord;
    for (int i = 0; i < board.size(); ++i)
    {
      for (int j = 0; j < board[i].size(); ++j)
      {
        if (board[i][j] != '.')
        {
          int2coord.emplace(make_pair(board[i][j] - '0',make_pair(i,j)));
        }
      }
    }
    int key = 0, x = 0, y = 0;
    if (DeepSearch(board, int2coord, valid_coord, 0, 0))
    {
      for (int i = 0; i < valid_coord.size(); ++i)
      {
        key = get<0>(valid_coord[i]);
        x   = get<1>(valid_coord[i]);
        y   = get<2>(valid_coord[i]);
        board[x][y] = key + '0';
      }
    }
    cout<<endl;
  }
};

int main()
{
  Solution s;
  vector<vector<char>> board;
  board.push_back({'5','3','.','.','7','.','.','.','.'});
  board.push_back({'6','.','.','1','9','5','.','.','.'});
  board.push_back({'.','9','8','.','.','.','.','6','.'});
  board.push_back({'8','.','.','.','6','.','.','.','3'});
  board.push_back({'4','.','.','8','.','3','.','.','1'});
  board.push_back({'7','.','.','.','2','.','.','.','6'});
  board.push_back({'.','6','.','.','.','.','2','8','.'});
  board.push_back({'.','.','.','4','1','9','.','.','5'});
  board.push_back({'.','.','.','.','8','.','.','7','9'});
  s.solveSudoku(board);
  for (int i = 0; i < board.size(); ++i)
  {
    for (int j = 0; j < board[i].size(); ++j)
    {
      cout<<board[i][j]<<"    ";
    }
    cout<<endl;
  }
  cout<<endl;
  return 0;
}


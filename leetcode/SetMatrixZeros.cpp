#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
  void setZeroes(vector<vector<int>>& matrix)
  {
    if (matrix.empty() || matrix[0].empty())
    {
      return;
    }
    bool is_zero = matrix[0][0] == 0;
    bool has_zero_row = false, has_zero_col = false;
    for (int i = 0; i < matrix.size(); ++i)
    {
      if (matrix[i][0] == 0)
      {
        has_zero_col = true;
        break;
      }
    }
    for (int j = 0; j < matrix[0].size(); ++j)
    {
      if (matrix[0][j] == 0)
      {
        has_zero_row = true;
        break;
      }
    }
    for (int i = 0; i < matrix.size(); ++i)
    {
      for (int j = 0; j < matrix[i].size(); ++j)
      {
        if (matrix[i][j] == 0)
        {
          matrix[i][0] = 0;
          matrix[0][j] = 0;
        }
      }
    }

    for (int i = matrix.size()-1; i > 0; --i)
    {
      if (matrix[i][0] == 0)
      {
        for (int j = 0; j < matrix[i].size(); ++j)
          matrix[i][j] = 0;
      }
    }
    for (int j = matrix[0].size()-1; j > 0; --j)
    {
      if (matrix[0][j] == 0)
      {
        for (int i = 0; i < matrix.size(); ++i)
          matrix[i][j] = 0;
      }
    }

    if (has_zero_col)
    {
      for (int i = 0; i < matrix.size(); ++i)
        matrix[i][0] = 0;
    }
    if (has_zero_row)
    {
      for (int j = 0; j < matrix[0].size(); ++j)
        matrix[0][j] = 0;
    }
    if (is_zero)
    {
      for (int j = 0; j < matrix[0].size(); ++j)
        matrix[0][j] = 0;
      for (int i = 0; i < matrix.size(); ++i)
        matrix[i][0] = 0;
    }
  }
};


int main()
{
  Solution s;
  vector<vector<int>> matrix;

  matrix = {
   {0,0,0,5},{4,3,1,4},{0,1,1,4},{1,2,1,3},{0,0,1,1}
  };

  s.setZeroes(matrix);
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    for (size_t j = 0; j < matrix[i].size(); ++j)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
  matrix = {
   {1,0,0,5},{4,3,1,4},{0,1,1,4},{1,2,1,3},{0,0,1,1}
  };

  s.setZeroes(matrix);
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    for (size_t j = 0; j < matrix[i].size(); ++j)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;
  matrix = {
   {1,1,2,5},{4,3,1,4},{0,1,1,4},{1,2,1,3},{0,0,1,1}
  };

  s.setZeroes(matrix);
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    for (size_t j = 0; j < matrix[i].size(); ++j)
    {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
  return 0;
}

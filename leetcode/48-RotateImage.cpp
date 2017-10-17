#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
  void rotate(vector<vector<int>>& matrix) {
    int row = matrix.size();
    for (int row_index = 0; row_index < row - 1; ++row_index)
    {
      int col = matrix[row_index].size();
      for (int col_index = row_index; col_index < col - row_index - 1; ++col_index)
      {
        int current_row = row_index, current_col = col_index;
        int next_row = current_col, next_col = col - current_row - 1;
        int value = matrix[current_row][current_col];
        do
        {
          std::swap(matrix[next_row][next_col],value);
          current_row = next_row;
          current_col = next_col;
          next_row = current_col;
          next_col = col - current_row - 1;
        }
        while (current_row != row_index || current_col != col_index);
      }
    }
  }
};

int main()
{
  Solution s;
  vector<vector<int>> matrix;
  int n = 3;
  int count = 1;
  matrix.resize(n);
  for (int i = 0; i < n; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      matrix[i].push_back(count++);
    }
  }

  for (int i = 0; i < matrix.size(); ++i)
  {
    for (int j = 0; j < matrix[i].size(); ++j)
    {
      cout<<matrix[i][j]<<"    ";
    }
    cout<<endl;
  }

  s.rotate(matrix);

  for (int i = 0; i < matrix.size(); ++i)
  {
    for (int j = 0; j < matrix[i].size(); ++j)
    {
      cout<<matrix[i][j]<<"    ";
    }
    cout<<endl;
  }
  return 0;
}

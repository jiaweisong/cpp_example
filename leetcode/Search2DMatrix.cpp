#include <iostream>
#include <vector>
using namespace std;


class Solution
{
public:
  bool searchMatrix(vector<vector<int>>& matrix, int target)
  {
    if (matrix.empty() || matrix[0].empty())
    {
      return false;
    }
    int m = matrix.size(), n = matrix[0].size();
    int low = 0, mid = 0, high = m*n - 1;
    while (low <= high)
    {
      mid = (low + high) >> 1;

      int row = mid/n, col = mid%n;
      if (matrix[row][col] == target)
        return true;
      else if (matrix[row][col] < target)
        low = mid + 1;
      else
        high = mid - 1;
    }
    return false;
  }
};


int main()
{
  Solution s;
  vector<vector<int>> matrix;
  matrix =
  {
    {1,   3,  5,  7},
    {10, 11, 16, 20},
    {23, 30, 34, 50}
  };

  cout << (s.searchMatrix(matrix, 0) ? "find target " : "cant't find target ") << 0 << endl;
  cout << (s.searchMatrix(matrix, 40) ? "find target " : "cant't find target ") << 40 << endl;
  cout << (s.searchMatrix(matrix, 100) ? "find target " : "cant't find target ") << 100 << endl;
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    for (size_t j = 0; j < matrix[0].size(); ++j)
    {
      cout << (s.searchMatrix(matrix, 3) ? "find target " : "cant't find target ") << matrix[i][j] << endl;
    }
  }

  matrix = {{1}};
  cout << (s.searchMatrix(matrix, 1) ? "find target " : "cant't find target ") << 1 << endl;
  cout << (s.searchMatrix(matrix, 0) ? "find target " : "cant't find target ") << 0 << endl;

  return 0;
}

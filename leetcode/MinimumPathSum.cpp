#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  int minPathSum(vector<vector<int>>& grid)
  {
    if (grid.size() <= 0 || grid[0].size() <= 0)
      return 0;

    int m = grid.size(), n = grid[0].size();
    vector<int> init_vec(n, 0);
    vector<vector<int>> result(m, init_vec);
    result[0][0] = grid[0][0];

    for (size_t j = 1; j < n; ++j)
      result[0][j] = grid[0][j] + result[0][j-1];
    for (size_t i = 1; i < m; ++i)
      result[i][0] = grid[i][0] + result[i-1][0];

    for (size_t i = 1; i < m; ++i)
    {
      for (size_t j = 1; j < n; ++j)
      {
        int min = result[i-1][j] < result[i][j-1] ? result[i-1][j] : result[i][j-1];
        result[i][j] = min + grid[i][j];
      }
    }
    return result[m-1][n-1];
  }
};

int main()
{
  Solution s;
  vector<vector<int>> grid;
  grid =
  {
    {1,  2, 2,  1},
    {1,  1, 2,  12},
    {10, 1, 1, 1},
  };
  cout << s.minPathSum(grid) << endl;
  return 0;
}

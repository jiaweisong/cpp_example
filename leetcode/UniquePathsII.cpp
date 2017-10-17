#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
  {
    if (obstacleGrid.size() > 0 && obstacleGrid[0].size() > 0)
    {
      int m = obstacleGrid.size();
      int n = obstacleGrid[0].size();
      vector<int> init_vec(n, 0);
      vector<vector<int>> result(m, init_vec);
      if (obstacleGrid[m-1][n-1] == 1)
      {
        return 0;
      }
      result[m-1][n-1] = 1;
      for (int i = m-2; i >= 0; --i)
      {
        result[i][n-1] = obstacleGrid[i][n-1] != 1 ? result[i+1][n-1] : 0;
      }
      for (int j = n-2; j >= 0; --j)
      {
        result[m-1][j] = obstacleGrid[m-1][j] != 1 ? result[m-1][j+1] : 0;
      }
      for (int i = m-2; i >= 0; --i)
      {
        for (int j = n-2; j >= 0; --j)
        {
          result[i][j] = obstacleGrid[i][j] == 1 ? 0 : (result[i+1][j] + result[i][j+1]);
        }
      }
      return result[0][0];
    }
    else
      return 0;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> test;
  test =
  {
    {0, 0, 0},
    {0, 0, 0},
  };
  cout << s.uniquePathsWithObstacles(test) << endl;

  test =
  {
    {0, 1, 0},
    {0, 0, 0},
  };
  cout << s.uniquePathsWithObstacles(test) << endl;

  test =
  {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0},
  };
  cout << s.uniquePathsWithObstacles(test) << endl;
  return 0;
}

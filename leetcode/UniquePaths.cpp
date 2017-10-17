#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  int uniquePaths(int m, int n)
  {
    if (m > 0 && n > 0)
    {
      vector<int64_t> init_vec(n, 1);
      vector<vector<int64_t>> result(m, init_vec);
      for (int i = m-2; i >= 0; --i)
      {
        for (int j = n-2; j >= 0; --j)
        {
          result[i][j] = result[i+1][j] + result[i][j+1];
        }
      }
      return result[0][0];
    }
    else
      return 0;
  }

//  int dfs(int i, int j, int m , int n)
//  {
//    if (i == m-1 && j == n-1)
//    {
//      return 1;
//    }
//    int down = 0, right = 0;
//    if (i < m - 1)
//      down = dfs(i+1, j, m, n);
//    if (j < n - 1)
//      right = dfs(i, j+1, m, n);
//    return down + right;
//  }
//
//  int uniquePaths(int m, int n)
//  {
//    if (m > 0 && n > 0)
//      return dfs(0, 0, m, n);
//    else
//      return 0;
//  }

//  void dfs(int i, int j, int m , int n, int& count)
//  {
//    if (i == m && j == n)
//    {
//      count++;
//      return;
//    }
//    if (i < m)
//       dfs(i+1, j, m, n, count);
//    if (j < n)
//       dfs(i, j+1, m, n, count);
//  }
//
//  int uniquePaths(int m, int n)
//  {
//    int count = 0;
//    if (m > 0 && n > 0)
//    {
//      dfs(0, 0, m-1, n-1, count);
//    }
//    return count;
//  }

};


int main()
{
  Solution s;
  int64_t m = 0, n = 0, result = 0;

  m = 0, n = 0;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 1, n = 1;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 1, n = 3;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 2, n = 2;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 2, n = 3;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 2, n = 4;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 3, n = 4;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 23, n = 14;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 53, n = 64;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;

  m = 100, n = 100;
  result = s.uniquePaths(m, n);
  cout << "m = " << m << "\t" << "n = " << n << "\t" << "result = " << result << endl;
  return 0;
}

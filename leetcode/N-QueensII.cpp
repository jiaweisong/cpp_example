#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    int totalNQueens(int n)
    {
      vector<int> col_row_flags (n, 0);
      vector<int> deg_45_flags  (2*n - 1, 0);
      vector<int> deg_135_flags (2*n - 1, 0);
      int count = 0;
      deep_first(0, n, count, col_row_flags, deg_45_flags, deg_135_flags);
      return count;
    }

    void deep_first(int row, int n, int& count, vector<int>& col_row_flags, vector<int>& deg_45_flags, vector<int>& deg_135_flags)
    {
      if (row == n)
      {
        ++count;
        return;
      }
      for (int col = 0; col < n; ++col)
      {
        if (col_row_flags[col] == 0 && deg_45_flags[row + col] == 0 && deg_135_flags[n - 1 + row - col] == 0)
        {
          col_row_flags[col] = deg_45_flags[row + col] = deg_135_flags[n - 1 + row - col] = 1;
          deep_first(row + 1, n, count, col_row_flags, deg_45_flags, deg_135_flags);
          col_row_flags[col] = deg_45_flags[row + col] = deg_135_flags[n - 1 + row - col] = 0;
        }
      }
    }
};

int main()
{
  Solution s;
  int n = 5;
  for (int i = 1; i < n; ++i)
  {
    int res = s.totalNQueens(i);
    cout<<"size = "<<res<<endl;
  }
  return 0;
}

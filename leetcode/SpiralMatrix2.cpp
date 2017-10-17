#include <iostream>
#include <vector>

using namespace std;

void Print(vector<vector<int>>& result)
{
  for (size_t i = 0; i < result.size(); ++i)
  {
    for (size_t j = 0; j < result[i].size(); ++j)
    {
      cout << result[i][j] << "\t";
    }
    cout << endl;
  }
}

class Solution
{
public:
  vector<vector<int>> generateMatrix(int n)
  {
    vector<vector<int>> result;
    vector<int> zeros(n, 0);
    result.resize(n, zeros);

    int start_n = 1, max_num = n * n;
    int round = 0, max_round = (n & 0x1) == 0 ? (n >> 1) : (n >> 1) + 1;
    int row = 0, col = 0;
    while (round < max_round)
    {
      //upper
      while (col < n - round && start_n <= max_num)
      {
        result[row][col++] = start_n++;
      }
      --col;

      //right
      ++row;
      while (row < n - round && start_n <= max_num)
      {
        result[row++][col] = start_n++;
      }
      --row;

      //lower
      --col;
      while (col >= round && start_n <= max_num)
      {
        result[row][col--] = start_n++;
      }
      ++col;

      //left
      --row;
      while (row > round && start_n <= max_num)
      {
        result[row--][col] = start_n++;
      }
      ++round;
      row = round; col = round;
    }
    return result;
  }
};

int main()
{
  Solution s; int n; vector<vector<int>> result;

  n = 0;
  cout << "n = " << n << endl;
  result = s.generateMatrix(n);
  Print(result);

  n = 1;
  cout << "n = " << n << endl;
  result = s.generateMatrix(n);
  Print(result);

  n = 2;
  cout << "n = " << n << endl;
  result = s.generateMatrix(n);
  Print(result);

  n = 3;
  cout << "n = " << n << endl;
  result = s.generateMatrix(n);
  Print(result);

  n = 4;
  cout << "n = " << n << endl;
  result = s.generateMatrix(n);
  Print(result);
  return 0;
}

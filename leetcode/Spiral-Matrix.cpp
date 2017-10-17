#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> spiralOrder(vector<vector<int>>& matrix)
  {
    vector<int> result;
    if (matrix.size() <= 0 || matrix[0].size() <= 0)
    {
      return result;
    }
    int n = matrix.size(), m = matrix[0].size();

    for (int round = 0; round <= (m >> 1) && round <= (n >> 1);  ++round)
    {
      for (int row = round, col = round; row < m - round && col < n - round; ++col)
      {
        result.push_back(matrix[row][col]);
      }
      for (int row = round + 1, col = n - round - 1; row < m - round; ++row)
      {
        result.push_back(matrix[row][col]);
      }
      for (int row = m - round - 1, col = n - round - 2; row > round && col >= round; --col)
      {
        result.push_back(matrix[row][col]);
      }
      for (int row = m - round - 2, col = round; row > round && col < n - round - 1; --row)
      {
        result.push_back(matrix[row][col]);
      }
    }
    return result;
  }
};

void Print(vector<int>& res)
{
  for (auto it = res.begin(); it != res.end(); ++it)
  {
    cout<<*it<<"\t";
  }
  cout<<endl;
}

int main()
{
  Solution s;
  vector<vector<int>> array;
  vector<int> result;

  array = {{0}};
  result = s.spiralOrder(array);
  Print(result);

  array = {{0, 1, 2, 3}};
  result = s.spiralOrder(array);
  Print(result);

  array = {{0}, {1}, {2}, {3}};
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {1, 2},
      {3, 4}
  };
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {1, 2, 3},
      {4, 5, 6}
  };
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {1, 2},
      {3, 4},
      {5, 6},
      {7, 8}
  };
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
  };
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {0, 1, 2, 3},
      {3, 4, 5, 6},
      {6, 7, 8, 9},
      {2, 3, 4, 5}
  };
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {1, 2, 3, 4, 5},
      {4, 5, 6, 7, 8},
      {7, 8, 9, 0, 1}
  };
  result = s.spiralOrder(array);
  Print(result);

  array = {
      {0, 1, 2},
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
      {3, 4, 5}
  };
  result = s.spiralOrder(array);
  Print(result);
  return 0;
}

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  bool Find(int target, const vector<vector<int>>& matrix)
  {
    if (matrix.size() <= 0 || matrix[0].size() <= 0)
    {
      return false;
    }
    int height = matrix.size(), width = matrix[0].size();
    int row = 0, col = width-1;
    while (row < height && col >= 0)
    {
      if (target < matrix[row][col])
      {
        --col;
      }
      else if (target > matrix[row][col])
      {
        ++row;
      }
      else
      {
        cout<<"row = "<<row<<"\t"<<"col = "<<col<<endl;
        return true;
      }
    }
    return false;
  }
};

int main()
{
  Solution s;
  vector<vector<int>> matrix=
  {
    {1, 2, 8 , 9 , 10},
    {2, 4, 9 , 12, 13},
    {4, 7, 10, 13, 14},
    {6, 8, 11, 15, 16}
  };

  int target = 6;
  s.Find(target, matrix);
  return 0;
}

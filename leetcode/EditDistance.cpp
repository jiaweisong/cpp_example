#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
  int minDistance(string word1, string word2)
  {
    size_t n1 = word1.length(), n2 = word2.length();
    cout << n1 << n2 << endl;
    if (n1 == 0 || n2 == 0)
    {
      return n1 != 0 ? n1 : n2;
    }

    vector<int> col_vec(n2+1, 0);
    vector<vector<int>> result(n1+1, col_vec);
    for (size_t i = 0; i <= n1; ++i)
    {
      result[i][0] = i;
    }
    for (size_t j = 0; j <= n2; ++j)
    {
      result[0][j] = j;
    }

    for (size_t i = 1; i <= n1; ++i)
    {
      for (size_t j = 1; j <= n2; ++j)
      {
        int min = result[i-1][j] < result[i][j-1] ? result[i-1][j]+1 : result[i][j-1]+1;
        int res = result[i-1][j-1] + (word1[i-1] == word2[j-1] ? 0 : 1);
        result[i][j] = min < res ? min : res;
      }
    }

//    cout << endl;
//    for (size_t i = 0; i <= n1; ++i)
//    {
//      for (size_t j = 0; j <= n2; ++j)
//      {
//        cout << result[i][j] << " ";
//      }
//      cout << endl;
//    }
//    cout << endl;
    return result[n1][n2];
  }
};


int main()
{
  Solution s;
  string a, b;

  a = "a"; b = "cab";
  cout << "word1 = " << a << "  word2 = " << b << "  edit_distance = " << s.minDistance(a, b) << endl;

  a = "cab"; b = "a";
  cout << "word1 = " << a << "  word2 = " << b << "  edit_distance = " << s.minDistance(a, b) << endl;

  a = "kitten"; b = "sitting";
  cout << "word1 = " << a << "  word2 = " << b << "  edit_distance = " << s.minDistance(a, b) << endl;
  return 0;
}

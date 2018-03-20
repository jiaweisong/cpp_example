#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
void print(vector<T>& result)
{
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << *it << "\t";
  }
  cout << endl;
}

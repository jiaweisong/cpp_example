#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
  vector<int> list = {1,2,3,4,5};
  random_shuffle(list.begin(), list.end());
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    cout<<*it<<"  ";
  }

  cout<<endl<<"------------------"<<endl;

  sort(list.begin(), list.end());
  random_shuffle(list.begin(), list.end());
  for (auto it = list.begin(); it != list.end(); ++it)
  {
    cout<<*it<<"  ";
  }

  cout<<endl;
  return 0;
}

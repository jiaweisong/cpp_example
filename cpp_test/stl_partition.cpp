#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Meta
{
  int index;
  int falg;
};

int main()
{
  auto lambda = [](const Meta& meta)
  {
    return meta.falg < 3;
  };
  vector<Meta> metas{{1,1}, {2,2}, {2,2}, {3,3}};
  auto iter = partition(metas.begin(), metas.end(), lambda);
  cout<<metas.end() - iter<<endl;
  metas.erase(iter, metas.end());
  for (auto it = metas.begin(); it != metas.end(); ++it)
  {
    cout<<it->index<<"    ";
  }
  cout<<endl;
  for (auto it = iter; it != metas.end(); ++it)
  {
    cout<<it->index<<"    ";
  }
  cout<<endl;
  return 0;
}



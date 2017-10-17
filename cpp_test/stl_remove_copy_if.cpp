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
  vector<Meta> metas{{1,1}, {2,2}, {3,3}, {4,4}};
  vector<Meta> results;
  results.reserve(metas.size());
//  auto removed_it = remove_copy_if(metas.begin(), metas.end(), results.begin(), lambda);
  auto removed_it = remove_if(metas.begin(), metas.end(), lambda);
  metas.erase(removed_it, metas.end());
  for (auto it = metas.begin(); it != metas.end(); ++it)
  {
    cout<<it->index<<"    ";
  }
  cout<<endl;
  for (auto it = results.begin(); it != results.end(); ++it)
  {
    cout<<it->index<<"    ";
  }
  cout<<endl;
  return 0;
}



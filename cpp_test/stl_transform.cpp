#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct MetaInfo
{
  int index;
  string feature;
  double weight;
};

int main()
{
  vector<MetaInfo> src{{0, "advertiserId = 1001", 0.5}, {1, "publisherId = 1002", 0.6}, {2, "cookielabel = invalid", 0.7}};
  std::transform(src.begin(), src.end(), src.begin(), [](MetaInfo& v)
          {
            if (v.feature.find("advertiserId") != string::npos)
            {
              v.feature = "invalid";
            }
            return v;
          });
  for (auto it = src.begin(); it != src.end(); ++it)
  {
    cout<<it->feature<<endl;
  }
  return 0;
}

#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<bool> bitset;
  for (int i = 0; i < 10; ++i)
  {
    if (i>>1 == 0)
    {
      bitset.push_back(true);
    }
    else
    {
      bitset.push_back(false);
    }
  }

  auto bitset_ref = bitset[2];
  {
    if (bitset_ref.operator bool())
    {
      cout<<"true\n";
    }
    else
    {
      cout<<"false\n";
    }
  }
  return 0;
}


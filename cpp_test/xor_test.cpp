#include <iostream>
#include <bitset>
#include <iostream>
#include <climits>

using namespace std;

size_t BitCount1(int64_t n)
{
  std::bitset<sizeof(int64_t) * CHAR_BIT> b(n);
  return b.count();
}


size_t BitCount2(int64_t n)
{
    size_t c = 0 ;
    for (c = 0; n; ++c)
    {
        n &= (n-1) ; // 清除最低位的1
    }
    return c ;
}

int main()
{
  int32_t a = 2;
  int32_t b = 4;
  int32_t c = a ^ b;
  cout << BitCount1(c) << endl;
  cout << BitCount2(c) << endl;
}

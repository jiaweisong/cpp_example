#include <iostream>
using namespace std;

int main()
{
  union u_type
  {
    int a;
    char b;
  };
  u_type test;
  test.a = 1;
  if (test.b == 1)
  {
    cout<<"little endian\n";
  }
  else
  {
    cout<<"big endian\n";
  }
  return 0;
}

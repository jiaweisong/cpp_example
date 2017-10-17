#include <iostream>
using namespace std;

void foo(unsigned i)
{
  cout<<"ordinary foo\n";
}

template <typename T>
void foo(const T t)
{
  cout<<"const template\n";
}

//template <typename T>
//typename T::value_type foo(const T t)
//{
//  return -t();
//}

int main()
{
  foo(2);
  return 0;
}

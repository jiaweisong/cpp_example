#include <iostream>
using namespace std;

template<typename T, size_t N>
size_t size_array(T (&)[N])
{
  return N;
}

template<typename T, typename U>
auto Multiply(U u, T t)->decltype(u*t)
{
  
  //decltype(u*t) value =  u*t;
  return t;
}

template<typename T>
auto Extractor(T value_type)->decltype(value_type)
{
  return value_type;
}
int main()
{
  auto ret = Extractor("songjw");
  cout<<ret<<endl;
  
}

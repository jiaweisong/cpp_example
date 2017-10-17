#include <iostream>
#include <vector>
using namespace std ;

template <class InputIt, class UnaryFunction>
UnaryFunction self_for_each(InputIt first, InputIt last, UnaryFunction f)
{
  for ( ; first != last; ++first)
  {
    f(*first);
  }
  return f;
}

struct Print
{
  void operator()(const int& v)
  {
    cout<< v<< "  ";
  }
};

int main()
{
  vector<int> list = {1,2,3,4,5,6,7,8,9};
  self_for_each(list.begin(), list.end(), [](const int& v){cout << v << "  ";});
  cout<<endl;
  self_for_each(list.begin(), list.end(), Print);
  cout<<endl;
  return 0;
}

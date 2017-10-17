#include <iostream>
#include <vector>
#include <memory>
#include <type_traits>
using namespace std;

class Test
{
  public:
    template<typename FuncType, typename ... ArgsType>
    auto RunInside(FuncType func, const ArgsType& ...args)->decltype((this->*func)(args...))
    {
      return (this->*func)(args...);
    }

    template<typename FuncType, typename ... ArgsType>
    auto RunOutside(FuncType func, const ArgsType& ...args)->decltype(func(args...))
    {
      return func(args...);
    }
    int func1(const string& info)
    {
      cout<<"func1  "<<info<<endl;
      return 0;
    }
};

int func2(const string& info1, const string& info2)
{
  cout<<"func2 "<<info1<<"\t"<<info2<<endl;
  return 0;
}

int main()
{
  Test t;
  t.RunInside(&Test::func1, "hello world");
  t.RunOutside(func2, "songjw", "test");
  return 0;
}

#include <iostream>
using namespace std;

template<typename...> struct Tuple {};
template<typename T1, typename T2> struct Pair {};

template<class ...Args1> struct zip
{
  template<class ...Args2> struct with
  {
    typedef Tuple<Pair<Args1, Args2>...> type;
  };
};

int main()
{
  typedef zip<short, int>::with<unsigned short, unsigned>::type T1;
  typedef zip<short>::with<unsigned short, unsigned>::type T2;
  return 0;
}


#include <tuple>
#include <type_traits>
#include <functional>
#include <utility>
#include "include/head.h"
using namespace std;

template <int I>
struct Placeholder
{
};

Placeholder<1> _1; Placeholder<2> _2; Placeholder<3> _3; Placeholder<4> _4; Placeholder<5> _5;
Placeholder<6> _6; Placeholder<7> _7; Placeholder<8> _8; Placeholder<9> _9; Placeholder<10> _10;

template <typename T, class Tuple>
inline auto select(T&& val, Tuple&)->T&&
{
    return std::forward<T>(val);
}

template <int I, class Tuple>
inline auto select(Placeholder<I>&, Tuple& tp) -> decltype(std::get<I - 1>(tp))
{
    return std::get<I - 1>(tp);
}

int f0(const string& info, int64_t score)
{
  cout << info<< "\t" << score << endl;
  return 0;
}

template <typename T, std::size_t... Is>
void expand(T& t, std::index_sequence<Is...>)
{
  f0(std::get<Is>(t)...);
}

template<class Fn, class... Args>
void Func(Fn func, Args&&... args)
{
  std::tuple<typename decay<Args>::type...> my_args(args...), argtp;
  typename std::decay<Fn>::type f = func;
//  expand(my_args, std::index_sequence_for<Args...>());
  func(select(my_args, argtp)...);
}

int main()
{
  Func(&f0, "songjw", 100);
  return 0;
}

// implementation details, users never invoke these directly
#include <iostream>
#include <tuple>
using namespace std;
namespace detail
{
    template <typename F, typename Tuple, int... N>
    struct call_func
    {
        static void call(F f, Tuple && t)
        {
            cout << "last " << endl;
            f(std::get<N>(std::forward<Tuple>(t))...);
        }
    };
}

namespace detail
{
    template <typename F, typename Tuple, bool Done, int Total, typename... N>
    struct call_impl
    {
        static void call(F f, Tuple && t)
        {
            cout << Total << "\t" << 1 + sizeof...(N) << endl;
            call_impl<F, Tuple, Total == 1 + sizeof...(N), Total, N..., sizeof...(N)>::call(f, std::forward<Tuple>(t));
        }
    };

    template <typename F, typename Tuple, int Total, typename... N>
    struct call_impl<F, Tuple, true, Total, N...>
    {
        static void call(F f, Tuple && t)
        {
            cout << "last " << endl;
            f(std::get<N>(std::forward<Tuple>(t))...);
        }
    };
}

// user invokes this
template <typename F, typename Tuple>
void call(F f, Tuple && t)
{
    typedef typename std::decay<Tuple>::type ttype;
    cout << std::tuple_size<ttype>::value << endl;
    detail::call_impl<F, Tuple, 0 == std::tuple_size<ttype>::value, std::tuple_size<ttype>::value>::call(f, std::forward<Tuple>(t));
    detail::call_func<F, Tuple, 0,1,2,3,4>::call(f, std::forward<Tuple>(t));
}


#include <cstdio>
int main()
{
    auto t = std::make_tuple("%d, %d, %d, %f\n", 1,2,3,4.0);
    call(std::printf, t);
}

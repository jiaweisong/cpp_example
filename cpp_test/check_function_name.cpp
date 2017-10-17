#include <iostream>
using namespace std;

template<class CFunction, typename = typename std::enable_if<std::is_function<typename std::remove_pointer<CFunction>::type>::value>::type>
std::string function_arg_name(CFunction f)
{
    Dl_info info;
    dladdr((void const*)f, &info);
    return demangle(info.dli_sname);
}

int main()
{
  return 0;
}


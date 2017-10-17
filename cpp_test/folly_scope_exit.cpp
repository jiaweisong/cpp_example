#include <iostream>
using namespace std;

#ifndef FB_ANONYMOUS_VARIABLE
#define FB_CONCATENATE_IMPL(s1, s2) s1##s2
#define FB_CONCATENATE(s1, s2) FB_CONCATENATE_IMPL(s1, s2)
#ifdef __COUNTER__
#define FB_ANONYMOUS_VARIABLE(str) FB_CONCATENATE(str, __COUNTER__)
#else
#define FB_ANONYMOUS_VARIABLE(str) FB_CONCATENATE(str, __LINE__)
#endif
#endif

enum class ScopeGuardOnExit {};

template <typename FunctionType>
ScopeGuardImpl<typename std::decay<FunctionType>::type> operator+(ScopeGuardOnExit, FunctionType&& fn)
{
  return ScopeGuardImpl<typename std::decay<FunctionType>::type>(std::forward<FunctionType>(fn));
}

#define SCOPE_EXIT \
auto FB_ANONYMOUS_VARIABLE(SCOPE_EXIT_STATE) \
 = ScopeGuardOnExit() + [&]() noexcept

void call()
{
  SCOPE_EXIT {
        cout << "call exit" << endl;
      };
}

int main()
{
  cout << "before main" << endl;
  call();
  cout << "after main" << endl;
}

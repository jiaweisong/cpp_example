#include <iostream>
#include <cassert>
#include <google/heap-checker.h>

using namespace std;

int func()
{
  HeapLeakChecker heap_checker("fun");
  int * p = new int(10);
  assert(heap_checker.NoLeaks());
  return 0;
}

int main(int argn, char* argv[])
{
  func();
  return 0;
}

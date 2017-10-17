#include <string>
#include <iostream>
#include <iomanip>
#include <utility>
using namespace std;

struct A
{
  std::string s;
  A() : s("test") {cout<<"default constructor\n";}


//  A(A& o) : s(o.s) { std::cout << "copy constructor!\n";}
  template<class T>
  A& operator = (T& other)
  {
    std::cout << "template copy constructor!\n";
  }
  A& operator = (A& other)
  {
    std::cout << "customer copy constructor!\n";
  }

  A(A&& o) noexcept : s(std::move(o.s)) {cout<<"move constructor!\n";}
  A& operator=(A&& other)
  {
    s = std::move(other.s);
    std::cout << "move assigned\n";
    return *this;
  }
};

A Temp()
{
  cout<<"temp\n";
  A a;
  return a;
}

void CallB(A a)
{
  cout<<"callB\n";
}

void CallC(A&& a)
{
  cout << a.s << endl;
}

void CallC(A& a)
{
  a.s = "songjw";
}

int main()
{

  A a;
  A b = std::move(a);
  a = std::move(b);
  CallC(std::move(a));

  b = a;
  return 0;
}

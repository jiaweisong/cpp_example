#include <iostream>
using namespace std;
class A
{
public:
  A()
  {
    cout << "A构造函数";
    foo();
    Test();
  }
  ~A()
  {
     cout << "A析构函数";
     cout << "A::Test()" << endl;
  }
  virtual void Test()
  {
     cout << "A::Test()" << endl;
  }
  void foo()
  {
    cout<<"A::foo()"<<endl;
  }
};

class B:public A
{
public:
  B()
  {
    cout << "B构造函数";
    foo();
    Test();
  }
  ~B()
  {
    cout << "B析构函数";
    Test();
  }
  void foo()
  {
    cout<<"B::foo()"<<endl;
  }
  virtual void Test()
  {
    cout << "B::Test()" << endl;
  }
};

int main()
{
  cout<<sizeof(A)<<endl;
  cout<<sizeof(B)<<endl;
  B* pA = new B();
  cout << "动态调用：";
  pA->Test();
  delete pA;
  return 0;
}

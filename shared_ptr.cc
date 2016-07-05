#include <iostream>
#include <memory>

using namespace std;

struct Test
{
  public:
  ~Test(){cout<<"destory Test\n";}
};

template<class T>
struct Deleter
{
  int operator()(T* t)
  {
    cout<<"call deleter\n";
    delete t;
    return 0;
  }

  static int destructor(T* t, string& name)
  {
    cout<<"call destructor\n";
    delete t;
    name = "songjw\n";
    return 0;
  }
};

int main()
{
  string name;
  shared_ptr<Test>(new Test(), [&](Test* a){Deleter<Test>::destructor(a,name);});
  cout<<name;
  //shared_ptr<Test>(new Test(), Deleter<Test>());
  return 0;
}

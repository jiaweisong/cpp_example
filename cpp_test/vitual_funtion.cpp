#include <iostream>
#include <memory>
using namespace std;

class base
{
  public:
    base(){}
    ~base(){cout<<"base destructor"<<endl;}
};

class derived : public base
{
  public:
    derived(){}
    ~derived(){cout<<"derived destructor"<<endl;}
};

class others
{
  public:
    others(){}
    ~others(){}
};


int main()
{
  shared_ptr<base> ptr(new derived(),[](base* ptr){ delete ptr; });
  ptr.reset();
  return 0;
}

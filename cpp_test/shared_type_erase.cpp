#include <iostream>
#include <functional>
#include <memory>
using namespace std;

template <typename T>
void delete_deleter(void * p)
{
  delete static_cast<T*>(p);
//  cout<<"destructor\n";
}

template <typename T>
class my_unique_ptr
{
  public:
    std::function<void (void*)> deleter;
    T* p;
    template <typename U>
    my_unique_ptr(U* p, std::function< void(void*)> deleter = delete_deleter<U>) : p(p), deleter(deleter){}
    ~my_unique_ptr()
    {
       deleter(p);
    }
};

template <typename T>
class SharedPtr
{
  public:
    template<class U>
    SharedPtr(U* ptr = nullptr) : ptr_(ptr){}
    ~SharedPtr()
    {
      if (ptr_ != nullptr)
      {
        delete ptr_;
      }
    }
  private:
    T* ptr_;
};

class Base
{
  public:
  ~Base(){ cout << "destruct base\n"; }
};

class Devired : public Base
{
  public:
  ~Devired(){ cout << "destruct Devired\n"; }
};

int main()
{
//  cout << "normal pointer :";
//  SharedPtr<Base> dev(new Devired());
//  cout << endl;
//
//  cout << "type erase pointer :";
//  my_unique_ptr<Base> p(new Devired()); // deleter == &delete_deleter<double>
//  cout << endl;
//
//  cout << "unique pointer :";
//  auto deleter = [](Base* ptr){ delete ptr; ptr = nullptr; };
//  std::unique_ptr<Base, decltype(deleter)> uptr(new Devired(), deleter);
//  cout << endl;
//
//  cout << "shared pointer :";
//  std::shared_ptr<Base> sptr(new Devired(), [](Base* ptr){ delete ptr; ptr = nullptr; });
//  cout << endl;
  return 0;
}
// ~my_unique_ptr calls delete_deleter<double>(p)

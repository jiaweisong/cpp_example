#include <iostream>
#include <stdexcept>
#include <mutex>

using namespace std;

/*
  class Singleton {
  public:
    static Singleton* GetInstance()
    {
      if (pInstance == nullptr)
      {
        //Lock
        if (pInstance == nullptr)
        {
          pInstance = static_cast<Singleton*>(operator new(sizeof(Singleton)));
          new (pInstance)Singleton;
        }
      }
      return pInstance;
    }

    void SayHello()
    {
      cout<<"hello world\n";
    }

  private:
    static Singleton* pInstance;
};
*/
class Singleton {
  public:
    static Singleton* GetInstance();
    void SayHello()
    {
      cout<<"hello world\n";
    }

  private:
    static Singleton* pInstance;
};
Singleton* Singleton::pInstance = nullptr;

Singleton* Singleton::GetInstance()
{
  static std::once_flag once;
  try
  {
    std::call_once(once,[&]{pInstance = new Singleton;});
  }
  catch(std::exception& e)
  {
    cout<<e.what()<<endl;
  }
  return pInstance;
}
int main()
{
  Singleton* ptr = Singleton::GetInstance();
  ptr->SayHello();
  return 0;
}

#include <iostream>
using namespace std;

#define hello_world(x) x

template <class HashFcn>
class Table
{
  public:
    typedef HashFcn FUNC_TYPE;
    Table(const FUNC_TYPE& f) : func_(f){}
    void Run()
    {
      func_();
    }

  private:
    FUNC_TYPE func_;
};

template <class HashFcn>
class TestMap
{
  public:
    typedef Table<HashFcn> HT;
    typedef typename HT::FUNC_TYPE FUNC_TYPE;
  public:
    TestMap() : table_(FUNC_TYPE()){}
    void RunFunc()
    {
      table_.Run();
    }
  private:
    HT table_;
};

auto lambda_f = [](){cout<<"hello world\n";};
struct HashKey
{
  void operator()()
  {
    cout<<"hello world\n";
  }
};

int main()
{
  int a = 10;
  int x = hello_world(a);
  TestMap<decltype(lambda_f)> test_map;
//  TestMap<HashKey> test_map;
  test_map.RunFunc();
  return 0;
}

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
//[capture](params) mutable -> decltype(return_type){body}
//capture [=]按值捕获在lambda表达式所在函数的函数体中提及的全部自动储存持续性变量
//capture [&] 按引用捕获在lambda表达式所在函数的函数体中提及的全部自动储存持续性变量
//capture [a,&b]，按值捕获a，并按引用捕获b
int main()
{
  int low_bound = 5;
  vector<int> c{ 1,2,3,4,5,6,7 };
  //for_each(c.begin(), c.end(), [](int& item) { item = item + 2; });
  //c.erase(std::remove_if(c.begin(), c.end(), [low_bound](int& item){ return item < low_bound; }), c.end());
  auto it = std::remove_if(c.begin(), c.end(), [low_bound](int& item){ return item < low_bound; });
  for_each(c.begin(), it, [](int& item) { cout<<item; });
  for_each(it, c.end(), [](int& item) { cout<<item; });
  return 0;
}

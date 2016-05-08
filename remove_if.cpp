#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
struct Predictor
{
  Predictor(T value):threshhold(value){}
  bool operator ()(const T& value)
  {
    if (value < threshhold)
    {
      return true;
    }
    return false;
  }
  T threshhold;
};

template<typename Iterator, class Predictor>
Iterator self_remove_if (Iterator first, Iterator last, Predictor predictor)
{
  while (first != last && !predictor(*first))
  {
    ++first;
  }
  Iterator invalid = first;
  ++first;
  while (first < last)
  {
    if (!predictor(*first))
    {
      *invalid = *first;
      ++invalid;
    }
    ++first;
  }
  return invalid;
}
int main()
{
  int32_t low_bound = 6;
  vector<int> value = {9,1,2,3,4,5,6,7,8};
  self_remove_if(value.begin(), value.end(), Predictor<int>(low_bound));
  for_each(value.begin(), value.end(), [](int32_t& item){cout<<item;});
  return 0;
}

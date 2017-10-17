#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Interval
{
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
};

class Solution
{
public:
  vector<Interval> merge(vector<Interval>& intervals)
  {
    vector<Interval> result;
    result.reserve(intervals.size());
    if (intervals.empty())
    {
      return result;
    }

    auto lambda_comparer = [](const Interval& left, const Interval& right){ return left.start != right.start ? left.start < right.start : left.end < right.end; };
    set<Interval, decltype(lambda_comparer)> sorted_set(lambda_comparer);

    for (auto it = intervals.begin(); it != intervals.end(); ++it)
    {
      sorted_set.emplace(std::move(*it));
    }
    auto set_it = sorted_set.begin();
    result.emplace_back(*set_it);
    while (++set_it != sorted_set.end())
    {
      auto& last  = result.back();
      auto& value = *set_it;
      if (last.end < value.start)
      {
        result.emplace_back(std::move(value));
      }
      else
      {
       last.end = last.end < value.end ? value.end : last.end;
       last.start = last.start < value.start ? last.start : value.start;
      }
    }
    return result;
  }
};


int main()
{
//  vector<Interval> input = {{1, 4}, {0, 4}, {1, 4}, {1,4}, {0, 4}};
//  vector<Interval> input = {{1,10}, {2,3}, {4,5}, {7,8}};
  vector<Interval> input;

  Solution s;
  vector<Interval> result = s.merge(input);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << it->start << "\t" << it->end << endl;
  }
  return 0;
}

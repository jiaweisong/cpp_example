#include <iostream>
#include <vector>
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
  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
  {
    vector<Interval> result;
    result.reserve(intervals.size());

    bool has_inserted = false;
    auto it = intervals.begin();
    while (it != intervals.end())
    {
      auto& curr = *it;
      if (newInterval.end < curr.start)
      {
        result.emplace_back(std::move(newInterval));
        has_inserted = true;
        break;
      }

      if (curr.end < newInterval.start)
      {
        result.emplace_back(std::move(curr));
      }
      else
      {
        newInterval.start = newInterval.start < curr.start ? newInterval.start : curr.start;
        newInterval.end = newInterval.end > curr.end ? newInterval.end : curr.end;
      }
      ++it;
    }

    while (it != intervals.end())
    {
      result.emplace_back(std::move(*it));
      ++it;
    }

    if (!has_inserted)
    {
      result.emplace_back(std::move(newInterval));
    }
    return result;
  }
};


int main()
{

  Solution s;
//  vector<Interval> result = s.insert(input, {0, 1});

//  vector<Interval> input = {{1,2}, {3,5}, {6,7}, {8,10}, {12,16}};
//  vector<Interval> result = s.insert(input, {4,9});

//  vector<Interval> input = {{1,2}, {3,5}, {6,7}, {8,10}, {12,16}};
//  vector<Interval> result = s.insert(input, {0, 1});

  vector<Interval> input = {{1,2}, {3,5}, {6,7}, {8,10}, {12,16}};
  vector<Interval> result = s.insert(input, {17,18});
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout << it->start << "\t" << it->end << endl;
  }
  return 0;
}


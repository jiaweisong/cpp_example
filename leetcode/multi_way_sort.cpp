#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    template<class Type>
    struct Meta
    {
      size_t way;
      typename vector<Type>::const_iterator iter;
      Meta(size_t w, typename vector<Type>::const_iterator it) : way(w), iter(it){}
      bool operator < (const Meta& other)
      {
        return *iter < *(other.iter);
      }
    };

    template<class Type>
    void AdjustHeap(vector<Type>& heap, int parent)
    {
      Type tmp = heap[parent];
      int left_child = (parent << 1) + 1;
      while (left_child < heap.size())
      {
        int right_child = left_child + 1;
        Type min = heap[left_child];
        if (right_child < heap.size() && heap[right_child] < min)
        {
          min = heap[right_child];
          left_child = right_child;
        }
        if (tmp < min)
        {
          break;
        }
        heap[parent] = min;
        parent = left_child;
        left_child = (parent << 1) + 1;
      }
      heap[parent] = tmp;
    }

    template <class Type>
    vector<Type> MultiWaySort(const vector<vector<Type>>& input)
    {
      vector<Meta<Type>> heap;
      heap.reserve(input.size());
      size_t result_size = 0;
      for (size_t index = 0; index < input.size(); ++index)
      {
        if (!input[index].empty())
        {
          heap.emplace_back(index, input[index].begin());
          result_size += input[index].size();
        }
      }
      vector<Type> result;
      result.reserve(result_size);

      for (int index = (heap.size()>>1)-1; index >= 0; --index)
      {
        AdjustHeap(heap, index);
      }
      while (!heap.empty())
      {
        result.push_back(*(heap[0].iter));
        ++heap[0].iter;
        if (heap[0].iter == input[heap[0].way].end())
        {
          heap[0] = heap.back();
          heap.pop_back();
        }
        AdjustHeap(heap, 0);
      }
      return result;
    }
};

int main()
{
  Solution s;

  vector<int> array0 = {9, 12, 17, 15, 10, 20, 60, 65, 14, 19};
  vector<int> array1 = {11, 12, 27, 30, 50, 18, 6,  5, 25, 15};
  vector<int> array2 = {42, 32, 14, 10, 20, 30, 61, 65, 4, 29};
  vector<int> array3 = {6, 22, 13, 32, 50, 26, 60, 62, 16, 39};

  std::sort(array0.begin(), array0.end());
  std::sort(array1.begin(), array1.end());
  std::sort(array2.begin(), array2.end());
  std::sort(array3.begin(), array3.end());
  vector<vector<int>> inputs = {array0, array1, array2, array3};
  vector<int32_t> result = s.MultiWaySort(inputs);
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    cout<<*it<<"\t";
  }
  cout<<endl;
  return 0;
}

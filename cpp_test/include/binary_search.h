#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <iostream>
#include <vector>
using namespace std;

template <class T>
int32_t lower_bound(const vector<T>& values, const T& key)
{
  int32_t low = 0, mid = 0, high = values.size()-1;
  while (low <= high)
  {
    mid = (low + high) >> 1;
    if (values[mid] >= key)
      high = mid - 1;
    else
      low = mid + 1;
  }
  return low;
}

template <class it_type, class T>
it_type my_lower_bound( it_type begin, it_type end, const T& key)
{
  int32_t low = 0, mid = 0, high = end - begin - 1;
  while (low <= high)
  {
    mid = (low + high) >> 1;
    if (key <= *(begin + mid))
      high = mid - 1;
    else
      low = mid + 1;
  }
  return begin+low;
}

template <class T>
int32_t upper_bound(const vector<T>& values, const T& key)
{
  int32_t low = 0, mid = 0, high = values.size()-1;
  while (low <= high)
  {
    mid = (low + high) >> 1;
    if (key >= values[mid])
      low = mid + 1;
    else
      high = mid - 1;
  }
  return high < 0 ? high+1 : high;
}

template <class it_type, class T>
it_type my_upper_bound( it_type begin, it_type end, const T& key)
{
  int32_t low = 0, mid = 0, high = end - begin - 1;
  while (low <= high)
  {
    mid = (low + high) >> 1;
    if (key >= *(begin + mid))
      low = mid + 1;
    else
      high = mid - 1;
  }
  return begin+low;
}

//template <class T>
//int32_t upper_bound(const vector<T>& values, int32_t low, int32_t high, const T& key)
//{
//  int32_t mid = 0;
//  while (low <= high)
//  {
//    mid = (low + high) >> 1;
//    if (key >= values[mid])
//      low = mid + 1;
//    else
//      high = mid - 1;
//  }
//  return high < 0 ? high+1 : high;
//}
//
//template <class T>
//bool upper_bound(const vector<T>& values, int32_t low, const T& key, int32_t& pos)
//{
//  int32_t mid = 0, high = values.size()-1;
//  while (low <= high)
//  {
//    mid = (low + high) >> 1;
//    if (key >= values[mid])
//      low = mid + 1;
//    else
//      high = mid - 1;
//  }
//  pos = high < 0 ? high+1 : high;
//  return values[pos] == key;
//}

template <class T>
int32_t binary_search(const vector<T>& values, const T& key)
{
  int32_t low = 0, mid = 0, high = values.size()-1;
  while (low <= high)
  {
    mid = (low + high) >> 1;
    if (key == values[mid])
      return mid;
    else if (key > values[mid])
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}

template <class T>
int32_t binary_search(const T* begin, const T* end, const T& key)
{
  int32_t low = 0, mid = 0, high = begin - end;
  while (low <= high)
  {
    mid = (low + high) >> 1;
    if (key == *(begin + mid))
      return mid;
    else if (key > *(begin + mid))
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}

// nums1.size > nums2.size
template <class T>
vector<T> binary_intersect(const vector<T>& nums1, const vector<T>& nums2)
{
  vector<T> result;
  result.reserve(nums1.size() > nums2.size() ? nums1.size() : nums2.size());
  auto begin1 = nums1.begin(), begin2 = nums2.begin();
  while (begin1 != nums1.end() && begin2 != nums2.end())
  {
    auto find_it = my_upper_bound(begin2, nums2.end(), *begin1);
    if (find_it != begin2 && *(find_it-1) == *begin1)
    {
      result.push_back(*begin1);
    }
    begin2 = find_it;
    ++begin1;

    if (begin1 >= nums1.end() || begin2 >= nums2.end())
      break;

    find_it = my_upper_bound(begin1, nums1.end(), *begin2);
    if (find_it != begin1 && *(find_it-1) == *begin2)
    {
      result.push_back(*begin2);
    }
    begin1 = find_it;
    ++begin2;
  }
  return result;
}

//template <class T>
//vector<T> binary_intersect(const vector<T>& nums1, const vector<T>& nums2)
//{
//  vector<T> result;
//  if (nums1.empty() || nums2.empty())
//    return result;
//  result.reserve(nums1.size() > nums2.size() ? nums1.size() : nums2.size());
//  auto begin1 = nums1.begin(), begin2 = nums2.begin();
//  while (begin1 != nums1.end() && begin2 != nums2.end())
//  {
//    auto find_it = my_lower_bound(begin2, nums2.end(), *begin1);
//    if (*find_it == *begin1)
//    {
//      result.push_back(*begin1);
//    }
//    begin2 = find_it+1;
//
//    if (begin2 >= nums2.end())
//    {
//      break;
//    }
//
//    find_it = my_lower_bound(begin1, nums1.end(), *begin2);
//    if (*find_it == *begin2)
//    {
//      result.push_back(*begin2);
//    }
//    begin1 = find_it+1;
//  }
//  return result;
//}

// nums1.size > nums2.size
template <class T>
vector<T> normal_intersect(const vector<T>& nums1, const vector<T>& nums2)
{
  vector<T> result;
  if (nums1.empty() || nums2.empty())
    return result;
  result.reserve(nums2.size());
  size_t pos1 = 0, pos2 = 0;
  while (pos1 < nums1.size() && pos2 < nums2.size())
  {
    if (nums1[pos1] == nums2[pos2])
    {
      result.push_back(nums1[pos1]);
      ++pos1;
      ++pos2;
    }
    else if (nums1[pos1] < nums2[pos2])
    {
      ++pos1;
    }
    else
    {
      ++pos2;
    }
  }
  return result;
}

// 4 5 6
// 3 4 5 6 7 8
// nums1.size > nums2.size
// nums1.size > nums2.size
template <class T>
vector<T> binary_union(const vector<T>& nums1, const vector<T>& nums2)
{
  vector<T> result;
  if (nums1.empty() || nums2.empty())
    return result;
  result.reserve(nums1.size() + nums2.size());
  auto begin1 = nums1.begin(), begin2 = nums2.begin();
  while (begin1 != nums1.end() && begin2 != nums2.end())
  {
    auto find_it = my_upper_bound(begin2, nums2.end(), *begin1);
    result.insert(result.end(), begin2, find_it);
    if (find_it == begin2 || *(find_it-1) != *begin1)
    {
      result.push_back(*begin1);
    }
    begin2 = find_it;
    ++begin1;

    if (begin1 >= nums1.end() || begin2 >= nums2.end())
      break;

    find_it = my_upper_bound(begin1, nums1.end(), *begin2);
    result.insert(result.end(), begin1, find_it);
    if (find_it == begin1 || *(find_it-1) != *begin2)
    {
      result.push_back(*begin2);
    }
    begin1 = find_it;
    ++begin2;
  }
  result.insert(result.end(), begin1, nums1.end());
  result.insert(result.end(), begin2, nums2.end());
  return result;
}

// nums1.size > nums2.size
template <class T>
vector<T> normal_union(const vector<T>& nums1, const vector<T>& nums2)
{
  vector<T> result;
  if (nums1.empty() || nums2.empty())
    return !nums1.empty() ? nums1 : nums2;
  result.reserve(nums1.size()+nums2.size());
  size_t pos1 = 0, pos2 = 0;
  while (pos1 < nums1.size() && pos2 < nums2.size())
  {
    if (nums1[pos1] == nums2[pos2])
    {
      result.push_back(nums1[pos1]);
      ++pos1;
      ++pos2;
    }
    else if (nums1[pos1] < nums2[pos2])
    {
      result.push_back(nums1[pos1]);
      ++pos1;
    }
    else
    {
      result.push_back(nums2[pos2]);
      ++pos2;
    }
  }
  while (pos1 < nums1.size())
  {
    result.push_back(nums1[pos1++]);
  }
  while (pos2 < nums2.size())
  {
    result.push_back(nums2[pos2++]);
  }
  return result;
}

template<typename T>
void Deduplication(vector<T>& values)
{
  int pos = 0;
  for (size_t i = 1; i < values.size(); ++i)
  {
    if (values[i] != values[pos])
    {
      values[++pos] = values[i];
    }
  }
  values.resize(values.empty() ? 0 : pos+1);
}
#endif

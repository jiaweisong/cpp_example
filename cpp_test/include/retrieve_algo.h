#ifndef RETRIEVER_ALGO_H_
#define RETRIEVER_ALGO_H_
#include <vector>
#include <list>
using std::vector;
using std::list;
using std::size_t;
/*
 * intersect, behave like merge algorithm
 */
template <typename value_type>
void NormalIntersect(const vector<value_type>& list1, const vector<value_type>& list2,
                     vector<value_type>& result)
{
  result.reserve(list1.size());
  for (typename vector<value_type>::const_iterator it1 = list1.begin(), it2 = list2.begin();
       it1 != list1.end() && it2 != list2.end();)
  {
    value_type e1 = *it1, e2 = *it2;
    if (e1 < e2)
    {
      ++it1;
    }
    else if (e1 > e2)
    {
      ++it2;
    }
    else
    {
      result.push_back(e1);
      ++it1;
      ++it2;
    }
  }
}

/*
 * binary search v in lists, return true denote find v successfully
 * store the lower bound index of v in result. that is, lists[result] <= v,
 * result is the largest index.
 */
template <typename value_type >
bool BinarySearch(const vector<value_type>& lists, const value_type& v, int i, int& result)
{
  int left = i, right = static_cast<int>(lists.size()); //[left, right), lower bound algorithm
  while (left < right - 1)
  {
    int mid = (right + left) >> 1;
    if (lists[mid] <= v)
    {
      left = mid;
    }
    else
    {
      right = mid;
    }
  }
  result = left;
  return left >= 0 && lists[left] == v;
}
template <typename value_type>
void BinaryIntersect(const vector<value_type>& small,
                     const vector<value_type>& large, vector<value_type>& result)
{
  int occur = 0;
  int i = 0, j = -1;
  int size1 = static_cast<int>(small.size()), size2 = static_cast<int>(large.size());
  result.reserve(small.size());

  while (i < size1 && j < size2)
  {
    if (BinarySearch(large, small[i], j, occur))
    {
      result.push_back(small[i]);
    }
    j = occur + 1;

    if (j < size2 && BinarySearch(small, large[j], i, occur))
    {
      result.push_back(large[j]);
    }
    i = occur + 1;
  }
}

template<typename value_type>
void BinaryIntersect2(const vector<value_type>& v1, const vector<value_type>& v2, vector<value_type>& result)
{
  result.reserve(v1.size());
  typename vector<value_type>::const_iterator it1 = v1.begin(), it2 = v2.begin();
  while (it1 != v1.end() && it2 != v2.end())
  {
    it2 = lower_bound(it2, v2.end(), *it1);
    if (it2 != v2.end())
    {
        if (*it2 == *it1)
        {
            result.push_back(*it1);
            ++it2;
            if (it2 == v2.end())
            {
              break;
            }
        }
    }
    else
    {
      break;
    }
    ++it1;
    it1 = lower_bound(it1, v1.end(), *it2);
    if (it1 != v1.end())
    {
        if (*it1 == *it2)
        {
            result.push_back(*it2);
            ++it1;
        }
    }
    ++it2;
  }
}



template <typename value_type>
void FastIntersectAux(const vector<value_type>& list1, const vector<value_type>& list2, vector<value_type>& result)
{
  if ((list1.size() << 2) <= list2.size())
  {
    BinaryIntersect(list1, list2, result);
  }
  else
  {
    NormalIntersect(list1, list2, result);
  }
}

template <typename value_type>
void FastIntersect(const vector<value_type>& list1, const vector<value_type>& list2, vector<value_type>& result)
{
  if (list1.size() < list2.size())
  {
    FastIntersectAux(list1, list2, result);
  }
  else
  {
    FastIntersectAux(list2, list1, result);
  }
}

template <typename Iterator, typename value_type>
void Intersect(Iterator beg, Iterator end, size_t size, vector<value_type>& result)
{
  vector<value_type> cur, tmp;

  if (size == 1ul)
  {
    cur.insert(cur.end(), (*beg)->begin(), (*beg)->end());
    ++beg;
  }
  else if (size >= 2ul)
  {
    const vector<value_type>* p1 = *beg, *p2 = *(++beg);
    FastIntersect(*p1, *p2, cur);
    ++beg;
  }

  for (; beg != end; ++beg)
  {
    FastIntersect(cur, *(*beg), tmp);
    cur.swap(tmp);
    tmp.clear();
  }
  result.swap(cur);
}
template <typename value_type>
void Intersect(const list<const vector<value_type>*>& lists, vector<value_type>& result)
{
  Intersect(lists.begin(), lists.end(), lists.size(), result);
}

template <typename value_type>
void Intersect(const vector<const vector<value_type>*>& lists, vector<value_type>& result)
{
  Intersect(lists.begin(), lists.end(), lists.size(), result);
}

template <typename value_type>
void Union(const vector<value_type>& list1,
           const vector<value_type>& list2, vector<value_type>& result)
{
  typename vector<value_type>::const_iterator iter_1 = list1.begin(), iter_2 =
    list2.begin();
  result.reserve(list1.size() + list2.size());

  while (iter_1 != list1.end() && iter_2 != list2.end())
  {
    value_type entry1 = *iter_1;
    value_type entry2 = *iter_2;
    if (entry1 == entry2)
    {
      result.push_back(entry1);
      ++iter_1;
      ++iter_2;
    }
    else if (entry1 < entry2)
    {
      result.push_back(entry1);
      ++iter_1;
    }
    else
    {
      result.push_back(entry2);
      ++iter_2;
    }
  }

  if (iter_1 != list1.end())
  {
    result.insert(result.end(), iter_1, list1.end());
  }

  if (iter_2 != list2.end())
  {
    result.insert(result.end(), iter_2, list2.end());
  }
}

template <typename Iterator, typename value_type>
void Union(Iterator beg, Iterator end, size_t size, vector<value_type>& result)
{
  vector<value_type> cur, tmp;

  if (size >= 2ul)
  {
    const vector<value_type>* p1 = *beg, *p2 = *(++beg);
    Union(*p1, *p2, cur);
    ++beg;
  }

  for (; beg != end; ++beg)
  {
    Union(cur, *(*beg), tmp);
    cur.swap(tmp);
    tmp.clear();
  }
  result.swap(cur);
}
template <typename value_type>
void Union(const list<const vector<value_type>*>& lists, vector<value_type>& result)
{
  Union(lists.begin(), lists.end(), lists.size(), result);
}
template <typename value_type>
void Union(const vector<const vector<value_type>*>& lists, vector<value_type>& result)
{
  Union(lists.begin(), lists.end(), lists.size(), result);
}

/*
 * an easy substraction implementation if sub_rhs_lists size is not big.
 */
template <typename value_type>
void Substraction(const vector<value_type>& list1, const vector<value_type>& list2, vector<value_type>& result)
{
  typename vector<value_type>::const_iterator iter_1 = list1.begin(), iter_2 =
    list2.begin();
  result.reserve(list1.size());

  while (iter_1 != list1.end() && iter_2 != list2.end())
  {
    const value_type& entry1 = *iter_1;
    const value_type& entry2 = *iter_2;
    if (entry1 == entry2)
    {
      ++iter_1;
      ++iter_2;
    }
    else if (entry1 < entry2)
    {
      result.push_back(entry1);
      ++iter_1;
    }
    else
    {
      ++iter_2;
    }
  }

  if (iter_1 != list1.end())
  {
    result.insert(result.end(), iter_1, list1.end());
  }
}

template <typename value_type>
struct Position
{
  typename vector<value_type>::const_iterator begin, end;
  //non-explicit
  Position(const vector<value_type>* pl): begin(pl->begin()), end(pl->end())
  {
  }
};

template <typename value_type>
void MultiWaySubstract(const vector<value_type>& sub_lhs, const vector<const vector<value_type>*>& sub_rhs_lists,
                       vector<value_type>& result)
{
  list<Position<value_type>> positions(sub_rhs_lists.begin(), sub_rhs_lists.end());
  result.reserve(sub_lhs.size());

  for (typename vector<value_type>::const_iterator it = sub_lhs.begin(); it != sub_lhs.end(); ++it)
  {
    typename vector<value_type>::value_type v = *it;
    bool found = false;

    for (typename list<Position<value_type>>::iterator pos = positions.begin();
         pos != positions.end();)
    {
      typename vector<value_type>::const_iterator& begin = pos->begin, &end = pos->end;
      while (begin != end && *begin < v)
      {
        ++begin;
      }

      if (begin == end)
      {
        pos = positions.erase(pos);
      }
      else
      {
        if (*begin == v)
        {
          ++begin;
          found = true;
          break;
        }
        ++pos;
      }
    }

    if (!found)
    {
      result.push_back(v);
    }
  }
}

#endif // RETRIEVER_ALGO_H_

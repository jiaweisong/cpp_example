#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Solution {
public:
  int findKthNumSortedArrays(vector<int>& nums1,vector<int>& nums2,int kth)
  {
    int m = nums1.size(), n = nums2.size();
	if (m == 0)
	{
	  return nums2[kth - 1];
	}
	if (n == 0)
	{
      return nums1[kth - 1];
	}
    int begin1 = 0, end1 = m;
    int begin2 = 0, end2 = n;
    while(kth > 1)
    {
      int length1 = end1 - begin1;
      if (length1 == 0)
      {
        return nums2[begin2 + kth - 1];
      }
        
      int length2 = end2 - begin2;
      if (length2 == 0)
      {
        return nums1[begin1 + kth - 1];
      }
	 
	  int step1 = std::min(kth >> 1, length1);
	  int step2 = std::min(kth >> 1, length2);
    
      if (nums1[begin1 + step1 - 1] <= nums2[begin2 + step2 - 1])
      {
        begin1 = begin1 + step1;
		kth -= step1;
      }
      else if(nums1[begin1 + step1 - 1] > nums2[begin2 + step2 - 1])
      {
        begin2 = begin2 + step2;
		kth -= step2;
      }
    }
	
    if (end1 - begin1 == 0)
    {
      return nums2[begin2 + kth - 1];
    }
     
    if (end2 - begin2 == 0)
    {
      return nums1[begin1 + kth - 1];
    }
    return nums1[begin1] < nums2[begin2] ? nums1[begin1] : nums2[begin2];
  }

  double findMedianSortedArrays(vector<int> nums1, vector<int> nums2) {
	cout<<setprecision(8);
    int m = nums1.size(), n = nums2.size();
    int length = m + n;
	if (length % 2 == 0)
	{
	  double value1 = findKthNumSortedArrays(nums1, nums2, length/2);
	  double value2 = findKthNumSortedArrays(nums1, nums2, length/2 + 1);
	  cout<<value1<<endl;
	  cout<<value2<<endl;
	  return (value1 + value2) / 2.0;
	}
	else
	{
      return findKthNumSortedArrays(nums1, nums2, length/2 + 1);
	}
  } 
};


void expect_true(double a, double b)
{
  if (a != b)
  {
	cout<<"error : "<< a <<" != "<< b <<endl;
  }
}
int main()
{
  vector<int> nums1 = {1,2};
  vector<int> nums2 = {1,2};


  Solution s;
  double res = s.findMedianSortedArrays({1,2},{1,2});
  expect_true(res,1.5);
  res = s.findMedianSortedArrays({3},{1,2,4});
  expect_true(res,2.5);
  res = s.findMedianSortedArrays({3},{1,2,4,5,6});
  expect_true(res, 3.5);
  res = s.findMedianSortedArrays({1},{1});
  expect_true(res,1);
  //int res = s.findKthNumSortedArrays(nums1,nums2,2);
  //cout<<res<<endl;
  return 0;
}

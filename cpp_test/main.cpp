#include "include/head.h"
#include "include/time.h"
#include "include/random.h"
#include "include/binary_search.h"
#include "include/retrieve_algo.h"
using namespace std;

int main()
{
  int i = 0, num = 1000;
//  int i = 0, num = 1;
  int64_t binary_sum = 0, normal_sum = 0;
  while (i++ < num)
  {
    vector<int> nums1, nums2;
    int r_num = 50;
    nums1.reserve(r_num);
    nums2.reserve(r_num);
    int i = 0;
    while (i++ < (r_num >> 2))
    {
      nums1.push_back(random(0, 100 >> 2));
    }
    while (i++ < r_num)
    {
      nums2.push_back(random(0, 100));
    }
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    Deduplication(nums1);
    Deduplication(nums2);

    int64_t binary_start = Time();
//    vector<int> result1 = binary_intersect(nums1, nums2);
    vector<int> result1;
    BinaryIntersect(nums1, nums2, result1);

    binary_sum += (Time() - binary_start);
    int64_t normal_start = Time();
//    vector<int> result2 = binary_intersect(nums1, nums2);
    vector<int> result2 = normal_intersect(nums1, nums2);
    normal_sum += (Time() - normal_start);
    if (result1 != result2)
    {
      cout << "binary intersect error" << endl;
    }
  }
//  float binary_avg = binary_sum / num;
//  float normal_avg = normal_sum / num;
//  cout << "binary_avg " << binary_avg << "\t" << "normal_avg " << normal_avg << "\t"
//      << "performace " << (normal_avg - binary_avg) / binary_avg << endl;
  cout << "binary_sum " << binary_sum << "\t" << "normal_sum " << normal_sum << "\t"
      << "performace " << (normal_sum - binary_sum) / binary_sum << endl;
  return 0;
}

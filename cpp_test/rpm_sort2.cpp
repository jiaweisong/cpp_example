#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <random>
using namespace std;

size_t GenRandomNum(std::ptrdiff_t num)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, num);
  return dis(gen);
}

struct AdCandidate
{
  int32_t rpm;
  int32_t id;
};

auto ad_cpm_greater = [](const AdCandidate& ad1, const AdCandidate& ad2)
          {
            return  ad1 .rpm != ad2.rpm ? ad1.rpm > ad2.rpm : ad1.id > ad2.id;
          };

int main()
{
  AdCandidate ad0  = {16, 1001};
  AdCandidate ad1  = {18, 1004};
  AdCandidate ad2  = {13, 1003};
  AdCandidate ad3  = {18, 1004};
  AdCandidate ad4  = {16, 1002};
  AdCandidate ad5  = {13, 1001};
  AdCandidate ad6  = {15, 1005};
  AdCandidate ad7  = {14, 1006};
  AdCandidate ad8  = {17, 1007};
  AdCandidate ad9  = {16, 1001};
  AdCandidate ad10 = {13, 1005};
  AdCandidate ad11 = {13, 1004};

  vector<AdCandidate> ad_list = {ad0, ad1, ad2, ad3, ad4, ad5, ad6, ad7, ad8, ad9, ad10, ad11};
  sort(ad_list.begin(), ad_list.end(), ad_cpm_greater);
  cout<<"~~~~~~~~~~~~before_sort~~~~~~~~~~~~~~~"<<endl;
  for (auto it = ad_list.begin(); it != ad_list.end(); ++it)
  {
    cout<<"rpm = "<<it->rpm<<"  advertiserId = "<<it->id<<endl;
  }
  unordered_set<int32_t> id_selected;
  vector<AdCandidate> selected_result, removed_result, same_rpm_result;
  int32_t same_rpm_count = 0;
  auto last_it = ad_list.begin();
  auto it = ad_list.begin();
  while (last_it != ad_list.end())
  {
    if (it != ad_list.end() && last_it->rpm == it->rpm)
    {
      ++it;
      continue;
    }
    auto diff_it = last_it;
    while((diff_it+1) != it && diff_it->id != (diff_it+1)->id) {
      if (id_selected.end() == id_selected.find(diff_it->id)) {
        selected_result.push_back(*diff_it);
        id_selected.insert(diff_it->id);
      }
      ++diff_it;
    }
    std::ptrdiff_t region = it - diff_it;
    size_t index = GenRandomNum(region - 1);
    cout << diff_it->rpm << "\t" << index << endl;
    auto cand = diff_it + index;
    if (id_selected.end() == id_selected.find(cand->id)) {
      selected_result.push_back(*cand);
      id_selected.insert(cand->id);
    }
    last_it = it;
    ++it;
  }
  for (auto it = selected_result.begin(); it != selected_result.end(); ++it)
  {
    cout << it->rpm << "\t" << it->id << endl;
  }
}

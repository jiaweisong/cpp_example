#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

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
  auto begin0 = ad_list.begin(), end = ad_list.end();
  sort(begin0, end, ad_cpm_greater);
  cout<<"~~~~~~~~~~~~before_sort~~~~~~~~~~~~~~~"<<endl;
  for (auto it = begin0; it != end; ++it)
  {
    cout<<"rpm = "<<it->rpm<<"  advertiserId = "<<it->id<<endl;
  }
  unordered_set<int32_t> id_selected;
  vector<AdCandidate> selected_result, removed_result, same_rpm_result;
  int32_t same_rpm_count = 0;
  auto begin = ad_list.begin();
  if (begin != ad_list.end() && selected_result.empty())
  {
    selected_result.push_back(*begin);
    id_selected.insert(begin->id);
    ++begin;
  }
  for (auto it = begin; it != ad_list.end(); ++it)
  {
    if (id_selected.end() != id_selected.find(it->id))
    {
      removed_result.push_back(*it);
      continue;
    }

    if (it->rpm != selected_result.back().rpm)
    {
      std::random_shuffle(same_rpm_result.begin(), same_rpm_result.end());
      for (auto same_it = same_rpm_result.begin(); same_it != same_rpm_result.end(); ++same_it)
      {
        selected_result.push_back(*same_it);
        id_selected.insert(same_it->id);
      }
      same_rpm_result.clear();
      selected_result.push_back(*it);
      id_selected.insert(it->id);
      continue;
    }

    if (it->rpm == selected_result.back().rpm)
    {
      if (same_rpm_result.empty() || same_rpm_result.back().id != it->id)
      {
        same_rpm_result.push_back(*it);
        same_rpm_count = 0;
      }
      else
      {
        same_rpm_count++;
        bool need_swap = (rand() / double(RAND_MAX)) < (1.0 / (same_rpm_count + 1)) ? true : false;
        if (need_swap)
        {
          removed_result.push_back(same_rpm_result.back());
          same_rpm_result.pop_back();
          same_rpm_result.push_back(*it);
        }
        else
        {
          removed_result.push_back(*it);
        }
      }
      continue;
    }
  }
  if (!same_rpm_result.empty())
  {
    std::random_shuffle(same_rpm_result.begin(), same_rpm_result.end());
    for (auto same_it = same_rpm_result.begin(); same_it != same_rpm_result.end(); ++same_it)
    {
      selected_result.push_back(*same_it);
      id_selected.insert(same_it->id);
    }
    same_rpm_result.clear();
  }

  cout<<"~~~~~~~~~~~~after_sort~~~~~~~~~~~~~~~"<<endl;
//  selected_result.insert(selected_result.end(), removed_result.begin(), removed_result.end());
  for (auto it = selected_result.begin(); it != selected_result.end(); ++it)
  {
    cout<<"rpm = "<<it->rpm<<"  advertiserId = "<<it->id<<endl;
  }
  return 0;
}

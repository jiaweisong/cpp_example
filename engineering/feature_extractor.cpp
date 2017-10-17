#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class FeatureExtractor;
using FUNC_TYPE = void* (FeatureExtractor::*)(void);

enum VALUE_TYPE
{
  INT64,
  VECTOR_INT64,
};

struct FeatureInfo
{
  VALUE_TYPE type;
  FUNC_TYPE extract_func;
};


class FeatureExtractor
{
  public:
    using int64_feature = int64_t (FeatureExtractor::*)(void);
    using vector_int64_feature = vector<int64_t> (FeatureExtractor::*)(void);

  public:
    int64_t AdvertiseId();
    vector<int64_t> CookieLabel();

    inline void FeatureValue(const FeatureInfo& feature, vector<int64_t>& value)
    {
      if (feature.type == VALUE_TYPE::INT64)
      {
        value.push_back((this->*(int64_feature)feature.extract_func)());
      }
      else if (feature.type == VALUE_TYPE::VECTOR_INT64)
      {
        vector<int64_t> res = (this->*(vector_int64_feature)feature.extract_func)();
        value.swap(res);
      }
    }

    inline FUNC_TYPE GetFunction(const string& name)
    {
      auto it = feature_func_map.find(name);
      return (it != feature_func_map.end()) ? it->second.extract_func : nullptr;
    }

  private:
    static unordered_map<string, FeatureInfo> feature_func_map;
};

unordered_map<string, FeatureInfo> FeatureExtractor::feature_func_map =
{
  {"AdvertiseId", {VALUE_TYPE::INT64,        (FUNC_TYPE)&FeatureExtractor::AdvertiseId}},
  {"CookieLabel", {VALUE_TYPE::VECTOR_INT64, (FUNC_TYPE)&FeatureExtractor::CookieLabel}},
};

int64_t FeatureExtractor::AdvertiseId(void)
{
  return 100;
}

vector<int64_t> FeatureExtractor::CookieLabel(void)
{
  vector<int64_t> res;
  res.push_back(101);
  res.push_back(102);
  return res;
}

int main()
{
  FeatureExtractor extractor;
  FeatureInfo advertiseid;
  advertiseid.type = VALUE_TYPE::INT64;
  advertiseid.extract_func = extractor.GetFunction("AdvertiseId");
  if (advertiseid.extract_func != nullptr)
  {
    vector<int64_t> value;
    extractor.FeatureValue(advertiseid, value);
    for (auto it : value)
    {
      cout<<it<<endl;
    }
  }

  FeatureInfo cookielabel;
  cookielabel.type = VALUE_TYPE::VECTOR_INT64;
  cookielabel.extract_func = extractor.GetFunction("CookieLabel");
  if (cookielabel.extract_func != nullptr)
  {
    vector<int64_t> value;
    extractor.FeatureValue(cookielabel, value);
    for (auto it : value)
    {
      cout<<it<<endl;
    }
  }

  FeatureInfo creativeid;
  creativeid.type = VALUE_TYPE::VECTOR_INT64;
  creativeid.extract_func = extractor.GetFunction("CreativeId");
  if (creativeid.extract_func != nullptr)
  {
    vector<int64_t> value;
    extractor.FeatureValue(creativeid, value);
    for (auto it : value)
    {
      cout<<it<<endl;
    }
  }
  else
  {
    cout<<"creative is null\n";
  }

  return 0;
}

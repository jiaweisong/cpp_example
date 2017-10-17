#include <iostream>
#include <functional>
#include <map>

using namespace std;

struct Request
{
  string feature_name;
  string feature_value;
};

class Extractor
{
  private:
    static map<string, std::function<string (Request* info)>> func_map_;
  public:
    Extractor()
    {
      func_map_["cookielabel"] = [](Request* req)->string
      {
        //return std::to_string(req);
        return req->feature_value;
      };
    }

    bool find(string feature_name)
    {
      return func_map_.find(feature_name) != func_map_.end();
    }

    std::function<string (Request* req)> Get(string feature_name)
    {
      return func_map_[feature_name];
    }
};

map<string, std::function<string (Request* info)>> Extractor::func_map_;

int main()
{
  Extractor extractor;
  Request* req = new Request();
  req->feature_name = "cookielabel";
  req->feature_value = "hello world";
  if (extractor.find(req->feature_name))
  {
    std::function<string (Request* req)> func = extractor.Get(req->feature_name);
    string value = func(req);
    cout<<value<<endl;
   }
  return 0;
}

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct Request;

struct BatchRequest
{
  vector<weak_ptr<Request>> requests;
  ~BatchRequest(){ cout<<"BatchRequest destructor\n"; }
};

auto BatchRequest_Deleter = [](BatchRequest* ptr)
{
  delete ptr;
};

struct Request
{
  Request() = default;
  Request(const string& info): info_(info){}
  ~Request(){ cout<<info_<< "  "<< "destructor\n"; }

  shared_ptr<BatchRequest> batch;
  string info_;
};

auto Request_Deleter = [](Request* ptr)
{
  shared_ptr<Request> req(ptr);
  ptr->batch->requests.push_back(req);
};

void test(shared_ptr<BatchRequest>& batch)
{
  shared_ptr<Request> request;
  request.reset(new Request("request 1"), Request_Deleter);
  request->batch = batch;
}
int main()
{
  shared_ptr<BatchRequest> batch_request(new BatchRequest(), BatchRequest_Deleter);
  test(batch_request);
  auto& requests = batch_request->requests;
  for (auto it = requests.begin(); it != requests.end(); ++it)
  {
    auto sp = it->lock();
    if (sp != nullptr)
    {
      cout<<sp->info_<<endl;
    }
    else
    {
      cout<<"after shared_ptr destructed\n";
    }
  }
  return 0;
}

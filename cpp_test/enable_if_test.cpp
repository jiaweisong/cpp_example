#include <type_traits>
#include <iostream>
#include <string>

using namespace std;
struct CtrModel
{
  int expid;
};

struct CvrModel
{
  int expid;
  int cvr_type;
};

template<typename T>
int GetKey(T& model, std::true_type)
{
  cout<<"cvr type is true"<<endl;
  return model.expid + model.cvr_type;
}

template<typename T>
int GetKey(T& model, std::false_type)
{
  cout<<"cvr type is false"<<endl;
  return model.expid;
}

template<typename T, typename std::enable_if<std::is_same<T, CvrModel>::value ,int>::type = 0>
int GetKey(T& model)
{
  cout<<"is cvrmodel\n";
  return model.expid + model.cvr_type;
}

template<typename T>
int GetKey(T& model)
{
  cout<<"is not cvrmodel\n";
  return model.expid;
}

template<typename T>
int GetModelKey(T& model)
{
  return GetKey(model, std::is_same<T, CvrModel>());
}

int main()
{
  CtrModel ctr;
  CvrModel cvr;
  GetKey(ctr);
  GetKey(cvr);
//  GetModelKey(ctr);
//  cout<<"---------"<<endl;
//  GetModelKey(cvr);
  return 0;
}

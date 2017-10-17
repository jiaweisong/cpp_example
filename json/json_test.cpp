#include <iostream>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include <vector>
#include "json/json.h"
using namespace std;
enum NodeOpt
{
  EMBEDDING = 0,
  GROUP = 1,
  PRODUCT = 2,
  FULL_CONNECT = 3,
  RELU = 4,
  L2_NORM = 5,
  FINAL = 6,
};

struct Params
{
  int32_t size;
  unordered_map<int64_t, vector<float>> embedding_map;
  vector<int32_t> weights;
};

void DumpParams(const Params& params)
{
  cout<<"size = "<<params.size<<endl;
  for (auto it = params.embedding_map.begin(); it != params.embedding_map.end(); ++it)
  {
//    int64_t key = it->first;
//    const vector<float>& values = it->second;
//    cout<<key<<" : ";
//    for (size_t i = 0; i < values.size(); ++i)
//    {
//      cout<<values[i]<<"\t";
//    }
//    cout<<endl;
  }
}

struct PNNNode
{
  int32_t node_id;
  vector<int32_t> dep_nodes;
  string operation;
  string dep_feature;
  bool is_cand_related;
  Params params;
};

struct PNNModel
{
  vector<PNNNode> nodes;
};

void DumpPNNModel(const PNNModel& pnn_model)
{
  for (auto it = pnn_model.nodes.begin(); it != pnn_model.nodes.end(); ++it)
  {
    cout<<"==========================================\n";
    cout<<"node_id = "<<it->node_id<<endl;
    cout<<"operation = "<<it->operation<<endl;
    cout<<"candidate_related = "<<it->is_cand_related<<endl;
    cout<<"dep_feature = "<<it->dep_feature<<endl;
//    for (size_t i = 0; i < it->dep_nodes.size(); ++i)
//    {
//      cout<<it->dep_nodes[i]<<"\t";
//    }
//    cout<<endl;
    DumpParams(it->params);
  }
}

struct Ctr_model
{
  int32_t expid;
  int32_t major_version;
  int32_t minor_version;
  string model_tag;
  PNNModel model;
};


void DumpModel(const Ctr_model& model)
{
  cout<<"expid = "<<model.expid<<endl;
  cout<<"major_version = "<<model.major_version<<endl;
  cout<<"minor_version = "<<model.minor_version<<endl;
  cout<<"model_tag = "<<model.model_tag<<endl;
  DumpPNNModel(model.model);
}

vector<float> ConvertToFloatVector(Json::Value& array)
{
  vector<float> list(array.size(), 0);
  for (size_t i = 0; i < array.size(); ++i)
  {
    list[i] = array[i].asFloat();
  }
  return list;
}

vector<int> ConvertToIntVector(Json::Value& array)
{
  vector<int> list(array.size(), 0);
  for (size_t i = 0; i < array.size(); ++i)
  {
    list[i] = array[i].asInt();
  }
  return list;
}

int main()
{
  ifstream file_obj("/mnt/hgfs/shared/deep_learning.st_pnn");
  if (!file_obj.is_open())
  {
    cout<<"file open error\n";
    return -1;
  }
  stringstream buffer;
  buffer << file_obj.rdbuf();
//  cout<<buffer.str()<<endl;
  Json::Reader reader;
  Json::Value value;
  clock_t start = clock();
  if (reader.parse(buffer.str(), value))
  {
    Ctr_model model;
    model.expid = value["exp_id"].asInt();
    model.major_version = value["major_version"].asInt();
    model.minor_version = value["minor_version"].asInt();
    model.model_tag = value["model_tag"].asString();
    PNNModel& pnn_model = model.model;

    Json::Value nodes = value["entire_model"];
    for (size_t i = 0; i < nodes.size(); ++i)
    {
      PNNNode pnn_node;
      Params params;
      pnn_node.node_id = nodes[i]["id"].asInt();
      pnn_node.dep_feature = nodes[i]["dep_fea"].asString();
      pnn_node.operation = nodes[i]["op"].asString();
      pnn_node.is_cand_related = nodes[i]["candidate_related"].asBool();
      Json::Value dep_ids = nodes[i]["dep_ids"];
      Json::Value param = nodes[i]["param"];
      Json::Value embedding_map = param["embedding_map"];
      params.size = param["size"].asInt();
      pnn_node.dep_nodes = ConvertToIntVector(dep_ids);
      Json::Value::Members sub_mem = embedding_map.getMemberNames();
      for (auto name_it = sub_mem.begin(); name_it != sub_mem.end(); ++name_it)
      {
        Json::Value array = embedding_map[*name_it];
        int64_t key = stoll(*name_it);
        params.embedding_map[key] = ConvertToFloatVector(array);
      }
      pnn_node.params = std::move(params);
      pnn_model.nodes.emplace_back(std::move(pnn_node));
    }
    double loadtime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    cout <<"time : "<< loadtime <<"s"<<endl;
//    DumpModel(model);
  }

}

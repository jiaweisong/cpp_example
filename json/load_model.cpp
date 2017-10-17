#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <vector>
#include <algorithm>
#include <math.h>
#include "rapidjson/document.h"

using namespace rapidjson;
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
unordered_map<string, NodeOpt> opt_map = {{"Embedding", NodeOpt::EMBEDDING}, {"Group", NodeOpt::GROUP}, {"Product", NodeOpt::PRODUCT}, {"Conn", NodeOpt::FULL_CONNECT}, {"Relu", NodeOpt::RELU}, {"L2-Norm", NodeOpt::L2_NORM}, {"Final", NodeOpt::FINAL}};

struct Params
{
  int32_t size = 0;
  unordered_map<int64_t, vector<float>> embedding_map;
  vector<vector<float>> weights;
  vector<float> bias;
};

struct PNNNode
{
  int32_t node_id;
  vector<int32_t> dep_nodes;
  string operation = "none";
  NodeOpt opt;
  string dep_feature;
  int32_t dep_feature_index = -1;
  bool is_cand_related = false;
  Params params;
};

struct PNNModel
{
  vector<PNNNode> nodes;
};

struct CtrModel
{
  int32_t expid;
  int32_t major_version;
  int32_t minor_version;
  string model_tag;
  PNNModel model;
};

struct FeatureValue
{
  vector<int64_t> values;
};

struct NodeValue
{
  NodeValue() = default;
  NodeValue(const vector<float>& v) : values(v){}
  void push_back(const NodeValue& v)
  {
    values.insert(values.end(), v.values.begin(), v.values.end());
  }
  vector<float> values;
};

struct Status
{
  int32_t ac_size = 3;
  vector<vector<FeatureValue>> feature_values;
  vector<vector<NodeValue>> deep_values;
};

void InitStatus(const vector<vector<FeatureValue>>& values, const vector<PNNNode>& nodes, Status& status)
{
  size_t ac_size = status.ac_size;
  status.feature_values = values;
  size_t node_size = nodes.size();
  status.deep_values.resize(ac_size);
  for (size_t i = 0; i < ac_size; ++i)
  {
    status.deep_values[i].resize(node_size);
  }
}

void PrintStatus(const Status& status)
{
  auto& deep_values = status.deep_values;
  for (size_t ac_index = 0; ac_index < deep_values.size(); ++ac_index)
  {
    cout<<"ac_index = "<<ac_index<<endl;
    for (size_t node_index = 0; node_index < deep_values[ac_index].size(); ++node_index)
    {
      cout<<"node_index = "<<node_index<<endl;
      auto& values = deep_values[ac_index][node_index].values;
      for (auto it = values.begin(); it != values.end(); ++it)
      {
        cout<<*it<<"\t";
      }
      cout<<endl;
    }
    cout<<"-------------------------------------------------------\n";
  }
}

vector<int> ConvertToIntVector(const Value& array)
{
  vector<int> list;
  if (array.IsArray() && !array.IsNull())
  {
    list.resize(array.Size());
    for (size_t i = 0; i < array.Size(); ++i)
    {
      list[i] = array[i].GetInt();
    }
  }
  if (array.IsNumber() && !array.IsNull())
  {
    list.push_back(array.GetInt());
  }
  return list;
}

vector<float> ConvertToFloatVector(const Value& array)
{
  vector<float> list;
  if (array.IsArray() && !array.IsNull())
  {
    list.resize(array.Size());
    for (size_t i = 0; i < array.Size(); ++i)
    {
      list[i] = array[i].GetDouble();
    }
  }
  return list;
}


template<class T>
vector<vector<T>> MatrixTranspose(vector<vector<T>>& matrix)
{
  vector<vector<T>> result;
  if (matrix.size() == 0 || matrix[0].size() == 0)
  {
    return result;
  }
  result.resize(matrix[0].size());
  for (auto it = result.begin(); it != result.end(); ++it)
  {
    it->resize(matrix.size());
  }
  for (size_t i = 0; i < matrix.size(); ++i)
  {
    for (size_t j = 0; j < matrix[i].size(); ++j)
    {
      result[j][i] = matrix[i][j];
    }
  }
  return result;
}

void VectorSum(const NodeValue& node_value, NodeValue& node_sum)
{
  const vector<float>& values = node_value.values;
  vector<float>& sum = node_sum.values;
  size_t size = sum.size() < values.size() ? values.size() : sum.size();
  sum.resize(size);
  for (size_t i = 0; i < values.size(); ++i)
  {
    sum[i] += values[i];
  }
}

void VectorProduct(const NodeValue& pre, const NodeValue& post, NodeValue& target)
{
  const vector<float>& pre_values = pre.values;
  const vector<float>& post_values = post.values;
  vector<float>& values = target.values;
  size_t size = pre_values.size() < post_values.size() ? pre_values.size() : post_values.size();
  for (size_t i = 0; i < size; ++i)
  {
    values.push_back(pre_values[i] * post_values[i]);
  }
}

void VectorConn(const NodeValue& src_node, const vector<vector<float>>& weights, NodeValue& dst_node)
{
  const vector<float>& src = src_node.values;
  vector<float>& dst = dst_node.values;
  if (weights.size() == 0 || weights[0].size() == 0 || weights[0].size() != src.size())
  {
    return;
  }
  dst.resize(weights.size(), 0);
  for (size_t i = 0; i < weights.size(); ++i)
  {
    float sum = 0;
    for (size_t j = 0; j < weights[i].size(); ++j)
    {
      sum += (src[j] * weights[i][j]);
    }
    dst[i] = sum;
  }
}

void VectorRelu(const NodeValue& src_node, NodeValue& dst_node)
{
  const vector<float>& src = src_node.values;
  vector<float>& dst = dst_node.values;
  dst.resize(src.size(), 0);
  std::transform(src.begin(), src.end(), dst.begin(), [](float value)
          {
            return value > 0 ? value : 0;
          });
}

void VectorNorm(const NodeValue& src_node, NodeValue& dst_node)
{
  const vector<float>& src = src_node.values;
  vector<float>& dst = dst_node.values;
  dst.resize(src.size(), 0);
  double sum = 0;
  for (size_t i = 0; i < src.size(); ++i)
  {
    sum += pow(src[i], 2);
  }
  if (sum == 0)
  {
    return;
  }
  double square = sqrt(sum);
  std::transform(src.begin(), src.end(), dst.begin(), [square](float value)
          {
            return  value / square;
          });
}

class DeepLearning
{
  public:
    static void PredictCtr(const CtrModel& ctr_model, Status& status);
    static void Embedding(const PNNNode& node, Status& status);
    static void Group(const vector<PNNNode>& nodes, const PNNNode& node, Status& status);
    static void Product(const vector<PNNNode>& nodes, const PNNNode& node, Status& status);
    static void Conn(const vector<PNNNode>& nodes, const PNNNode& node, Status& status);
    static void Relu(const vector<PNNNode>& nodes, const PNNNode& node, Status& status);
    static void Norm(const vector<PNNNode>& nodes, const PNNNode& node, Status& status);
    static void Final(const PNNNode& node, Status& status);
};

void DeepLearning::PredictCtr(const CtrModel& ctr_model, Status& status)
{
  auto& nodes = ctr_model.model.nodes;
  for (auto it = nodes.begin(); it != nodes.end(); ++it)
  {
    switch (it->opt)
    {
      case NodeOpt::EMBEDDING:
        Embedding(*it, status);
        break;

      case NodeOpt::GROUP:
        Group(ctr_model.model.nodes, *it, status);
        break;

      case NodeOpt::PRODUCT:
        Product(ctr_model.model.nodes, *it, status);
        break;

      case NodeOpt::FULL_CONNECT:
        Conn(ctr_model.model.nodes, *it, status);
        break;

      case NodeOpt::RELU:
        Relu(ctr_model.model.nodes, *it, status);
        break;

      case NodeOpt::L2_NORM:
        Norm(ctr_model.model.nodes, *it, status);
        break;

      case NodeOpt::FINAL:
        Final(*it, status);
        break;
      default:
        break;

    }
  }
}

void DeepLearning::Embedding(const PNNNode& node, Status& status)
{
  int32_t feature_index = node.dep_feature_index;
  int32_t node_id = node.node_id;
  int32_t ac_size = node.is_cand_related ? status.ac_size : 1;
  for (size_t i = 0; i < ac_size; ++i)
  {
    const vector<int64_t>& feature_value = status.feature_values[feature_index][i].values;
    vector<NodeValue> node_values;
    for (auto it = feature_value.begin(); it != feature_value.end(); ++it)
    {
      auto find_it = node.params.embedding_map.find(*it);
      if (find_it != node.params.embedding_map.end())
      {
        node_values.push_back(find_it->second);
      }
    }
    for (size_t j = 1; j < node_values.size(); ++j)
    {
      VectorSum(node_values[j], node_values[0]);
    }
    status.deep_values[i][node_id] = std::move(node_values[0]);
  }
}

void DeepLearning::Group(const vector<PNNNode>& nodes, const PNNNode& node, Status& status)
{
  int32_t node_id = node.node_id;
  int32_t ac_size = node.is_cand_related ? status.ac_size : 1;
  const vector<int32_t>&dep_ids = node.dep_nodes;
  for (size_t i = 0; i < ac_size; ++i)
  {
    NodeValue tmp;
    for (auto it = dep_ids.begin(); it != dep_ids.end(); ++it)
    {
      NodeValue& values = nodes[*it].is_cand_related ? status.deep_values[i][*it] : status.deep_values[0][*it];
      VectorSum(values, tmp);
    }
    status.deep_values[i][node_id] = std::move(tmp);
  }
}

void DeepLearning::Product(const vector<PNNNode>& nodes, const PNNNode& node, Status& status)
{
  int32_t node_id = node.node_id;
  int32_t ac_size = node.is_cand_related ? status.ac_size : 1;
  const vector<int32_t>&dep_ids = node.dep_nodes;
  for (size_t k = 0; k < ac_size; ++k)
  {
    NodeValue tmp;
    tmp.values.reserve(512);

    for (auto it = dep_ids.begin(); it != dep_ids.end(); ++it)
    {
      NodeValue& v = nodes[*it].is_cand_related ? status.deep_values[k][*it] : status.deep_values[0][*it];
      tmp.push_back(v);
    }
    for (size_t i = 0; i < dep_ids.size(); ++i)
    {
      int32_t pre_id = dep_ids[i];
      NodeValue& pre_values = nodes[pre_id].is_cand_related ? status.deep_values[k][pre_id] : status.deep_values[0][pre_id];
      for (size_t j = i + 1; j < dep_ids.size(); ++j)
      {
        int32_t post_id = dep_ids[j];
        NodeValue& post_values = nodes[post_id].is_cand_related ? status.deep_values[k][post_id] : status.deep_values[0][post_id];
        VectorProduct(pre_values, post_values, tmp);
      }
    }
    status.deep_values[k][node_id] = std::move(tmp);
  }
}

void DeepLearning::Conn(const vector<PNNNode>& nodes, const PNNNode& node, Status& status)
{
  int32_t node_id = node.node_id;
  int32_t ac_size = node.is_cand_related ? status.ac_size : 1;
  const vector<int32_t>&dep_ids = node.dep_nodes;
  for (size_t i = 0; i < ac_size; ++i)
  {
    NodeValue tmp;
    for (auto it = dep_ids.begin(); it != dep_ids.end(); ++it)
    {
      const NodeValue& values = nodes[*it].is_cand_related ? status.deep_values[i][*it] : status.deep_values[0][*it];
      VectorConn(values, node.params.weights, tmp);
    }
    if (tmp.values.size() == node.params.bias.size())
    {
      const vector<float>& bias = node.params.bias;
      for (size_t i = 0; i < bias.size(); ++i)
      {
        tmp.values[i] += bias[i];
      }
    }
    status.deep_values[i][node_id] = std::move(tmp);
  }
}

void DeepLearning::Relu(const vector<PNNNode>& nodes, const PNNNode& node, Status& status)
{
  int32_t node_id = node.node_id;
  int32_t ac_size = node.is_cand_related ? status.ac_size : 1;
  const vector<int32_t>&dep_ids = node.dep_nodes;
  for (size_t i = 0; i < ac_size; ++i)
  {
    NodeValue tmp;
    for (auto it = dep_ids.begin(); it != dep_ids.end(); ++it)
    {
      const NodeValue& values = nodes[*it].is_cand_related ? status.deep_values[i][*it] : status.deep_values[0][*it];
      VectorRelu(values, tmp);
    }
    status.deep_values[i][node_id] = std::move(tmp);
  }
}

void DeepLearning::Norm(const vector<PNNNode>& nodes, const PNNNode& node, Status& status)
{
  int32_t feature_index = node.dep_feature_index;
  int32_t node_id = node.node_id;
  int32_t ac_size = node.is_cand_related ? status.ac_size : 1;
  const vector<int32_t>&dep_ids = node.dep_nodes;
  for (size_t i = 0; i < ac_size; ++i)
  {
    NodeValue tmp;
    for (auto it = dep_ids.begin(); it != dep_ids.end(); ++it)
    {
      const NodeValue& values = nodes[*it].is_cand_related ? status.deep_values[i][*it] : status.deep_values[0][*it];
      VectorNorm(values, tmp);
    }
    status.deep_values[i][node_id] = std::move(tmp);
  }
}

void DeepLearning::Final(const PNNNode& node, Status& status)
{
}

void LoadDeepLearningModel(const string& model_info, CtrModel& model)
{
  Document document;
  clock_t start = clock();
  document.Parse(model_info.c_str());
  if (!document.HasParseError())
  {
    cout<<"hello world\n";
    unordered_map<string, int32_t> lexicon;
    int32_t feature_index = 0;
    if (document.HasMember("exp_id"))
    {
      model.expid = document["exp_id"].GetInt();
    }
    if (document.HasMember("major_version"))
    {
      model.major_version = document["major_version"].GetInt();
    }
    if (document.HasMember("minor_version"))
    {
      model.minor_version = document["minor_version"].GetInt();
    }
    if (document.HasMember("model_tag"))
    {
      model.model_tag = document["model_tag"].GetString();
    }

    if (document.HasMember("entire_model"))
    {
      PNNModel& pnn_model = model.model;
      const Value& nodes = document["entire_model"];
      if (nodes.IsNull())
      {
        return;
      }
      for (SizeType i = 0; i < nodes.Size(); ++i)
      {
        PNNNode pnn_node;
        Params params;
        pnn_node.node_id = nodes[i]["id"].GetInt();
        if (!nodes[i]["op"].IsNull())
        {
          pnn_node.operation = nodes[i]["op"].GetString();
          pnn_node.opt = opt_map[pnn_node.operation];
        }
        if (!nodes[i]["candidate_related"].IsNull())
        {
          pnn_node.is_cand_related = nodes[i]["candidate_related"].GetBool();
        }
        if (!nodes[i]["dep_fea"].IsNull())
        {
          pnn_node.dep_feature = nodes[i]["dep_fea"].GetString();
          auto lexicon_it = lexicon.find(pnn_node.dep_feature);
          if (lexicon_it != lexicon.end())
          {
            pnn_node.dep_feature_index = lexicon_it->second;
          }
          else if (!pnn_node.dep_feature.empty())
          {
            lexicon[pnn_node.dep_feature] = feature_index;
            pnn_node.dep_feature_index = feature_index;
            ++feature_index;
          }
        }
        if (!nodes[i]["dep_ids"].IsNull())
        {
          pnn_node.dep_nodes = ConvertToIntVector(nodes[i]["dep_ids"]);
        }
        if (!nodes[i]["param"].IsNull())
        {
          const Value& param = nodes[i]["param"];
          params.size = param["size"].GetInt();
          if (param.HasMember("embedding_map"))
          {
            if (!param["embedding_map"].IsNull())
            {
              const Value& embedding_map = param["embedding_map"];
              for (auto mem_it = embedding_map.MemberBegin(); mem_it != embedding_map.MemberEnd(); ++mem_it)
              {
                int64_t key = stoll(mem_it->name.GetString());
                params.embedding_map[key] = ConvertToFloatVector(mem_it->value);
              }
            }
          }
          if (param.HasMember("weights"))
          {
            if (!param["weights"].IsNull())
            {
              vector<vector<float>> weights;
              const Value& matrix = param["weights"];
              for (SizeType k = 0; k < matrix.Size(); ++k)
              {
                const Value& list = matrix[k];
                weights.emplace_back(ConvertToFloatVector(list));
              }
              params.weights = MatrixTranspose(weights);
            }
          }
          if (param.HasMember("bias"))
          {
            if (!param["bias"].IsNull())
            {
              const Value& list = param["bias"];
              params.bias = ConvertToFloatVector(list);
            }
          }
        }
        pnn_node.params = std::move(params);
        pnn_model.nodes.emplace_back(std::move(pnn_node));
      }
    }
    double loadtime = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    cout <<"time : "<< loadtime <<"s"<<endl;
  }
}

void DumpParams(const Params& params)
{
  cout<<"size = "<<params.size<<endl;
//  for (auto it = params.embedding_map.begin(); it != params.embedding_map.end(); ++it)
//  {
//    int64_t key = it->first;
//    const vector<float>& values = it->second;
//    cout<<key<<" : ";
//    for (size_t i = 0; i < values.size(); ++i)
//    {
//      cout<<values[i]<<"\t";
//    }
//    cout<<endl;
//  }
//  const vector<vector<float>>& weights = params.weights;
//  for (size_t i = 0; i < weights.size(); ++i)
//  {
//    for (size_t j = 0; j < weights[i].size(); ++j)
//    {
//      cout<<weights[i][j]<<"\t";
//    }
//    cout<<"\n---------------------------------------------"<<endl;
//  }
}

void DumpPNNModel(const PNNModel& pnn_model)
{
  for (auto it = pnn_model.nodes.begin(); it != pnn_model.nodes.end(); ++it)
  {
    cout<<"==========================================\n";
    cout<<"node_id = "<<it->node_id<<endl;
    cout<<"operation = "<<it->operation<<endl;
    cout<<"opt = "<<it->opt<<endl;
    cout<<"candidate_related = "<<it->is_cand_related<<endl;
    cout<<"dep_feature = "<<it->dep_feature<<endl;
    cout<<"dep_feature_index = "<<it->dep_feature_index<<endl;
    cout<<"dep_node = ";
    for (size_t i = 0; i < it->dep_nodes.size(); ++i)
    {
      cout<<it->dep_nodes[i]<<"\t";
    }
    cout<<endl;
    DumpParams(it->params);
  }
}

void DumpModel(const CtrModel& model)
{
  cout<<"expid = "<<model.expid<<endl;
  cout<<"major_version = "<<model.major_version<<endl;
  cout<<"minor_version = "<<model.minor_version<<endl;
  cout<<"model_tag = "<<model.model_tag<<endl;
  DumpPNNModel(model.model);
}

int main()
{
  CtrModel model;
  ifstream file_obj("/mnt/hgfs/shared/pnn_model_1-24");
//  ifstream file_obj("test");
  if (!file_obj.is_open())
  {
    cout<<"file is not open\n";
    return -1;
  }
  stringstream buffer;
  buffer << file_obj.rdbuf();
  LoadDeepLearningModel(buffer.str(), model);
  DumpModel(model);

  PNNNode node0, node1, node2, node3, node4, node5, node6;
  node0.node_id = 0;
  node0.is_cand_related = true;
  node0.dep_feature_index = 0;
  node0.opt = NodeOpt::EMBEDDING;
  node0.params.embedding_map = {{1, {-1, 3, 5}}, {2, {2,-4, 6}}, {3, {2, 2, 2}}, {4, {3, 3, 3}}};

  node1.node_id = 1;
  node1.is_cand_related = false;
  node1.opt = NodeOpt::EMBEDDING;
  node1.dep_feature_index = 1;
  node1.params.embedding_map = {{3, {2, 2, 2}}};

  node2.node_id = 2;
  node2.is_cand_related = true;
  node2.opt = NodeOpt::GROUP;
  node2.dep_nodes = {0, 1};

  node3.node_id = 3;
  node3.is_cand_related = true;
  node3.opt = NodeOpt::PRODUCT;
  node3.dep_nodes = {0, 2};

  node4.node_id = 4;
  node4.is_cand_related = true;
  node4.opt = NodeOpt::FULL_CONNECT;
  node4.params.weights = {{1,2,1,2,1,2,1,2,1}, {2,2,2,2,2,2,2,2,2}};
  node4.params.bias = {-180, -350};
  node4.dep_nodes = {3};

  node5.node_id = 5;
  node5.is_cand_related = true;
  node5.opt = NodeOpt::RELU;
  node5.dep_nodes = {4};

  node6.node_id = 6;
  node6.is_cand_related = true;
  node6.opt = NodeOpt::L2_NORM;
  node6.dep_nodes = {5};

  vector<PNNNode> nodes = {node0, node1, node2, node3, node4, node5, node6};
  CtrModel ctr_model;
  ctr_model.model.nodes = nodes;

  Status status;
  status.ac_size = 2;
  FeatureValue cookie_value1, cookie_value2, city_value;
  cookie_value1.values = {1, 2};
  cookie_value2.values = {3, 4};
  city_value.values    = {3};
  InitStatus({{cookie_value1, cookie_value2}, {city_value}}, nodes, status);

//  DeepLearning::Embedding(nodes[0], status);
//  DeepLearning::Embedding(nodes[1], status);
//  DeepLearning::Group(nodes, nodes[2], status);
//  DeepLearning::Product(nodes, nodes[3], status);
//  DeepLearning::Conn(nodes, nodes[4], status);
//  DeepLearning::Relu(nodes, nodes[5], status);
//  DeepLearning::Norm(nodes, nodes[6], status);
  DeepLearning::PredictCtr(ctr_model, status);
  PrintStatus(status);

  return 0;
}

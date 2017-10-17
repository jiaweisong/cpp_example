#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <vector>
using namespace rapidjson;
using namespace std;
int main()
{
  //1,获取Document对象
  Document doc;
  doc.SetArray();        //数组型 相当与vector
  Document::AllocatorType &allocator=doc.GetAllocator(); //获取分配器

  //添加数组型数据
  vector<string> ips {"192.168.0.1", "192.168.0.2", "192.168.0.3"};
  vector<string> countrys {"china", "america", "english"};

  for(int i=0;i<3;i++)
  {
    Value obj(kObjectType);
    Value ip, country;
    ip.SetString(ips[i].c_str(), ips[i].length(), allocator);
    country.SetString(countrys[i].c_str(), countrys[i].length(), allocator);
    obj.AddMember("ip", ip, allocator);
    obj.AddMember("city", country, allocator);
    doc.PushBack(obj, allocator);
  }

  //3，将doc对象的值写入字符串
  StringBuffer buffer;
  //PrettyWriter<StringBuffer> writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
  Writer<StringBuffer> writer(buffer);
  doc.Accept(writer);

  cout<<buffer.GetString()<<endl;
}


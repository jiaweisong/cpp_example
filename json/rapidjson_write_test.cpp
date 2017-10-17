#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
using namespace rapidjson;
using namespace std;
int main()
{
  //1,获取Document对象
  Document doc;
  doc.SetObject();    //key-value 相当与map
  //doc.SetArray();        //数组型 相当与vector
  Document::AllocatorType &allocator=doc.GetAllocator(); //获取分配器

  //2，给doc对象赋值
  doc.AddMember("name","张山",allocator);

  //添加数组型数据
  Value array1(kArrayType);
  for(int i=0;i<3;i++)
  {
      Value int_object(kObjectType);
      int_object.SetInt(i);
      array1.PushBack(int_object,allocator);
  }

  doc.AddMember("number",array1,allocator);

  //3，将doc对象的值写入字符串
  StringBuffer buffer;
  //PrettyWriter<StringBuffer> writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json
  Writer<StringBuffer> writer(buffer);
  doc.Accept(writer);

  cout<<buffer.GetString()<<endl;
}

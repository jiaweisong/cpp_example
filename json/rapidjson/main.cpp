#include <stdio.h>
#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
using namespace std;
using namespace rapidjson;
int main(){
    /*
    生成如下格式的json，并输出字符串
    {
      "name":"chenzuhuang",
      "sites":["http://www.chenzuhuang.com","http://blog.chenzuhuang.com"]
    }
    */
    Document document;
    Document::AllocatorType& allocator = document.GetAllocator();
    //根
    Value root(kObjectType);
    //一个值，类型为string
    Value name(kStringType);
    //设置value的值
    name.SetString("chenzuhuang", allocator);
    //将值name放到root中，并用"name"作为key
    root.AddMember("name", name, allocator);
    //一个值，类型为数组
    Value sites(kArrayType);
    //往数组里放元素
    sites.PushBack("http://www.chenzuhuang.com", allocator).PushBack("http://blog.chenzuhuang.com", allocator);
    //将数组放到root中，并用"sites"作为key
    root.AddMember("sites", sites, allocator);
    //输出字符串
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);
    string reststring = buffer.GetString();
    cout << reststring << endl;
    system("pause");
    return 0;
}

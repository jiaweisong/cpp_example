#include <iostream>
#include <fstream>
#include <utility>
#include <string>

using namespace std;

int main()
{
  ifstream file_obj("log");
  if (file_obj.is_open())
  {
    while(!file_obj.eof())
    {
      string line;
      file_obj >> line;
      cout<<line<<endl;
    }
  }
  return 0;
}

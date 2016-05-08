#include <string>
#include <iostream>
#include <limits>
#include <exception>
using namespace std;
int main()
{
  try {
    // convert to numeric type
    std::cout << std::stoi ("  77") << std::endl;
    std::cout << std::stod ("  77.7") << std::endl;
    // convert numeric value to string
    long long ll = std::numeric_limits<long long>::max();
    std::string s = std::to_string(ll);  // converts maximum long long to string
    std::cout << s << std::endl;
    // try to convert back
    std::cout << std::stoi(s) << std::endl;  // throws out_of_range
    string value = "hello world" + std::to_string(100);
     std::cout<<value<<endl;
  }
  catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  cout<<"game over"<<endl;
}

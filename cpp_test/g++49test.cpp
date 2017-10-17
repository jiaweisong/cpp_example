#include <iostream>
int main(int argc, char* argv[]){ auto f = [](int n){ std::cout << "print "  << n <<  " by lambda" << std::endl;  }; f(10);  }
